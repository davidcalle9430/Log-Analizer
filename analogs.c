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
	Fecha �ltima modificaci�n: 
		marzo 21 de 2015
	*/

   int main(int argc, char *argv[])
   {   
		int resultado, opcion, resultado3[3];
		char basura;


		basura=' ';
		resultado=0;
		opcion=0;
		
		if (argc != 3) {
     		printf("Cantidad de argumentos incorrectos\n");
     		exit(1);
   		}else{
			while (opcion!=6){
				printf("1. N�mero de procesos que se ejecut� �nicamente en un procesador.\n ");
				printf("2. Numero de procesos que se ejecut� en 64 o m�s procesadores.\n");
				printf("3. Qu� proceso utiliz� m�s CPU (se debe imprimir el identificador del proceso y su uso de CPU y memoria)\n");
				printf("4. Cantidad de procesos Interactivos encontrados\n");
				printf("5. N�mero de procesos cuya ejecuci�n fue cancelada por el administrador\n");
				printf("6. Salir del sistema \n"); 
				
				scanf("%d",&opcion);
				printf("\e[1;1H\e[2J");
				
			
	   			if(opcion==1){
	   				resultado= NumeroProcesosUnProcesador(argv[1], atoi(argv[2]));
					printf("El numero  de procesos que se ejecut� �nicamente en un procesador es: %d\n", resultado);
				}else if(opcion==2){
					resultado= NumeroProcesosMasDe64(argv[1], atoi(argv[2]));
					printf("El numero de procesos que se ejecut� en 64 o m�s procesadores es: %d\n", resultado);
	        	}else if(opcion==3){
	        		ProcesoUtilizaMasCPU(argv[1], atoi(argv[2]), resultado3);
					printf("Proceso que utiliz� m�s CPU: %d  ;", resultado3[0] );
					printf("Tiempo de uso de CPU: %d  ;", resultado3[1]);
					printf("Memoria utilizada: %d\n", resultado3[2]);
					
	        	}else if(opcion==4){
	        		resultado = ProcesosInteractivos(argv[1], atoi(argv[2]));
					printf("La cantidad de procesos Interactivos es: %d\n", resultado);
	        	}else if(opcion==5){
	        		resultado = EjecucionCancelada(argv[1], atoi(argv[2]));
	        		printf("N�mero de procesos cuya ejecuci�n fue cancelada por el administrador es: %d\n", resultado);
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
