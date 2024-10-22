#include "Curl.hpp"

size_t grava_conteudo(void* ptr, size_t size, size_t nmemb, void* userp) {
    std::ofstream* arquivo = reinterpret_cast<std::ofstream*>(userp);
    arquivo->write(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}

// Função para baixar o conteúdo de um livro usando cURL
bool baixarLivro(const std::string& url, const std::string& caminhoArquivo) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Erro ao inicializar cURL!" << std::endl;
        return false;
    }

    std::ofstream arquivo(caminhoArquivo, std::ios::binary);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir arquivo para salvar o livro!" << std::endl;
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, grava_conteudo);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &arquivo);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Erro ao baixar livro: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        return false;
    }

    curl_easy_cleanup(curl);
    arquivo.close();
    return true;
}
