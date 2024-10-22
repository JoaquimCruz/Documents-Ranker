#include "BancoDeDados.hpp"
#include "Curl.hpp"
#include "Tratamento.hpp"
#include <fstream>
#include <sstream>

std::string lerConteudoDoArquivo(const std::string& caminhoArquivo) {
    std::ifstream arquivo(caminhoArquivo);
    std::stringstream buffer;

    if (arquivo) {
        buffer << arquivo.rdbuf();  // Lê o conteúdo do arquivo inteiro
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo: " << caminhoArquivo << std::endl;
    }

    return buffer.str();
}

int main() {
    BancoDeDados banco("livros.db");

    banco.CriarTabela();  // Se necessário criar a tabela

    // URLs dos livros a serem baixados
    std::string url1 = "https://www.gutenberg.org/files/1342/1342-0.txt"; // "Orgulho e Preconceito"
    std::string url2 = "https://www.gutenberg.org/files/2701/2701-0.txt"; // "Moby Dick"

    // Caminhos para salvar os livros baixados
    std::string caminhoLivro1 = "Documents/orgulho_e_preconceito.txt";
    std::string caminhoLivro2 = "Documents/moby_dick.txt";

    // Baixar os livros
    if (baixarLivro(url1, caminhoLivro1)) {
        std::cout << "Livro 'Orgulho e Preconceito' baixado com sucesso!" << std::endl;
        // Inserir o livro no banco de dados
        std::ifstream livroFile(caminhoLivro1);
        std::string conteudo((std::istreambuf_iterator<char>(livroFile)), std::istreambuf_iterator<char>());
        banco.inserirLivro("Orgulho e Preconceito", conteudo);
    }

    if (baixarLivro(url2, caminhoLivro2)) {
        std::cout << "Livro 'Moby Dick' baixado com sucesso!" << std::endl;
        // Inserir o livro no banco de dados
        std::ifstream livroFile(caminhoLivro2);
        std::string conteudo((std::istreambuf_iterator<char>(livroFile)), std::istreambuf_iterator<char>());
        banco.inserirLivro("Moby Dick", conteudo);
    }

    // Chamar a função para calcular TF-IDF
    ChamamentoDeFuncoes(banco);

    banco.FecharBanco();

    return 0;
}
