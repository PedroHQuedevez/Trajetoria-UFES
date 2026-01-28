#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "../libs/include/monitorBanheiro.h"

volatile int continuar = 1; // Variável global para controlar a execução das threads

void *thread_corintiano(void *arg)
{
    int id = *(int *)arg;
    while (continuar)
    {
        corintiano_quer_entrar();
        printf("Eu sou corintiano-%d: ... UFA! Entrei no banheiro!\n", id);
        sleep(3);

        corintiano_sai();
        printf("Eu sou corintiano-%d: ... Estou aliviado! Vou trabalhar!\n", id);
        sleep(5);
    }
    return NULL;
}

void *thread_palmeirense(void *arg)
{
    int id = *(int *)arg;
    while (continuar)
    {
        palmeirense_quer_entrar();
        printf("Eu sou palmeirense-%d: ... UFA! Entrei no banheiro!\n", id);
        sleep(3);

        palmeirense_sai();
        printf("Eu sou palmeirense-%d: ... Estou aliviado! Vou trabalhar!\n", id);
        sleep(5);
    }
    return NULL;
}

int main()
{
    pthread_t corintianos[10], palmeirenses[10];
    int ids[20];

    for (int i = 0; i < 10; i++)
    {
        ids[i] = i + 1;
        pthread_create(&corintianos[i], NULL, thread_corintiano, &ids[i]);
        ids[i + 10] = i + 1;
        pthread_create(&palmeirenses[i], NULL, thread_palmeirense, &ids[i + 10]);

        sleep((i + 10) % 4); // o tamanho do sleep varia nesta ordem 2 3 0 1 2 3 0 1 2 3
    }

    continuar = 0; // Sinalize para as threads pararem

    for (int i = 0; i < 10; i++)
        pthread_join(corintianos[i], NULL); // Aguarde as threads terminarem

    for (int i = 0; i < 10; i++)
        pthread_join(palmeirenses[i], NULL);

    return 0;
}
