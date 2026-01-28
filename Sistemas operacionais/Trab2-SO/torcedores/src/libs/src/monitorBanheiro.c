#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/monitorBanheiro.h"

#define MAX_NO_BANHEIRO 3

// Inicializa o mutex e as variáveis de condição
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_corintianos = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_palmeirenses = PTHREAD_COND_INITIALIZER;

int num_corintianos = 0;
int num_palmeirenses = 0;

void corintiano_quer_entrar()
{
    pthread_mutex_lock(&mutex);

    // Espera enquanto houver palmeirenses no banheiro ou o número máximo de corintianos for atingido
    while (num_palmeirenses > 0 || (num_corintianos + 1) > MAX_NO_BANHEIRO)
        pthread_cond_wait(&cond_corintianos, &mutex);

    num_corintianos++;
    printf("Numero de corintianos no banheiro: %d\n", num_corintianos);
    printf("Numero de palmeirenses no banheiro: %d\n", num_palmeirenses);
    pthread_mutex_unlock(&mutex);
}

void corintiano_sai()
{
    pthread_mutex_lock(&mutex);
    num_corintianos--;

    // Se não houver mais corintianos no banheiro, sinaliza para os palmeirenses que podem entrar
    if (num_corintianos == 0)
        pthread_cond_broadcast(&cond_palmeirenses);

    // Sinaliza para outros corintianos que podem entrar
    pthread_cond_broadcast(&cond_corintianos);
    pthread_mutex_unlock(&mutex);
}

void palmeirense_quer_entrar()
{
    pthread_mutex_lock(&mutex);

    // Espera enquanto houver corintianos no banheiro ou o número máximo de palmeirenses for atingido
    while (num_corintianos > 0 || (num_palmeirenses + 1) > MAX_NO_BANHEIRO)
        pthread_cond_wait(&cond_palmeirenses, &mutex);

    num_palmeirenses++;
    printf("Numero de corintianos no banheiro: %d\n", num_corintianos);
    printf("Numero de palmeirenses no banheiro: %d\n", num_palmeirenses);
    pthread_mutex_unlock(&mutex);
}

void palmeirense_sai()
{
    pthread_mutex_lock(&mutex);
    num_palmeirenses--;

    // Se não houver mais palmeirenses no banheiro, sinaliza para os corintianos que podem entrar
    if (num_palmeirenses == 0)
        pthread_cond_broadcast(&cond_corintianos);

    // Sinaliza para outros palmeirenses que podem entrar
    pthread_cond_broadcast(&cond_palmeirenses);
    pthread_mutex_unlock(&mutex);
}
