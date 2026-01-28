#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "paciente.h"
#include "lesoes.h"
#include"dadospaciente.h"
#include "clinica.h"


int main(int argc, char *argv[ ]) {

cria_pastas();

tclinica *clinica;

clinica = construir_clinica();

ler_clinica(clinica,argv[1]);



return 0;
}















