/*#######################################################################################
 #* Autores:   Andres Eduardo Meneses Rincon, Karol Dayan Torres Vides
 #* Docente:   J. Corredor, PhD
 #* Fichero:   moduloClasicaPosix.h
 #* Descripcion:
 #*    Cabecera de la version clasica con hilos POSIX: declara la estructura de parametros y las funciones del modulo.
 #######################################################################################*/

#ifndef __MODULOCLASICAPOSIX_H__
#define __MODULOCLASICAPOSIX_H__

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

extern pthread_mutex_t MM_mutex;
extern double *matrixA, *matrixB, *matrixC;
extern struct timeval inicio, fin;

struct parametros{
	int nH;
	int idH;
	int N;
};

void InicioMuestra();
void FinMuestra();
void iniMatrix(double *m1, double *m2, int D);
void impMatrix(double *matriz, int D);
void *multiMatrix(void *variables);


#endif