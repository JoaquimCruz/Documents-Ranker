#ifndef TRATAMENTO_HPP  
#define TRATAMENTO_HPP 
#include <bits/stdc++.h>

std :: vector<std :: string> LeituraDocumentos(const std::string& filePath);
std :: vector < std :: string > TratamentoDoTexto(std :: vector < std :: string > words);
bool isStopWord(const std::string& word, const std::string stopWords[], int size);
std :: unordered_map<std :: string, int> FrequenciaPalavras(std :: vector < std :: string >& words);
double calculaTFIDF(const std :: unordered_map<std :: string, int>& frequencias, const std :: vector<std :: string>& PalavrasFrases,
                    const std :: unordered_map < std :: string, int >& DF, int totalLivros);
void ChamamentoDeFunções();
#endif 