#include "BancoDeDados.hpp"
#include "Tratamento.hpp"
#include "Curl.hpp"
#include <iostream>
#include <fstream>

int main() {
    BancoDeDados banco("livros.db");

    banco.CriarTabela();

    std::string url1, url2, titulo1, titulo2;

    std::cout << "Cole a URL do livro 1: ";
    std::cin >> url1;
    std::cout << "Digite o título do livro 1: ";
    std::cin.ignore(); 
    std::getline(std::cin, titulo1);

    std::cout << "Cole a URL do livro 2: ";
    std::cin >> url2;
    std::cout << "Digite o título do livro 2: ";
    std::cin.ignore();
    std::getline(std::cin, titulo2);

    
    std::string caminhoLivro1 = "Documents/" + titulo1 + ".txt";
    std::string caminhoLivro2 = "Documents/" + titulo2 + ".txt";

    
    if (!banco.verificarLivroExistente(titulo1)) {
        if (baixarLivro(url1, caminhoLivro1)) {

            std::cout << "Livro 1 baixado com sucesso!" << std::endl;
            std::ifstream livroFile(caminhoLivro1);
            std::string conteudo((std::istreambuf_iterator<char>(livroFile)), std::istreambuf_iterator<char>());
            banco.inserirLivro(titulo1, conteudo);

        } else {
            std::cerr << "Erro ao baixar o livro 1!" << std::endl;
        }
    } else {
        std::cout << "O livro 1 já existe no banco de dados." << std::endl;
    }

    if (!banco.verificarLivroExistente(titulo2)) {
        if (baixarLivro(url2, caminhoLivro2)) {

            std::cout << "Livro 2 baixado com sucesso!" << std::endl;
            std::ifstream livroFile(caminhoLivro2);
            std::string conteudo((std::istreambuf_iterator<char>(livroFile)), std::istreambuf_iterator<char>());
            banco.inserirLivro(titulo2, conteudo);

        } else {
            std::cerr << "Erro ao baixar o livro 2!" << std::endl;
        }
    } else {
        std::cout << "O livro 2 já existe no banco de dados." << std::endl;
    }

    ChamamentoDeFuncoes(banco, url1, url2);

    banco.FecharBanco();

    return 0;
}
