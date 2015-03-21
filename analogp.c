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
     	

        //////////////////////////////////////////////////////////7
 		

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



        //////////////////////////////////////////////////////////////
		basura=' ';
		resultado=0;
		opcion=0;
		
		if (argc != 3) {
     		printf("Cantidad de argumentos incorrectos\n");
     		exit(1);
   		}else{
			while (opcion!=6){
				printf("1. Número de procesos que se ejecutó únicamente en un procesador.\n ");
				printf("2. Numero de procesos que se ejecutó en 64 o más procesadores.\n");
				printf("3. Qué proceso utilizó más CPU (se debe imprimir el identificador del proceso y su uso de CPU y memoria)\n");
				printf("4. Cantidad de procesos Interactivos encontrados\n");
				printf("5. Número de procesos cuya ejecución fue cancelada por el administrador\n");
				printf("6. Salir del sistema \n"); 
				
				scanf("%d",&opcion);
				printf("\e[1;1H\e[2J");
				
			
	   			if(opcion==1){
	   				resultado= NumeroProcesosUnProcesador(argv[1], atoi(argv[2]));
					printf("El numero  de procesos que se ejecutó únicamente en un procesador es: %d\n", resultado);
				}else if(opcion==2){
					resultado= NumeroProcesosMasDe64(argv[1], atoi(argv[2]));
					printf("El numero de procesos que se ejecutó en 64 o más procesadores es: %d\n", resultado);
	        	}else if(opcion==3){
	        		ProcesoUtilizaMasCPU(argv[1], atoi(argv[2]), resultado3);
					printf("Proceso que utilizó más CPU: %d  ;", resultado3[0] );
					printf("Tiempo de uso de CPU: %d  ;", resultado3[1]);
					printf("Memoria utilizada: %d\n", resultado3[2]);
					
	        	}else if(opcion==4){
	        		resultado = ProcesosInteractivos(argv[1], atoi(argv[2]));
					printf("La cantidad de procesos Interactivos es: %d\n", resultado);
	        	}else if(opcion==5){
	        		resultado = EjecucionCancelada(argv[1], atoi(argv[2]));
	        		printf("Número de procesos cuya ejecución fue cancelada por el administrador es: %d\n", resultado);
				}
				
				if(opcion!=6){
					printf("Oprima cualquier tecla para continuar \n" );
	            	scanf("%c",&basura);
	            	scanf("%c",&basura);
			    	printf("\e[1;1H\e[2J");	
			    }
	
	   		}
		} 
   }
