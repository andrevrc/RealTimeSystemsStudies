#include <iostream>
#include <cstdlib>

#include "../../BlackGPIO/BlackGPIO.h"
#include "../../ADC/Adc.h"
#include "../../PWM/PWM.h"
#include <unistd.h>
#include <pthread.h>
#include <sys/resource.h>

using namespace BlackLib;

int prioridadeThreads[2] = {0, 0};
pthread_mutex_t mutex[2] = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER};

void carga(int n = 1000); //Função para durar mais ou menos 1 segundo.

void* execucaoThread(void *idThread, void *l);

int main(int argc, char *argv[]){
    pthread_t tarefa1, tarefa2;

    ADC potenciometro1 = ADC(AIN0); // Potenciômetro responsável pela prioridade da Thread tarefa1.
    ADC potenciometro2 = ADC(AIN1); // Potenciômetro responsável pela prioridade da Thread tarefa2.

    BlackGPIO led1 = BlackGPIO(GPIO_48, output); // Led relacionado a Thread tarefa1.
    BlackGPIO led2 = BlackGPIO(GPIO_51, output); // Led relacionado a Thread tarefa2.

    pthread_create(&tarefa1, NULL, execucaoThread, 1, led1);
    pthread_create(&tarefa1, NULL, execucaoThread, 2, led2);

    // Laço infinito para ler e setar a prioridade.
    while(1) {
        // Setando prioridade para tarefa1.
        pthread_mutex_lock(&mutex[0]);
        prioridadeThreads[0] = 19 * potenciometro1.getPercentValue()/100;
        pthread_mutex_unlock(&mutex[0]);

        // Setando prioridade para tarefa2.
        pthread_mutex_lock(&mutex[1]);
        prioridadeThreads[1] = 19 * potenciometro2.getPercentValue()/100;
        pthread_mutex_unlock(&mutex[1]);

        sleep(1);
    }

    return 0;
}

// Função que demora aproximadamente 1 segundo.
void* carga(int n = 1000) {
    int i, j;
    double soma = 0.0;
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            soma += (double) 0.9*0.9*(1.0/3) - 0.27;
        }
    }
}

void* execucaoThread(void *idThread, void *l) {
    int thread = idThread - 1; //Foi passado 1 e 2, porém isso será usado para acesso aos vetores, por isso subtrai-se 1.
    BlackGPIO led = l;

    while (1) {
        // Lendo a prioridade
        pthread_mutex_lock(&mutex[thread]);
        setpriority(PRIO_PROCESS, 0, prioridadeThreads[thread]);
        pthread_mutex_unlock(&mutex[thread]);

        printf("Prioridade da tarefa %d: %d\n\n", thread+1, getpriority(PRIO_PROCESS, 0));

        led.setValue(high);
        carga(4000);
        led.setValue(low);
        carga(4000);       
    }
}