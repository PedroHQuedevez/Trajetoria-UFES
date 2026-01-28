#if !defined(PROCESS_MANAGER_H_)
#define PROCESS_MANAGER_H_

#include <stdbool.h>

/**
 * @brief Executa um comando no shell.
 *
 * Esta função cria um novo processo para executar o comando fornecido.
 * Se o comando deve ser executado em primeiro plano, a função espera
 * até que o comando termine. Caso contrário, o comando é executado em
 * segundo plano.
 *
 * @param command O comando a ser executado.
 * @param is_foreground Indica se o comando deve ser executado em primeiro plano.
 */
void execute_command(char *command, bool is_foreground);

/**
 * @brief Espera por processos zumbis.
 *
 * Esta função verifica se há processos filhos que terminaram a execução
 * e ainda não foram coletados (processos zumbis) e os coleta.
 */
void wait_for_zombies();

/**
 * @brief Termina o shell.
 *
 * Esta função encerra a execução do shell, imprimindo uma mensagem
 * de término e chamando exit.
 */
void terminate_shell();

#endif // PROCESS_MANAGER_H_