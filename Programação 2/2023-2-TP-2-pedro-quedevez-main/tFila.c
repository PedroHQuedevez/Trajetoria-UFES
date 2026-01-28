#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "tFila.h"
#include "tDocumento.h"

struct tFila
{
    tDocumento **fila;
    int size;
};

tFila *criaFila()
{
    tFila *fila = (tFila *)calloc(1, sizeof(tFila));
    return fila;
}

void desalocaFila(tFila *f)
{
    for (int i = 0; i < f->size; i++)
    {
        if (f->fila[i] != NULL)
        {
            tDocumento *d = f->fila[i];
            desalocaDocumento(d);
        }
    }
    free(f->fila);
    free(f);
}

void insereDocumentoFila(tFila *f, void *dado, func_ptr_imprimeNaTela imprimeNaTela,
                         func_ptr_imprimeEmArquivo ImprimeEmArquivo,
                         func_ptr_desaloca desaloca)
{
    f->size++;
    f->fila = (tDocumento **)realloc(f->fila, sizeof(tDocumento *) * f->size);
    f->fila[f->size - 1] = criaDocumento(dado, imprimeNaTela, ImprimeEmArquivo, desaloca);
}

int quantidadeDocumentosNaFila(tFila *f)
{
    return f->size;
}

void imprimeFila(tFila *f, char *path)
{
    for (int i = 0; i < f->size; i++)
    {
        if (f->fila[i] != NULL)
        {
            tDocumento *d = f->fila[i];
            imprimeNaTelaDocumento(d);
            imprimeEmArquivoDocumento(d, path);
        }
    }
}