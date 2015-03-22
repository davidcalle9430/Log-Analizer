#include <stdio.h> //librerías de C
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
/*
  Archivo: 
    analogh.c
  Realizado por: 
    Erika Jeniffer Harker
    David Calle
  Contiene: 
    archivo para probar las las funciones definidas anteriormente.
  Fecha última modificación: 
    marzo 21 de 2015
*/

typedef struct{
  int numero_tarea;
  int numero_procesadores;
  float tiempo_promedio_cpu;
  int memoria_usada;
  int status;
  int numero_cola;
}Proceso;

typedef struct{
  Proceso* procesos;
  int inicio;
  int fin;
  float *respuesta;
  
}Parametro;


void* NumeroProcesosUnProcesador(Parametro *parametro){
  int *retorno, i,valor;
  retorno= (int*)malloc(sizeof(int));
  *(retorno)=0;
 
  for (i =parametro->inicio; i < parametro->fin; i++)
  { 
    valor=parametro->procesos[i].numero_procesadores;
    if(valor==1){
      *(retorno)= *(retorno)+1;
      parametro->respuesta[0]++;
    }
  }
  //printf(" al final el retorno es %i \n",*retorno );
  //pthread_exit(retorno);
}

void* NumeroProcesosMasDe64(Parametro *parametro){
  int *retorno, i, valor;
  retorno= (int*)malloc(sizeof(int));
  *(retorno)=0;
 
  for (i =parametro->inicio; i < parametro->fin; i++)
  { 
     valor=parametro->procesos[i].numero_procesadores;
    if(valor>=64){
      *(retorno)= *(retorno)+1;
      parametro->respuesta[0]++;
    }
  }
  //printf(" al final el retorno es %i \n",*retorno );
  //pthread_exit(retorno);
}

void* NumeroProcesosUtilizaMasCPU(Parametro *parametro){
  int i;
  float valor;
  
  for (i =parametro->inicio; i < parametro->fin; i++)
  { 
     valor=parametro->procesos[i].tiempo_promedio_cpu;
    if(valor>parametro->respuesta[0]){
      parametro->respuesta[0]=valor;
      parametro->respuesta[1]=parametro->procesos[i].numero_tarea;
      parametro->respuesta[2]=parametro->procesos[i].memoria_usada;
    }
  }
  //printf(" al final el retorno es %i \n",*retorno );
  //pthread_exit(retorno);
}

void* ProcesosInteractivos(Parametro *parametro){
  int  i, valor;
  for (i =parametro->inicio; i < parametro->fin; i++)
  { 
     valor=parametro->procesos[i].numero_cola;
    if(valor==0){
      parametro->respuesta[0]++;
    }
  }
}
void* EjecucionCancelada(Parametro *parametro){
  int  i, valor;
  for (i =parametro->inicio; i < parametro->fin; i++)
  { 
     valor=parametro->procesos[i].status;
    if(valor==5){
      parametro->respuesta[0]++;
    }
  }
}
int main(int argc, char *argv[])
 {      
  FILE * fp;
  
  char *line, *lee, basura;
  size_t len;
  ssize_t read;
  int i,contador, contador_lineas, cantidad_hilos, aumento, cantidad_lineas,opcion, *acum;
  float *resultado;
  double datos[18];
  Proceso* procesos;
  Parametro *p;
  pthread_t *hilos;

  fp = fopen(argv[1], "r");
  if (fp == NULL){
      printf("El archivo con el nombre especificado no existe\n");
      exit(EXIT_FAILURE);
  }else{
    contador_lineas=0;
    //resultado=0;
    len = 0;
    resultado= (float*) malloc(sizeof(float)*3);
    resultado[0]=0;
    resultado[1]=0;
    resultado[2]=0;
    
    line = NULL;
    cantidad_hilos= atoi(argv[3]);
    cantidad_lineas= atoi(argv[2]);
     
/////////////////////////////// falta validar el caso en que no sea entera la división.  
    aumento= cantidad_lineas/cantidad_hilos;
    procesos= (Proceso*) malloc(sizeof(Proceso)*cantidad_lineas);
    while ( (read = getline(&line, &len, fp)) != -1 ) {        
      if( line[0]!=';'&&contador_lineas<cantidad_lineas){
        lee=strtok(line, " \t" );
        contador=0;
        while(lee != NULL){ 
          datos[contador]=atof(lee); 
          lee=strtok(NULL, " \t");
          contador++;
        }
      procesos[contador_lineas].numero_tarea = datos[0];
      procesos[contador_lineas].numero_procesadores = datos[4];
      procesos[contador_lineas].tiempo_promedio_cpu = datos[5];
      procesos[contador_lineas].memoria_usada = datos[6];
      procesos[contador_lineas].status = datos[10];
      procesos[contador_lineas].numero_cola = datos[14];
      contador_lineas++;
    }      
    } 
    }
  fclose(fp);



  /*
   pthread_create(&thread1, NULL, (void*) primera_funcion, (void*)&i);
        pthread_create(&thread2, NULL, (void*) segunda_funcion, (void*)&i);
     
        pthread_join(thread1,(void **)&tiempo_dormido1);
        pthread_join(thread2, (void **)&tiempo_dormido2);
  */
  if (argc != 4) {
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
        
        scanf("%d", &opcion );
        printf("\e[1;1H\e[2J");
        
      
        if(opcion==1){
          hilos =  malloc(sizeof(pthread_t)*cantidad_hilos);
          p= malloc((sizeof(Parametro)*cantidad_hilos));
          for (i = 0; i < cantidad_hilos; i++)
          { 
            p[i].procesos = procesos;
            p[i].inicio= aumento *i;
            p[i].fin= (aumento * i)+ aumento;
            p[i].respuesta=&resultado[0];
            pthread_create(&(hilos[i]), NULL, (void*) NumeroProcesosUnProcesador, (void*) &(p[i]));
          }
          // joineo los hilos
          for (i = 0; i < cantidad_hilos; i++)
          { 
            pthread_join(hilos[i],(void **)&acum);
            //resultado+= *acum;

          }
          printf("El numero  de procesos que se ejecutó únicamente en un procesador es: %f\n", resultado[0]);
          free(hilos);
          free(p);
        }else if(opcion==2){

          hilos =  malloc(sizeof(pthread_t)*cantidad_hilos);
          p= malloc((sizeof(Parametro)*cantidad_hilos));
          for (i = 0; i < cantidad_hilos; i++)
          { 
            p[i].procesos = procesos;
            p[i].inicio= aumento *i;
            p[i].fin= (aumento * i)+ aumento;
            p[i].respuesta=resultado;
            pthread_create(&(hilos[i]), NULL, (void*) NumeroProcesosMasDe64, (void*) &(p[i ]));
          }
          // joineo los hilos
          for (i = 0; i < cantidad_hilos; i++)
          { 
            pthread_join(hilos[i],NULL);
            //resultado+= *acum;

          }
          printf("El numero  de procesos en más de 64 procesadores es: %f\n", resultado[0]);
          free(hilos);
          free(p);


    
        }else if(opcion==3){
          hilos =  malloc(sizeof(pthread_t)*cantidad_hilos);
          p= malloc((sizeof(Parametro)*cantidad_hilos));
                   for (i = 0; i < cantidad_hilos; i++)
          { 
            p[i].procesos = procesos;
            p[i].inicio= aumento *i;
            p[i].fin= (aumento * i)+ aumento;
            p[i].respuesta=resultado;
            pthread_create(&(hilos[i]), NULL, (void*) NumeroProcesosUtilizaMasCPU, (void*) &(p[i ]));
          }
          // joineo los hilos
          for (i = 0; i < cantidad_hilos; i++)
          { 
            pthread_join(hilos[i],NULL);
            //resultado+= *acum;

          }
          printf("Proceso que utilizó más CPU: %f  ;", resultado[1] );
          printf("Tiempo de uso de CPU: %f  ;", resultado[0]);
          printf("Memoria utilizada: %f\n", resultado[2]);
          free(hilos);
          free(p);
          
        }else if(opcion==4){
         hilos =  malloc(sizeof(pthread_t)*cantidad_hilos);
          p= malloc((sizeof(Parametro)*cantidad_hilos));
          for (i = 0; i < cantidad_hilos; i++)
          { 
            p[i].procesos = procesos;
            p[i].inicio= aumento *i;
            p[i].fin= (aumento * i)+ aumento;
            p[i].respuesta=resultado;
            pthread_create(&(hilos[i]), NULL, (void*) ProcesosInteractivos, (void*) &(p[i ]));
          }
          // joineo los hilos
          for (i = 0; i < cantidad_hilos; i++)
          { 
            pthread_join(hilos[i],NULL);
            //resultado+= *acum;

          }
          printf("El numero  de procesos nteractivos es de: %f\n", resultado[0]);
          free(hilos);
          free(p);
        }else if(opcion==5){
           hilos =  malloc(sizeof(pthread_t)*cantidad_hilos);
          p=malloc((sizeof(Parametro)*cantidad_hilos));
          for (i = 0; i < cantidad_hilos; i++)
          { 
            p[i].procesos = procesos;
            p[i].inicio= aumento *i;
            p[i].fin= (aumento * i)+ aumento;
            p[i].respuesta=resultado;
            pthread_create(&(hilos[i]), NULL, (void*) EjecucionCancelada, (void*) &(p[i ]));
          }
          // joineo los hilos
          for (i = 0; i < cantidad_hilos; i++)
          { 
            pthread_join(hilos[i],NULL);
            //resultado+= *acum;

          }
          printf("El numero  de procesos con ejecución`cancelada es de: %f\n", resultado[0]);
          free(hilos);
          free(p);
        }
        
        if(opcion!=6){
          free(procesos);
          printf("Oprima cualquier tecla para continuar \n" );
          scanf("%c",&basura);
          scanf("%c",&basura);
          printf("\e[1;1H\e[2J"); 
        }
  
        }
    } 
 }