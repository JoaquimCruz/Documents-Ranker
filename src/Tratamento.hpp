#ifndef TRATAMENTO_HPP  
#define TRATAMENTO_HPP 
#include <bits/stdc++.h>

std :: vector<std :: string> LeituraDocumentos(const std::string& filePath);
std :: vector < std :: string > TratamentoDoTexto(std :: vector < std :: string > words);
bool isStopWord(const std::string& word, const std::string stopWords[], int size);
void FrequenciaPalavras(std :: vector < std :: string >& words);
#endif 