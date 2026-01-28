#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libs/include/macaco.h"
#include "../libs/include/semaforo.h"

#define NUM_MACACOS 10

void *macaco_thread(void *arg) {
    Macaco *macaco = (Macaco *)arg;

    // Macaco tenta atravessar
    travar_ponte(macaco->direcao);
    iniciar_travessia(macaco);
    sleep(1); // Simula o tempo de travessia
    finalizar_travessia(macaco);
    liberar_ponte();

    return NULL;
}

int main() {
    pthread_t threads[NUM_MACACOS];
    Macaco macacos[NUM_MACACOS];

    // Inicializa os semáforos
    inicializar_semaforos();

    // Cria macacos e distribui nas duas margens
    for (int i = 0; i < NUM_MACACOS; i++) {
        macacos[i].id = i + 1;
        macacos[i].direcao = (i < NUM_MACACOS / 2) ? ESQUERDA_PARA_DIREITA : DIREITA_PARA_ESQUERDA;
        pthread_create(&threads[i], NULL, macaco_thread, &macacos[i]);
    }

    // Espera todas as threads terminarem
    for (int i = 0; i < NUM_MACACOS; i++) 
        pthread_join(threads[i], NULL);
    
    // Destroi os semáforos
    destruir_semaforos();
    
    return 0;
}
