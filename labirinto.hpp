#ifndef LABIRINTO_HPP__
#define LABIRINTO_HPP__
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<tuple>
#include<ctime>

using namespace std;

tuple<int, int> PosicaoInicial(int linha, int coluna, int tam_matriz);
tuple<int, int>LePrimeraLinha();
bool linhaVazia(const string& linha);
void LerArquivo(string **matriz, int tam_matriz, int qtd_matriz);
void ImprimirMatriz(string **matriz, int tam_matriz);
int RandomLinha(short int linha, short int tam_matriz);
int RandomColuna(short int coluna, short int tam_matriz);
void PercorrerMatriz(int **matriz, int linha, int coluna, int tam_matriz);
void CriandoArquivoParaCadaMatriz(string **matriz, int tam_matriz, int qtd_matriz, int& i);

#endif