/*

 Nombre Archivo:

    analogp.c

 Realizado por:

    Erika Jeniffer Harker

    David Calle

 Objetivo:

    Programa el cual analiza la informacion de un log por medio de procesos

 Fecha 趌tima Modificaci髇:

    Marzo 21 de 2015

 */

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

#include "procesos.h"



#define SHMSZ 27

#define MAX  50

#define SMES 30

#define CANT_RESPUESTAS 3

#define CANT_RESP_TIEMPO 3
#define MAX_LINEAS 100

int main(int argc, char *argv[]) {



    int shmid, shmid2;

    key_t key, key2;

    char *shm, *shm2;

    char basura;

    int i, j;

    float **respuesta;

    Proceso **procesos;

    int cantidad_hijos, division, modulo, modulo_lineas, division_lineas;

    int child_pid;

    int numero, contador, cant_lineas, opcion;

    float respuestas_tiempo[CANT_RESP_TIEMPO], resultado;





    if (argc != 4) {

        printf("Cantidad de argumentos incorrectos\n");

        exit(1);

    } else if (atoi(argv[2]) <= 0 || atoi(argv[3]) <= 0) {

        printf("Tamano de archivo o  cantidad de procesos incorrecto\n");

        exit(1);

    }
    else {

        basura = ' ';

        cant_lineas = atoi(argv[2]);

        cantidad_hijos = atoi(argv[3]);

        /*

         * Crear el segmento de memoria compartida

         */
        division_lineas = (cant_lineas - 1) / 100;
        modulo_lineas = cant_lineas % 100;
        procesos = malloc(sizeof (Proceso)*(division_lineas + 1));
        //respuesta = malloc(sizeof (int)*(CANT_RESPUESTAS));
        respuesta = malloc(sizeof (void*)*(cantidad_hijos));
        if (division_lineas == 0) {
            if ((shmid = shmget(key, sizeof (Proceso) * cant_lineas, IPC_CREAT | 0666)) < 0) {

                perror("Lineas shmget");

                exit(1);

            }



            /*

             * Anexar (attach)  el segmento al espacio de direcciones del proceso 

             */

            if ((shm = shmat(shmid, NULL, 0)) == (char *) - 1) {

                perror("shmat");

                exit(1);

            }

            procesos[0] = (Proceso*) shm;
        } else {
            for (i = 0; i < division_lineas; i++) {
                if ((shmid = shmget(key, sizeof (Proceso) * MAX_LINEAS, IPC_CREAT | 0666)) < 0) {

                    perror("Lineas shmget");

                    exit(1);

                }



                /*

                 * Anexar (attach)  el segmento al espacio de direcciones del proceso 

                 */

                if ((shm = shmat(shmid, NULL, 0)) == (char *) - 1) {

                    perror("shmat");

                    exit(1);

                }

                procesos[i] = (Proceso*) shm;
            }
            if ((shmid = shmget(key, sizeof (Proceso) * modulo_lineas, IPC_CREAT | 0666)) < 0) {

                perror("Lineas shmget");

                exit(1);

            }



            /*

             * Anexar (attach)  el segmento al espacio de direcciones del proceso 

             */

            if ((shm = shmat(shmid, NULL, 0)) == (char *) - 1) {

                perror("shmat");

                exit(1);

            }

            procesos[i] = (Proceso*) shm;
        }



        // memoria compartida respuesta

        for (i = 0; i < cantidad_hijos; i++) {

            if ((shmid2 = shmget(key2, sizeof (float)*CANT_RESPUESTAS, IPC_CREAT | 0666)) < 0) {

                perror("shmget");

                exit(1);

            }



            /*

             * Anexar (attach)  el segmento al espacio de direcciones del proceso 

             */

            if ((shm2 = shmat(shmid2, NULL, 0)) == (char *) - 1) {

                perror("shmat");

                exit(1);

            }

            respuesta[i] = (float*) shm2;

        }

        //cargar todo al vector de procesos

        leerArchivo(argv[1], procesos, cant_lineas);

        //creo los hijos y se les asigno



        division = cant_lineas / cantidad_hijos;

        modulo = cant_lineas % cantidad_hijos;

        opcion = 0;

        while (opcion != 6) {

            printf("1. Numero de procesos que se ejecut贸 煤nicamente en un procesador.\n ");

            printf("2. Numero de procesos que se ejecut贸 en 64 o m谩s procesadores.\n");

            printf("3. Que proceso utilizo m谩s CPU\n");

            printf("4. Cantidad de procesos Interactivos encontrados\n");

            printf("5. Numero de procesos cuya ejecuci贸n fue cancelada por el administrador\n");

            printf("6. Salir del sistema \n");



            scanf("%d", &opcion);

            printf("\e[1;1H\e[2J");



            struct timeval start, end;

            gettimeofday(&start, NULL);

            int idMiproceso;

            for (i = 0; i < cantidad_hijos; i++) {

                idMiproceso = i;


                if ((child_pid = fork()) < 0) {

                    perror("fork: \n");

                }

                if (child_pid == 0) {
		    
                    if (opcion == 1) {


                        if (idMiproceso < modulo) {

                            respuesta[idMiproceso][0] = NumeroProcesosUnProcesador(idMiproceso * (division + 1), (idMiproceso + 1)*(division + 1), procesos);

                        } else {

                            respuesta[idMiproceso][0] = NumeroProcesosUnProcesador((idMiproceso * division) + modulo, ((idMiproceso + 1) * division) + modulo, procesos);

                        }

                        exit(0);

                    } else if (opcion == 2) {

                        if (i < modulo) {

                            respuesta[idMiproceso][0] = NumeroProcesosMasDe64(i * (division + 1), (i + 1)*(division + 1), procesos);

                        } else {

                            respuesta[idMiproceso][0] = NumeroProcesosMasDe64((i * division) + modulo, ((i + 1) * division) + modulo, procesos);

                        }

                        exit(0);

                    } else if (opcion == 3) {

                        if (i < modulo) {

                            ProcesoUtilizaMasCPU(i * (division + 1), (i + 1)*(division + 1), procesos, respuestas_tiempo);

                            for (j = 0; j < CANT_RESP_TIEMPO; j++) {

                                respuesta[idMiproceso][j] = respuestas_tiempo[j];

                            }

                        } else {

                            ProcesoUtilizaMasCPU((i * division) + modulo, ((i + 1) * division) + modulo, procesos, respuestas_tiempo);

                            for (j = 0; j < CANT_RESP_TIEMPO; j++) {

                                respuesta[idMiproceso][j] = respuestas_tiempo[j];

                            }

                        }

                        exit(0);

                    } else if (opcion == 4) {

                        if (i < modulo) {

                            respuesta[idMiproceso][0] = ProcesosInteractivos(i * (division + 1), (i + 1)*(division + 1), procesos);

                        } else {

                            respuesta[idMiproceso][0] = ProcesosInteractivos((i * division) + modulo, ((i + 1) * division) + modulo, procesos);

                        }

                        exit(0);

                    } else if (opcion == 5) {

                        if (i < modulo) {

                            respuesta[idMiproceso][0] = EjecucionCancelada(i * (division + 1), (i + 1)*(division + 1), procesos);

                        } else {

                            respuesta[idMiproceso][0] = EjecucionCancelada((i * division) + modulo, ((i + 1) * division) + modulo, procesos);

                        }

                        exit(0);

                    }

                }

            }

            for (i = 0; i < cantidad_hijos; i++) {

                int status;

                wait(&status);

            }

            if (opcion == 1) {

                resultado = SumaDeRespuestas(respuesta, cantidad_hijos);

                printf("El numero  de procesos que se ejecuta unicamente en un procesador es: %f\n", resultado);

            } else if (opcion == 2) {

                resultado = SumaDeRespuestas(respuesta, cantidad_hijos);

                printf("El numero de procesos que se ejecuta en 64 o mas procesadores es: %f\n", resultado);

            } else if (opcion == 3) {

                MayorTiempo(respuesta, respuestas_tiempo, cantidad_hijos, CANT_RESP_TIEMPO);

                printf("Proceso que utiliza mas CPU: %f  ;", respuestas_tiempo[1]);

                printf("Tiempo de uso de CPU: %f  ;", respuestas_tiempo[0]);

                printf("Memoria utilizada: %f\n", respuestas_tiempo[2]);

            } else if (opcion == 4) {

                resultado = SumaDeRespuestas(respuesta, cantidad_hijos);

                printf("La cantidad de procesos Interactivos es: %f\n", resultado);

            } else if (opcion == 5) {

                resultado = SumaDeRespuestas(respuesta, cantidad_hijos);

                printf("Numero de procesos cuya ejecuci贸n fue cancelada por el administrador es: %f\n", resultado);

            }

            if (opcion != 6) {

                gettimeofday(&end, NULL);

                printf("%ld\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));



                printf("Oprima cualquier tecla para continuar \n");

                scanf("%c", &basura);

                scanf("%c", &basura);

                printf("\e[1;1H\e[2J");

            }

        }

    }

} 
