#include "../include/macaco.h"
#include <stdio.h>

void iniciar_travessia_macaco(Macaco *macaco) {
    printf("Macaco %d INICIOU a travessia indo de %s.\n", 
            macaco->id, 
            macaco->direcao == ESQUERDA_PARA_DIREITA ? 
                            "ESQUERDA para DIREITA" : 
                            "DIREITA para ESQUERDA"
        );
}

void finalizar_travessia_macaco(Macaco *macaco) {
    printf("Macaco %d TERMINOU a travessia.\n", macaco->id);
}

// Funções de travessia dos gorilas
void iniciar_travessia_gorila(Gorila *gorila) {
    printf("Gorila %d INICIOU a travessia indo de %s.\n", 
            gorila->id,
            gorila->direcao == ESQUERDA_PARA_DIREITA ? 
                            "ESQUERDA para DIREITA" : 
                            "DIREITA para ESQUERDA"
    );
}

void finalizar_travessia_gorila(Gorila *gorila) {
    printf("Gorila %d TERMINOU a travessia.\n", gorila->id);
}
