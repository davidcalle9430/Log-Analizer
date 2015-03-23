# PROYECTO #1 - Makefile para generar 2 ejecutables
# 

all: secuencial procesos hilos

secuencial: 
	gcc -o Secuencial/ejecutableSecuencial Secuencial/analogs.c
procesos:
	gcc -o Procesos/ejecutableProcesos Procesos/analogp.c
hilos:
	gcc -o  Hilos/ejecutableHilos Hilos/analogh.c -lpthread

