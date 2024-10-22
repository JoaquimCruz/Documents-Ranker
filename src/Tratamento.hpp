#ifndef TRATAMENTO_HPP  
#define TRATAMENTO_HPP 
#include <bits/stdc++.h>
#include "BancoDeDados.hpp"
#include "sqlite3.h"

std::vector<std::string> LeituraDocumentos(std::istringstream& stream);
std::vector<std::string> LeituraDocumentos1(const std::string& filePath);
std :: vector < std :: string > TratamentoDoTexto(std :: vector < std :: string > words);
bool isStopWord(const std::string& word, const std::string stopWords[], int size);
std :: unordered_map<std :: string, int> FrequenciaPalavras(std :: vector < std :: string >& words);
double calculaTFIDF(const std :: unordered_map<std :: string, int>& frequencias, const std :: vector<std :: string>& PalavrasFrases,
                    const std :: unordered_map < std :: string, int >& DF, int totalLivros);
void ChamamentoDeFuncoes(BancoDeDados& banco);
void troca(std::pair<std::string, double>& a, std::pair<std::string, double>& b);
int particiona(std::vector<std::pair<std::string, double>>& documentos, int inicio, int fim);
void quickSort(std::vector<std::pair<std::string, double>>& documentos, int inicio, int fim);
void RanqueamentoDocumentos(std::vector<std::pair<std::string, double>>& documentosTFIDF);
#endif 