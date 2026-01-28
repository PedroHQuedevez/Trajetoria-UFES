#ifndef MONITOR_BANHEIRO_H
#define MONITOR_BANHEIRO_H

#include <pthread.h>

/**
 * @file monitorBanheiro.h
 * @brief Declarações de funções para controle de acesso ao banheiro por corintianos e palmeirenses.
 */

/**
 * @brief Função chamada quando um corintiano quer entrar no banheiro.
 * 
 * Esta função bloqueia a entrada de corintianos se houver palmeirenses no banheiro ou se o número máximo de corintianos no banheiro for atingido.
 */
void corintiano_quer_entrar();

/**
 * @brief Função chamada quando um corintiano sai do banheiro.
 * 
 * Esta função atualiza o número de corintianos no banheiro e sinaliza para outros corintianos ou palmeirenses que o banheiro está disponível.
 */
void corintiano_sai();

/**
 * @brief Função chamada quando um palmeirense quer entrar no banheiro.
 * 
 * Esta função bloqueia a entrada de palmeirenses se houver corintianos no banheiro ou se o número máximo de palmeirenses no banheiro for atingido.
 */
void palmeirense_quer_entrar();

/**
 * @brief Função chamada quando um palmeirense sai do banheiro.
 * 
 * Esta função atualiza o número de palmeirenses no banheiro e sinaliza para outros palmeirenses ou corintianos que o banheiro está disponível.
 */
void palmeirense_sai();

#endif /* MONITOR_BANHEIRO_H */