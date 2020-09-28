/**
 * A01636381-homework-04
 *
 * José Enrique Santana Martínez
 * A01636381
 *
 * Link a gráfica: https://drive.google.com/file/d/1kM2RusZVK4kSlSkDKZ7YBT72ngyTTMCp/view?usp=sharing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define NUM_PTS 50000000

int num_hilos;
int pts_por_hilo;
int pts_circulo;
long puntos;
unsigned int semilla;

clock_t inicio, fin;
double tiempo;

double aleatorio() {
	return (double)rand_r(&semilla) / (double)((unsigned)RAND_MAX + 1);
}

void *calculo_pi (void*t_id) {
	double coorX, coorY;
	int *pts_dentro = (int *)malloc(sizeof(int));
	*pts_dentro = 0;

	int i;
	for (i = 0; i < pts_por_hilo; i++) {
		coorX = aleatorio();
		coorY = aleatorio();
		if (sqrt(pow(coorX - 0.5,2) + pow(coorY - 0.5,2)) <= 0.5) {
			*pts_dentro += 1;
		}
	}

	pthread_exit((void *) pts_dentro);
}

int main (int argc, const char* argv[]) {
	semilla = time(NULL);
	puntos = NUM_PTS;
	
	inicio = clock();

	if (argc < 2 || argc > 3) {
		printf ("Por favor escriba solamente la cantidad de hilos a usar\n");
		exit(1);
	} else {
		num_hilos = atoi(argv[1]);
		if (num_hilos <= 0) {
			printf ("El número de hilos debe ser mayor a 0\n");
			exit(1);
		}

		printf("Cantidad de puntos a usar = %zd \n", puntos);
	}

	double pi_calculado;
	void *pts_dentro_hilo;
	int hilo_no_exitoso;

	pthread_t hilos[num_hilos];
	pts_por_hilo = puntos / num_hilos;
	printf("%d puntos por hilo\n\n", pts_por_hilo);

	unsigned int i;
	for (i = 0; i < num_hilos; i++) {
		hilo_no_exitoso = pthread_create(&hilos[i], NULL, calculo_pi, (void *)(intptr_t) i);
		semilla++;
		if (hilo_no_exitoso) {
			exit(1);
		} else {
			printf("Se creo el hilo %i correctamente\n", i+1);
		}
	}

	for (i = 0; i < num_hilos; i++) {
		pthread_join (hilos[i], &pts_dentro_hilo);
		pts_circulo += *(long *) pts_dentro_hilo;
	}

	printf("\nPuntos dentro del círculo = %zd\n",  pts_circulo);

	pi_calculado = (4.00 * (float)pts_circulo) / (float)puntos;
	printf("\nCalculo de PI = %.6f\n", pi_calculado);

	fin = clock();
	tiempo = ((double)(fin - inicio)) / (num_hilos * CLOCKS_PER_SEC);

	printf ("\nTiempo transcurrido = %.5f\n", tiempo);

	exit(0);
}
