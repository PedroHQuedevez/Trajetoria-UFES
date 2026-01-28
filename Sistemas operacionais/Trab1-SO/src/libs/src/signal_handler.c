#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "../include/signal_handler.h"
#include "../include/process_manager.h"

extern pid_t child_pids[];
extern int child_count;


void handle_sigint(int sig) {
    sigset_t block_mask;
    sigfillset(&block_mask);
    sigprocmask(SIG_BLOCK, &block_mask, NULL); // Bloqueia sinais

    // Verifica se há processos filhos vivos
    bool has_live_children = false;
    for (int i = 0; i < child_count; i++) {
        if (kill(child_pids[i], 0) == 0) {
            has_live_children = true;
            break;
        }
    }

    if (has_live_children) {
        printf("\nSIGINT received. Do you want to terminate the shell? (y/n): ");
        char response = getchar();
        if (response == 'y' || response == 'Y') {
            // Finaliza todos os processos filhos
            for (int i = 0; i < child_count; i++) 
                kill(child_pids[i], SIGKILL);
            terminate_shell();
        }
    } else {
        // Se não houver processos filhos, finaliza o shell imediatamente
        terminate_shell();
    }
    sigprocmask(SIG_UNBLOCK, &block_mask, NULL); // Desbloqueia sinais
}

void handle_sigtstp(int sig) {
    printf("\nSIGTSTP received. Suspending all child processes...\n");
    for (int i = 0; i < child_count; i++) 
        kill(child_pids[i], SIGTSTP);
}
