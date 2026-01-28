#if !defined(_INTERNAL_COMMANDS_H_)
#define _INTERNAL_COMMANDS_H_

/**
 * @brief Processa um comando interno.
 *
 * Esta função recebe um comando interno como entrada e executa a ação
 * correspondente. Comandos suportados incluem "waitall" para esperar
 * por todos os processos filhos e "die" para matar todos os processos filhos.
 *
 * @param command O comando interno a ser processado.
 */
void process_internal_command(char *command);

#endif // _INTERNAL_COMMANDS_H_