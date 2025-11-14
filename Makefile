# Pontificia Universidad Javeriana
# Autores:   Andres Eduardo Meneses Rincon, Karol Dayan Torres Vides
# Docente:   J. Corredor, PhD
# Fichero:   Makefile
# Descripcion:
#    Reglas de compilacion para los ejecutables de multiplicacion de matrices del taller de rendimiento.

GCC = gcc
CFLAGS = -lm
FOPENMP = -fopenmp -O3
POSIX = -lpthread

PROGRAMAS = mmClasicaOpenMP 

All: $(PROGRAMAS)

mmClasicaFork:
	$(GCC) $(CLFAGS) $@.c -o $@ 

mmClasicaOpenMP:
	$(GCC) $(CLFAGS) $@.c -o $@ $(FOPENMP)

clean:
	$(RM) $(PROGRAMAS) 
