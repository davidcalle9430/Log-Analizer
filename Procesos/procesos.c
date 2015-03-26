/*
     Nombre Archivo:
      	analogpFunciones.c
     Realizado por:
      	Erika Jeniffer Harker
      	David Calle
     Objetivo:
      	Funciones utilizadas en el programa analogp, el cual analiza la informacion de un log por medio de procesos
     Fecha Última Modificación:
      	Marzo 21 de 2015
    */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "procesos.h"
/*
	Función: 
		leerArchivo
	Parámetros de Entrada: 
		archivo: nombre del archivo a buscar
		procesos: apuntador a la seccion de memoria asigmada a la memoria compartida
	Valor de Salida:
		No tiene una salida
	Descripción:
		carga la informacion del archivo a la memoria compartida
	*/
void leerArchivo(char* archivo, Proceso** procesos, int lineas){
    	int contador_lineas=0, contador, division, modulo;
 	int resultado=0;
 	size_t len = 0;
	ssize_t read;
 	char *line = NULL;
	char * lee;
	double datos[18];
 	FILE * fp;
	fp = fopen(archivo, "r");
	if (fp == NULL){
	    	printf("El archivo con el nombre especificado no existe\n");
    		exit(EXIT_FAILURE);
	}else{	

		while ( (read = getline(&line, &len, fp)) != -1 ) {       
			if( line[0]!=';'&&contador_lineas<lineas){
				division=(contador_lineas)/100;
				modulo=(contador_lineas)%100;
				lee=strtok(line, " \t" );
				contador=0;
				while(lee != NULL) { 
			   		datos[contador]=atof(lee); 
  					lee=strtok(NULL, " \t");
  					contador++;
				}
				//creo la estructura //1 6 7 5 15 11
				procesos[division][modulo].numero_tarea=datos[0];
				procesos[division][modulo].numero_procesadores=datos[4];
				procesos[division][modulo].tiempo_promedio_cpu=datos[5];
				procesos[division][modulo].memoria_usada=datos[6];
				procesos[division][modulo].status=datos[10];
				procesos[division][modulo].numero_cola=datos[14];
   		    		contador_lineas++;
			}      
		}
	}
	fclose(fp);
}
/*
	Función: 
		NumeroProcesosUnProcesador
	Parámetros de Entrada: 
		inicio: primera fila que analiza el proceso
		fin: ultima fila que analiza el proceso
		procesos: Memoria compartida del archivo
	Valor de Salida:
		Numero de procesos que utiliza un procesador en esa parte especifica de la memoria compartida
	Descripción:
		Cuenta de la memoria compartida en el campo de numero_procesadores valores iguales a 1
		esta funcion solo la realizan los procesos hijos
	*/
int NumeroProcesosUnProcesador( int inicio, int fin, Proceso** procesos){
     	int i, resultado, division, modulo;
     	resultado=0;
     	for( i=inicio ; i<fin ; i++ ){
		division=(i)/100;
		modulo=(i)%100;
     		if(procesos[division][modulo].numero_procesadores==1){
     			resultado++;
     		}
     	}
	return resultado;
		
}
/*
	Función: 
		NumeroProcesosMasDe64
	Parámetros de Entrada: 
		inicio: primera fila que analiza el proceso
		fin: ultima fila que analiza el proceso
		procesos: Memoria compartida del archivo
	Valor de Salida:
		Numero de procesos que utiliza 64 o más procesador en esa parte especifica de la memoria compartida
	Descripción:
		Cuenta de la memoria compartida en el campo de numero_procesadores valores iguales o mayores que 64
		esta funcion solo la realizan los procesos hijos
	*/
int NumeroProcesosMasDe64( int inicio, int fin, Proceso** procesos){
     	int i, resultado, division, modulo;
     	resultado=0;
     	for( i=inicio ; i<fin ; i++ ){
		division=(i)/100;
		modulo=(i)%100;
     		if(procesos[division][modulo].numero_procesadores >= 64){
     			resultado++;
     		}
     	}
	return resultado;
		
}
/*
	Función: 
		SumaDeRespuestas
	Parámetros de Entrada: 
		respuestas: memoria compartida donde se encuentran las respuestas de los procesos hijos
		cant_procesos: cantidad de procesos hijos
	Valor de Salida:
		Suma de las respuestas de los procesos hijos
	Descripción:
		suma las respuesta dque los procesos hijos han colocado en la memoria compartida
		Esta suma es valida para todas las opciones, ecepto la tercera opcion
		Esta funcion solo la realiza el proceso padre
	*/
int SumaDeRespuestas (float** respuestas, int cant_procesos){
	int resultado, i;
	resultado=0;
	for (i=0; i<cant_procesos; i++){
		resultado = resultado + respuestas[i][0];
	}

	return resultado;

}
/*
	Función: 
		ProcesoUtilizaMasCPU
	Parámetros de Entrada: 
		inicio: primera fila que analiza el proceso
		fin: ultima fila que analiza el proceso
		procesos: Memoria compartida del archivo
		respuestas: vector donde se guardaran las 3 respuestas que da la funcion
	Valor de Salida:
		vector de respuestas modificado con el proceso que tuvo mayor tiempo, su numero de proceso y memoria utilizada
	Descripción:
		Busca en la memoria compartida en el campo de tiempo_promedio_cpu el valor mas alto, 
		en base a este guarda el numero del proceso, la memoria utilizada y el tiempo promedio de cpu en el vector de respuestas
		esta funcion solo la realizan los procesos hijos
	*/
void ProcesoUtilizaMasCPU( int inicio, int fin, Proceso** procesos, float respuestas[]){
     	int i, numero_tarea, memoria_usada;
	int division, modulo;
	float mayor_tiempo;
	mayor_tiempo=0;
     	for( i=inicio ; i<fin ; i++ ){
		division=(i)/100;
		modulo=(i)%100;
     		if(procesos[division][modulo].tiempo_promedio_cpu > mayor_tiempo){
     			mayor_tiempo = procesos[division][modulo].tiempo_promedio_cpu;
			numero_tarea = procesos[division][modulo].numero_tarea;
			memoria_usada = procesos[division][modulo].memoria_usada;
     		}
     	}
	respuestas[0] = mayor_tiempo;
	respuestas[1] = numero_tarea;
	respuestas[2] = memoria_usada;	
}
/*
	Función: 
		MayorTiempo
	Parámetros de Entrada: 
		respuestas: memoria compartida donde se encuentran las respuestas de los procesos hijos
		respuestas_finales: guarda las respuestas de todo el analisis del log
		cant_procesos: cantidad de procesos hijos
		cant_respuestas: cantidad de respuestas en el vector de respuestas (3)
	Valor de Salida:
		vector de respuestas modificado con el proceso que tuvo mayor tiempo, su numero de proceso y memoria utilizada
	Descripción:
		compara las respuesta que los procesos hijos han colocado en la memoria compartida Buscando el valor mas alto de tiempo promedio de cpu, 
		en base a este guarda el numero del proceso, la memoria utilizada y el tiempo promedio de cpu en el vector de respuestas
		Esta funcion solo la realiza el proceso padre
	*/
void MayorTiempo (float** respuestas, float respuestas_finales[], int cant_procesos, int cant_respuestas){
	int i, j;
	float mayor_tiempo;
	mayor_tiempo=0;
	for (i = 0; i < cant_procesos; i++){
		if (respuestas[i][1]>mayor_tiempo){
			for (j=0; j <  cant_respuestas; j++){
				respuestas_finales[j] = respuestas[i][j];
			}
		}
	}
}
/*
	Función: 
		ProcesosInteractivos
	Parámetros de Entrada: 
		inicio: primera fila que analiza el proceso
		fin: ultima fila que analiza el proceso
		procesos: Memoria compartida del archivo
	Valor de Salida:
		Numero de procesos que son procesos interactivos en esa parte especifica de la memoria compartida
	Descripción:
		Cuenta de la memoria compartida en el campo de numero_cola valores iguales a 0
		esta funcion solo la realizan los procesos hijos
	*/
int ProcesosInteractivos( int inicio, int fin, Proceso** procesos){
	int i, resultado, division, modulo;
     	resultado=0;
     	for( i=inicio ; i<fin ; i++ ){
		division=(i)/100;
		modulo=(i)%100;
     		if(procesos[division][modulo].numero_cola==0){
     			resultado++;
     		}
     	}
	return resultado;
		
}
/*
	Función: 
		EjecucionCancelada
	Parámetros de Entrada: 
		inicio: primera fila que analiza el proceso
		fin: ultima fila que analiza el proceso
		procesos: Memoria compartida del archivo
	Valor de Salida:
		Numero de procesos cuya ejecución fue cancelada por el administrador en esa parte especifica de la memoria compartida
	Descripción:
		Cuenta de la memoria compartida en el campo de status valores iguales a 5
		esta funcion solo la realizan los procesos hijos
	*/
int EjecucionCancelada( int inicio, int fin, Proceso** procesos){
	int i, resultado, division, modulo;
     	resultado=0;
     	for( i=inicio ; i<fin ; i++ ){
		division=(i)/100;
		modulo=(i)%100;
     		if(procesos[division][modulo].status==5){
     			resultado++;
     		}
     	}
	return resultado;
		
}
