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

void FrequenciaPalavras(std :: vector < std :: string >& words){

    std :: unordered_map<std :: string, int> wordCount;

    for(const auto& w : words){
        wordCount[w]++; 
    }

    for(const auto& aux : wordCount){
        std :: cout << "Palavra: " << aux.first << "\tFrequencia: " << aux.second << std :: endl;
    }
}
