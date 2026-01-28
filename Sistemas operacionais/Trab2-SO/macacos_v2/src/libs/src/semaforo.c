#include "../include/semaforo.h"
#include <stdio.h>
#include <unistd.h>

static sem_t semaforo_ponte;
static sem_t mutex; // Protege variáveis compartilhadas
static sem_t gorila_na_ponte; // Exclusividade dos gorilas na ponte
static int direcao_atual = -1;
static int macacos_na_ponte = 0;
static int gorila_quer_atravessar = 0; // Flag indicando gorila esperando
static int max_macacos_na_ponte = 2;

void inicializar_semaforos() {
    sem_init(&semaforo_ponte, 0, max_macacos_na_ponte);
    sem_init(&mutex, 0, 1);
    sem_init(&gorila_na_ponte, 0, 1); // Somente um gorila na ponte por vez
}

void destruir_semaforos() {
    sem_destroy(&semaforo_ponte);
    sem_destroy(&mutex);
    sem_destroy(&gorila_na_ponte);
}

void travar_ponte_macaco(int direcao) {
    sem_wait(&mutex);
    
    // Macacos devem esperar se um gorila quiser atravessar ou estiver atravessando
    while (gorila_quer_atravessar) {
        sem_post(&mutex);
        sem_wait(&mutex);
    }

    // Se a direção está livre ou igual, macacos podem atravessar
    if (direcao_atual == -1 || direcao_atual == direcao) {
        direcao_atual = direcao;
    } else {
        // Espera até que todos os macacos na direção atual terminem
        while (macacos_na_ponte > 0) {
            sem_post(&mutex);
            sem_wait(&mutex);
        }
        direcao_atual = direcao;
    }

    macacos_na_ponte++;
    sem_post(&mutex);
    sem_wait(&semaforo_ponte);
}

void liberar_ponte_macaco() {
    sem_wait(&mutex);
    macacos_na_ponte--;

    // Se não há mais macacos na ponte, a direção é liberada
    if (macacos_na_ponte == 0) {
        direcao_atual = -1;
    }

    sem_post(&mutex);
    sem_post(&semaforo_ponte);
}

void travar_ponte_gorila(int direcao) {
    sem_wait(&mutex);

    // Gorila sinaliza que deseja atravessar
    gorila_quer_atravessar = 1;

    // Esperar até que todos os macacos tenham terminado
    while (macacos_na_ponte > 0) {
        sem_post(&mutex); // Liberar o mutex para permitir que macacos terminem
        usleep(1000); // Pausa curta para evitar busy-waiting
        sem_wait(&mutex); // Reobter o mutex para verificar a condição
    }

    // Gorila tem exclusividade sobre a ponte
    sem_post(&mutex); // Liberar o mutex antes de travar a ponte para o gorila
    sem_wait(&gorila_na_ponte); // Trava o uso exclusivo da ponte para o gorila

    // Define a direção da travessia
    sem_wait(&mutex);
    direcao_atual = direcao;
    sem_post(&mutex);
}

void liberar_ponte_gorila() {
    sem_post(&gorila_na_ponte); // Gorila termina a travessia
    sem_wait(&mutex);
    direcao_atual = -1; // Libera a direção da ponte
    gorila_quer_atravessar = 0; // Gorila não deseja mais atravessar
    sem_post(&mutex);
}
