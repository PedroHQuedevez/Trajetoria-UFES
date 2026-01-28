#include "../include/macaco.h"
#include <stdio.h>

void iniciar_travessia(Macaco *macaco) {
    printf("Macaco %d INICIOU a travessia indo de %s.\n", 
            macaco->id, 
            macaco->direcao == ESQUERDA_PARA_DIREITA ? 
                            "ESQUERDA para DIREITA" : 
                            "DIREITA para ESQUERDA"
        );
}

void finalizar_travessia(Macaco *macaco) {
    printf("Macaco %d TERMINOU a travessia.\n", macaco->id);
}
