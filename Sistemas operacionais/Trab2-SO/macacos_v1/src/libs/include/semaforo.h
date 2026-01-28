#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <semaphore.h>

/**
 * @file semaforo.h
 * @brief Declarações de funções para controle de semáforos na travessia de macacos.
 */

/**
 * @brief Inicializa os semáforos utilizados no controle da ponte.
 * 
 * Esta função deve ser chamada antes de qualquer operação de travessia.
 */
void inicializar_semaforos();

/**
 * @brief Destroi os semáforos utilizados no controle da ponte.
 * 
 * Esta função deve ser chamada após todas as operações de travessia terem sido concluídas.
 */
void destruir_semaforos();

/**
 * @brief Trava a ponte para a travessia de macacos em uma direção específica.
 * 
 * @param direcao A direção da travessia (0 para esquerda para direita, 1 para direita para esquerda).
 * 
 * Esta função garante que a ponte seja utilizada por macacos que se movem em uma única direção de cada vez.
 */
void travar_ponte(int direcao);

/**
 * @brief Libera a ponte após a travessia de um macaco.
 * 
 * Esta função deve ser chamada quando um macaco termina de atravessar a ponte.
 */
void liberar_ponte();

#endif /* SEMAFORO_H */