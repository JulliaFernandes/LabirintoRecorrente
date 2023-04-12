#include<iostream>
#include<string>
#include"labirinto.hpp"

using namespace std;

int main(){
	clock_t inicio = clock();

	int tam_matriz, qtd_matriz;
	int linha=0, coluna=0, vida=10;
	
	tie(tam_matriz, qtd_matriz) = LePrimeraLinha();
	cout << "Codigo Jullia" << endl;
	cout << "Matriz [" << tam_matriz << "]" << "[" << tam_matriz << "]" <<endl;
	cout << "Existe " << qtd_matriz << " matriz(ez) no arquivo" << endl << endl; 

	string** matriz=new string*[tam_matriz];
    for(int i = 0; i < tam_matriz; i++){
        matriz[i]=new string[tam_matriz];
    }

	LerArquivo(matriz, tam_matriz, qtd_matriz);
	StartJogo(linha, coluna, tam_matriz, qtd_matriz, vida);

	clock_t fim = clock();

	double tempoTotalExecucao = (double) (fim-inicio)/CLOCKS_PER_SEC;
	cout << "TEMPO DE EXECUÇÂO É DE: " << tempoTotalExecucao << "SEGUNDOS" << endl; 
	return 0;
}