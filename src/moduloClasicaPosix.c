/*#######################################################################################
 #* Autores:   Andres Eduardo Meneses Rincon, Karol Dayan Torres Vides
 #* Docente:   J. Corredor, PhD
 #* Fichero:   moduloClasicaPosix.c
 #* Descripcion:
 #*    Implementa las funciones compartidas por la version clasica de multiplicacion de matrices con hilos POSIX.
 #######################################################################################*/

#include "moduloClasicaPosix.h"

pthread_mutex_t MM_mutex;
double *matrixA, *matrixB, *matrixC;
struct timeval inicio, fin;

/* Marca el inicio del cronometro para medir el tiempo total de la multiplicacion. */
void InicioMuestra(){
	gettimeofday(&inicio, (void *)0);
}

/* Calcula el tiempo transcurrido desde InicioMuestra y lo imprime en microsegundos. */
void FinMuestra(){
	gettimeofday(&fin, (void *)0);
	fin.tv_usec -= inicio.tv_usec;
	fin.tv_sec  -= inicio.tv_sec;
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);
	printf("%.0f", tiempo);
}


/* Inicializa las matrices con valores aleatorios para probar el rendimiento del algoritmo. */
void iniMatrix(double *m1, double *m2, int D){ 
	for(int i = 0; i < D*D; i++, m1++, m2++){
			*m1 = (double)rand()/RAND_MAX*(5.0-1.0); 
			*m2 = (double)rand()/RAND_MAX*(9.0-5.0); 
		}	
}

/* Imprime la matriz por pantalla cuando el tamano es pequeno para poder revisarla. */
void impMatrix(double *matriz, int D){
	if(D < 9){
    		for(int i = 0; i < D*D; i++){
     				if(i%D==0) printf("\n");
            		printf(" %.2f ", matriz[i]);
			}	
    	printf("\n>-------------------->\n");
	}
}

void *multiMatrix(void *variables){
	struct parametros *data = (struct parametros *)variables;
	
	int idH		= data->idH;
	int nH		= data->nH;
	int D		= data->N;
	int filaI	= (D/nH)*idH;
	int filaF	= (D/nH)*(idH+1);
	double Suma, *pA, *pB;

    for (int i = filaI; i < filaF; i++){
        for (int j = 0; j < D; j++){
			pA = matrixA + i*D; 
			pB = matrixB + j;
			Suma = 0.0;
            for (int k = 0; k < D; k++, pA++, pB+=D){
				Suma += *pA * *pB;
			}
			matrixC[i*D+j] = Suma;
		}
	}

	pthread_mutex_lock (&MM_mutex);
	pthread_mutex_unlock (&MM_mutex);
	pthread_exit(NULL);
}