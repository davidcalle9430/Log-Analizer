    /*
     Nombre Archivo:
      	secuencial.c
     Realizado por:
      	Erika Jeniffer Harker
      	David Calle
     Objetivo:
      	Analizar la informaci�n de un log de manera secuencial
     Fecha �ltima Modificaci�n:
      	Marzo 21 de 2015
    */	
	#include <stdio.h> //librer�as de C
	#include <stdlib.h>
	#include <string.h>
	#include "secuencial.h" // Archivo de cabecera con la definci�n de las funciones
	/*
	Funci�n: 
		NumeroProcesosUnProcesador
	Par�metros de Entrada: 
		Cadena con el nombre del archivo a buscar, representa el log
	Valor de Salida:
		Entero que representa el n�mero de procesos que usaron un procesador
	Descripci�n:
		Cuenta el n�mero de procesos que solo usaron un procesador en el log
	*/
	int NumeroProcesosUnProcesador(char* nombre_archivo, int total_lineas){
		FILE * fp;
     	char *line, *lee;
     	size_t len;
     	ssize_t read;
     	int numero, contador, contador_lineas, resultado,i;
     	double datos[18];
     	

     	contador_lineas=0;
     	resultado=0;
     	len = 0;
     	line = NULL;
    	fp = fopen(nombre_archivo, "r");
    	

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
      			    if(datos[4]==1){
          				resultado++;
          			}
           		    contador_lineas++;
        		}      
      		}	
        }
		fclose(fp);
		return resultado;
	}

	/*
	Funci�n:
		NumeroProcesosMasDe64
	Par�metros de Entrada: 
		Cadena con el nombre del archivo a buscar, representa el log
	Valor de Salida:
		Entero que representa el n�mero de procesos que usaron 64 o m�s procesadores
	Descripci�n:
		Cuenta el n�mero de procesos que usaron 64 procesadores
	*/	
    int NumeroProcesosMasDe64(char* nombre_archivo, int total_lineas){
		FILE * fp;
     	char *line,*lee;
     	size_t len;
     	ssize_t read;
     	int numero, contador, contador_lineas, resultado,i;
     	double datos[18];


     	contador_lineas=0;
     	resultado=0;
     	len = 0;
     	line = NULL;
    	fp = fopen(nombre_archivo, "r");
    	

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
      			    if(datos[4]>=64){
          				resultado++;
          			}
           		    contador_lineas++;
        		}      
      		}
      	}
		fclose(fp);
		return resultado;
	}






	/*
	Funci�n: ProcesoUtilizaMasCPU
	Par�metros de Entrada: 
		Cadena con el nombre del archivo a buscar, representa el log
	Valor de Salida:
		Entero que representa el proceso que utiliz� m�s CPU
	Descripci�n:
		Cuenta el n�mero de procesos que usaron 64 procesadores
	*/	


    void ProcesoUtilizaMasCPU(char *nombre_archivo,  int total_lineas, int resultado[3]){
		FILE * fp;
     	char * line, *lee;
     	ssize_t read;
     	double datos[18], tiempo_mayor;
     	int numero, contador, contador_lineas,i;
     	

     	line = NULL;
     	size_t len = 0;
     	contador_lineas=0;
     	tiempo_mayor=0.0;


    	fp = fopen(nombre_archivo, "r");
   		if (fp == NULL){
           exit(EXIT_FAILURE);
   		}	
  		while ( (read = getline(&line, &len, fp)) != -1 ) {        
   			if( line[0]!=';'&&contador_lineas<total_lineas){
       				lee=strtok(line, " \t" );
       				contador=0;
       				while(lee != NULL) { 
					   	datos[contador]=atof(lee); 
          				lee=strtok(NULL, " \t");
          				contador++;
      				}
      				//TiempoMayor (datos[0], datos[5], datos[6]);
      				if(datos[5]>tiempo_mayor){
      					tiempo_mayor=datos[5];
      					resultado[0]=datos[0];
      					resultado[1]=datos[5];
      					resultado[2]=datos[6];
      				}
           		    contador_lineas++;
        	}      
      	}
		fclose(fp);
	}
	
   /*
		Funci�n: 
			ProcesosInteractivos
		Par�metros de entrada: 
			Nombre del archivo del log, y el total de lineas a analizar
		Valor de salida: 
			cantidad de Procesos Interactivos
		Descripci�n: 
			Cuenta directamente del archivo los procesos que son interactivos
	*/
	int ProcesosInteractivos (char *nombre_archivo, int total_lineas){
		FILE * fp;
     	char * line;
     	char *lee;
     	size_t len;
     	ssize_t read;
     	int numero, columna, contador_lineas, i, resultado;
		resultado=0;
		len = 0;
		line=NULL;
    	fp = fopen(nombre_archivo, "r");
   		if (fp == NULL){
           exit(EXIT_FAILURE);
   		}	

   		contador_lineas=0;

  		while ( (read = getline(&line, &len, fp)) != -1 ) {        
   			if( line[0]!=';'&&contador_lineas<total_lineas){	
       				lee=strtok(line, " \t" );
       				columna=1;
       				while(lee != NULL) { 
          				if (columna==15&&strcmp(lee, "0")==0){
							resultado++;
						}
						lee=strtok(NULL, " \t");
          				columna++;
      				}
      				contador_lineas++;
        	}      
      	}
		fclose(fp);
		return resultado;
	}
	/*
		Funci�n: 
			EjecucionCancelada
		Par�metros de entrada: 
			Nombre del archivo del log, y el total de lineas a analizar
		Valor de salida: 
			cantidad de Procesos cancelados por el administrador
		Descripci�n: 
			Cuenta directamente del archivo los procesos que fueron cancelados por el administrador
	*/
	int EjecucionCancelada (char *nombre_archivo, int total_lineas){
		FILE * fp;
     	char * line;
     	char *lee;
     	size_t len;
     	ssize_t read;
     	int numero, columna, contador_lineas, i, resultado;
		resultado=0;
		len = 0;
		line=NULL;
    	fp = fopen(nombre_archivo, "r");
   		if (fp == NULL){
           exit(EXIT_FAILURE);
   		}	

   		contador_lineas=0;

  		while ( (read = getline(&line, &len, fp)) != -1 ) {        
   			if( line[0]!=';'&&contador_lineas<total_lineas){	
       				lee=strtok(line, " \t" );
       				columna=1;
       				while(lee != NULL) { 
          				if (columna==11&&strcmp(lee, "5")==0){
							resultado++;
						}
						lee=strtok(NULL, " \t");
          				columna++;
      				}
      				contador_lineas++;
        	}      
      	}
		fclose(fp);
		return resultado;
	}
