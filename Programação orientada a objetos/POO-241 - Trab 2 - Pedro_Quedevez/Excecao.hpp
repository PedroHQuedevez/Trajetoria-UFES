#ifndef EXCECAO_HPP
#define EXCECAO_HPP

#include <exception>
#include <iostream>
#include <string>

using namespace std;

class Excecao : public exception
{
private:
    string mensagem;

public:
    Excecao(string mensagem)
    {
        this->mensagem = mensagem;
    }

    const char *what() const throw()
    {
        return mensagem.c_str();
    }
};

#endif
