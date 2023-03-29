#include<iostream>
#include<string>
#include"labirinto.hpp"

using namespace std;

int main(){
	
	short int tam_matriz, qtd_matriz;
	//int i=0;
	//int linha=0, coluna=0;
	
	tie(tam_matriz, qtd_matriz) = LePrimeraLinha();
	cout << "Matriz [" << tam_matriz << "]" << "[" << tam_matriz << "]" <<endl;
	cout << "Existe " << qtd_matriz << " matriz(ez) no arquivo" << endl; 

	string** matriz=new string*[tam_matriz];
    for(int i = 0; i < tam_matriz; i++){
        matriz[i]=new string[tam_matriz];
    }

	//tie(linha, coluna) = PosicaoInicial(linha, coluna, tam_matriz);
	LerArquivo(matriz, tam_matriz, qtd_matriz);
	//RandomLinha(tam_matriz, tam_matriz);
	//CriandoArquivoParaCadaMatriz(qtd_matriz, i);

	//cout << "Posição inicial [" << linha << "]" << "[" << coluna << "]" <<endl;

	return 0;
}