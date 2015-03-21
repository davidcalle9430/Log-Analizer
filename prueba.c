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
	#define MAX       100
	#define SMES       30

 	int main(int argc, char *argv[]){

 	char c;
    int shmid;
    key_t key;
    char *shm;
    int   i,j,x, cuantos, numero, pos, totalhijo, cuantoshijo, *result, *res;
    FILE *filein; 
    float *memoria_compartida;
    char mensaje[MAX];
    
     /*
     * Crear el segmento de memoria compartida
     */
     int pepe = sizeof(float)*10*10;
   if ((shmid = shmget(key, pepe, SHM_HUGETLB | IPC_CREAT | 0666)) < 0) {
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


    memoria_compartida = (float*)shm;
   
 
    for ( i = 0; i < 10; i++)
    {
    	for (j = 0; j < 10; j++)
    	{
    		memoria_compartida[(i*10) +j]=-1;
    	}
	}

  pid_t child_pid;
    for ( i = 0; i < 10; i++)
    {  
    	if((child_pid=fork())<0){
    		printf("error fatalisisisisimo\n");
    	    exit(1);
    	}
    	if(child_pid==0){
    		//printf("error fatalisimo\n");
         for (j = 0; j < 10; j++)
         {
           memoria_compartida[(i*10) +j]=0;	
         }
         exit(0);
    	}
    }
    for (i = 0; i < 10; i++)
    {   int s;
    	wait(&s);
    }

     for ( i = 0; i < 10; i++)
    {
    	for (j = 0; j < 10; j++)
    	{
    		printf("%f " ,memoria_compartida[(i*10) +j]);
    	}
    	printf("\n");
    }

 	}  