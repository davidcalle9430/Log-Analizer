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
	

	#define SHMSZ     27
	#define MAX       50
	#define SMES       30

	 typedef struct{
	 	//1 6 7 5 15 11
		int numero_tarea;
		//int submit_time;
		//int tiempo_espera;
		//int tiempo_ejecucion;
		int numero_procesadores;
		float tiempo_promedio_cpu;
		int memoria_usada;
		//int num_proc_solicitados;
		//int tiempo_solicitado;
		//int memoria_solicitada;
		int status;
		//int id_usuario;
		//int id_grupo;
		//int id_aplicacion;
		int numero_cola;
		//int numero_particion;
		//int tarea_anterior;
		//int tiempo_reflexion;
	} Proceso;


int NumeroProcesosUnProcesador( int inicio, int fin, Proceso* procesos, int* respuesta){
     	char *line, *lee;
     	size_t len;
     	ssize_t read;
     	int numero, contador, contador_lineas, resultado,i;
     	double datos[18];
     	resultado=0;
     	printf("El proceso con pid %i busca de %i a %i \n",getpid(),inicio, fin );
     	for( i=inicio ; i<fin ; i++ ){
     		if(procesos[i].numero_procesadores==1){
     			*(respuesta)= *(respuesta)+1;
     		}
     	}
		
	}



 int main(int argc, char *argv[]){
    int shmid,shmid2;
    key_t key,key2;
    char *shm,*shm2;
    int   i,j, *respuesta;
    Proceso *procesos;
    
    
 	char *line, *lee;
 	size_t len;
 	ssize_t read;
 	int numero, contador, contador_lineas, resultado;
 	double datos[18];

     /*
     * Crear el segmento de memoria compartida
     */
     int pepe = sizeof(Proceso)*1000;
   if ((shmid = shmget(key, pepe, IPC_CREAT | 0666)) < 0) {
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
   /////////////////////////////////////// memoria compartida respuesta

	if ((shmid2 = shmget(key2, sizeof(int), IPC_CREAT | 0666)) < 0) {
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
    respuesta= (int*) shm2;
    *respuesta=0;


    //////////////////////////////////////////777
    
    //cargar todo al vector de procesos
    contador_lineas=0;
 	resultado=0;
 	len = 0;
 	line = NULL;
 	FILE * fp;
	fp = fopen(argv[1], "r");
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

	//creo los hijos y se les asigno 
	int cantidad_hijos=5;
	int division= 100/5; //no hay que quemar los datos
	int child_pid;
	for (i = 0; i < 100; i+=division)
	{   
		if((child_pid=fork())<0){
 	    printf("Error fatal\n");
		}
		if(child_pid==0){
			// lo pongo a hacer lo que tenga que hacer
			NumeroProcesosUnProcesador(i, i+division, procesos, respuesta);
			exit(0);
		}
	}
    for (i = 0; i < 5; i++)
	{   
		int status;
		wait(&status);
	}
	printf("La respuesta es %i \n", *respuesta);
 	}  