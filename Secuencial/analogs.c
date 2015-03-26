	#include <stdio.h>
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
	int resultado, opcion, total_lineas;
	float resultado3[3];
	char basura;
	Proceso* memoria;

	basura=' ';
	resultado=0;
	opcion=0;
	
	if (argc != 3) {
		printf("Cantidad de argumentos incorrectos\n");
     		exit(1);
   	}else{
		total_lineas=atoi(argv[2]);
		memoria= malloc (sizeof (Proceso)*total_lineas);
		leerArchivo (argv[1], memoria, total_lineas);
		while (opcion!=6){
			printf("1. Número de procesos que se ejecutó únicamente en un procesador.\n ");
			printf("2. Numero de procesos que se ejecutó en 64 o más procesadores.\n");
			printf("3. Qué proceso utilizó más CPU (se debe imprimir el identificador del proceso y su uso de CPU y memoria)\n");
			printf("4. Cantidad de procesos Interactivos encontrados\n");
			printf("5. Número de procesos cuya ejecución fue cancelada por el administrador\n");
			printf("6. Salir del sistema \n"); 
			
			scanf("%d",&opcion);
			printf("\e[1;1H\e[2J");
			
			struct timeval start, end;
  			gettimeofday(&start, NULL);
		
	  		if(opcion==1){
	   			resultado= NumeroProcesosUnProcesador(memoria, total_lineas);
				printf("El numero  de procesos que se ejecutó únicamente en un procesador es: %d\n", resultado);
			}else if(opcion==2){
				resultado= NumeroProcesosMasDe64(memoria, total_lineas);
				printf("El numero de procesos que se ejecutó en 64 o más procesadores es: %d\n", resultado);
	        	}else if(opcion==3){
	        		ProcesoUtilizaMasCPU(memoria, total_lineas, resultado3);
				printf("Proceso que utilizó más CPU: %f  ;", resultado3[0] );
				printf("Tiempo de uso de CPU: %f  ;", resultado3[1]);
				printf("Memoria utilizada: %f\n", resultado3[2]);	
	        	}else if(opcion==4){
	        		resultado = ProcesosInteractivos(memoria, total_lineas);
				printf("La cantidad de procesos Interactivos es: %d\n", resultado);
	        	}else if(opcion==5){
	        		resultado = EjecucionCancelada(memoria, total_lineas);
	        		printf("Número de procesos cuya ejecución fue cancelada por el administrador es: %d\n", resultado);
			}
			if(opcion!=6){
				gettimeofday(&end, NULL);
  				printf("%ld\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));

				printf("Oprima cualquier tecla para continuar \n" );
	            		scanf("%c",&basura);
	            		scanf("%c",&basura);
			    	printf("\e[1;1H\e[2J");	
			}
	
	   	}
	} 
   }
