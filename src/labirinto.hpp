#ifndef LABIRINTO_HPP__
#define LABIRINTO_HPP__
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<tuple>
#include<ctime>
#include<vector>
#include<stdlib.h>//colocada depois de o srand() estar funcioando sem;
#include<stdio.h>//para usar a remove() para remover os arquivos criados
#include<string.h>
#include <utility> //para usar o pair

using namespace std;
typedef struct SalvaCaminho{
    string nomeArq;
    vector<pair<int, int>> caminho;
}SalvaCaminho;

tuple<int, int> PosicaoInicial(int linha, int coluna, int tam_matriz);
tuple<int, int>LePrimeraLinha();
bool linhaVazia(const string& linha);
void LerArquivo(string **matriz, int tam_matriz, int qtd_matriz);
void ImprimirMatriz(string **matriz, int tam_matriz);
void PercorrerMatriz(string **matriz, int linha, int coluna, int tam_matriz, int& vida, int &totalCasas, int& totalItens, int& totalPerigo, string Nome1Arquivo, int& mochila, SalvaCaminho& caminho);
void CriandoArquivoParaCadaMatriz(string **matriz, int tam_matriz, int qtd_matriz, int& i);
void StartJogo(int linha, int coluna, int tam_matriz, int qtd_matriz, int& vida);
bool Vida(int& vida, int acao);
void MudaValorCaminho(string **matriz, int linha, int coluna);
void PassaNovaMatrizParaArquivo(string **matriz, string nomeArq, int tam_matriz);
void ExcluiArquivosCriados(int qtd_matriz);
void CasasPercorridasAoTodo(int &total);
void TotalDeItensConsumidos(int &total_itens);
void TotalDePerigosEnfrentados(int &totalPerigo);
int CasasTotal(int tam_matriz, int qtd_matriz);
void CasasNaoPercorridas(int& qtdCasasNaoPercorridas);
void MudaPosicaoAtual(string **matriz, int tam_matriz, int& linha_aux, int& coluna_aux, int acaoLinha, int acaoColuna, int& vida, int &totalCasas, int &totalItens, int &totalPerigo, int& mochila, SalvaCaminho& caminho, string nomeArq);
void CaminhoFoiPercorrido(SalvaCaminho& caminhoNaoPercorrido, int linha, int coluna, string nomeArq);
void RecebeNomeDosArquivosJaCriados(vector<SalvaCaminho>& caminho, int qtd_matriz);
int CasasNaoVisitadas(vector<SalvaCaminho>& caminho, int qtd_matriz, int tam_matriz);
#endif