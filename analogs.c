    /*
      nombre archivo:
      	analogs.c
      Realizado por:
      	Erika Jeniffer Harker
      	David Calle
      Objetivo:
      	Analizar la información de un log de manera secuencial
      Fecha Última Modificación:
      	Marzo 21 de 2015

    */	
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	int mayor_tiempo=0;
	int num_proceso;
	int num_memoria;
	int OpcionesProcesador (int numero, int opcion){
		if(opcion==1){
			if (numero==1){
				return 1;
			}
        } else if(opcion==2){
			if (numero>=64){
				return 1;
			}
        }else if(opcion==4){
			if (numero==0){
				return 1;
			}
        }else if(opcion==5){
			if (numero==5){
				return 1;
			}
		}
		return 0;
	}
	void TiempoMayor (double proceso, double tiempo, double memoria){
		if (mayor_tiempo < tiempo){
			mayor_tiempo=tiempo;
			num_proceso=proceso;
			num_memoria=memoria;
		}		
	}

   int numeroProcesosUnProcesador(char *nombre_archivo, int opcion, int total_lineas){
		FILE * fp;
     	char * line = NULL;
     	size_t len = 0;
     	ssize_t read;
     	int numero, contador, contador_lineas;
     	contador_lineas=0;
     	int resultado=0;
    	fp = fopen(nombre_archivo, "r");
    	double datos[18];

   		if (fp == NULL){
           exit(EXIT_FAILURE);
   		}
   		int i;	
  		while ( (read = getline(&line, &len, fp)) != -1 ) {        
   			if( line[0]!=';'&&contador_lineas<total_lineas){
       				char *lee;
       				lee=strtok(line, " \t" );
       				contador=0;
       				while(lee != NULL) { 
					   	datos[contador]=atof(lee); 
          				lee=strtok(NULL, " \t");
          				contador++;
      				}
      				if (opcion==3){
          				TiempoMayor (datos[0], datos[5], datos[6]);
						resultado=-3;		
          			}else if (opcion==4){
						resultado= resultado+OpcionesProcesador(datos[14], opcion);
					}else if (opcion==5){
						resultado= resultado+OpcionesProcesador(datos[10], opcion);
					}else{
          				resultado= resultado+OpcionesProcesador(datos[4], opcion);
           			}
           		    contador_lineas++;
        	}      
      	}
		fclose(fp);
		return resultado;
	}
	
   int main(int argc, char *argv[])
   {   
		int resultado =0;
		int opcion=0;
		char basura=' ';

		if (argc != 3) {
     		printf("Usage hilos [1/2]\n");
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
			if (opcion>=1&&opcion<=5){
   				resultado= numeroProcesosUnProcesador(argv[1], opcion, atoi(argv[2]));
   			}
   			if(opcion==1){
				printf("El numero  de procesos que se ejecutó únicamente en un procesador es: %d\n", resultado);
			}else if(opcion==2){
				printf("El numero de procesos que se ejecutó en 64 o más procesadores es: %d\n", resultado);
        	}else if(opcion==3){
				printf("Proceso que utilizó más CPU: %d  ;",  num_proceso);
				printf("Tiempo de uso de CPU: %d  ;", mayor_tiempo);
				printf("Memoria utilizada: %d\n", num_memoria);
				mayor_tiempo=0;
        	}else if(opcion==4){
				printf("La cantidad de procesos Interactivos es: %d\n", resultado);
        	}else if(opcion==5){
        		printf("Número de procesos cuya ejecución fue cancelada por el administrador es: %d\n", resultado);
			}
			//cin
			if(opcion!=6){
			printf("Oprima cualquier tecla para continuar \n" );
            scanf("%c",&basura);
            scanf("%c",&basura);
		    printf("\e[1;1H\e[2J");	
		    }

   			}
		} 
   }
