#include "Tratamento.hpp"


bool isStopWord(const std::string& word, const std::string stopWords[], int size) {
    for (int i = 0; i < size; ++i) {
        if (word == stopWords[i]) {
            return true; 
        }
    }
    return false; 
}

std::vector<std::string> LeituraDocumentos1(const std::string& filePath) {
    std::ifstream Doc(filePath);
    std::vector<std::string> words;
    std::string line, word;

    if (!Doc) {
        std::cerr << "Error ao abrir o arquivo: " << filePath << std::endl;
        return words;
    }

    while (std::getline(Doc, line)) {
        std::istringstream iss(line);
        while (iss >> word) {
            words.emplace_back(word);
        }
    }

    Doc.close();
    return words;
}
std::vector<std::string> LeituraDocumentos(std::istringstream& stream) {
    std::vector<std::string> words;
    std::string line, word;

    while (std::getline(stream, line)) {
        std::istringstream iss(line);
        while (iss >> word) {
            words.emplace_back(word);
        }
    }

    return words;
}
std :: vector < std :: string > TratamentoDoTexto(std :: vector < std :: string > words){

    std :: ifstream StopWords("Documents/stopwords.txt");
    std :: string line;
    std :: string stopWords[264];
    int i = 0;

    if(!StopWords){
        std :: cerr << "Error!" << std :: endl;
    }

    while(std :: getline(StopWords,line)){
        
        stopWords[i] = line;
        i++;

        if(i >= 264){
            break;
        }
    }

    StopWords.close();


    for (auto& w : words) { // tirar pontuações e deixar as letras minúsculas

        w.erase(std::remove_if(w.begin(), w.end(), ispunct), w.end());

        std :: transform(w.begin(), w.end(), w.begin(), ::tolower);
    }

    for (size_t i = 0; i < words.size(); ) { // tiras as stopwords
        
        if (isStopWord(words[i], stopWords, 264)) {
            
            words.erase(words.begin() + i);
        } else {
            
            ++i;
        }
    }

    return words;

}

std :: unordered_map<std :: string, int> FrequenciaPalavras(std :: vector < std :: string >& words){

    std :: unordered_map<std :: string, int> wordCount;

    for(const auto& w : words){
        wordCount[w]++; 
    }


    return wordCount;
}

double calculaTFIDF(const std :: unordered_map<std :: string, int>& frequencias, const std :: vector<std :: string>& PalavrasFrases,
                    const std :: unordered_map < std :: string, int >& DF, int totalLivros){

    double totalTFIDF = 0.0, Idf = 0.0, Tf = 0.0;
    int Df = 0;

    for(const auto& w : PalavrasFrases){
        auto aux = frequencias.find(w);

        if(aux != frequencias.end()){
            Tf = aux -> second;
            Tf = Tf/frequencias.size();
            Df = DF.at(w);
            Idf = std::log(static_cast<double>( 1 + totalLivros) / (1 + Df) + 1);
            totalTFIDF += Tf * Idf;
            
        }
    }

    return totalTFIDF;
}


void troca(std::pair<std::string, double>& a, std::pair<std::string, double>& b) {
    std::pair<std::string, double> temp = a;
    a = b;
    b = temp;
}

int particiona(std::vector<std::pair<std::string, double>>& documentos, int inicio, int fim) {
    double pivô = documentos[fim].second;
    int i = inicio - 1;

    for (int j = inicio; j < fim; ++j) {
        if (documentos[j].second > pivô) { 
            i++;
            troca(documentos[i], documentos[j]);
        }
    }
    troca(documentos[i + 1], documentos[fim]);
    return i + 1;
}

void quickSort(std::vector<std::pair<std::string, double>>& documentos, int inicio, int fim) {
    if (inicio < fim) {
        int pi = particiona(documentos, inicio, fim);
        quickSort(documentos, inicio, pi - 1);
        quickSort(documentos, pi + 1, fim);
    }
}

void RanqueamentoDocumentos(std::vector<std::pair<std::string, double>>& documentosTFIDF) {
    quickSort(documentosTFIDF, 0, documentosTFIDF.size() - 1);

    std::cout << "Documentos ranqueados por relevância (TF-IDF):" << std::endl;
    for (const auto& doc : documentosTFIDF) {
        std::cout << "Documento: " << doc.first << " - TF-IDF total: " << doc.second << std::endl;
    }
}

void ChamamentoDeFuncoes(BancoDeDados& banco, const std::vector<std::string>& urls, const std::vector<std::string>& titulos) {
    std::unordered_map<std::string, std::unordered_map<std::string, int>> frequenciasLivros;
    std::unordered_map<std::string, int> DF;
    int totalLivros = titulos.size();

    for (size_t i = 0; i < urls.size(); ++i) {
        std::string caminhoLivro = "Documents/" + titulos[i] + ".txt";
        std::string conteudoLivro = banco.buscarLivro(titulos[i]);

        if (conteudoLivro.empty()) {
            std::cerr << "Erro: O livro " << titulos[i] << " não foi encontrado no banco de dados!" << std::endl;
            continue;
        }

        std::istringstream streamLivro(conteudoLivro);
        std::vector<std::string> palavrasLivro = LeituraDocumentos(streamLivro);
        palavrasLivro = TratamentoDoTexto(palavrasLivro);

        std::unordered_map<std::string, int> frequencias = FrequenciaPalavras(palavrasLivro);
        frequenciasLivros[titulos[i]] = frequencias;

        // Atualizar DF (document frequency)
        for (const auto& [word, _] : frequencias) {
            DF[word]++;
        }
    }

    std::ifstream frasesFile("Documents/frases.txt");
    std::string frase;

    if (!frasesFile) {
        std::cerr << "Erro ao abrir o arquivo de frases: Documents/frases.txt" << std::endl;
        return;
    }

    // Processar as frases e calcular o TF-IDF para cada livro
    while (std::getline(frasesFile, frase)) {
        std::istringstream fraseStream(frase);
        std::vector<std::string> palavrasFrase = LeituraDocumentos(fraseStream);
        palavrasFrase = TratamentoDoTexto(palavrasFrase);

        std::vector<std::pair<std::string, double>> documentosTFIDF;
        
        for (const auto& titulo : titulos) {
            double tfidf = calculaTFIDF(frequenciasLivros[titulo], palavrasFrase, DF, totalLivros);
            documentosTFIDF.emplace_back(titulo, tfidf);
        }

        std::cout << "Resultado para a frase: \"" << frase << "\"" << std::endl;
        RanqueamentoDocumentos(documentosTFIDF);
        std::cout << "-------------------------------------" << std::endl;
    }

    frasesFile.close();
}

