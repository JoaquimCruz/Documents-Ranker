# Sistema de Ranqueamento de Documentos com TF-IDF
<div style="display: inline-block;">
<img align="center" height="20px" width="60px" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"/> 
<img align="center" height="20px" width="80px" src="https://img.shields.io/badge/Made%20for-VSCode-1f425f.svg"/> 
</a> 
</div>

Este projeto implementa um sistema de ranqueamento de documentos utilizando o algoritmo **TF-IDF (Term Frequency - Inverse Document Frequency)** em C++. A aplicação permite que o usuário baixe conteúdo de livros a partir de URLs fornecidas, armazene-os em um banco de dados SQLite, processe o conteúdo para análise e, em seguida, classifique os documentos por relevância em relação a frases de pesquisa. Este projeto explora conceitos fundamentais de Estruturas de Dados e Algoritmos, como listas, filas, tabelas hash e ordenação.


## Sumário
- [Descrição do Projeto](#descrição-do-projeto)
- [Funcionalidades](#funcionalidades)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Passo a Passo do Código](#passo-a-passo-do-código)
- [Desafios Computacionais e Otimizações](#desafios-computacionais-e-otimizações)
  - [Estruturas de Dados Utilizadas](#estruturas-de-dados-utilizadas)
  - [Desempenho e Alternativas](#desempenho-e-alternativas)
- [Reflexão sobre o Uso de Estruturas de Dados Avançadas](#reflexão-sobre-o-uso-de-estruturas-de-dados-avançadas)
  - [1. Utilização de Árvores Binárias de Busca (BST) ou Árvores AVL](#1-utilização-de-árvores-binárias-de-busca-bst-ou-árvores-avl)
  - [2. Representação com Grafos para Relações de Relevância entre Documentos](#2-representação-com-grafos-para-relações-de-relevância-entre-documentos)
  - [Comparação e Conclusão](#comparação-e-conclusão)
- [Instruções de Compilação e Execução](#instruções-de-compilação-e-execução)
  - [Pré-requisitos](#pré-requisitos)
  - [Compilação](#compilação)
- [Adição de Livros ao Banco de Dados](#adição-de-livros-ao-banco-de-dados)
- [Desempenho do Sistema](#desempenho-do-sistema)
  - [Tempo de Execução](#tempo-de-execução)
  - [Uso de Memória](#uso-de-memória)
- [Considerações Finais](#considerações-finais)
- [Autores](#autores)

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

## Reflexão sobre o Uso de Estruturas de Dados Avançadas

Embora a solução proposta com as estruturas atuais seja funcional e suficiente para atender a todos os requisitos do trabalho, o uso de estruturas em árvore, como **Árvores Binárias de Busca (BST)** ou **Árvores AVL**, e de **grafos** poderia aprimorar a eficiência do sistema.

### 1. Utilização de Árvores Binárias de Busca (BST) ou Árvores AVL

Atualmente, o sistema utiliza listas lineares ou `std::unordered_map` para armazenar e buscar termos dentro dos documentos. Embora sejam eficientes para inserções e buscas, há cenários em que uma estrutura de árvore poderia otimizar ainda mais o tempo de busca e organização dos dados.

#### Vantagens do Uso de Árvores Balanceadas

1. **Redução do Tempo de Busca**:
   - Em uma lista, a busca por um termo específico pode ter complexidade **O(n)** no pior caso, onde `n` é o número de termos. Utilizando uma **árvore balanceada**, como a **Árvore AVL**, a complexidade de busca é reduzida para **O(log n)**, tornando a pesquisa mais eficiente.

2. **Inserções Ordenadas**:
   - Árvores AVL e BSTs mantêm os dados ordenados, permitindo que operações como a ordenação de termos ou a criação de rankings sejam realizadas diretamente durante o processo de inserção, sem precisar de um passo adicional de ordenação. Isso pode ser útil, por exemplo, no armazenamento de frequências de palavras.

3. **Aplicação**:
   - Podemos usar uma árvore AVL para armazenar as palavras dos documentos e suas frequências. Em vez de uma lista, onde a contagem de frequência pode ser mais lenta, uma árvore AVL permite que as inserções e buscas sejam feitas em **O(log n)**, mesmo que o conjunto de dados cresça significativamente.
   - Por exemplo, cada nó da árvore pode representar uma palavra, com o valor do nó representando a frequência da palavra no documento.

#### Exemplo de Estrutura com Árvore AVL para Armazenamento de Termos

Cada nó de uma Árvore AVL poderia armazenar:
- **Termo**: A palavra do documento.
- **Frequência**: O número de ocorrências dessa palavra no documento.
  
Com essa abordagem, calcular a **TF (Term Frequency)** e manter uma estrutura organizada e rápida para busca de termos se torna mais eficiente, principalmente em documentos extensos com grande diversidade de palavras.

### 2. Representação com Grafos para Relações de Relevância entre Documentos

Outra estrutura avançada que poderia melhorar a organização e análise dos documentos é o uso de um **grafo** para representar as relações de relevância entre documentos e termos de pesquisa.

#### Vantagens do Uso de Grafos

1. **Modelagem de Relações entre Documentos**:
   - Em um grafo, cada **vértice** pode representar um documento, e as **arestas** podem representar uma relação de similaridade ou relevância entre documentos, com pesos que representam o valor de **TF-IDF** ou outras métricas de relevância.
   - Por exemplo, se dois documentos compartilham uma alta frequência de termos importantes, a aresta entre esses dois vértices pode ter um peso mais alto, indicando uma relação forte entre os documentos.

2. **Análises Semânticas e Caminhos**:
   - Com um grafo, é possível analisar quais documentos são mais relevantes para certos termos de pesquisa, encontrando caminhos entre documentos e identificando agrupamentos (clusters) de documentos com relevâncias similares.
   - Técnicas de análise de grafos, como **busca em largura** (BFS) ou **busca em profundidade** (DFS), podem ser aplicadas para explorar documentos relacionados de maneira mais eficiente e sofisticada.

3. **Aplicação**:
   - Cada vez que uma análise TF-IDF é realizada, o grafo pode ser atualizado com arestas ponderadas entre documentos relacionados. Isso facilita a visualização e a recuperação de documentos semelhantes ou relevantes para um conjunto de termos.

#### Estrutura Proposta de Grafo

- **Vértices**: Cada vértice representa um documento.
- **Arestas**: As arestas entre vértices representam a relevância entre documentos, calculada com base nos termos comuns e suas pontuações de TF-IDF.
- **Pesos das Arestas**: O peso pode ser determinado pelo valor de similaridade entre documentos, utilizando métricas como **coseno de similaridade** ou **Jaccard** com base nas palavras-chave compartilhadas.

### Comparação e Conclusão

| Estrutura      | Complexidade de Busca | Vantagens                                                | Aplicação no Sistema                |
|----------------|-----------------------|----------------------------------------------------------|-------------------------------------|
| Lista / Vector | O(n)                  | Simples e fácil de implementar                           | Armazenamento inicial dos termos    |
| AVL / BST      | O(log n)              | Ordenação automática, rápida busca e inserção             | Armazenamento de termos e frequências |
| Grafo          | Depende do algoritmo  | Modelagem de relações complexas, análise de similaridade | Relação entre documentos e termos   |

### Reflexão Final

Embora a estrutura atual seja funcional e atende aos requisitos do trabalho, o uso de **árvores AVL** e **grafos** fornece um entendimento mais profundo sobre o processamento eficiente de dados textuais. A implementação dessas estruturas oferece uma solução otimizada para o sistema de ranqueamento de documentos, reduzindo tempos de busca e inserção e permitindo a modelagem de relações complexas entre documentos e termos de pesquisa.


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
## Adição de Livros ao Banco de Dados
Este projeto utiliza livros da [biblioteca digital Projeto Gutenberg](https://www.gutenberg.org/), que possui mais de 70.000 livros em seu acervo. Para adicioná-los ao banco de dados, selecione dentro do site a opção de arquivo de texto simples (Plain Text UTF-8). A seguir, será exemplificado qual será a URL a ser usada no código:
```Markdown
# Url do livro Orgulho e Preconceito
https://www.gutenberg.org/files/1342/1342-0.txt
```

## Desempenho do Sistema

### Tempo de Execução
- **Download e Inserção**: A execução é `O(n)`, onde `n` é o tamanho do documento. Para grandes volumes, o tempo depende da velocidade de conexão e do tamanho do conteúdo.
- **Cálculo de Frequência e TF-IDF**: A complexidade é `O(m)` para a contagem de palavras e `O(p + q)` para o cálculo TF-IDF, onde `m` é o número de palavras únicas, `p` é o número de palavras no documento e `q` é o número de palavras na frase de pesquisa.

### Uso de Memória
- **Banco de Dados**: O SQLite armazena dados em disco, minimizando o uso de memória principal.
- **Estruturas Temporárias**: `std::unordered_map` oferece acesso rápido sem sobrecarregar a memória, armazenando apenas palavras e suas frequências para cálculo.

## Considerações Finais

Este sistema oferece uma aplicação prática do cálculo de relevância com TF-IDF em documentos textuais, utilizando cURL para download, SQLite para armazenamento e Pistache para integração com o frontend. Estruturas de dados como `std::unordered_map` e `std::vector` oferecem acesso rápido e eficiente para manipulação de dados. Melhorias futuras podem incluir o uso de árvores de busca e grafos para refinar o desempenho e agregar funcionalidades.

## Autores
<p>
  Joaquim Cézar Santana da Cruz - Graduando em Engenharia da Computação pelo <a href="https://www.cefetmg.br" target="_blank">CEFET-MG</a>. Contato: (<a href="mailto:joaquim.cruz@aluno.cefetmg.br">joaquim.cruz@aluno.cefetmg.br</a>)
</p>

<p>
  Lucas Cerqueira Portela - Graduando em Engenharia da Computação pelo <a href="https://www.cefetmg.br" target="_blank">CEFET-MG</a>. Contato: (<a href="mailto:lucas.portela@aluno.cefetmg.br">lucas.portela@aluno.cefetmg.br</a>)
</p>

<p>
  João Francisco Teles da Silva - Graduando em Engenharia da Computação pelo <a href="https://www.cefetmg.br" target="_blank">CEFET-MG</a>. Contato: (<a href="mailto:joao.silva.05@aluno.cefetmg.br">joao.silva.05@aluno.cefetmg.br</a>)
</p>
