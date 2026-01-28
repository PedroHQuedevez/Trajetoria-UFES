#ifndef _TENCAMINHAMENTO_H
#define _TENCAMINHAMENTO_H

typedef struct Encaminhamento tEncaminhamento;

tEncaminhamento *CriaEncaminhamento(char *nomePaciente, char *cpfPaciente, char *especialidade,
                                    char *motivo, char *nomeMedico, char *CRM, char *data);

void DesalocaEncaminhamento(void *dado);

void ImprimeNaTelaEncaminhamento(void *dado);

void ImprimeEmArquivoEncaminhamento(void *dado, char *path);

#endif