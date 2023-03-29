#include"labirinto.hpp"

using namespace std;

tuple<int, int> PosicaoInicial(int linha, int coluna, int tam_matriz){
    cout << "Qual posição deseja começar: " << endl << ">";
	cin >> linha;
	cout << ">";
	cin >>coluna;
	while(coluna>=tam_matriz || coluna<0 || linha>=tam_matriz || linha<0){
		cout << "Posição invalida. Digite somente valores entre 0 e " << tam_matriz-1 << endl;
		cout << "Qual posição deseja começar: " << endl << ">";
		cin >> linha;
		cout << ">";
		cin >>coluna;
	}

    return make_tuple(linha, coluna);
}

tuple<int, int> LePrimeraLinha(){
    ifstream arquivo;
    string linha, valor_str, aux_str, elemento, qtdMatriz_str;
    int aux=0, tam=0, cont=0, qtdMatriz;

    arquivo.open("dataset/input.data", ios::in);
    //while(cont == 0){
        while(getline(arquivo, linha, '\n')){
            if(cont == 0){
                stringstream aux_str(linha);
                while(getline(aux_str, elemento, ' ')){
                    if(aux==2){
                        qtdMatriz_str = elemento;
                        qtdMatriz = atoi(qtdMatriz_str.c_str());
                    }
                    else{
                        valor_str  = elemento;
                        tam = atoi(valor_str.c_str());
                        aux++;
                    }
                }
                cont++;
            }
        }
   // }
    arquivo.close();
    return make_tuple(tam, qtdMatriz);
}

bool linhaVazia(const string& linha){
    for (char c : linha) {
        if (!isspace(c)) {
            // Se o caractere não for espaço em branco, a linha não está vazia
            return false;
        }
    }
    // Se todos os caracteres forem espaços em branco, a linha está vazia
    return true;
}

void LerArquivo(string **matriz, int tam_matriz, int qtd_matriz){
    ifstream arquivo;
    string linha_arq, elemento;
    int aux_linha=0, aux_coluna=0, aux_tam=0;
    int linha=0, coluna=0, i=0;

    tie(linha, coluna) = PosicaoInicial(linha, coluna, tam_matriz);
    cout << "Posição inicial [" << linha << "]" << "[" << coluna << "]" <<endl;
    
    arquivo.open("dataset/input.data", ios::in);

    while(!arquivo.eof()){
        while(getline(arquivo, linha_arq, '\n')){
            if(aux_tam==0){
                aux_tam++;
            }
            else{
                if(linhaVazia(linha_arq)){
                    cout << "---------------------------------------------";
                    cout << "\n\t---Nova Matriz---" << endl;
                    CriandoArquivoParaCadaMatriz(matriz, tam_matriz, qtd_matriz, i);
                    ImprimirMatriz(matriz, tam_matriz);
                    aux_coluna = 0;
                    aux_linha = 0;
                }
                else{
                    //está criando um fluxo de caracteres para que a função getline possa ler e manipular os dados
                    stringstream aux(linha_arq);

                    //lendo a cada elemento presente na minha linha armazena para minha variavel elemento e tendo o delimitador ''
                    while(getline(aux, elemento, ' ')){
                        if(aux_coluna < tam_matriz && aux_linha < tam_matriz){
                            matriz[aux_linha][aux_coluna] = elemento;
                            aux_coluna++;
                        } 
                    }

                    if(aux_coluna > 0 && aux_linha < tam_matriz){
                        aux_linha++;
                        aux_coluna=0;
                    }
                }
            }    
        }
    }
    arquivo.close();  

    cout << "---------------------------------------------";
    cout << "\n\taa---Nova Matriz---" << endl;
    CriandoArquivoParaCadaMatriz(matriz, tam_matriz, qtd_matriz, i);
    ImprimirMatriz(matriz, tam_matriz);
}

void ImprimirMatriz(string **matriz, int tam_matriz){
    cout << endl;
    for (int i=0; i<tam_matriz; i++) {
        for (int j=0; j<tam_matriz; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

int RandomLinha(short int linha, short int tam_matriz){
    short int linha_randomica=0;
    srand(time(nullptr));
    if(linha == 0){
        linha_randomica = rand() %2;
        cout << "Randomico" << linha_randomica << endl;
    }
    else if(linha == tam_matriz){
        linha_randomica = rand() %2;
        if(linha_randomica == 1){
            linha_randomica*=-1;
        }
        cout << "Randomico" << linha_randomica << endl;
    }
    else{
        string vetor_str[] = {"-1", "1", "0"};
        string num_str = vetor_str[rand()%3];
        linha_randomica = atoi(num_str.c_str());
        cout << "Randomico" << linha_randomica << endl;
    }

    return linha_randomica;
}
int RandomColuna(short int coluna, short int tam_matriz){
    short int coluna_randomica=0;
    srand(time(nullptr));
    if(coluna == 0){
        coluna_randomica = rand() %2;
        cout << "Randomico" << coluna_randomica << endl;
    }
    else if(coluna == tam_matriz){
        coluna_randomica = rand() %2;
        if(coluna_randomica == 1){
            coluna_randomica*=-1;
        }
        cout << "Randomico" << coluna_randomica << endl;
    }
    else{
        string vetor_str[] = {"-1", "1", "0"};
        string num_str = vetor_str[rand()%3];
        coluna_randomica = atoi(num_str.c_str());
        cout << "Randomico" << coluna_randomica << endl;
    }

    return coluna_randomica;
}

void PercorrerMatriz(string **matriz, int linha, int coluna, int tam_matriz){
    srand(time(nullptr));

    int linha_aux=linha, coluna_aux=coluna;
    int vida=10, valorCaminho=0, mochila;
    string valorCaminho_str;
    stringstream aux;


    while(linha_aux < tam_matriz && coluna_aux < tam_matriz){
        if(linha_aux != tam_matriz-1 || coluna_aux != tam_matriz-1){
            int direcaoAleatoria = rand()%8;

            switch(direcaoAleatoria){
                case 0: //irei para direita;
                    if(coluna_aux<tam_matriz-1 && matriz[linha_aux][coluna_aux+1] != "#"){
                        if(matriz[linha_aux][coluna_aux+1] == "*"){
                            vida--;
                            coluna_aux++;
                        }
                        else{ //é pq é um numero
                            coluna_aux++;
                            valorCaminho_str =  matriz[linha_aux][coluna_aux];
                            valorCaminho = atoi(valorCaminho_str.c_str());
                            valorCaminho--;
                            aux << valorCaminho;
                            valorCaminho_str  = aux.str();
                            matriz[linha_aux][coluna_aux]=valorCaminho_str;
                            mochila++;
                        }
                    }
                    break;

                case 1: // irei para a esquerda
                    if(coluna_aux>0 && matriz[linha_aux][coluna_aux-1] != "#"){
                        if(matriz[linha_aux][coluna_aux-1] == "*"){
                            vida--;
                            coluna_aux--;
                        }
                        else{ // é pq é um numero
                            coluna_aux--;
                            valorCaminho_str =  matriz[linha_aux][coluna_aux];
                            valorCaminho = atoi(valorCaminho_str.c_str());
                            valorCaminho--;
                            aux << valorCaminho;
                            valorCaminho_str  = aux.str();
                            matriz[linha_aux][coluna_aux]=valorCaminho_str;
                            mochila++;
                        }
                    }
                    break;

                case 2:  //irei para cima
                    if(linha_aux>0 && matriz[linha_aux-1][coluna_aux] != "#"){
                        if(matriz[linha_aux-1][coluna_aux] == "*"){
                            vida--;
                            linha_aux--;
                        }
                        else{ //é pq é um numero
                            linha_aux--;
                            valorCaminho_str =  matriz[linha_aux][coluna_aux];
                            valorCaminho = atoi(valorCaminho_str.c_str());
                            valorCaminho--;
                            aux << valorCaminho;
                            valorCaminho_str  = aux.str();
                            matriz[linha_aux][coluna_aux]=valorCaminho_str;
                            mochila++;
                        }
                    }
                    break;
                    
                case 3: //irei para baixo
                    if(linha_aux<tam_matriz-1 && matriz[linha_aux+1][coluna_aux] != "#"){
                        if(matriz[linha_aux+1][coluna_aux] == "*"){
                            vida--;
                            linha_aux++;
                        }
                        else{ //é pq é numero
                            linha_aux++;
                            valorCaminho_str =  matriz[linha_aux][coluna_aux];
                            valorCaminho = atoi(valorCaminho_str.c_str());
                            valorCaminho--;
                            aux << valorCaminho;
                            valorCaminho_str  = aux.str();
                            matriz[linha_aux][coluna_aux]=valorCaminho_str;
                            mochila++;
                        }
                    }
                    break;

                case 4: //irei para diagonal-esquerda-superior
                    if(linha_aux != 0 && coluna_aux != 0 && matriz[linha_aux-1][coluna_aux-1] != "#"){
                        if(matriz[linha_aux-1][coluna_aux-1]  == "*"){
                            vida--;
                            linha_aux--;
                            coluna_aux--;
                        }
                        else{//é pq é um numero
                            linha_aux--;
                            coluna_aux--;
                            valorCaminho_str =  matriz[linha_aux][coluna_aux];
                            valorCaminho = atoi(valorCaminho_str.c_str());
                            valorCaminho--;
                            aux << valorCaminho;
                            valorCaminho_str  = aux.str();
                            matriz[linha_aux][coluna_aux]=valorCaminho_str;
                            mochila++;
                        }
                    }
                    break;
                
                case 5: //irei para a diagonal-direita-superior
                    if(linha_aux != 0 && coluna_aux != tam_matriz-1 && matriz[linha_aux-1][coluna_aux+1] != "#"){
                        if(matriz[linha_aux-1][coluna_aux+1] == "*"){
                            vida--;
                            linha_aux--;
                            coluna_aux++;
                        }
                        else{ //é pq é um numero
                            linha_aux--;
                            coluna_aux++;
                            valorCaminho_str =  matriz[linha_aux][coluna_aux];
                            valorCaminho = atoi(valorCaminho_str.c_str());
                            valorCaminho--;
                            aux << valorCaminho;
                            valorCaminho_str  = aux.str();
                            matriz[linha_aux][coluna_aux]=valorCaminho_str;
                            mochila++;
                        }
                    }
                    break;
                
                case 6: //irei para a diagonal-esquerda-inferior
                    if(linha_aux != tam_matriz-1 && coluna_aux != 0 && matriz[linha_aux+1][coluna_aux-1] != "#"){
                        if(matriz[linha_aux+1][coluna_aux-1] == "*"){
                            vida--;
                            linha_aux++;
                            coluna_aux--;
                        }
                        else{ //é pq é um numero
                            linha_aux++;
                            coluna_aux--;
                            valorCaminho_str =  matriz[linha_aux][coluna_aux];
                            valorCaminho = atoi(valorCaminho_str.c_str());
                            valorCaminho--;
                            aux << valorCaminho;
                            valorCaminho_str  = aux.str();
                            matriz[linha_aux][coluna_aux]=valorCaminho_str;
                            mochila++;
                        }
                    }
                    break;
                
                case 7: //irei para a diagonal-direita-inferior
                    if(linha_aux != tam_matriz-1 && coluna_aux != tam_matriz-1 && matriz[linha_aux+1][coluna_aux+1] != "#"){
                        if(matriz[linha_aux+1][coluna_aux+1] == "*"){
                            vida--;
                            linha_aux++;
                            coluna_aux++;
                        }
                        else{ //é pq é numero
                            linha_aux++;
                            coluna_aux++;
                            valorCaminho_str =  matriz[linha_aux][coluna_aux];
                            valorCaminho = atoi(valorCaminho_str.c_str());
                            valorCaminho--;
                            aux << valorCaminho;
                            valorCaminho_str  = aux.str();
                            matriz[linha_aux][coluna_aux]=valorCaminho_str;
                            mochila++;
                        }
                    }
                    break;
            }
        }
        else{ //estou ou na ultima linha ou na ultima coluna, e devo me teletransportar para a nova matriz
            if(matriz[linha_aux][coluna_aux] == "*"){
                vida--;
            }
            else{//é pq é um numero
                valorCaminho_str =  matriz[linha_aux][coluna_aux];
                valorCaminho = atoi(valorCaminho_str.c_str());
                valorCaminho--;
                aux << valorCaminho;
                valorCaminho_str  = aux.str();
                matriz[linha_aux][coluna_aux]=valorCaminho_str;
                mochila++;
            }
        }
    }
}

void CriandoArquivoParaCadaMatriz(string **matriz, int tam_matriz, int qtd_matriz, int& i){
    string PATH = "dataset/";
    string nomeArquivo;
    string numeroArquivo_str;
    int numeroArquivo;
    stringstream aux;

    if(i<qtd_matriz){
        numeroArquivo = i+1;
        aux << numeroArquivo;
        numeroArquivo_str = aux.str();
        nomeArquivo = PATH+"matriz"+numeroArquivo_str+".data";
        aux.str("");
        i++;
    }
    cout << "Nome: " << nomeArquivo << endl;

    ofstream arquivo;
    arquivo.open(nomeArquivo, ios::out);
        for (int i=0; i<tam_matriz; i++) {
            for (int j=0; j<tam_matriz; j++) {
                arquivo << matriz[i][j] << " ";
            }
            arquivo << endl;
        }
    arquivo.close();
}