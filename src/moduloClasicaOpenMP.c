/*#######################################################################################
 #* Autores:   Andres Eduardo Meneses Rincon, Karol Dayan Torres Vides
 #* Docente:   J. Corredor, PhD
 #* Fichero:   moduloClasicaOpenMP.c
 #* Descripcion:
 #*    Implementa las funciones de la version clasica de multiplicacion de matrices paralelizada con OpenMP.
 #######################################################################################*/

#include "moduloClasicaOpenMP.h"

struct timeval inicio, fin; 

/* Marca el inicio del cronometro para medir el tiempo de ejecucion del kernel OpenMP. */
void InicioMuestra(){
	gettimeofday(&inicio, (void *)0);
}

/* Calcula el tiempo transcurrido desde InicioMuestra y lo imprime en microsegundos. */
void FinMuestra(){
	gettimeofday(&fin, (void *)0);
	fin.tv_usec -= inicio.tv_usec;
	fin.tv_sec  -= inicio.tv_sec;
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec); 
	printf("%.0f;", tiempo);
}

/* Imprime la matriz cuadrada completa cuando el tamano es suficientemente pequeno. */
void impMatrix(double *matrix, int D){
	if(D < 9){
		printf("\n");
		for(int i=0; i<D*D; i++){
			if(i%D==0) printf("\n");
			printf("%.2f ", matrix[i]);
		}
		printf("\n**-----------------------------**\n");
	}
}

/* Inicializa las matrices A y B con valores aleatorios en un intervalo fijo. */
void iniMatrix(double *m1, double *m2, int D){
	for(int i=0; i<D*D; i++, m1++, m2++){
		*m1 = (double)rand()/RAND_MAX*(5.0-1.0);	
		*m2 = (double)rand()/RAND_MAX*(9.0-2.0);	
	}
}

/* Multiplica las matrices A y B usando un doble bucle paralelo con OpenMP. */
void multiMatrix(double *mA, double *mB, double *mC, int D){
	double Suma, *pA, *pB;
	#pragma omp parallel
	{
	#pragma omp for
	for(int i=0; i<D; i++){
		for(int j=0; j<D; j++){
			pA = mA+i*D;	
			pB = mB+j; 
			Suma = 0.0;
			for(int k=0; k<D; k++, pA++, pB+=D){
				Suma += *pA * *pB;
			}
			mC[i*D+j] = Suma;
		}
	}
	}
}