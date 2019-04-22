/**
 * Programa que conterá 6 opções:
 *  0 - Sair
 *  1 - Pausar um processo
 *  2 - Reiniciar um processo pausado
 *  3 - Finalizar um processo
 *  4 - Iniciar um processo em um processador
 *  5 - Mudar a prioridade um processo
*/

#define _GNU_SOURCE
#include <sched.h>

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

#include <sys/time.h>     // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <sys/resource.h>

void menuOpcoes() {
    printf("Escolha uma opção:\n");
    printf(" 0 - Sair\n 1 - Pausar um processo\n 2 - Reiniciar um processo pausado\n 3 - Finalizar um processo\n 4 - Mudar o processador do processo atual\n 5 - Mudar a prioridade um processo\n\n");
}

int main() {
    int opcao;
    int processo;

    while(1) {
        menuOpcoes();
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                exit(0);    
            case 1:
                printf("Informe o número do processo:\n");
                scanf("%d", &processo);

                kill(processo, SIGSTOP); //Interropendo o processo.

                break;
            case 2:
                printf("Informe o número do processo:\n");
                scanf("%d", &processo);

                kill(processo, SIGCONT); //Continuando o processo parado.
                
                break;
            case 3:
                printf("Informe o número do processo:\n");
                scanf("%d", &processo);

                kill(processo, SIGKILL); //Continuando o processo parado.

                break;
            case 4: {
                // Forçar o processo iniciar em um processador.
                
                int processador;

                printf("Informe o número do processo:\n");
                scanf("%d", &processo);

                printf("Informe o número do processador:\n");
                scanf("%d", &processador);

                cpu_set_t my_set;        /* Define your cpu_set bit mask. */
                CPU_ZERO(&my_set);       /* Initialize it all to 0, i.e. no CPUs selected. */
                
                //CPU_SET(7, &my_set);
                CPU_SET(processador, &my_set);
                
                sched_setaffinity(processo, sizeof(cpu_set_t), &my_set); /* Set affinity of this process to */
                                                                  /* the defined mask, i.e. only 7. */
                break;
            } case 5: {
                // Mudar a prioridade de um processo.
                int prioridade;

                printf("Informe o número do processo:\n");
                scanf("%d", &processo);

                printf("Informe a prioridade do processo:\n");
                scanf("%d", &prioridade);

                setpriority(PRIO_PROCESS, processo, prioridade);
                break;
            } default:
                printf("Opção inválida, por favor escolha outra!");
                break;
        }


    }

    return 0;
}