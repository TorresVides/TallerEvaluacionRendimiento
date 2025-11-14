#!/usr/bin/perl
#-------------------------------------------------------------------------------
# Autores:   Andres Eduardo Meneses Rincon, Karol Dayan Torres Vides
# Docente:   J. Corredor, PhD
# Fichero:   lanzadorCFork.pl
# Descripcion:
#    Script Perl que automatiza la ejecucion por lotes de mmClasicaFork, lanzando procesos para distintos tamanos de matriz y consolidando los tiempos en un .csv.
#-------------------------------------------------------------------------------

$Path = `pwd`;
chomp($Path);

$Nombre_Ejecutable = "mmClasicaFork";
@Size_Matriz = ("2","10","20", '500', '1000');
@Num_Hilos = (1,2,4,8,16,20);
$Repeticiones = 30;

# Bucle principal que recorre los tamaños de matriz que fueron definidos ya  en @Size_Matriz.
foreach $size (@Size_Matriz){
	foreach $hilo (@Num_Hilos) {
		$file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat";
		for ($i=0; $i<$Repeticiones; $i++) {
            system("$Path/$Nombre_Ejecutable $size $hilo  >> $file");
			printf("$Path/$Nombre_Ejecutable $size $hilo \n");
		}
		close($file);
	$p=$p+1;
	}
}

# Esto une todos los ficheros .dat generados en un unico archivo .csv que es el que se usa para la creación de las graficas
system("cat *.dat > resultadosClasicosFork.csv");
