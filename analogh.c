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
  
}Parametro;


void* NumeroProcesosUnProcesador(Parametro *parametro){
  // el valor del parametro es
  //printf(" dirección de llegada %p\n", parametro);
  int *retorno, i;
  retorno= (int*)malloc(sizeof(int));
  *(retorno)=0;
  //printf("DURANTE %p\n",parametro->procesos );
  for (i =parametro->inicio; i < parametro->fin; i++)
  { 

    int a=parametro->procesos[i].numero_procesadores;

    //printf("el valor en %i es %i\n",i, a );
    if(a==1){
      *(retorno)= *(retorno)+1;
    }
  }
  printf(" al final el retorno es %i \n",*retorno );
  pthread_exit(retorno);
}

int main(int argc, char *argv[])
 {      
  FILE * fp;
  
  char *line, *lee, basura;
  size_t len;
  ssize_t read;
  int i,contador, contador_lineas, resultado, cantidad_hilos, aumento, cantidad_lineas,opcion;
  double datos[18];
  Proceso* procesos;
  Parametro *p;
   pthread_t *hilos;
  //pthread_t* hilos;


  
  

  fp = fopen(argv[1], "r");
  if (fp == NULL){
      printf("El archivo con el nombre especificado no existe\n");
      exit(EXIT_FAILURE);
  }else{
    contador_lineas=0;
    resultado=0;
    len = 0;
    
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
      //creo la estructura //1 6 7 5 15 11
      procesos[contador_lineas].numero_tarea = datos[0];
      procesos[contador_lineas].numero_procesadores = datos[4];
      //printf("original %i: %i\n",cantidad_lineas, procesos[contador_lineas].numero_procesadores);
      procesos[contador_lineas].tiempo_promedio_cpu = datos[5];
      procesos[contador_lineas].memoria_usada = datos[6];
      procesos[contador_lineas].status = datos[10];
      procesos[contador_lineas].numero_cola = datos[14];
      contador_lineas++;
    }      
    } 
    }
  fclose(fp);



  // ahora es con base en cada opción crear los hilos y llamar a una función en específico
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
          // crear la cantidad de hilos que se pasen por parámetro
          //acumulador=(int*) malloc(sizeof(int)*cantidad_hilos);
          hilos = (pthread_t*) malloc(sizeof(pthread_t)*cantidad_hilos);
          //Parametro p[cantidad_hilos];
          p=(Parametro*) malloc((sizeof(Parametro)*cantidad_hilos));
          //pthread_t hilos[cantidad_hilos];
          for (i = 0; i < cantidad_hilos; i++)
          { 
          
            p[i].procesos = procesos;
            p[i].inicio= aumento *i;
            p[i].fin= (aumento * i)+ aumento;
            //printf("ANTES  %p\n",(&(p[i]))->procesos );
            
            pthread_create(&(hilos[i]), NULL, (void*) NumeroProcesosUnProcesador, (void*) &(p[i ]));
            //printf("DESPUES  %p\n",(p+i)->procesos );
            //printf("imprimo %i\n",(p+i)->procesos[0].numero_procesadores );
          }
          // joineo los hilos
          int *pepeiro;
          for (i = 0; i < cantidad_hilos; i++)
          { 
            pthread_join(hilos[i],(void **)&pepeiro);
            
            //printf("acum %p\n",(acumulador+i) );
            resultado+= *pepeiro;
           
          }
          printf("El numero  de procesos que se ejecutó únicamente en un procesador es: %i\n", resultado);
          free(hilos);
          free(p);
          //printf("Direccion Impresión FINAL %p y es %i \n",(&(p[0]))->procesos ,(&(p[0]))->procesos[0].numero_procesadores );
          //printf("Direccion Impresión FINAL %p y es %i \n",(&(p[0]))->procesos ,(&(p[0]))->procesos[99].numero_procesadores );
        
        }else if(opcion==2){
    
        }else if(opcion==3){
        
          
        }else if(opcion==4){
          
        }else if(opcion==5){

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