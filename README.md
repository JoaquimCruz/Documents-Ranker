# Sistema de Ranqueamento de Documentos com TF-IDF

Este projeto é uma aplicação em C++ que implementa um sistema de ranqueamento de documentos utilizando o algoritmo **TF-IDF (Term Frequency - Inverse Document Frequency)**. O sistema permite que o usuário baixe conteúdos de livros a partir de URLs fornecidas, os armazene em um banco de dados SQLite e analise sua relevância em relação a frases de pesquisa. Além de explorar o cálculo de TF-IDF, o projeto revisa conceitos fundamentais de Estruturas de Dados e Algoritmos.

---

## Sumário

1. [Descrição do Projeto](#descrição-do-projeto)
2. [Funcionalidades](#funcionalidades)
3. [Arquivos e Funções](#arquivos-e-funções)
4. [Desafios Computacionais e Otimizações](#desafios-computacionais-e-otimizações)
5. [Como Executar](#como-executar)
6. [Requisitos](#requisitos)
7. [Considerações Finais](#considerações-finais)
8. [Autor](#autor)

---

## Descrição do Projeto

O sistema foi projetado para baixar livros, armazená-los em um banco de dados SQLite, processar seu conteúdo e calcular a relevância dos documentos em relação a frases de consulta. Utilizando o algoritmo TF-IDF, ele oferece uma classificação dos documentos mais relevantes para a consulta.

---

## Funcionalidades

1. **Download de Livros**: Solicita URLs e títulos dos livros para realizar o download e salva o conteúdo localmente.
2. **Armazenamento no Banco de Dados**: Armazena o conteúdo dos livros em uma tabela SQLite, evitando duplicidade.
3. **Processamento de Texto**: Realiza normalização dos textos, removendo pontuações e palavras irrelevantes (*stopwords*).
4. **Cálculo de TF-IDF**: Determina a relevância de cada livro em relação a frases de consulta.
5. **Ranqueamento de Documentos**: Classifica os livros por relevância usando algoritmos de ordenação.

---

## Arquivos e Funções

### `BancoDeDados.hpp/cpp`
Define a classe `BancoDeDados`, responsável por gerenciar o banco de dados SQLite, incluindo operações de criação, inserção, verificação e recuperação.

- **`BancoDeDados(const std::string& banco)`**: Construtor que inicializa a conexão com o banco SQLite. Exibe uma mensagem de erro se a conexão falhar.
- **`~BancoDeDados()`**: Destrutor que fecha a conexão com o banco, garantindo o encerramento ao final da execução.
- **`CriarTabela()`**: Cria a tabela `livros` (com `id`, `titulo` e `conteudo`) caso não exista.
- **`inserirLivro(const std::string& titulo, const std::string& conteudo)`**: Insere um novo livro no banco. Retorna `false` se houver erro durante a inserção.
- **`verificarLivroExistente(const std::string& titulo)`**: Verifica se um livro já existe no banco de dados com base no título.
- **`buscarLivro(const std::string& titulo)`**: Retorna o conteúdo de um livro dado seu título. Retorna uma string vazia se o livro não for encontrado.
- **`FecharBanco()`**: Fecha a conexão explicitamente com o banco de dados.

### `Tratamento.hpp/cpp`
Implementa o processamento de texto, incluindo normalização, remoção de pontuações e *stopwords*, e cálculo de frequências para o TF-IDF.

- **`isStopWord(const std::string& word, const std::string stopWords[], int size)`**: Verifica se uma palavra é uma *stopword*.
- **`LeituraDocumentos1(const std::string& filePath)`**: Lê palavras de um arquivo e retorna um vetor com as palavras.
- **`LeituraDocumentos(std::istringstream& stream)`**: Similar à função anterior, mas lê de um fluxo de texto (`std::istringstream`), útil para documentos já carregados na memória.
- **`TratamentoDoTexto(std::vector<std::string> words)`**: Realiza limpeza no texto, removendo pontuações e convertendo para minúsculas. Também remove as *stopwords*.
- **`FrequenciaPalavras(std::vector<std::string>& words)`**: Calcula a frequência de cada palavra em um vetor de palavras e retorna um mapa (`unordered_map`) com essas frequências.
- **`calculaTFIDF(...)`**: Calcula o TF-IDF de cada termo em relação aos documentos, considerando a frequência da palavra no documento e o número de documentos onde ela aparece.
- **`RanqueamentoDocumentos(...)`**: Ordena e exibe os documentos com base na relevância de TF-IDF para uma frase de consulta usando um algoritmo de ordenação.

### `Curl.hpp/cpp`
Implementa as funções para realizar o download de conteúdo via cURL e salvar os dados em arquivos locais.

- **`grava_conteudo(void* ptr, size_t size, size_t nmemb, void* userp)`**: Callback para gravar dados baixados diretamente no arquivo. Escreve os dados recebidos pelo cURL no arquivo de destino.
- **`baixarLivro(const std::string& url, const std::string& caminhoArquivo)`**: Função principal que baixa o conteúdo da URL fornecida e salva no caminho especificado. Retorna `true` se o download for bem-sucedido e `false` se houver falha.

### `main.cpp`
Ponto de entrada do programa, coordena a execução dos módulos para download, armazenamento, processamento e análise dos livros.

- **Banco de Dados e Tabela**: Inicializa `BancoDeDados` e cria a tabela `livros`, se necessário.
- **Coleta de URLs e Títulos**: Solicita ao usuário URLs e títulos para download.
- **Verificação e Download**: Verifica se o livro já existe no banco. Se não, realiza o download e o armazena.
- **Processamento e Ranqueamento**: Chama `ChamamentoDeFuncoes` para processar o texto, calcular o TF-IDF e exibir o ranqueamento.
- **Fechamento**: Finaliza a conexão com o banco de dados ao encerrar a execução.

---

## Desafios Computacionais e Otimizações

### Estruturas de Dados e Desempenho

Este projeto explora o uso de listas, filas e tabelas hash, o que implica certas limitações de desempenho que podem ser otimizadas:

- **Complexidade de Busca e Inserção**: A busca e inserção em listas e filas têm custo \( O(n) \), que é limitado para grandes volumes de dados. 
- **Ordenação**: QuickSort tem complexidade \( O(n \log n) \), sendo eficiente, mas possível de melhorar com estruturas de dados alternativas.

### Considerações para Estruturas Avançadas

Possíveis melhorias incluem:
- **Árvores de Busca Balanceadas**: Usar árvores binárias de busca (BST) ou árvores AVL pode reduzir o tempo de busca e melhorar a organização dos termos para \( O(\log n) \).
- **Representação em Grafos**: A relação entre documentos e termos pode ser vista como um grafo, onde os documentos são vértices conectados com base na relevância dos termos. Essa estrutura permitiria análises semânticas e de relações entre os documentos.

---
