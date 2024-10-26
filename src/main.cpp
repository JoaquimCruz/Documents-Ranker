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
    std::string url, titulo;
    int i = 1, aux = -1, aux1 = -1;

    do{
        std :: cout << "------------MENU------------" << std :: endl;
        std :: cout << "1 - Inserir URLs dos livros desejados" << std :: endl;
        std :: cout << "2 - Procurar livros direto do banco de dados" << std :: endl;
        std :: cout << "3 - Sair" << std :: endl;
        std :: cout << "Digite a opcao desejada: ";
        std :: cin >> aux1;
        std :: cin.ignore();

        switch (aux1)
        {
        case 1:
            do {
        
        
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

            

            banco.FecharBanco();

            break;


        case 2:
        
            std::cout << "Digite o título do livro que deseja procurar: ";
            std :: getline(std :: cin, titulo);

            if(banco.verificarLivroExistente(titulo)){

                std :: cout << "Livro encontrado!" << std :: endl;
                titulos.emplace_back(titulo);
                urls.emplace_back("Documents/" + titulo + ".txt");
                std :: cout << "Livro adionado a pesquisa!" << std :: endl;
            } else{
                std :: cout << "Livro não encontrado!" << std :: endl;
            }

            
            break;
        
        case 3:
            std :: cout << "Saindo..." << std :: endl;
            break;
        
        default:
            std :: cout << "Opcao invalida!" << std :: endl;
            break;
        }
    }while(aux1 != 3);

    std :: cout << "Processando livros..." << std :: endl;
    ChamamentoDeFuncoes(banco, urls, titulos);
    return 0;
}