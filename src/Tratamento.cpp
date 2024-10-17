#include "Tratamento.hpp"


bool isStopWord(const std::string& word, const std::string stopWords[], int size) {
    for (int i = 0; i < size; ++i) {
        if (word == stopWords[i]) {
            return true; 
        }
    }
    return false; 
}

std :: vector<std :: string> LeituraDocumentos(const std::string& filePath){

    std :: ifstream Doc1(filePath);
    std :: vector<std :: string> words;
    std :: string line, word; 

    if(!Doc1){
        std :: cerr << "Error!" << std :: endl;
    }

    while(std :: getline(Doc1, line)){
        std :: istringstream iss(line);

        while(iss >> word){
            words.emplace_back(word);
        }
    }

    Doc1.close();

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

    /*for(const auto& aux : wordCount){
        std :: cout << "Palavra: " << aux.first << "\tFrequencia: " << aux.second << std :: endl;
    }*/

    return wordCount;
}

double calculaTFIDF(const std :: unordered_map<std :: string, int>& frequencias, const std :: vector<std :: string>& PalavrasFrases,
                    const std :: unordered_map < std :: string, int >& DF, int totalLivros){

    double totalTFIDF = 0.0, Idf = 0.0;
    int Tf = 0, Df = 0;

    for(const auto& w : PalavrasFrases){
        auto aux = frequencias.find(w);

        if(aux != frequencias.end()){
            Tf = aux -> second;
            Df = DF.at(w);
            Idf = std::log(static_cast<double>(totalLivros) / (1 + Df));
            totalTFIDF += Tf * Idf;
            
        }
    }

    return totalTFIDF;
}

void ChamamentoDeFunções(){

    std :: string path = "Documents/A mão e a luva.txt";
    std :: string path2 = "Documents/biblia.txt";
    //std :: string path3 = "Documents/DomCasmurro.txt";
    //std :: string path4 = "Documents/quincas borda.txt";
    //std :: string path5 = "Documents/Semana_Machado_Assis.txt";
    //std :: string path6 = "Documents/terremoto.txt";
    std :: string frasesPath = "Documents/frases.txt"; 
    int totalLivros = 2;


    std :: vector<std :: string> words1, words2, words3, words4, words5, words6;
    std :: unordered_map<std :: string, int> Frequencia1,Frequencia2,Frequencia3,Frequencia4,Frequencia5,Frequencia6;
    std :: vector<std::string> palavrasFrases;
    std :: unordered_map<std::string, int> DF;


    words1 = LeituraDocumentos(path);
    words1 = TratamentoDoTexto(words1);
    Frequencia1 = FrequenciaPalavras(words1);

    words2 = LeituraDocumentos(path2);
    words2 = TratamentoDoTexto(words2);
    Frequencia2 = FrequenciaPalavras(words2);

    //words3 = LeituraDocumentos(path3);
    //words3 = TratamentoDoTexto(words3);
    //Frequencia3 = FrequenciaPalavras(words3);

    //words4 = LeituraDocumentos(path4);
    //words4 = TratamentoDoTexto(words4);
    //Frequencia4 = FrequenciaPalavras(words4);

    //words5 = LeituraDocumentos(path5);
    //words5 = TratamentoDoTexto(words5);
    //Frequencia5 = FrequenciaPalavras(words5);

    //words6 = LeituraDocumentos(path6);
    //words6 = TratamentoDoTexto(words6);
    //Frequencia6 = FrequenciaPalavras(words6);

    palavrasFrases = LeituraDocumentos(frasesPath);
    palavrasFrases = TratamentoDoTexto(palavrasFrases);

    for (const auto& [word, _] : Frequencia1) DF[word]++; 
    for (const auto& [word, _] : Frequencia2) DF[word]++;
    //for (const auto& [word, _] : Frequencia3) DF[word]++;

    double tfidfLivro1 = calculaTFIDF(Frequencia1, palavrasFrases, DF, totalLivros);
    double tfidfLivro2 = calculaTFIDF(Frequencia2, palavrasFrases, DF, totalLivros);
    double tfidfLivro3 = calculaTFIDF(Frequencia3, palavrasFrases, DF, totalLivros);

    std::cout << "TF-IDF total no Livro 1: " << tfidfLivro1 << std::endl;
    std::cout << "TF-IDF total no Livro 2: " << tfidfLivro2 << std::endl;
    std::cout << "TF-IDF total no Livro 3: " << tfidfLivro3 << std::endl;
   
    
}
