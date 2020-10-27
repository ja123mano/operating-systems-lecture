/**
 *	Jose Enrique Santana Martínez		A01636381
 *	Vendedores de leche usando MUTEX	lab_06
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>

pthread_mutex_t mutex;
int botesLeche = 1000;
int vendedores = 5;
int rondas = 5;
int ventas = 0;
//int numero =1;

void venderLeche(intptr_t *t_id) {
	intptr_t t_id2 = (intptr_t) t_id;
	ventas = 1 + (rand() %201);
	if (ventas < botesLeche) {
		botesLeche = botesLeche - ventas;
		printf("Vendedor %zd vendio %d botes de leche\n", t_id2, ventas);
	}
	else {
		printf("Ups, el vendedor intento vender mas botellas de las que habia en stock\n");
		printf("No se completo la venta por %d botellas de leche\n", ventas);
	}
}

void *hilos(void *i) {
	intptr_t t_id = (intptr_t) i;
	
	//printf("Dentro del hilo %zd\n", t_id);
	//printf("\n%d\n", numero++);
	
	printf("Vendedor %zd intentando acceder a la venta\n", t_id);
	pthread_mutex_lock(&mutex);
	
	//printf("Mutex bloqueado por vendedor %zd\n", t_id);
	
	if (botesLeche > 0) {
		venderLeche((intptr_t *)t_id);
		
		//printf("Mutex desbloqueado por vendedor %zd\n", t_id);
		
		printf("\n\t\t\t Botes de leche restantes = %d\n", botesLeche);
		pthread_mutex_unlock(&mutex);
	}
	else {
		pthread_mutex_unlock(&mutex);
		
		//printf("Desbloqueado por vendedor %zd\n", t_id);
		
		printf("\n");
		pthread_exit(NULL);
	}
}

int main(void) {
	srand(time(0));		//semilla para generar números aleatorios

	pthread_mutex_init(&mutex, NULL);
	//printf("Mutex creado por %p\n", (void *) &mutex);
	printf("\t\t\t Botes de leche restantes = %d\n", botesLeche);
	pthread_t thread[vendedores];

	int i;
	for (i = 0; i < rondas; i++) {
		pthread_create(&thread[0], NULL, hilos, (void*) (intptr_t)(1));
		pthread_create(&thread[1], NULL, hilos, (void*) (intptr_t)(2));
		pthread_create(&thread[2], NULL, hilos, (void*) (intptr_t)(3));
		pthread_create(&thread[3], NULL, hilos, (void*) (intptr_t)(4));
		pthread_create(&thread[4], NULL, hilos, (void*) (intptr_t)(5));
	}

	for (i = 0; i < vendedores; i++) {
		pthread_join(thread[i], NULL);
	}


	printf("\n\nSe acabo la leche por hoy, por favor vuelva mañana\n");
}

