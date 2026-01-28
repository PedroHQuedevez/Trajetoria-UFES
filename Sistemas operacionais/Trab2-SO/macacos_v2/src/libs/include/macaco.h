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
 * @struct Gorila
 * @brief Estrutura que representa um gorila.
 */
typedef struct {
    int id;         /**< Identificador do gorila */
    Direcao direcao; /**< Direção da travessia */
} Gorila;

/**
 * @brief Inicia a travessia de um macaco.
 * 
 * @param macaco Ponteiro para a estrutura Macaco.
 */
void iniciar_travessia_macaco(Macaco *macaco);

/**
 * @brief Finaliza a travessia de um macaco.
 * 
 * @param macaco Ponteiro para a estrutura Macaco.
 */
void finalizar_travessia_macaco(Macaco *macaco);

/**
 * @brief Inicia a travessia de um gorila.
 * 
 * @param gorila Ponteiro para a estrutura Gorila.
 */
void iniciar_travessia_gorila(Gorila *gorila);

/**
 * @brief Finaliza a travessia de um gorila.
 * 
 * @param gorila Ponteiro para a estrutura Gorila.
 */
void finalizar_travessia_gorila(Gorila *gorila);

#endif /* MACACO_H */