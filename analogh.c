 	#include <stdlib.h>
	#include <string.h>
	#include "secuencial.h"
	/*
	Archivo: 
		analogs.c
	Realizado por: 
		Erika Jeniffer Harker
		David Calle
	Contiene: 
		archivo para probar las las funciones definidas anteriormente.
	Fecha última modificación: 
		marzo 21 de 2015
	*/

 int main(int argc, char *argv[])
 { 
        
 			int resultado, opcion, resultado3[3],numero, contador, contador_lineas,i;
		FILE * fp;
     	char *line, *lee, basura;
     	size_t len;
     	ssize_t read;
     	double datos[argv[2]][18];

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
					   	datos[contador_lineas][contador]=atof(lee); 
          				lee=strtok(NULL, " \t");
          				contador++;
      				}
           		    contador_lineas++;
        		}      
      		}	
        }
		fclose(fp);
  
 }