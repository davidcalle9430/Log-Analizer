    /*
     Nombre Archivo:
      	secuencial.c
     Realizado por:
      	Erika Jeniffer Harker
      	David Calle
     Objetivo:
      	Analizar la información de un log de manera secuencial
     Fecha Última Modificación:
      	Marzo 21 de 2015
    */	
#include <stdio.h> //librerías de C
#include <stdlib.h>
#include <string.h>
#include "secuencial.h" // Archivo de cabecera con la definción de las funciones
void leerArchivo (char* archivo, Proceso* procesos, int total_lineas){
	int contador_lineas=0, contador;
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
			if( line[0]!=';'&&contador_lineas<total_lineas){

				lee=strtok(line, " \t" );
				contador=0;
				while(lee != NULL) { 
			   		datos[contador]=atof(lee); 
  					lee=strtok(NULL, " \t");
  					contador++;
				}
				//creo la estructura //1 6 7 5 15 11
				procesos[contador_lineas].numero_tarea=datos[0];
				procesos[contador_lineas].numero_procesadores=datos[4];
				procesos[contador_lineas].tiempo_promedio_cpu=datos[5];
				procesos[contador_lineas].memoria_usada=datos[6];
				procesos[contador_lineas].status=datos[10];
				procesos[contador_lineas].numero_cola=datos[14];

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
		Cadena con el nombre del archivo a buscar, representa el log
	Valor de Salida:
		Entero que representa el número de procesos que usaron un procesador
	Descripción:
		Cuenta el número de procesos que solo usaron un procesador en el log
	*/

int NumeroProcesosUnProcesador(Proceso* procesos, int total_lineas){
	int resultado, i;
	resultado=0;
	for(i=0; i<total_lineas; i++){
		if(procesos[i].numero_procesadores==1){
			resultado++;
		}
	}

	return resultado;
}

	/*
	Función:
		NumeroProcesosMasDe64
	Parámetros de Entrada: 
		Cadena con el nombre del archivo a buscar, representa el log
	Valor de Salida:
		Entero que representa el número de procesos que usaron 64 o más procesadores
	Descripción:
		Cuenta el número de procesos que usaron 64 procesadores
	*/	
int NumeroProcesosMasDe64(Proceso* procesos, int total_lineas){
	int resultado, i;
	resultado=0;
	for(i=0; i<total_lineas; i++){
		if(procesos[i].numero_procesadores>=64){
			resultado++;
		}
	}

	return resultado;
}
/*
	Función: ProcesoUtilizaMasCPU
	Parámetros de Entrada: 
		Cadena con el nombre del archivo a buscar, representa el log
	Valor de Salida:
		Entero que representa el proceso que utilizó más CPU
	Descripción:
		Cuenta el número de procesos que usaron 64 procesadores
	*/	

void ProcesoUtilizaMasCPU(Proceso* procesos, int total_lineas, float resultado[3]){
	int i, tiempo_mayor;
	tiempo_mayor=0;
	for(i=0; i<total_lineas; i++){
		if(procesos[i].tiempo_promedio_cpu>tiempo_mayor){
			tiempo_mayor=procesos[i].tiempo_promedio_cpu;
			resultado[0]= procesos[i].numero_tarea;
			resultado[1]= procesos[i].tiempo_promedio_cpu;
			resultado[2]= procesos[i].memoria_usada;
		}
	}     

}
	
   /*
		Función: 
			ProcesosInteractivos
		Parámetros de entrada: 
			Nombre del archivo del log, y el total de lineas a analizar
		Valor de salida: 
			cantidad de Procesos Interactivos
		Descripción: 
			Cuenta directamente del archivo los procesos que son interactivos
	*/
int ProcesosInteractivos (Proceso* procesos, int total_lineas){

	int resultado, i;
	resultado=0;
	for(i=0; i<total_lineas; i++){
		if(procesos[i].numero_cola==0){
			resultado++;
		}
	}

	return resultado;
}
/*
	Función: 
		EjecucionCancelada
	Parámetros de entrada: 
		Nombre del archivo del log, y el total de lineas a analizar
	Valor de salida: 
		cantidad de Procesos cancelados por el administrador
	Descripción: 
		Cuenta directamente del archivo los procesos que fueron cancelados por el administrador
	*/
int EjecucionCancelada (Proceso* procesos, int total_lineas){
	int resultado, i;
	resultado=0;
	for(i=0; i<total_lineas; i++){
		if(procesos[i].status==5){
			resultado++;
		}
	}

	return resultado;
}
