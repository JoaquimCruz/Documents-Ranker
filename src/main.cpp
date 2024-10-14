#include "Tratamento.hpp"

int main(){

    std::string path = "Documents/A mão e a luva.txt";
    std :: vector<std :: string> words;


    words = LeituraDocumentos(path);
    words = TratamentoDoTexto(words);

    FrequenciaPalavras(words);


    return 0;

}