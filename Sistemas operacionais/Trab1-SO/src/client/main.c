#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../libs/include/process_manager.h"
#include "../libs/include/signal_handler.h"
#include "../libs/include/internal_commands.h"

#define MAX_COMMANDS 5
#define MAX_PATH_LENGTH 1024

int main(int argc, char *argv[])
{
    char input[MAX_PATH_LENGTH];
    char cwd[MAX_PATH_LENGTH]; // Buffer para armazenar o diretório atual
    char *commands[MAX_COMMANDS];
    int command_count = 0;

    // Configurar signal handlers
    struct sigaction sa_int;
    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    struct sigaction sa_tstp;
    sa_tstp.sa_handler = handle_sigtstp;
    sigemptyset(&sa_tstp.sa_mask);
    sa_tstp.sa_flags = 0;
    sigaction(SIGTSTP, &sa_tstp, NULL);

    while (1)
    {
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s fsh> ", cwd); // Exibe o diretório atual antes do prompt
        }
        else
        {
            perror("getcwd");
            printf("fsh> ");
        }

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            perror("fgets");
            continue;
        }

        input[strcspn(input, "\n")] = 0;

        // Checa se há comandos internos
        if (strcmp(input, "waitall") == 0 || strcmp(input, "die") == 0)
        {
            process_internal_command(input);
            continue;
        }

        // Divide os comandos separados por #
        command_count = 0;
        char *token = strtok(input, "#");
        while (token != NULL && command_count < MAX_COMMANDS)
        {
            commands[command_count++] = token;
            token = strtok(NULL, "#");
        }

        // Executa os comandos, o primeiro em foreground e os demais em background
        for (int i = 0; i < command_count; i++)
            execute_command(commands[i], i == 0);

        // Espera pelo processo em foreground terminar
        if (command_count > 0)
            wait(NULL); // NULL para esperar por qualquer processo filho
    }

    return 0;
}
