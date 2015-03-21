  /*
     Nombre Archivo:
      	secuencial.h
     Realizado por:
      	Erika Jeniffer Harker
      	David Calle
     Objetivo:
      	 Prototipo de las funciones que manipulan el log.
     Fecha Última Modificación:
      	Marzo 21 de 2015
    */
    #ifndef SECUENCIAL_H
    #define SECUENCIAL_H
    int NumeroProcesosUnProcesador(char* nombre_archivo, int total_lineas); ; // prototipo de las funciones
    int NumeroProcesosMasDe64(char* nombre_archivo, int total_lineas);
    void ProcesoUtilizaMasCPU(char *nombre_archivo, int total_lineas, int resultado[3]);
    int ProcesosInteractivos (char *nombre_archivo, int total_lineas);
    int EjecucionCancelada (char *nombre_archivo, int total_lineas);
    #include "secuencial.c"
    #endif