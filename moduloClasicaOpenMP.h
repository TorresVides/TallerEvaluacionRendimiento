/*#######################################################################################
 #* Autores:   Andres Eduardo Meneses Rincon, Karol Dayan Torres Vides
 #* Docente:   J. Corredor, PhD
 #* Fichero:   moduloClasicaOpenMP.h
 #* Descripcion:
 #*    Cabecera de la version clasica con OpenMP: incluye librerias necesarias y prototipos de funciones.
 #######################################################################################*/

#ifndef __MMCLASICAOPENMP_H__
#define __MMCLASICAOPENMP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

void InicioMuestra();
void FinMuestra();
void impMatrix(double *matrix, int D);
void iniMatrix(double *m1, double *m2, int D);
void multiMatrix(double *mA, double *mB, double *mC, int D);

#endif