#include "BancoDeDados.hpp"
#include "Tratamento.hpp"
#include "Curl.hpp"
#include <iostream>
#include <fstream>

int main() {
    BancoDeDados banco("livros.db");

    banco.CriarTabela();

    std::vector<std::string> urls;
    std::vector<std::string> titulos;
    int i = 1, aux = -1;

    do {
        std::string url, titulo;
        
        std::cout << "Cole a URL do livro " << i << ": ";
        std::cin >> url;
        std::cout << "Digite o título do livro " << i << ": ";
        std::cin.ignore(); 
        std::getline(std::cin, titulo);
        
        urls.emplace_back(url);
        titulos.emplace_back(titulo);

        if(!banco.verificarLivroExistente(titulo)){
            if(!baixarLivro(url, "Documents/" + titulo + ".txt")){
                std::cerr << "Erro ao baixar o livro " << titulo << "!" << std::endl;
            } else {
                std::ifstream livro("Documents/" + titulo + ".txt");
                std::string conteudo((std::istreambuf_iterator<char>(livro)), std::istreambuf_iterator<char>());
                banco.inserirLivro(titulo, conteudo);
            }
        } else {
            std::cout << "O livro " << titulo << " já está no banco de dados!" << std::endl;
        }

        std::cout << "Para sair digite 0, para continuar digite 1: ";
        std::cin >> aux;
        ++i;
        
    } while (aux != 0);

    ChamamentoDeFuncoes(banco, urls, titulos);

    banco.FecharBanco();

    return 0;
}