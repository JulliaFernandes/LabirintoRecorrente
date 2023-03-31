#include"labirinto.hpp"

using namespace std;

vector<string>nomesDosArquivos;

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
    //int linha=0, coluna=0;
    int i=0;

    //tie(linha, coluna) = PosicaoInicial(linha, coluna, tam_matriz);
    //out << "Posição inicial [" << linha << "]" << "[" << coluna << "]" <<endl;
    
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
                    //ImprimirMatriz(matriz, tam_matriz);
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
    //ImprimirMatriz(matriz, tam_matriz);
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

void PercorrerMatriz(string **matriz, int linha, int coluna, int tam_matriz, int& vida){
    srand(42);

    int linha_aux=linha, coluna_aux=coluna, i=1;
    int mochila=0, acao=0;
    bool auxVida = Vida(vida, acao);
    //string valorCaminho_str;
    //stringstream aux;

    ImprimirMatriz(matriz, tam_matriz);

    while(linha_aux < tam_matriz && coluna_aux < tam_matriz && auxVida != false){
        cout << "Entrou aqui: " << i << endl;
        i++;
        if(linha_aux != tam_matriz-1 && coluna_aux != tam_matriz-1){
            int direcaoAleatoria = rand()%8;
            cout << "\nNumero aleatorio: " << direcaoAleatoria << endl;
            switch(direcaoAleatoria){
                case 0: //irei para direita;
                    if(coluna_aux<tam_matriz-1 && matriz[linha_aux][coluna_aux+1] != "#"){
                        if(matriz[linha_aux][coluna_aux+1] == "*"){
                            acao=-1;
                            Vida(vida, acao);
                            //vida--;
                            coluna_aux++;
                            //cout << "\nAAAAAAAAAAACOLUNAAAA: " << coluna_aux << endl;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nVida: " << vida << endl;
                        }
                        else{ //é pq é um numero
                            coluna_aux++;
                            cout << "\nAAAAAAAAAAACOLUNAAAA: " << coluna_aux << endl;
                            /*valorCaminho_str =  matriz[linha_aux][coluna_aux];
                            valorCaminho = atoi(valorCaminho_str.c_str());
                            valorCaminho--;
                            aux << valorCaminho;
                            valorCaminho_str  = aux.str();
                            aux.str("");
                            matriz[linha_aux][coluna_aux]=valorCaminho_str;*/
                            MudaValorCaminho(matriz, linha_aux, coluna_aux);
                            mochila++;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nMochila: " << mochila << endl;
                        }
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 1: // irei para a esquerda
                    if(coluna_aux>0 && matriz[linha_aux][coluna_aux-1] != "#"){
                        if(matriz[linha_aux][coluna_aux-1] == "*"){
                            acao=-1;
                            Vida(vida, acao);
                            //vida--;
                            coluna_aux--;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nVida: " << vida << endl;
                        }
                        else{ // é pq é um numero
                            coluna_aux--;
                            MudaValorCaminho(matriz, linha_aux, coluna_aux);
                            mochila++;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nMochila: " << mochila << endl;
                        }
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 2:  //irei para cima
                    if(linha_aux>0 && matriz[linha_aux-1][coluna_aux] != "#"){
                        if(matriz[linha_aux-1][coluna_aux] == "*"){
                            acao=-1;
                            Vida(vida, acao);
                            //vida--;
                            linha_aux--;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nVida: " << vida << endl;
                        }
                        else{ //é pq é um numero
                            linha_aux--;
                            MudaValorCaminho(matriz, linha_aux, coluna_aux);
                            mochila++;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nMochila: " << mochila << endl;
                        }
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;
                    
                case 3: //irei para baixo
                    if(linha_aux<tam_matriz-1 && matriz[linha_aux+1][coluna_aux] != "#"){
                        if(matriz[linha_aux+1][coluna_aux] == "*"){
                            acao=-1;
                            Vida(vida, acao);
                            //vida--;
                            linha_aux++;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nVida: " << vida << endl;
                        }
                        else{ //é pq é numero
                            linha_aux++;
                            MudaValorCaminho(matriz, linha_aux, coluna_aux);
                            mochila++;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nMochila: " << mochila << endl;
                        }
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 4: //irei para diagonal-esquerda-superior
                    if(linha_aux != 0 && coluna_aux != 0 && matriz[linha_aux-1][coluna_aux-1] != "#"){
                        if(matriz[linha_aux-1][coluna_aux-1]  == "*"){
                            acao=-1;
                            Vida(vida, acao);
                            //vida--;
                            linha_aux--;
                            coluna_aux--;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nVida: " << vida << endl;
                        }
                        else{//é pq é um numero
                            linha_aux--;
                            coluna_aux--;
                            MudaValorCaminho(matriz, linha_aux, coluna_aux);
                            mochila++;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nMochila: " << mochila << endl;
                        }
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;
                
                case 5: //irei para a diagonal-direita-superior
                    if(linha_aux != 0 && coluna_aux != tam_matriz-1 && matriz[linha_aux-1][coluna_aux+1] != "#"){
                        if(matriz[linha_aux-1][coluna_aux+1] == "*"){
                            acao=-1;
                            Vida(vida, acao);
                            //vida--;
                            linha_aux--;
                            coluna_aux++;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nVida: " << vida << endl;
                        }
                        else{ //é pq é um numero
                            linha_aux--;
                            coluna_aux++;
                            MudaValorCaminho(matriz, linha_aux, coluna_aux);
                            mochila++;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nMochila: " << mochila << endl;
                        }
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;
                
                case 6: //irei para a diagonal-esquerda-inferior
                    if(linha_aux != tam_matriz-1 && coluna_aux != 0 && matriz[linha_aux+1][coluna_aux-1] != "#"){
                        if(matriz[linha_aux+1][coluna_aux-1] == "*"){
                            acao=-1;
                            Vida(vida, acao);
                            //vida--;
                            linha_aux++;
                            coluna_aux--;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nVida: " << vida << endl;
                        }
                        else{ //é pq é um numero
                            linha_aux++;
                            coluna_aux--;
                            MudaValorCaminho(matriz, linha_aux, coluna_aux);
                            mochila++;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nMochila: " << mochila << endl;
                        }
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;
                
                case 7: //irei para a diagonal-direita-inferior
                    if(linha_aux != tam_matriz-1 && coluna_aux != tam_matriz-1 && matriz[linha_aux+1][coluna_aux+1] != "#"){
                        if(matriz[linha_aux+1][coluna_aux+1] == "*"){
                            acao=-1;
                            Vida(vida, acao);
                            //vida--;
                            linha_aux++;
                            coluna_aux++;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nVida: " << vida << endl;
                        }
                        else{ //é pq é numero
                            linha_aux++;
                            coluna_aux++;
                            MudaValorCaminho(matriz, linha_aux, coluna_aux);
                            mochila++;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "\nMochila: " << mochila << endl;
                        }
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;
            }
        }
        else{ //estou ou na ultima linha ou na ultima coluna, e devo me teletransportar para a nova matriz
            //preciso so chamar para ir pro proximo.
            break;
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
        nomesDosArquivos.push_back(nomeArquivo);
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

void StartJogo(int linha, int coluna, int tam_matriz, int qtd_matriz, int& vida){
    ifstream arquivo_leitura;
    string linha_arq;
    string nomeArquivo, elemento;
    int i=0, aux_linha=0, aux_coluna=0, acao=0;
    bool  auxVida = Vida(vida, acao);

    

    string** matriz_aux=new string*[tam_matriz];
    for(int i = 0; i < tam_matriz; i++){
        matriz_aux[i]=new string[tam_matriz];
    }

    tie(linha, coluna) = PosicaoInicial(linha, coluna, tam_matriz);
    cout << "Posição inicial [" << linha << "]" << "[" << coluna << "]" <<endl;

    while(auxVida == true){ //ainda nao morri
        if(i<qtd_matriz){
            nomeArquivo=nomesDosArquivos[i];
            i++;

            cout << "NOME ARQUIVO: " << nomeArquivo << endl;
            arquivo_leitura.open(nomeArquivo, ios::in);
                while(!arquivo_leitura.eof()){
                    while(getline(arquivo_leitura, linha_arq, '\n')){
                        stringstream aux(linha_arq); 
                        while(getline(aux, elemento, ' ')){ //lendo a cada elemento presente na minha linha armazena para minha variavel elemento e tendo o delimitador ''
                            if(aux_coluna < tam_matriz && aux_linha < tam_matriz){
                                matriz_aux[aux_linha][aux_coluna] = elemento;
                                aux_coluna++;
                            } 
                        }

                        if(aux_coluna > 0 && aux_linha < tam_matriz){
                            aux_linha++;
                            aux_coluna=0;
                        }
                    }
                }
            arquivo_leitura.close();
            aux_coluna =0;
            aux_linha=0;
            
            //ImprimirMatriz(matriz_aux, tam_matriz);

            PercorrerMatriz(matriz_aux, linha, coluna, tam_matriz, vida);
            auxVida = Vida(vida, acao);
            cout << "AUXX VIDAAAAAA1 " << auxVida << endl << endl;

            
             

            /*linha = rand()%tam_matriz;
            coluna = rand()%tam_matriz;
            cout << endl << endl << endl << endl << endl;
            cout << "Posição[" << linha << "]" << "[" << coluna << "]" <<endl;*/

        }
        else{ //acabei todas as matrizes e devo começar novamente da primeira matriz
            i=0;
            nomeArquivo=nomesDosArquivos[i];

            cout << "NOME ARQUIVO: " << nomeArquivo << endl;
            arquivo_leitura.open(nomeArquivo, ios::in);
                while(!arquivo_leitura.eof()){
                    while(getline(arquivo_leitura, linha_arq, '\n')){
                        stringstream aux(linha_arq); 
                        while(getline(aux, elemento, ' ')){ //lendo a cada elemento presente na minha linha armazena para minha variavel elemento e tendo o delimitador ''
                            if(aux_coluna < tam_matriz && aux_linha < tam_matriz){
                                matriz_aux[aux_linha][aux_coluna] = elemento;
                                aux_coluna++;
                            } 
                        }

                        if(aux_coluna > 0 && aux_linha < tam_matriz){
                            aux_linha++;
                            aux_coluna=0;
                        }
                    }
                }
            arquivo_leitura.close();
            aux_coluna =0;
            aux_linha=0;
            //ImprimirMatriz(matriz_aux, tam_matriz);

            PercorrerMatriz(matriz_aux, linha, coluna, tam_matriz, vida);
            auxVida = Vida(vida, acao);
            cout << "AUXX VIDAAAAAA " << auxVida << endl << endl;

            /*linha = rand()%tam_matriz;
            coluna = rand()%tam_matriz;
            cout << endl << endl << endl << endl << endl;
            cout << "Posição[" << linha << "]" << "[" << coluna << "]" <<endl;*/
        }
        cout << endl << endl << endl << endl;
        cout << "----------------------------------------------------------" << endl;
        ImprimirMatriz(matriz_aux, tam_matriz);
    }
}

bool Vida(int& vida, int acao){
    if(vida > 1){
        if(acao == 1){ //é porque vou ganhar vida
            vida++;
            return true;
        }
        else if(acao == 0){ //é so para saber se ainda tenho vida, feito para usar na funçao de startjogo
            return true; //ainda tenho vida
        }
        else{ //perdendo vida, acao é -1;
            vida--;
            //return false;
            return true;
        }
    }
    else{ //vida em 1 ai, vejo se vou morrer ou ganhar mais vida
        if(acao == 1){
            vida++;
            return true;
        }
        else if(acao == 0){//é so para saber se ainda tenho vida, feito para usar na funçao de startjogo
            if(vida!=0){
                return true; //ainda tenho vida
            }
            else{
                return false;
            }  
        }
        else{ //é pq é -1 a minha vida e vou morrer
            vida--;
            cout << "Voce morreu :(" << endl;
            return false; 
        }
    }
}

void MudaValorCaminho(string **matriz, int linha, int coluna){
    string valorCaminho_str;
    int valorCaminho;
    stringstream aux;

    valorCaminho_str =  matriz[linha][coluna];
    valorCaminho = atoi(valorCaminho_str.c_str());
    valorCaminho--;
    aux << valorCaminho;
    valorCaminho_str  = aux.str();
    aux.str("");
    matriz[linha][coluna]=valorCaminho_str;
}