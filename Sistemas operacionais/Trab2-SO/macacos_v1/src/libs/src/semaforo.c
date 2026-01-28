#include "../include/semaforo.h"
#include <stdio.h>

static sem_t semaforo_ponte;
static sem_t mutex; // Controla o acesso à variável de contagem de macacos
static int direcao_atual = -1; // -1 indica que a ponte está livre para qualquer direção
static int macacos_na_ponte = 0;
static int max_macacos_na_ponte = 2; // Número máximo de macacos que podem atravessar ao mesmo tempo

void inicializar_semaforos() {
    sem_init(&semaforo_ponte, 0, max_macacos_na_ponte); // Inicializa com o número máximo de macacos
    sem_init(&mutex, 0, 1); // Mutex para proteger variáveis compartilhadas
}

void destruir_semaforos() {
    sem_destroy(&semaforo_ponte);
    sem_destroy(&mutex);
}

void travar_ponte(int direcao) {
    sem_wait(&mutex); // Protege as variáveis compartilhadas

    // Se a ponte estiver livre ou na mesma direção, continua
    if (direcao_atual == -1 || direcao_atual == direcao) {
        direcao_atual = direcao; // Define a direção atual se a ponte estiver livre
    } else {
        // Espera até que os macacos da direção oposta saiam da ponte
        while (macacos_na_ponte > 0) {
            sem_post(&mutex); // Libera o mutex para outros threads
            sem_wait(&mutex); // Aguarda a liberação da ponte
        }
        direcao_atual = direcao; // Atualiza a direção após esvaziar a ponte
    }

    macacos_na_ponte++; // Incrementa o número de macacos na ponte
    sem_post(&mutex); // Libera o mutex
    sem_wait(&semaforo_ponte); // Travando a ponte com base no número máximo permitido
}

void liberar_ponte() {
    sem_wait(&mutex); // Protege as variáveis compartilhadas
    macacos_na_ponte--; // Um macaco saiu da ponte
    if (macacos_na_ponte == 0)
        direcao_atual = -1; // Libera a ponte para qualquer direção
    
    sem_post(&mutex); // Libera o mutex
    sem_post(&semaforo_ponte); // Libera uma "vaga" na ponte
}
