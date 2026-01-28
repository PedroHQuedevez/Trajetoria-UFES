#ifndef MACACO_H
#define MACACO_H

#include <pthread.h>


/**
 * @enum Direcao
 * @brief Enumeração para representar a direção da travessia.
 */
typedef enum {
    ESQUERDA_PARA_DIREITA, /**< Travessia da esquerda para a direita */
    DIREITA_PARA_ESQUERDA  /**< Travessia da direita para a esquerda */
} Direcao;

/**
 * @struct Macaco
 * @brief Estrutura que representa um macaco.
 */
typedef struct {
    int id;         /**< Identificador do macaco */
    Direcao direcao; /**< Direção da travessia */
} Macaco;

/**
 * @brief Inicia a travessia de um macaco.
 * 
 * @param macaco Ponteiro para a estrutura Macaco.
 */
void iniciar_travessia(Macaco *macaco);

/**
 * @brief Finaliza a travessia de um macaco.
 * 
 * @param macaco Ponteiro para a estrutura Macaco.
 */
void finalizar_travessia(Macaco *macaco);

#endif /* MACACO_H */