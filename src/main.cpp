#include "BancoDeDados.hpp"
#include "Tratamento.hpp"
#include "Curl.hpp"
#include <iostream>
#include <fstream>
#include <filesystem> // C++17 para manipulação de diretórios

int main() {
    BancoDeDados banco("livros.db");
    banco.CriarTabela();

    std::vector<std::string> urls;
    std::vector<std::string> titulos;
    std::string url, titulo;
    int i = 1, aux = -1, aux1 = -1;

    do {
        std::cout << "------------MENU------------" << std::endl;
        std::cout << "1 - Inserir URLs dos livros desejados" << std::endl;
        std::cout << "2 - Procurar livros direto do banco de dados" << std::endl;
        std::cout << "3 - Listar livros" << std::endl;
        std::cout << "4 - Inserir frase" << std::endl;
        std::cout << "5 - Sair" << std::endl;
        std::cout << "Digite a opcao desejada: ";
        std::cin >> aux1;
        std::cin.ignore(); // Ignorar o newline após a entrada numérica para getline funcionar corretamente

        switch (aux1) {
            case 1:
                do {
                    std::cout << "Cole a URL do livro " << i << ": ";
                    std::cin >> url;
                    std::cout << "Digite o título do livro " << i << ": ";
                    std::cin.ignore(); 
                    std::getline(std::cin, titulo);
        
                    urls.emplace_back(url);
                    titulos.emplace_back(titulo);

                    if (!banco.verificarLivroExistente(titulo)) {
                        if (!baixarLivro(url, "Documents/" + titulo + ".txt")) {
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

                break;

            case 2:
                std::cout << "Digite o título do livro que deseja procurar: ";
                std::getline(std::cin, titulo);

                if (banco.verificarLivroExistente(titulo)) {
                    std::cout << "Livro encontrado!" << std::endl;
                    titulos.emplace_back(titulo);
                    urls.emplace_back("Documents/" + titulo + ".txt");
                    std::cout << "Livro adicionado à pesquisa!" << std::endl;
                } else {
                    std::cout << "Livro não encontrado!" << std::endl;
                }
                break;

            case 3:
                std::cout << "Listando livros..." << std::endl;
                {
                    std::vector<std::string> livros = banco.listarLivros();
                    for (const auto& livro : livros) {
                        std::cout << livro << std::endl;
                    }
                }
                break;

            case 4: {
                std::cout << "Digite a frase que deseja adicionar: ";
                std::string frase;
                std::getline(std::cin, frase);

                // Verifica e cria o diretório Documents, se necessário
                if (!std::filesystem::exists("Documents")) {
                    std::filesystem::create_directory("Documents");
                }

                std::ofstream frasesFile("Documents/frases.txt", std::ios::app);
                if (frasesFile) {
                    frasesFile << frase << std::endl;
                    std::cout << "Frase adicionada!" << std::endl;
                } else {
                    std::cerr << "Erro ao abrir o arquivo para salvar a frase!" << std::endl;
                }
                frasesFile.close();
                }
                break;

            case 5:
                std::cout << "Saindo..." << std::endl;
                break;

            default:
                std::cout << "Opção inválida!" << std::endl;
                break;
        }
    } while (aux1 != 5);

    std::cout << "Processando livros..." << std::endl;
    ChamamentoDeFuncoes(banco, urls, titulos);

    banco.FecharBanco(); // Fechar o banco apenas no final
    return 0;
}
