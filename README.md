# Sistema de Ranqueamento de Documentos com TF-IDF

Este projeto é uma aplicação em C++ que implementa um sistema de ranqueamento de documentos utilizando o algoritmo **TF-IDF (Term Frequency - Inverse Document Frequency)**. O sistema permite que o usuário baixe conteúdos de livros a partir de URLs fornecidas, os armazene em um banco de dados SQLite e analise sua relevância em relação a frases de pesquisa. Além de explorar o cálculo de TF-IDF, o projeto revisa conceitos fundamentais de Estruturas de Dados e Algoritmos, como listas, filas, ordenação e tabelas hash.

---

## Sumário

1. [Descrição do Projeto](#descrição-do-projeto)
2. [Funcionalidades](#funcionalidades)
3. [Estrutura do Projeto](#estrutura-do-projeto)
4. [Passo a Passo do Código](#passo-a-passo-do-código)
5. [Desafios Computacionais e Otimizações](#desafios-computacionais-e-otimizações)
6. [Como Executar](#como-executar)
7. [Requisitos](#requisitos)
8. [Considerações Finais](#considerações-finais)
9. [Autor](#autor)

---

## Descrição do Projeto

O objetivo deste sistema é baixar livros, armazená-los em um banco de dados, processar seu conteúdo e classificá-los por relevância em relação a frases de consulta. Utilizando o algoritmo TF-IDF, o sistema calcula uma pontuação para cada livro baseada em termos específicos, oferecendo uma classificação dos documentos mais relevantes para a consulta.

A aplicação foi projetada para exercitar técnicas de manipulação de dados textuais, incluindo o uso de listas, tabelas hash e algoritmos de ordenação, além de explorar o funcionamento de banco de dados e operações de rede.

---

## Funcionalidades

1. **Download de Livros**: O sistema solicita URLs e títulos dos livros que o usuário deseja baixar. Utilizando `cURL`, ele obtém o conteúdo e salva o livro em arquivos locais.
2. **Armazenamento no Banco de Dados**: Cada livro é armazenado em uma tabela SQLite, evitando duplicação de registros e permitindo acesso rápido ao conteúdo.
3. **Processamento de Texto**: O sistema realiza limpeza e normalização do texto, removendo pontuações e convertendo o texto para letras minúsculas, além de excluir *stopwords* (palavras comuns e irrelevantes para a análise).
4. **Cálculo de TF-IDF**: Para cada frase de consulta, o sistema calcula o TF-IDF de cada termo nos documentos e determina a relevância de cada livro em relação à frase.
5. **Ranqueamento de Documentos**: Os livros são ordenados de acordo com a relevância calculada, permitindo ao usuário visualizar os documentos mais importantes para a consulta.

---

## Estrutura do Projeto

1. **Leitura e Processamento dos Documentos**
   - **Download e Armazenamento**: Os livros são baixados e salvos localmente. A classe `BancoDeDados` permite verificar se um livro já foi inserido no banco e evita duplicação.
   - **Normalização e Limpeza de Texto**: Cada texto é processado para remover pontuações, converter para minúsculas e remover palavras irrelevantes (*stopwords*), tornando o conteúdo mais consistente para a análise.

2. **Cálculo de TF-IDF**
   - **TF (Term Frequency)**: Mede a frequência com que cada termo aparece no documento específico.
   - **IDF (Inverse Document Frequency)**: Calcula a importância do termo no conjunto de todos os documentos, considerando que termos muito frequentes em todos os documentos têm menor relevância.
   - **Relevância Total**: Para cada frase de pesquisa, o sistema soma os valores de TF-IDF de termos que aparecem na frase e no documento, resultando em uma pontuação de relevância.

3. **Ranqueamento de Documentos**
   - O sistema classifica os documentos pela relevância usando algoritmos de ordenação como **QuickSort**, tornando-o eficiente para conjuntos de dados grandes.
   - Os documentos são exibidos em ordem decrescente de relevância para cada frase de consulta, permitindo que o usuário identifique rapidamente os mais importantes.

---

## Passo a Passo do Código

1. **Inicialização do Banco de Dados**: Cria uma instância da classe `BancoDeDados` e abre uma conexão com o arquivo `livros.db`, garantindo a criação da tabela de livros.
2. **Coleta de URLs e Títulos**: O sistema solicita ao usuário a URL e o título dos livros que deseja baixar.
3. **Verificação e Download dos Livros**:
   - Verifica se o livro já está armazenado no banco.
   - Se não estiver, utiliza `cURL` para baixar o conteúdo da URL e salva o livro em `Documents/[titulo].txt`.
   - Lê o conteúdo do arquivo baixado e armazena o texto no banco de dados.
4. **Processamento e Análise de Relevância**:
   - Após o download e armazenamento, o sistema processa o conteúdo dos livros para normalização do texto e remoção de *stopwords*.
   - Calcula-se o TF-IDF de cada termo nos documentos em relação à frase de consulta e classifica os livros por relevância.
5. **Exibição do Ranking de Relevância**: Exibe os livros classificados pela relevância em relação a cada frase de consulta processada.

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
