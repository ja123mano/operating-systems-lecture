/**
 *	José Enrique Santana Martínez		A01636381
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
int ventas = 0;

void venderLeche(intptr_t *t_id) {
	intptr_t t_id2 = (intptr_t) t_id;
	ventas = 1 + (rand() %201);
	if (ventas < botesLeche) {
		botesLeche = botesLeche - ventas;
		printf("Vendedor %zd vendió %d botes de leche\n", t_id2, ventas);
	}
	else {
		printf("Ups, el vendedor intentó vender más botellas de las que había en stock\n");
		printf("No se completó la venta por %d botellas de leche\n", ventas);
	}
}

void *hilos(void *i) {
	intptr_t t_id = (intptr_t) i;
	printf("Dentro del hilo %zd\n", t_id);
	int venta = 0;

	while (botesLeche > 0) {
		venta++;

		printf("Vendedor %zd intentando acceder a la venta #%d\n", t_id, venta);
		pthread_mutex_lock(&mutex);
		//printf("Mutex bloqueado por vendedor %zd\n", t_id);
		
		if (botesLeche > 0 && venta < 6) {
			venderLeche((intptr_t *)t_id);
			//printf("Mutex desbloqueado por vendedor %zd\n", t_id);
			printf("\n\t\t\t Botes de leche restantes = %d\n", botesLeche);
			pthread_mutex_unlock(&mutex);

			//printf("\n\nNúmero de venta = %d\n\n", venta);
		}
		else {
			printf("No se pudo, ya se hicieron 5 ventas\n");
			pthread_mutex_unlock(&mutex);
			//printf("Desbloqueado por vendedor %zd\n", t_id);
			
			//printf("\n\nNúmero de venta = %d\n\n", venta);
			printf("\n");
			venta = 0;
			pthread_exit(NULL);
		}
	}
}

int main(void) {
	srand(time(0));		//semilla para generar números aleatorios

	pthread_mutex_init(&mutex, NULL);
	//printf("Mutex creado por %p\n", (void *) &mutex);
	printf("\t\t\t Botes de leche restantes = %d\n", botesLeche);
	pthread_t thread[vendedores];

	int i;
	for (i = 0; i < vendedores; i++) {
		pthread_create(&thread[i], NULL, hilos, (void*) (intptr_t) (i+1));
	}

	for (i = 0; i < vendedores; i++) {
		pthread_join(thread[i], NULL);
	}


	printf("\n\nSe acabó la leche por hoy, por favor vuelva mañana\n");
}

