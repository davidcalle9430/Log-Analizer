#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
#include <signal.h>
#include "analogpFunciones.h"
	
#define SHMSZ 27
#define MAX  50
#define SMES 30
#define CANT_RESPUESTAS 3
#define CANT_RESP_TIEMPO 3


int main(int argc, char *argv[]){

    	int shmid,shmid2;
    	key_t key,key2;
    	char *shm,*shm2;
	char basura;
    	int   i,j;
	float *respuesta;
    	Proceso *procesos;
	int cantidad_hijos, division, modulo;
	int child_pid;
 	int numero, contador, cant_lineas, opcion;
	float respuestas_tiempo[CANT_RESP_TIEMPO], resultado;
 	

	if (argc != 4) {
     		printf("Cantidad de argumentos incorrectos\n");
     		exit(1);
   	}else if(atoi(argv[2])<=0||atoi(argv[3])<=0){
		printf("Tamano de archivo o  cantidad de procesos incorrecto\n");
     		exit(1);
	}
	else{
		basura=' ';
		cant_lineas = atoi(argv[2]);
		cantidad_hijos = atoi(argv[3]);		
		/*
     		* Crear el segmento de memoria compartida
     		*/
   		if ((shmid = shmget(key, sizeof(Proceso)*cant_lineas, IPC_CREAT | 0666)) < 0) {
        		perror("shmget");
        		exit(1);
    		}

     		/*
     		* Anexar (attach)  el segmento al espacio de direcciones del proceso 
     		*/
    		if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        		perror("shmat");
        		exit(1);
    		}
    		procesos = (Proceso*)shm;
   		// memoria compartida respuesta

		if ((shmid2 = shmget(key2, sizeof(float)*cantidad_hijos*CANT_RESPUESTAS, IPC_CREAT | 0666)) < 0) {
        		perror("shmget");
        		exit(1);
    		}

     		/*
     		* Anexar (attach)  el segmento al espacio de direcciones del proceso 
     		*/
    		if ((shm2 = shmat(shmid2, NULL, 0)) == (char *) -1) {
        		perror("shmat");
        		exit(1);
    		}
    		respuesta= (float*) shm2;
    
    		//cargar todo al vector de procesos
		leerArchivo(argv[1], procesos);
		//creo los hijos y se les asigno

		division = cant_lineas/cantidad_hijos;
		modulo = cant_lineas%cantidad_hijos;
		opcion = 0;
		while (opcion!=6){
				printf("1. Numero de procesos que se ejecutó únicamente en un procesador.\n ");
				printf("2. Numero de procesos que se ejecutó en 64 o más procesadores.\n");
				printf("3. Que proceso utilizo más CPU\n");
				printf("4. Cantidad de procesos Interactivos encontrados\n");
				printf("5. Numero de procesos cuya ejecución fue cancelada por el administrador\n");
				printf("6. Salir del sistema \n"); 
				
				scanf("%d",&opcion);
				printf("\e[1;1H\e[2J");
				
			for (i = 0; i < cantidad_hijos; i++){   
				if((child_pid=fork())<0){
 	    				perror("fork: \n");
				}
				if(child_pid==0){
					if(opcion==1){
	   					if(i < (cantidad_hijos-1)){
							respuesta[i]=NumeroProcesosUnProcesador(i*division, (i+1)*division, procesos);
						}else{
							respuesta[i]=NumeroProcesosUnProcesador(i*division, ((i+1)*division)+modulo, procesos);
						}
						exit(0);
					}else if(opcion==2){
						if(i < (cantidad_hijos-1)){
							respuesta[i]=NumeroProcesosMasDe64(i*division, (i+1)*division, procesos);
						}else{
							respuesta[i]=NumeroProcesosMasDe64(i*division, ((i+1)*division)+modulo, procesos);
						}
						exit(0);
	        			}else if(opcion==3){
	        				if(i < (cantidad_hijos-1)){
							ProcesoUtilizaMasCPU(i*division, (i+1)*division, procesos, respuestas_tiempo);
							for (j = 0; j < CANT_RESP_TIEMPO; j++){
								respuesta[i*CANT_RESP_TIEMPO+j] = respuestas_tiempo[j];
							}
						}else{
							ProcesoUtilizaMasCPU(i*division, ((i+1)*division)+modulo, procesos, respuestas_tiempo);
							for (j = 0; j < CANT_RESP_TIEMPO; j++){
								respuesta[i+j] = respuestas_tiempo[j];
							}
							printf("TCPU %f NT %f MU %f\n", respuestas_tiempo[0], respuestas_tiempo[1], respuestas_tiempo[2] );
						}
						exit(0);
					}else if(opcion==4){
	        				if(i < (cantidad_hijos-1)){
							respuesta[i]=ProcesosInteractivos(i*division, (i+1)*division, procesos);
						}else{
							respuesta[i]=ProcesosInteractivos(i*division, ((i+1)*division)+modulo, procesos);
						}
						exit(0);
	        			}else if(opcion==5){
	        				if(i < (cantidad_hijos-1)){
							respuesta[i]=EjecucionCancelada(i*division, (i+1)*division, procesos);
						}else{
							respuesta[i]=EjecucionCancelada(i*division, ((i+1)*division)+modulo, procesos);
						}
						exit(0);
					}
			    	}
			}
    			for (i = 0; i < cantidad_hijos; i++){   
				int status;
				wait(&status);
			}
			if(opcion==1){
				resultado=SumaDeRespuestas(respuesta,cantidad_hijos);
				printf("El numero  de procesos que se ejecutó únicamente en un procesador es: %f\n", resultado);
			}else if(opcion==2){
				resultado=SumaDeRespuestas(respuesta,cantidad_hijos);
				printf("El numero de procesos que se ejecutó en 64 o más procesadores es: %f\n", resultado);
	        	}else if(opcion==3){
				MayorTiempo (respuesta, respuestas_tiempo, cantidad_hijos, CANT_RESP_TIEMPO);
				printf("Proceso que utilizó más CPU: %f  ;", respuestas_tiempo[1] );
				printf("Tiempo de uso de CPU: %f  ;", respuestas_tiempo[0] );
				printf("Memoria utilizada: %f\n", respuestas_tiempo[2] );	
	        	}else if(opcion==4){
				resultado=SumaDeRespuestas(respuesta,cantidad_hijos);
				printf("La cantidad de procesos Interactivos es: %f\n", resultado);
	        	}else if(opcion==5){
				resultado=SumaDeRespuestas(respuesta,cantidad_hijos);
	        		printf("Número de procesos cuya ejecución fue cancelada por el administrador es: %f\n", resultado);
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
