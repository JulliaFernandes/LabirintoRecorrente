#include<iostream>
#include<string>
#include"labirinto.hpp"
#include<chrono>

using namespace std;

int main(){
	auto inicio = chrono::high_resolution_clock::now();

	int tam_matriz, qtd_matriz;
	int linha=0, coluna=0, vida=10;
	
	tie(tam_matriz, qtd_matriz) = LePrimeraLinha();
	cout << "-------BEM VINDO(A) AO JOGO THE MAZE-------" << endl;
	cout << ">Você está pronto para embarcar em uma jornada emocionante através de um labirinto repleto de desafios e surpresas?" << endl;
	cout << ">Sua missão é percorrer um caminho completamente zerado, no qual tenha pego todos os itens." << endl;
	cout << " Mas prepare-se para enfrentar obstáculos perigosos enquanto você luta para encontrar a saída." << endl;
	cout << ">Voce deve enfrentar " << qtd_matriz << " labirintos. Todos de tamanho [" << tam_matriz << "]" << "[" << tam_matriz << "]." << endl; 
	cout << " Será que consiguirá completar sua missão?" << endl;
	cout << "Boa sorte e que os jogos comecem" << endl << endl;
	

	string** matriz=new string*[tam_matriz];
    for(int i = 0; i < tam_matriz; i++){
        matriz[i]=new string[tam_matriz];
    }

	LerArquivo(matriz, tam_matriz, qtd_matriz);
	StartJogo(linha, coluna, tam_matriz, qtd_matriz, vida);

	auto fim = chrono::high_resolution_clock::now();
	auto tempoTotalExecucao = chrono::duration_cast<chrono::seconds>(fim - inicio);
	cout << "TEMPO DE EXECUÇÂO É DE: " << tempoTotalExecucao.count() << " SEGUNDOS" << endl; 
	
	return 0;
}