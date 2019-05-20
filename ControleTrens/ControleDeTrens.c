#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 

sem_t semaforo;

pthread_mutex_t mutexL2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexL3 = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t mutexL4 = PTHREAD_MUTEX_INITIALIZER;

void l1(int idTrem);
void l2(int idTrem);
void l3(int idTrem);
void l4(int idTrem);
void l5(int idTrem);
void l6(int idTrem);

void* t1();
void* t2();
void* t3();

int main(int argc, char *argv[]) {
    //Criando um semáforo.
    sem_init(&semaforo, 0, 2);

    pthread_t trem1, trem2, trem3;
    
    pthread_create(&trem1, NULL, t1, NULL);
    pthread_create(&trem1, NULL, t2, NULL);
    pthread_create(&trem1, NULL, t3, NULL);

    pthread_join(trem1,NULL); 
	pthread_join(trem2,NULL); 
    pthread_join(trem3,NULL); 
	sem_destroy(&semaforo); 

    return 0;
}

void* t1() {
    while(1) {
        l1(1);
        sleep(1);

        sem_wait(&semaforo); 
        
        pthread_mutex_lock(&mutexL2);
        l2(1);
        sleep(1);

        pthread_mutex_lock(&mutexL3);
        pthread_mutex_unlock(&mutexL2);
        
        l3(1);
        sleep(1);
        pthread_mutex_unlock(&mutexL3);

        sem_post(&semaforo); 
    }
}

void* t2() {
    while(1) {
        l5(2);
        sleep(2);

        sem_wait(&semaforo); 

        pthread_mutex_lock(&mutexL4);        
        l4(2);
        sleep(2);

        pthread_mutex_lock(&mutexL2);
        pthread_mutex_unlock(&mutexL4);
        
        l2(2);
        sleep(2);
        pthread_mutex_unlock(&mutexL2);
        
        sem_post(&semaforo); 
    }
}

void* t3() {
    while(1) {
        l6(3);
        sleep(3);

        sem_wait(&semaforo); 
        
        pthread_mutex_lock(&mutexL3);
        l3(3);
        sleep(3);

        pthread_mutex_lock(&mutexL4);
        pthread_mutex_unlock(&mutexL3);
        
        l4(3);
        sleep(3);
        pthread_mutex_unlock(&mutexL4);
        
        sem_post(&semaforo); 
    }
}

void l1(int idTrem) {
    printf("O trem %d está no trecho 1!!!\n\n", idTrem);
}

void l2(int idTrem) {
    printf("O trem %d está no trecho 2!!!\n\n", idTrem);
}

void l3(int idTrem) {
    printf("O trem %d está no trecho 3!!!\n\n", idTrem);
}

void l4(int idTrem) {
    printf("O trem %d está no trecho 4!!!\n\n", idTrem);
}

void l5(int idTrem) {
    printf("O trem %d está no trecho 5!!!\n\n", idTrem);
}

void l6(int idTrem) {
    printf("O trem %d está no trecho 6!!!\n\n", idTrem);
}