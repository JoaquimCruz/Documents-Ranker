# Sistema de Ranqueamento de Documentos com TF-IDF

Este projeto implementa um sistema de ranqueamento de documentos utilizando o algoritmo **TF-IDF (Term Frequency - Inverse Document Frequency)** em C++. A aplicação permite que o usuário baixe conteúdo de livros a partir de URLs fornecidas, armazene-os em um banco de dados SQLite, processe o conteúdo para análise e, em seguida, classifique os documentos por relevância em relação a frases de pesquisa. Este projeto explora conceitos fundamentais de Estruturas de Dados e Algoritmos, como listas, filas, tabelas hash e ordenação.

## Sumário
- [Descrição do Projeto](#descrição-do-projeto)
- [Funcionalidades](#funcionalidades)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Passo a Passo do Código](#passo-a-passo-do-código)
- [Desafios Computacionais e Otimizações](#desafios-computacionais-e-otimizações)
- [Instruções de Compilação e Execução](#instruções-de-compilação-e-execução)
- [Desempenho do Sistema](#desempenho-do-sistema)
- [Considerações Finais](#considerações-finais)
- [Autor](#autor)

## Descrição do Projeto

O objetivo deste sistema é classificar documentos por relevância em relação a frases de consulta fornecidas pelo usuário. Utilizando o algoritmo TF-IDF, o sistema calcula uma pontuação para cada livro, classificando-o com base em termos específicos encontrados nas frases de consulta. A aplicação foi projetada para aplicar e aprimorar técnicas de manipulação de dados textuais, gerenciamento de banco de dados e operações de rede.

Este projeto também explora o uso de listas, tabelas hash e algoritmos de ordenação, além de demonstrar o funcionamento do SQLite para armazenamento persistente e o uso da biblioteca cURL para operações de rede, oferecendo uma prática eficiente de análise de dados textuais.

## Funcionalidades

1. **Download de Livros**: Recebe URLs e títulos dos livros que o usuário deseja baixar. Utilizando `cURL`, o conteúdo é baixado e salvo em arquivos locais.
2. **Armazenamento no Banco de Dados**: Cada livro é armazenado em uma tabela do SQLite, permitindo acesso rápido e evitando duplicação.
3. **Processamento de Texto**: O sistema normaliza o texto, removendo pontuações, convertendo para minúsculas e excluindo *stopwords* (palavras irrelevantes para a análise).
4. **Cálculo de TF-IDF**: Para cada frase de consulta, o sistema calcula o valor TF-IDF de cada termo nos documentos, determinando a relevância do livro para a frase.
5. **Ranqueamento de Documentos**: Os livros são ordenados pela relevância calculada, permitindo que o usuário veja os documentos mais importantes para a consulta.

## Estrutura do Projeto

1. **Leitura e Processamento dos Documentos**
   - **Download e Armazenamento**: Os livros são baixados, salvos localmente e armazenados em uma tabela SQLite pela classe `BancoDeDados`, que evita duplicação de registros.
   - **Normalização e Limpeza de Texto**: Cada texto é processado para remover pontuações, converter para letras minúsculas e remover *stopwords*, garantindo uma análise mais consistente.

2. **Cálculo de TF-IDF**
   - **TF (Term Frequency)**: Mede a frequência com que um termo aparece em um documento.
   - **IDF (Inverse Document Frequency)**: Calcula a importância do termo no conjunto de todos os documentos. Termos que aparecem em todos os documentos têm menor relevância.
   - **Relevância Total**: Para cada frase de pesquisa, o sistema calcula o TF-IDF de cada termo e gera uma pontuação de relevância para o documento.

3. **Ranqueamento de Documentos**
   - Os documentos são classificados de forma decrescente por relevância para cada frase de consulta. O algoritmo de ordenação QuickSort é utilizado para ordenar os documentos de forma eficiente.

## Passo a Passo do Código

1. **Inicialização do Banco de Dados**: A classe `BancoDeDados` cria e abre uma conexão com o banco de dados (`livros.db`), garantindo a criação da tabela de livros.
2. **Coleta de URLs e Títulos**: O sistema recebe URLs e títulos dos livros que o usuário deseja baixar.
3. **Verificação e Download dos Livros**:
   - Verifica se o livro já está no banco de dados.
   - Caso não esteja, utiliza `cURL` para baixar o conteúdo da URL, salva o livro em `Documents/[titulo].txt`, lê o conteúdo e o insere no banco de dados.
4. **Processamento e Análise de Relevância**:
   - O sistema processa o conteúdo dos livros, normalizando o texto e removendo *stopwords*.
   - Para cada frase de consulta, o TF-IDF é calculado, e os livros são classificados pela relevância.
5. **Exibição do Ranking de Relevância**: Exibe os livros classificados de acordo com a relevância para cada frase de consulta.

## Desafios Computacionais e Otimizações

### Estruturas de Dados Utilizadas
- **`std::vector`**: Utilizado para armazenar palavras de documentos e frases de consulta. É uma escolha eficiente para armazenar listas de palavras devido ao acesso direto por índice.
- **`std::unordered_map`**: Usado para armazenar a frequência de cada palavra em documentos. Oferece uma complexidade média de `O(1)` para inserção e busca, ideal para cálculos frequentes de frequência de palavras.

### Desempenho e Alternativas
1. **Ordenação com QuickSort**: O QuickSort, com complexidade `O(n log n)`, é eficiente para ordenar documentos pela relevância, mas estruturas de dados avançadas, como árvores de busca balanceadas, poderiam ser alternativas para melhorar a busca e a ordenação.
2. **Árvores de Busca e Grafos**: Estruturas como árvores AVL poderiam reduzir o tempo de busca e melhorar a organização dos dados, enquanto uma representação em grafos poderia facilitar a análise semântica de relações entre documentos.

## Instruções de Compilação e Execução

### Pré-requisitos

Para compilar e executar este projeto, instale:
- **cURL** (para download de arquivos)
- **SQLite3** (para banco de dados)


Instale as dependências:
Para instação da biblioteca sqlite:
```Markdown
# Atualize o gerenciador de pacotes
sudo apt update
# Instale a biblioteca SQLite3
sudo apt install libsqlite3-dev

```
Para instação da biblioteca Curl:
```Markdown
# Atualize o gerenciador de pacotes
sudo apt update
# Instale a biblioteca cURL
sudo apt install libcurl4-openssl-dev

```
Por fim, caso prefira instalar todas as bilbiotecas em um comando apenas:

```Markdown
# Ubuntu
# Atualize o gerenciador de pacotes
sudo apt update
# Instala todas as bibliotecas necessárias
sudo apt install libcurl4-openssl-dev libsqlite3-dev 

# MacOS (Homebrew)
brew install curl sqlite3 

# Windows (vcpkg)
vcpkg install curl sqlite3 

```
# Compilação

Para compilar e rodar o código usando MakeFile, basta seguir os seguintes comandos.
| Comando                |  Função                                                                                               |                     
| -----------------------| ------------------------------------------------------------------------------------------------------|
|  make clean          | Apaga a última compilação realizada contida na pasta build                                            |
|  make                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build               |
|  make run            | Executa o programa da pasta build após a realização da compilação                                     |
|make r| Faz os três processos descritos acima em apenas um comando|

3. O servidor estará acessível em http://localhost:9080.

## Desempenho do Sistema

### Tempo de Execução
- **Download e Inserção**: A execução é `O(n)`, onde `n` é o tamanho do documento. Para grandes volumes, o tempo depende da velocidade de conexão e do tamanho do conteúdo.
- **Cálculo de Frequência e TF-IDF**: A complexidade é `O(m)` para a contagem de palavras e `O(p + q)` para o cálculo TF-IDF, onde `m` é o número de palavras únicas, `p` é o número de palavras no documento e `q` é o número de palavras na frase de pesquisa.

### Uso de Memória
- **Banco de Dados**: O SQLite armazena dados em disco, minimizando o uso de memória principal.
- **Estruturas Temporárias**: `std::unordered_map` oferece acesso rápido sem sobrecarregar a memória, armazenando apenas palavras e suas frequências para cálculo.

## Considerações Finais

Este sistema oferece uma aplicação prática do cálculo de relevância com TF-IDF em documentos textuais, utilizando cURL para download, SQLite para armazenamento e Pistache para integração com o frontend. Estruturas de dados como `std::unordered_map` e `std::vector` oferecem acesso rápido e eficiente para manipulação de dados. Melhorias futuras podem incluir o uso de árvores de busca e grafos para refinar o desempenho e agregar funcionalidades.

