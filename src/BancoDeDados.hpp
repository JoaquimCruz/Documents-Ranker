#ifndef BANCO_DE_DADOS_HPP
#define BANCO_DE_DADOS_HPP
#include "sqlite3.h"
#include <bits/stdc++.h>
#include <curl/curl.h>

class BancoDeDados{
private:
    sqlite3* db; 

    void verificarErros(int rc);

public:
    BancoDeDados();
    BancoDeDados(const std :: string& banco);
    ~BancoDeDados();

    void CriarTabela();

    bool inserirLivro(const std :: string& titulo, const std :: string & conteudo);
    std :: string buscarLivro(const std :: string& titulo);
    void FecharBanco();


};

#endif