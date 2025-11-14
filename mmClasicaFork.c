/*#######################################################################################
 #* Autores:   Andres Eduardo Meneses Rincon, Karol Dayan Torres Vides
 #* Docente:   J. Corredor, PhD
 #* Fichero:   mmClasicaFork.c
 #* Descripcion:
 #*    Programa completo que utiliza el algoritmo clasico de multiplicacion de 
 			matrices usando procesos fork, repartiendo las filas entre procesos hijos.
 #######################################################################################*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

struct timeval inicio, fin;

/* Marca el inicio del cronometro para medir el tiempo de ejecucion del programa con procesos fork */
void InicioMuestra(){
	gettimeofday(&inicio, (void *)0);
}

/* Calcula el tiempo transcurrido desde InicioMuestra y lo muestra por consola en microsegundos */
void FinMuestra(){
	gettimeofday(&fin, (void *)0);
	fin.tv_usec -= inicio.tv_usec;
	fin.tv_sec  -= inicio.tv_sec;
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);
	printf("%9.0f \n", tiempo);
}

/* Esta funcion usa el algoritmo clasico de la multiplicacion de matrices, y se guarda el resultado en la matriz C */
void multiMatrix(double *mA, double *mB, double *mC, int D, int filaI, int filaF) {
	double Suma, *pA, *pB;
    for (int i = filaI; i < filaF; i++) {
        for (int j = 0; j < D; j++) {
			Suma = 0.0;
			pA = mA+i*D;
			pB = mB+j;
            for (int k = 0; k < D; k++, pA++, pB+=D) {
				Suma += *pA * *pB;	
            }
			mC[i*D+j] = Suma;
        }
    }
}

/* Imprime la matriz cuadrada por pantalla cuando la dimension D es menor a 9 */
void impMatrix(double *matrix, int D) {
	if (D < 9) {
    	printf("\nImpresión	...\n");
    	for (int i = 0; i < D*D; i++, matrix++) {
			if(i%D==0) printf("\n");
            	printf(" %.2f ", *matrix);
        	}
        printf("\n ");
    }
}

/* Usando rand() y RAND_MAX, se inicializan las matrices A y B con valores aleatorios entre 0.0 y 4.0 para poder probar el rendimiento */
void iniMatrix(double *mA, double *mB, int D){
	for (int i = 0; i < D*D; i++, mA++, mB++){
            *mA = (double)rand()/RAND_MAX*(5.0-1.0); ; 
            *mB = (double)rand()/RAND_MAX*(9.0-5.0); 
        }
}

/* Funcion principal: crea los procesos hijos, reparte las filas entre ellos y coordina la medicion de tiempo. */
int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("\n \t\tUse: $./nom_ejecutable Size Hilos \n");
		exit(0);
	}
	int N      = (int) atoi(argv[1]);
	int num_P  = (int) atoi(argv[2]);
	double *matA = (double *) calloc(N*N, sizeof(double));
	double *matB = (double *) calloc(N*N, sizeof(double));
	double *matC = (double *) calloc(N*N, sizeof(double));

    srand(time(0)); 
    /* Se inicializan las matrices con los valores double aleatorios y se llama a las funciones de impresión */
    iniMatrix(matA, matB, N);
    impMatrix(matA, N);
    impMatrix(matB, N);
    /* Filas por proceso */
    int rows_per_process = N/num_P;
	/* Marcar el inicio de ejecución */
	InicioMuestra();

    for (int i = 0; i < num_P; i++) {
        pid_t pid = fork();
        
        if (pid == 0) { 
            int start_row = i * rows_per_process;
			/* Para dejar las filas restantes al ultimo proceso */
            int end_row = (i == num_P - 1) ? N : start_row + rows_per_process;
            
			multiMatrix(matA, matB, matC, N, start_row, end_row); 
            
			if(N<9){
           		printf("\nChild PID %d calculated rows %d to %d:\n", getpid(), start_row, end_row-1);
            	for (int r = start_row; r < end_row; r++) {
                	for (int c = 0; c < N; c++) {
                    	printf(" %.2f ", matC[N*r+c]);
                	}
                	printf("\n");
            	}
			}
            exit(0); 
        } else if (pid < 0) {
            perror("fork failed");
            exit(1);
        }
    }
    
    for (int i = 0; i < num_P; i++) {
        wait(NULL);
    }
  /* Marcar el tiempo total */	
	FinMuestra(); 
 /*Liberar memoria */
	free(matA);
	free(matB);
	free(matC);

    return 0;
}
