#ifndef CURL_HPP
#define CURL_HPP
#include <bits/stdc++.h>
#include <curl/curl.h>

size_t grava_conteudo(void* conteudo, size_t tamanho, size_t nmemb, void* userp);
bool baixarLivro(const std::string& url, const std::string& caminhoArquivo);

#endif