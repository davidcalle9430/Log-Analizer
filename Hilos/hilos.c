#include <stdio.h> //librerías de C
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "hilos.h"

/*
	Función: 
		NumeroProcesosUnProcesador
	Parámetros de Entrada: 
		recibe un parametro que incluye la línea de inicio, la línea final, el vector de resultados y la matriz que representa el log
	Valor de Salida:
		ninguno
	Descripción:
		Cuenta el número de procesos que solo usaron un procesador en el log
*/
void* NumeroProcesosUnProcesador(Parametro *parametro){
	int *retorno, i,valor;
	retorno= (int*)malloc(sizeof(int));
  	*(retorno)=0;
  
  	for (i =parametro->inicio; i < parametro->fin; i++){ 
    		valor=parametro->procesos[i].numero_procesadores;
    		if(valor==1){
      			*(retorno)= *(retorno)+1;
      			parametro->respuesta[0]++;
    		}
  	}
}
/*
	Función: 
		NumeroProcesosUnProcesador
	Parámetros de Entrada: 
		recibe un parametro que incluye la línea de inicio, la línea final, el vector de resultados y la matriz que representa el log
	Valor de Salida:
		ninguno
	Descripción:
		Cuenta el número de procesos que usaron 64 o más procesadores en el log
*/

void* NumeroProcesosMasDe64(Parametro *parametro){
  	int *retorno, i, valor;
  	for (i =parametro->inicio; i < parametro->fin; i++){ 
     		valor=parametro->procesos[i].numero_procesadores;
    		if(valor>=64){
      			parametro->respuesta[0]++;
    		}
  	}

}
/*
	Función: 
		NumeroProcesoUtilizaMasCPU
	Parámetros de Entrada: 
		recibe un parametro que incluye la línea de inicio, la línea final, el vector de resultados y la matriz que representa el log
	Valor de Salida:
		ninguno
	Descripción:
		Cuenta el número de proceso que utilizó más tiempo de procesador
*/

void* NumeroProcesoUtilizaMasCPU(Parametro *parametro){
  	int i;
  	float valor;
  	for (i =parametro->inicio; i < parametro->fin; i++){ 
     		valor=parametro->procesos[i].tiempo_promedio_cpu;
    		if(valor>parametro->respuesta[0]){
      			parametro->respuesta[0]=valor;
      			parametro->respuesta[1]=parametro->procesos[i].numero_tarea;
      			parametro->respuesta[2]=parametro->procesos[i].memoria_usada;
    		}
  	}
}
/*
	Función: 
		ProcesosInteractivos
	Parámetros de Entrada: 
		recibe un parametro que incluye la línea de inicio, la línea final, el vector de resultados y la matriz que representa el log
	Valor de Salida:
		ninguno
	Descripción:
		Cuenta el número de procesos interactivos
*/

void* ProcesosInteractivos(Parametro *parametro){
  	int  i, valor;
  	for (i =parametro->inicio; i < parametro->fin; i++){ 
     		valor=parametro->procesos[i].numero_cola;
    		if(valor==0){
      			parametro->respuesta[0]++;
    		}
  	}
}
/*
	Función: 
		ProcesosInteractivos
	Parámetros de Entrada: 
		recibe un parametro que incluye la línea de inicio, la línea final, el vector de resultados y la matriz que representa el log
	Valor de Salida:
		ninguno
	Descripción:
		Cuenta el número de procesos de ejecución cancelada
*/
void* EjecucionCancelada(Parametro *parametro){
  	int  i, valor;
  	for (i =parametro->inicio; i < parametro->fin; i++){ 
     		valor=parametro->procesos[i].status;
    		if(valor==5){
      			parametro->respuesta[0]++;
    		}
  	}
}
