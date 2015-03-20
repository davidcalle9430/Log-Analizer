#include <stdio.h>
  #include <stdlib.h>
#include <string.h>
 //#include <string>
   int numeroProcesosUnProcesador(char *nombreArchivo){
     FILE * fp;
     char * line = NULL;
     size_t len = 0;
     ssize_t read;
     int tamArchivo;
     int resultado=0;
    fp = fopen(nombreArchivo, "r");

   if (fp == NULL){
           exit(EXIT_FAILURE);
   }
   int i;	
  while ( (read = getline(&line, &len, fp)) != -1 ) {        
   if( line[0]!=';'){
       char *lee;
       lee=strtok(line, " \t" ); 
       int contador=1;
       while(lee != NULL) {  
          if(contador==5 && strcmp(lee, "1")==0){
          resultado++;
           }
          lee=strtok(NULL, " \t");
          contador++;
 
       } 
        }      
      }
fclose(fp);
return resultado;
}


   int main(void)
   {   
     int a= numeroProcesosUnProcesador("datos100.txt");
     printf("salida = %i \n", a);      
   }
