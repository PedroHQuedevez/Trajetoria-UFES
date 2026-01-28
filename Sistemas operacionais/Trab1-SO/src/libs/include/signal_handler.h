#if !defined(_SIGNAL_HANDLER_H_)
#define _SIGNAL_HANDLER_H_

/**
 * @brief Manipulador para o sinal SIGINT.
 *
 * Esta função é chamada quando o sinal SIGINT é recebido. Ela verifica
 * se há processos filhos vivos e pergunta ao usuário se deseja terminar
 * o shell. Se o usuário confirmar, todos os processos filhos são finalizados
 * e o shell é encerrado.
 *
 * @param sig O número do sinal recebido (deve ser SIGINT).
 */
void handle_sigint(int sig);

/**
 * @brief Manipulador para o sinal SIGTSTP.
 *
 * Esta função é chamada quando o sinal SIGTSTP é recebido. Ela suspende
 * todos os processos filhos do shell.
 *
 * @param sig O número do sinal recebido (deve ser SIGTSTP).
 */
void handle_sigtstp(int sig);

#endif // _SIGNAL_HANDLER_H_