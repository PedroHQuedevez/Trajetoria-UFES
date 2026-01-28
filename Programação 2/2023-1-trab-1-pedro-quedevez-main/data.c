#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "data.h"
#include "dadospaciente.h"
struct data {
    int dia;
    int mes;
    int ano;
};



tdata converte_data (char* data_paciente) {
    tdata data;
    sscanf(data_paciente, "%d/%d/%d", &data.dia, &data.mes, &data.ano);
    return data;
}



int calcular_idade (char *data_paciente,char *data_atual) {
tdata data_nascimento;
data_nascimento = converte_data(data_paciente);
tdata data_atendimento;
data_atendimento = converte_data(data_atual);


int idade;
    idade = data_atendimento.ano - data_nascimento.ano;

    if (data_atendimento.mes < data_nascimento.mes ||
        (data_atendimento.mes == data_nascimento.mes && data_atendimento.dia < data_nascimento.dia)) {
        idade--;
    }

    return idade;
}







