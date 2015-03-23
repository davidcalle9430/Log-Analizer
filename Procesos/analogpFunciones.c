#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leerArchivo(char* archivo, Proceso* procesos){
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
			if( line[0]!=';'&&contador_lineas<100){

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
//---------------------------------------------------------------------------
int NumeroProcesosUnProcesador( int inicio, int fin, Proceso* procesos){
     	int i, resultado;
     	resultado=0;
     	for( i=inicio ; i<fin ; i++ ){
     		if(procesos[i].numero_procesadores==1){
     			resultado++;
     		}
     	}
	return resultado;
		
}
//---------------------------------------------------------------------------
int NumeroProcesosMasDe64( int inicio, int fin, Proceso* procesos){
	int i, resultado;
     	resultado=0;
     	for( i=inicio ; i<fin ; i++ ){
     		if(procesos[i].numero_procesadores>=64){
     			resultado++;
     		}
     	}
	return resultado;
		
}
//---------------------------------------------------------------------------
int SumaDeRespuestas (float* respuestas, int cant_procesos){
	int resultado, i;
	resultado=0;
	for (i=0; i<cant_procesos; i++){
		resultado = resultado + respuestas[i];
	}
	return resultado;

}
//---------------------------------------------------------------------------
void ProcesoUtilizaMasCPU( int inicio, int fin, Proceso* procesos, float respuestas[]){
     	int i, numero_tarea, memoria_usada;
	float mayor_tiempo;
	mayor_tiempo=0;
     	for( i=inicio ; i<fin ; i++ ){
     		if(procesos[i].tiempo_promedio_cpu > mayor_tiempo){
     			mayor_tiempo = procesos[i].tiempo_promedio_cpu;
			numero_tarea = procesos[i].numero_tarea;
			memoria_usada = procesos[i].memoria_usada;
     		}
     	}
	respuestas[0] = mayor_tiempo;
	respuestas[1] = numero_tarea;
	respuestas[2] = memoria_usada;	
}
//---------------------------------------------------------------------------
void MayorTiempo (float* respuestas, float respuestas_finales[], int cant_procesos, int cant_respuestas){
	int i, j;
	float mayor_tiempo;
	mayor_tiempo=0;
	for (i = 0; i < cant_procesos; i++){
		if (respuestas[i*cant_respuestas]>mayor_tiempo){
			for (j=0; j <  cant_respuestas; j++){
				respuestas_finales[j] = respuestas[i*cant_respuestas+j];
			}
		}
	}
}
//---------------------------------------------------------------------------
int ProcesosInteractivos( int inicio, int fin, Proceso* procesos){
	int i, resultado;
     	resultado=0;
     	for( i=inicio ; i<fin ; i++ ){
     		if(procesos[i].numero_cola==0){
     			resultado++;
     		}
     	}
	return resultado;
		
}
//---------------------------------------------------------------------------
int EjecucionCancelada( int inicio, int fin, Proceso* procesos){
	int i, resultado;
     	resultado=0;
     	for( i=inicio ; i<fin ; i++ ){
     		if(procesos[i].status==5){
     			resultado++;
     		}
     	}
	return resultado;
		
}
