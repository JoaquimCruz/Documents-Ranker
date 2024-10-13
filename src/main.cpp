#include "Tratamento.hpp"

int main(){

    std :: ifstream Doc1("Documents/A mão e a luva.txt");
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

    words = TratamentoDoTexto(words);



    for(const auto& aux : words){
        std :: cout << aux << std :: endl;
    }



    return 0;

}