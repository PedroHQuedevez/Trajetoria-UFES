#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include "../include/internal_commands.h"
#include "../include/process_manager.h"

extern pid_t child_pids[];
extern int child_count;


void process_internal_command(char *command) {
    if (strcmp(command, "waitall") == 0) {
        wait_for_zombies(); // Espera por todos os processos filhos
    } else if (strcmp(command, "die") == 0) {
        for (int i = 0; i < child_count; i++)
            kill(child_pids[i], SIGKILL); // Mata todos os processos filhos
        terminate_shell();
    } else {
        printf("Unknown internal command: %s\n", command);
    }
}
