#include<pthread.h>
#include <stdio.h>
#include <stdlib.h>

//Variables globales para todos los hilos
int numeroHilos;
int numeroElementos;
double sumaTotal=0.0;
pthread_mutex_t mutex;
pthread_mutexattr_t atributos;

void* producirElementos (void* id){
long miId=(long) id;

int miN=numeroElementos/numeroHilos;
int miInicio=miId*miN;
int miFinal=miInicio+miN;
double  miSuma=0.0;
double signo;


    signo=1.0;
    int e;

void* factorial(long a) {
		long b=1;
		for(int i=1; i<b; i++) {
			b=b*i;
		}
		return b;
	}

    for( e=miInicio; e<miFinal;e++){
        miSuma=miSuma+signo/factorial(e);
    }

    pthread_mutex_lock(&mutex);//toma el mutex, para garantizar la exclusión mutua
//Esta es la regiòn crítica del programa
    sumaTotal=sumaTotal+miSuma;

    pthread_mutex_unlock(&mutex); //este método  inicializa un mutex
    pthread_exit(NULL);

}//producir Elementos()

int main(int argc, char* argv[]){
    numeroHilos=strtol(argv[1], NULL, 10);
    numeroElementos=strtol(argv[2], NULL, 10);

    pthread_t *hilos;
    //printf("%d", sizeof(pthread_t));
    hilos= malloc(numeroHilos*sizeof(pthread_t));  //malloc permite reservar memoria(memory allocation)
    long h;


    for( h=0; h<numeroHilos;h++)
        pthread_create(&hilos[h], NULL, producirElementos, (void*) h);

    for( h=0; h<numeroHilos;h++)
        pthread_join(hilos[h], NULL);

    printf("El valor estimado de e es: %.15f", (4*sumaTotal));

    free(hilos); //libera la memoria reservada para hilos con malloc
    return 0;




}//main

