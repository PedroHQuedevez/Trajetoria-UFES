#include <stdio.h>
#include <stdlib.h>
#include "tDocumento.h"

struct tDocumento
{
    void *dado;
    func_ptr_imprimeNaTela imprimeNaTela;
    func_ptr_imprimeEmArquivo ImprimeEmArquivo;
    func_ptr_desaloca desaloca;
};

tDocumento *criaDocumento(void *dado, func_ptr_imprimeNaTela imprimeNaTela,
                          func_ptr_imprimeEmArquivo ImprimeEmArquivo,
                          func_ptr_desaloca desaloca)
{
    tDocumento *doc = (tDocumento *)calloc(1, sizeof(tDocumento));
    doc->dado = dado;
    doc->desaloca = desaloca;
    doc->ImprimeEmArquivo = ImprimeEmArquivo;
    doc->imprimeNaTela = imprimeNaTela;
    return doc;
}

void desalocaDocumento(tDocumento *doc)
{
    doc->desaloca(doc->dado);
    free(doc);
}

void imprimeNaTelaDocumento(tDocumento *doc)
{

    doc->imprimeNaTela(doc->dado);
}

void imprimeEmArquivoDocumento(tDocumento *doc, char *path)
{
    doc->ImprimeEmArquivo(doc->dado, path);
}