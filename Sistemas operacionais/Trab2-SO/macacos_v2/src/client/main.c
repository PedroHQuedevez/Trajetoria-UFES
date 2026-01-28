#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libs/include/macaco.h"
#include "../libs/include/semaforo.h"

#define NUM_MACACOS 10
#define NUM_GORILAS 2

void *macaco_thread(void *arg) {
    Macaco *macaco = (Macaco *)arg;

    travar_ponte_macaco(macaco->direcao);
    iniciar_travessia_macaco(macaco);
    sleep(1); // Simula tempo de travessia
    finalizar_travessia_macaco(macaco);
    liberar_ponte_macaco();

    return NULL;
}

void *gorila_thread(void *arg) {
    Gorila *gorila = (Gorila *)arg;

    travar_ponte_gorila(gorila->direcao);
    iniciar_travessia_gorila(gorila);
    sleep(2); // Simula tempo de travessia, gorilas são mais lentos
    finalizar_travessia_gorila(gorila);
    liberar_ponte_gorila();

    return NULL;
}

int main() {
    pthread_t threads_macacos[NUM_MACACOS];
    pthread_t threads_gorilas[NUM_GORILAS];
    Macaco macacos[NUM_MACACOS];
    Gorila gorilas[NUM_GORILAS] = {{1, ESQUERDA_PARA_DIREITA}, {2, DIREITA_PARA_ESQUERDA}};

    inicializar_semaforos();

    // Cria threads para macacos
    for (int i = 0; i < NUM_MACACOS; i++) {
        macacos[i].id = i + 1;
        macacos[i].direcao = (i < NUM_MACACOS / 2) ? ESQUERDA_PARA_DIREITA : DIREITA_PARA_ESQUERDA;
        pthread_create(&threads_macacos[i], NULL, macaco_thread, &macacos[i]);
    }

    // Cria threads para gorilas
    for (int i = 0; i < NUM_GORILAS; i++) 
        pthread_create(&threads_gorilas[i], NULL, gorila_thread, &gorilas[i]);
    
    // Espera as threads dos macacos terminarem
    for (int i = 0; i < NUM_MACACOS; i++)
        pthread_join(threads_macacos[i], NULL);

    // Espera as threads dos gorilas terminarem
    for (int i = 0; i < NUM_GORILAS; i++)
        pthread_join(threads_gorilas[i], NULL);

    destruir_semaforos();

    return 0;
}
