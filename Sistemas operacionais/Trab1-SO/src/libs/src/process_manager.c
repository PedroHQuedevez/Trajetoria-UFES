#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#include "../include/process_manager.h"

#define MAX_ARGS 3
#define MAX_COMMANDS 5

pid_t child_pids[MAX_COMMANDS];  // Armazena PIDs dos processos filhos
int child_count = 0;  // Contador de processos filhos


void execute_command(char *command, bool is_foreground) {
    char *args[MAX_ARGS + 1];
    int arg_count = 0;

    // Divide o comando em argumentos
    char *token = strtok(command, " ");
    while (token != NULL && arg_count < MAX_ARGS) {
        args[arg_count++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL;

    pid_t pid = fork();
    if (pid < 0)
        return perror("fork");

    if (pid == 0) {
        // Processo filho
        signal(SIGINT, SIG_IGN);  // Ignora SIGINT no processo filho
        if (execvp(args[0], args) < 0) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        // Processo pai
        child_pids[child_count++] = pid;

        if (is_foreground) {
            waitpid(pid, NULL, 0);
        } else {
            // Cria um processo secundário em background
            pid_t pid2 = fork();
            if (pid2 < 0) 
                return perror("fork");
            
            if (pid2 == 0) {
                // Processo secundário
                waitpid(pid, NULL, 0);
                exit(EXIT_SUCCESS);
            } else {
                child_pids[child_count++] = pid2;
            }
        }
    }
}

void wait_for_zombies() {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

void terminate_shell() {
    printf("Terminating shell...\n");
    exit(EXIT_SUCCESS);
}
