#include "labirinto.hpp"

using namespace std;

vector<string> nomesDosArquivos;
bool CaminhoEhVazio=true;
bool comeco=false;
bool passouTodasMatrizes=false;
int inicioLinha, inicioColuna;
int contVezesEntradas=0;

tuple<int, int> PosicaoInicial(int linha, int coluna, int tam_matriz)
{
    cout << "Qual posição deseja começar: " << endl << ">";
    cin >> linha;
    cout << ">";
    cin >> coluna;
    while (coluna >= tam_matriz || coluna < 0 || linha >= tam_matriz || linha < 0){
        cout << "Posição invalida. Digite somente valores entre 0 e " << tam_matriz - 1 << endl;
        cout << "Qual posição deseja começar: " << endl << ">";
        cin >> linha;
        cout << ">";
        cin >> coluna;
    }

    return make_tuple(linha, coluna);
}

tuple<int, int> LePrimeraLinha()
{
    ifstream arquivo;
    string linha, valor_str, aux_str, elemento, qtdMatriz_str;
    int aux = 0, tam = 0, cont = 0, qtdMatriz, cont2 = 0;

    arquivo.open("dataset/input.data", ios::in);
    while (getline(arquivo, linha, '\n')){
        if (cont == 0){
            stringstream aux_str(linha);
            while (getline(aux_str, elemento, ' ')){
                if (aux == 2){
                    if (cont2 == 0){
                        qtdMatriz_str = elemento;
                        qtdMatriz = atoi(qtdMatriz_str.c_str());
                        cont2++;
                    }
                }
                else{
                    valor_str = elemento;
                    tam = atoi(valor_str.c_str());
                    aux++;
                }
            }
            cont++;
        }
    }
    arquivo.close();
    return make_tuple(tam, qtdMatriz);
}

bool linhaVazia(const string &linha)
{
    for (char c : linha){
        if (!isspace(c)){ // Se o caractere não for espaço em branco, a linha não está vazia
            return false;
        }
    }
    // Se todos os caracteres forem espaços em branco, a linha está vazia
    return true;
}

void LerArquivo(string **matriz, int tam_matriz, int qtd_matriz)
{
    ifstream arquivo;
    string linha_arq, elemento;
    int aux_linha = 0, aux_coluna = 0, aux_tam = 0;
    int i = 0;

    arquivo.open("dataset/input.data", ios::in);

    while (!arquivo.eof()){
        while (getline(arquivo, linha_arq, '\n')){
            if (aux_tam == 0){
                aux_tam++;
            }
            else{
                if (linhaVazia(linha_arq)){
                    CriandoArquivoParaCadaMatriz(matriz, tam_matriz, qtd_matriz, i);
                    aux_coluna = 0;
                    aux_linha = 0;
                }
                else{
                    // está criando um fluxo de caracteres para que a função getline possa ler e manipular os dados
                    stringstream aux(linha_arq);

                    while (getline(aux, elemento, ' ')){// lendo a cada elemento presente na minha linha armazena para minha variavel elemento e tendo o delimitador ''
                        if (aux_coluna < tam_matriz && aux_linha < tam_matriz){
                            matriz[aux_linha][aux_coluna] = elemento;
                            aux_coluna++;
                        }
                    }

                    if (aux_coluna > 0 && aux_linha < tam_matriz){
                        aux_linha++;
                        aux_coluna = 0;
                    }
                }
            }
        }
    }
    arquivo.close();
    CriandoArquivoParaCadaMatriz(matriz, tam_matriz, qtd_matriz, i);
}

void ImprimirMatriz(string **matriz, int tam_matriz)
{
    cout << endl;
    for (int i = 0; i < tam_matriz; i++){
        for (int j = 0; j < tam_matriz; j++){
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void PercorrerMatriz(string **matriz, int linha, int coluna, int tam_matriz, int &vida, int &totalCasas, int &totalItens, int &totalPerigo, string Nome1Arquivo, int& mochila, SalvaCaminho& caminho)
{
    srand(42);

    int linha_aux = linha, coluna_aux = coluna;
    int acao = 0;
    bool auxVida = Vida(vida, acao);
    int acaoLinha=0, acaoColuna=0;

    MudaPosicaoAtual(matriz, linha_aux, coluna_aux, acaoLinha, acaoColuna, vida, totalCasas, totalItens, totalPerigo, mochila, caminho, Nome1Arquivo);
    while (linha_aux < tam_matriz && coluna_aux < tam_matriz && auxVida != false){
        //cout << ">>Posição atual[" << linha_aux << "]" << "[" << coluna_aux << "]" << endl;
        if (linha_aux != tam_matriz - 1 && coluna_aux != tam_matriz - 1){   
            int direcaoAleatoria = rand() % 8;
            //cout << "Numero aleatorio: " << direcaoAleatoria << endl << endl;

            switch (direcaoAleatoria){
                case 0: // irei para direita;
                    if(coluna_aux < tam_matriz - 1 && matriz[linha_aux][coluna_aux + 1] != "#"){
                        acaoLinha=0;
                        acaoColuna=1;
                        MudaPosicaoAtual(matriz, linha_aux, coluna_aux, acaoLinha, acaoColuna, vida, totalCasas, totalItens, totalPerigo, mochila, caminho, Nome1Arquivo);
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 1: // irei para a esquerda
                    if (coluna_aux > 0 && matriz[linha_aux][coluna_aux - 1] != "#"){
                        acaoLinha=0;
                        acaoColuna=-1;
                        MudaPosicaoAtual(matriz, linha_aux, coluna_aux, acaoLinha, acaoColuna, vida, totalCasas, totalItens, totalPerigo, mochila, caminho, Nome1Arquivo);
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 2: // irei para cima
                    if (linha_aux > 0 && matriz[linha_aux - 1][coluna_aux] != "#"){
                        acaoLinha=-1;
                        acaoColuna=0;
                        MudaPosicaoAtual(matriz, linha_aux, coluna_aux, acaoLinha, acaoColuna, vida, totalCasas, totalItens, totalPerigo, mochila, caminho, Nome1Arquivo);             
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 3: // irei para baixo
                    if (linha_aux < tam_matriz - 1 && matriz[linha_aux + 1][coluna_aux] != "#"){
                        acaoLinha=1;
                        acaoColuna=0;
                        MudaPosicaoAtual(matriz, linha_aux, coluna_aux, acaoLinha, acaoColuna, vida, totalCasas, totalItens, totalPerigo, mochila, caminho, Nome1Arquivo);
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 4: // irei para diagonal-esquerda-superior
                    if (linha_aux != 0 && coluna_aux != 0 && matriz[linha_aux - 1][coluna_aux - 1] != "#"){
                        acaoLinha=-1;
                        acaoColuna=-1;
                        MudaPosicaoAtual(matriz, linha_aux, coluna_aux, acaoLinha, acaoColuna, vida, totalCasas, totalItens, totalPerigo, mochila, caminho, Nome1Arquivo);
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 5: // irei para a diagonal-direita-superior
                    if (linha_aux != 0 && coluna_aux != tam_matriz - 1 && matriz[linha_aux - 1][coluna_aux + 1] != "#"){
                        acaoLinha=-1;
                        acaoColuna=1;
                        MudaPosicaoAtual(matriz, linha_aux, coluna_aux, acaoLinha, acaoColuna, vida, totalCasas, totalItens, totalPerigo, mochila, caminho, Nome1Arquivo);
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 6: // irei para a diagonal-esquerda-inferior
                    if (linha_aux != tam_matriz - 1 && coluna_aux != 0 && matriz[linha_aux + 1][coluna_aux - 1] != "#"){
                        acaoLinha=1;
                        acaoColuna=-1;
                        MudaPosicaoAtual(matriz, linha_aux, coluna_aux, acaoLinha, acaoColuna, vida, totalCasas, totalItens, totalPerigo, mochila, caminho, Nome1Arquivo);
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 7: // irei para a diagonal-direita-inferior
                    if (linha_aux != tam_matriz - 1 && coluna_aux != tam_matriz - 1 && matriz[linha_aux + 1][coluna_aux + 1] != "#"){
                        acaoLinha=1;
                        acaoColuna=1;
                        MudaPosicaoAtual(matriz, linha_aux, coluna_aux, acaoLinha, acaoColuna, vida, totalCasas, totalItens, totalPerigo, mochila, caminho, Nome1Arquivo);
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;
            }
        }
         else{ // estou ou na ultima linha ou na ultima coluna, e devo me teletransportar para a nova matriz. 
            break;
        }
        contVezesEntradas++; 
    }
}

void CriandoArquivoParaCadaMatriz(string **matriz, int tam_matriz, int qtd_matriz, int &i)
{
    string PATH = "dataset/";
    string nomeArquivo;
    string numeroArquivo_str;
    int numeroArquivo;
    stringstream aux;
    if (i < qtd_matriz){
        numeroArquivo = i + 1;
        aux << numeroArquivo;
        numeroArquivo_str = aux.str();
        nomeArquivo = PATH + "matriz" + numeroArquivo_str + ".data";
        nomesDosArquivos.push_back(nomeArquivo);
        aux.str("");
        i++;
    }

    ofstream arquivo;
    arquivo.open(nomeArquivo, ios::out);
    for (int i = 0; i < tam_matriz; i++){
        for (int j = 0; j < tam_matriz; j++){
            arquivo << matriz[i][j] << " ";
        }
        arquivo << endl;
    }
    arquivo.close();
}

void StartJogo(int linha, int coluna, int tam_matriz, int qtd_matriz, int &vida)
{
    ifstream arquivo_leitura;
    string linha_arq;
    string nomeArquivo, elemento, nome1arquivo;
    int i = 0, aux_linha = 0, aux_coluna = 0, acao = 0;
    bool auxVida = Vida(vida, acao);
    int mochila=0, totalCasas = 0, totalItens = 0, totalPerigo = 0, qtdCasasNaoVisitadas=0, qtdCasasVisitadas=0;
    vector<SalvaCaminho>CaminhoPercorrido;
    CaminhoPercorrido.resize(qtd_matriz);
    SalvaCaminho auxCaminhoPercorrido;

    nome1arquivo=nomesDosArquivos[i];

    string **matriz_aux = new string *[tam_matriz];
    for (int i = 0; i < tam_matriz; i++){
        matriz_aux[i] = new string[tam_matriz];
    }

    tie(linha, coluna) = PosicaoInicial(linha, coluna, tam_matriz);
    cout << "Posição inicial [" << linha << "]" << "[" << coluna << "]" << endl;
    inicioLinha = linha;
    inicioColuna = coluna;
    RecebeNomeDosArquivosJaCriados(CaminhoPercorrido, qtd_matriz);

    while (auxVida == true){
        if (i == qtd_matriz){   
            passouTodasMatrizes=true;
            i = 0;
        }
        nomeArquivo = nomesDosArquivos[i];
        //RecebeNomeDosArquivosJaCriados(CaminhoPercorrido, qtd_matriz);
        auxCaminhoPercorrido = CaminhoPercorrido[i];

        if(contVezesEntradas!=0){
            if(nomeArquivo == nomesDosArquivos[i] && linha == inicioLinha && coluna == inicioColuna){
                comeco=true;
            }
        }
        if(passouTodasMatrizes && comeco){ //se passou em todas as matrizes se passou na posição inicial
            if(CaminhoEhVazio==true){
                cout << "\n-----VITÓRIA!! VOCE CHEGOU AO FINAL DO JOGO, PARABENS :) !! -----" << endl;
                break;
            }
            CaminhoEhVazio=true;
            passouTodasMatrizes=false;
            comeco=false;
        }
        
        arquivo_leitura.open(nomeArquivo, ios::in);
        while (!arquivo_leitura.eof()){
            while (getline(arquivo_leitura, linha_arq, '\n')) {
                stringstream aux(linha_arq);
                while (getline(aux, elemento, ' ')) { // lendo a cada elemento presente na minha linha armazena para minha variavel elemento e tendo o delimitador ''
                    if (aux_coluna < tam_matriz && aux_linha < tam_matriz){
                        matriz_aux[aux_linha][aux_coluna] = elemento;
                        aux_coluna++;
                    }
                }

                if (aux_coluna > 0 && aux_linha < tam_matriz){
                    aux_linha++;
                    aux_coluna = 0;
                }
            }
        }
        arquivo_leitura.close();
        aux_coluna = 0;
        aux_linha = 0;

        bool presoOuNao=ConfereSeEnvoltaEhParede(matriz_aux, linha, coluna, tam_matriz);//se for true nao posso andar gera dnv;

        if (matriz_aux[linha][coluna] == "#" || linha == tam_matriz-1 || coluna == tam_matriz-1 || presoOuNao==true){   
            while (matriz_aux[linha][coluna] == "#" || linha == tam_matriz-1 || coluna == tam_matriz-1 || presoOuNao==true){
                linha = rand() % tam_matriz;
                coluna = rand() % tam_matriz;
                cout << "Posição inicial mudada [" << linha << "]" << "[" << coluna << "]" << endl;
                inicioLinha=linha;
                inicioColuna=coluna;
                presoOuNao = ConfereSeEnvoltaEhParede(matriz_aux, linha, coluna, tam_matriz);
            }
            PercorrerMatriz(matriz_aux, linha, coluna, tam_matriz, vida, totalCasas, totalItens, totalPerigo, nomeArquivo, mochila, auxCaminhoPercorrido);
            auxVida = Vida(vida, acao);
            PassaNovaMatrizParaArquivo(matriz_aux, nomeArquivo, tam_matriz);
            CaminhoPercorrido[i]=auxCaminhoPercorrido;
    
        }
        else{
            PercorrerMatriz(matriz_aux, linha, coluna, tam_matriz, vida, totalCasas, totalItens, totalPerigo, nomeArquivo, mochila, auxCaminhoPercorrido);
            auxVida = Vida(vida, acao);
            PassaNovaMatrizParaArquivo(matriz_aux, nomeArquivo, tam_matriz);
            CaminhoPercorrido[i]=auxCaminhoPercorrido;
    
        }
        i++;
    }

    for(int j=0; j<qtd_matriz; j++){
        qtdCasasVisitadas += CaminhoPercorrido[j].caminho.size();
    } 
    qtdCasasNaoVisitadas=CasasNaoVisitadas(CaminhoPercorrido, qtd_matriz, tam_matriz);
    cout << " ________________________________________________________" << endl << "|" << "\t\t\t\t\t\t\t |";
    cout << "\n >TOTAL DE CASAS PERCORRIDAS: " << totalCasas << endl;
    cout << " >TOTAL DE ITENS CONSUMIDOS: " << totalItens << endl;
    cout << " >TOTAL DE PERIGOS ENFRENTADOS: " << totalPerigo << endl;
    cout << " >QUATIDADE DE CASAS VISITADAS: " << qtdCasasVisitadas << endl;
    cout << " >QUATIDADE DE CASAS NAO VISITADAS: " << qtdCasasNaoVisitadas << endl;
    cout << "|________________________________________________________"<< "|" << endl;
    SalvaMatrizesAlteradas(tam_matriz, qtd_matriz);
    ExcluiArquivosCriados(qtd_matriz);
}

bool Vida(int &vida, int acao)
{
    if (vida > 1){
        if (acao == 1){ // é porque vou ganhar vida
            vida++;
            return true;
        }
        else if (acao == 0){ // é so para saber se ainda tenho vida, feito para usar na funçao de startjogo
            return true; // ainda tenho vida
        }
        else{ // perdendo vida, acao é -1;
            vida--;
            return true;
        }
    }
    else{ // vida em 1 ai, vejo se vou morrer ou ganhar mais vida
        if (acao == 1){
            vida++;
            return true;
        }
        else if (acao == 0){ // é so para saber se ainda tenho vida, feito para usar na funçao de startjogo
            if (vida != 0){
                return true; // ainda tenho vida
            }
            else{
                return false;
            }
        }
        else{ // é pq é -1 a minha vida e vou morrer
            vida--;
            cout << "\n-------GAME OVER!! SUAS VIDAS ACABRAM :( ------" << endl;
            return false;
        }
    }
}

void MudaValorCaminho(string **matriz, int linha, int coluna)
{
    string valorCaminho_str;
    int valorCaminho;
    stringstream aux;

    valorCaminho_str = matriz[linha][coluna];
    valorCaminho = atoi(valorCaminho_str.c_str());
    valorCaminho--;
    aux << valorCaminho;
    valorCaminho_str = aux.str();
    aux.str("");
    matriz[linha][coluna] = valorCaminho_str;
}

void PassaNovaMatrizParaArquivo(string **matriz, string nomeArq, int tam_matriz)
{
    ofstream arquivo_escrita;

    arquivo_escrita.open(nomeArq, ios::out);
    for (int i = 0; i < tam_matriz; i++){
        for (int j = 0; j < tam_matriz; j++){
            arquivo_escrita << matriz[i][j] << " ";
        }
        arquivo_escrita << endl;
    }
    arquivo_escrita.close();
}

void ExcluiArquivosCriados(int qtd_matriz)
{
    for (int i = 0; i < qtd_matriz; i++){
        char nomeArquivoRemovido[100];
        strcpy(nomeArquivoRemovido, nomesDosArquivos[i].c_str());
        int resultado = remove(nomeArquivoRemovido);
        if (resultado != 0){
            perror("Erro ao excluir arquivo");
        }
    }
}

void CasasPercorridasAoTodo(int &total)
{
    total++;
}

void TotalDeItensConsumidos(int &total_itens)
{
    total_itens++;
}

void TotalDePerigosEnfrentados(int &totalPerigo)
{
    totalPerigo++;
}

int CasasTotal(int tam_matriz, int qtd_matriz)
{
    int qtdCasasNaoPercorridas = 0;
    qtdCasasNaoPercorridas = (tam_matriz * tam_matriz) * qtd_matriz;

    return qtdCasasNaoPercorridas;
}

void CasasNaoPercorridas(int &qtdCasasNaoPercorridas)
{
    qtdCasasNaoPercorridas--;
}

void MudaPosicaoAtual(string **matriz, int& linha_aux, int& coluna_aux, int acaoLinha, int acaoColuna, int& vida, int &totalCasas, int &totalItens, int &totalPerigo, int& mochila, SalvaCaminho& caminho, string nomeArq){
    int acao=0;
    if (matriz[linha_aux + acaoLinha][coluna_aux + acaoColuna] == "*"){
        acao = -1;
        Vida(vida, acao);
        TotalDePerigosEnfrentados(totalPerigo);
        linha_aux= linha_aux+acaoLinha;
        coluna_aux= coluna_aux+acaoColuna;
        CasasPercorridasAoTodo(totalCasas);
    }
    else{ // é pq é numero
        linha_aux= linha_aux+acaoLinha;
        coluna_aux= coluna_aux+acaoColuna;
        CasasPercorridasAoTodo(totalCasas);
        if (matriz[linha_aux][coluna_aux] != "0"){
            MudaValorCaminho(matriz, linha_aux, coluna_aux);
            mochila++;
            TotalDeItensConsumidos(totalItens);
            CaminhoEhVazio=false;
            if (mochila == 4){
                if (vida < 10){
                    int acao_aux;
                    acao_aux = 1;
                    Vida(vida, acao_aux);
                }
                mochila = 0;
            }
        }
    }
    CaminhoFoiPercorrido(caminho, linha_aux, coluna_aux, nomeArq);
}

void CaminhoFoiPercorrido(SalvaCaminho& caminhoNaoPercorrido, int linha, int coluna, string nomeArq){
    int tamanho = caminhoNaoPercorrido.caminho.size();
    if(caminhoNaoPercorrido.nomeArq == nomeArq){
        bool encontrado = false;
        for(int i=0; i<tamanho; i++){
            if(caminhoNaoPercorrido.caminho[i].first == linha && caminhoNaoPercorrido.caminho[i].second == coluna){//ja tem salvo esse caminho
                encontrado = true;
                break;
            }
        }
        if(!encontrado){//nao tem salvo e devo salvar
            caminhoNaoPercorrido.caminho.push_back({linha,coluna});
        }
    }
}

void RecebeNomeDosArquivosJaCriados(vector<SalvaCaminho>& caminho, int qtd_matriz){
    for(int i=0; i<qtd_matriz; i++){
        caminho[i].nomeArq=nomesDosArquivos[i];
    }
}

int CasasNaoVisitadas(vector<SalvaCaminho>& caminho, int qtd_matriz, int tam_matriz){
    int somaTodasCasasPercorridas=0, casasTotal=0, casasNaoVisitadas=0;
    for(int i=0; i<qtd_matriz; i++){
        somaTodasCasasPercorridas+=caminho[i].caminho.size();
    }
    casasTotal=CasasTotal(tam_matriz, qtd_matriz);

    casasNaoVisitadas=casasTotal-somaTodasCasasPercorridas;

    return casasNaoVisitadas;
}

bool ConfereSeEnvoltaEhParede(string **matriz, int linha, int coluna, int tam_matriz){
    bool retorno=false;
    if(linha == 0){
        if(coluna==0){
            if(matriz[linha+1][coluna]=="#" && matriz[linha+1][coluna+1]=="#" && matriz[linha][coluna+1]=="#"){ //ver embaixo, diagonal direita, direita, 
                retorno = true;//isso é verdade
            }
        }
        else if(coluna == tam_matriz-1){ 
            if(matriz[linha+1][coluna]=="#" && matriz[linha+1][coluna-1]=="#" && matriz[linha][coluna-1]=="#"){ //ver embaixo, diagonal esquerda, direita, 
                retorno=true;//isso é verdade e n tem como ir;
            }
        }
        else{ //estar no meio 
            if(matriz[linha+1][coluna]=="#" && matriz[linha+1][coluna-1]=="#" && matriz[linha][coluna-1]=="#" && matriz[linha+1][coluna+1]=="#" && matriz[linha][coluna+1]=="#"){ //ver embaixo, diagonal esquerda, direita, 
                retorno=true; //isso é verdade e n tem como ir;
            }
        }
    }
    else if(linha==tam_matriz-1){
        if(coluna==0){
            if(matriz[linha-1][coluna]=="#" && matriz[linha-1][coluna+1]=="#" && matriz[linha][coluna+1]=="#"){
                retorno = true;
            }
        }
        else if(coluna==tam_matriz-1){
            if(matriz[linha-1][coluna]=="#" && matriz[linha-1][coluna-1]=="#" && matriz[linha][coluna-1]=="#"){
                retorno = true;
            }
        }
        else{
            if(matriz[linha-1][coluna]=="#" && matriz[linha-1][coluna-1]=="#" && matriz[linha-1][coluna+1]=="#" && matriz[linha][coluna-1]=="#" && matriz[linha][coluna+1]=="#"){
                retorno = true;
            }
        }
    }
    else{
        if(matriz[linha+1][coluna]=="#" && matriz[linha-1][coluna]=="#" && matriz[linha][coluna+1]=="#" && matriz[linha][coluna-1]=="#" && matriz[linha+1][coluna+1]=="#" && matriz[linha+1][coluna-1]=="#" && matriz[linha-1][coluna+1]=="#" && matriz[linha-1][coluna-1]=="#"){
            retorno = true;
        }
    }

    return retorno;
}

void SalvaMatrizesAlteradas(int tam_matriz, int qtd_matriz){
    
    ifstream arquivoLeitura; //leitura
    ofstream arquivoFinal;  //escrita
    string nomeArquivo, linha_arq, elemento, arquivoOutput="dataset/output.data";
    int aux_linha=0, aux_coluna=0;

    string **matriz_aux = new string *[tam_matriz];
    for (int i = 0; i < tam_matriz; i++){
        matriz_aux[i] = new string[tam_matriz];
    }

    arquivoFinal.open(arquivoOutput, ios::out);
    for(int i=0; i<qtd_matriz; i++){
        nomeArquivo = nomesDosArquivos[i];
        arquivoLeitura.open(nomeArquivo, ios::in);

            while(!arquivoLeitura.eof()){
                while(getline(arquivoLeitura, linha_arq, '\n')){
                    stringstream aux(linha_arq);
                    
                    while (getline(aux, elemento, ' ')){ // lendo a cada elemento presente na minha linha armazena para minha variavel elemento e tendo o delimitador ''
                        if(aux_coluna < tam_matriz && aux_linha < tam_matriz){
                            matriz_aux[aux_linha][aux_coluna] = elemento;
                            aux_coluna++;
                        }
                    }
                    
                    if (aux_coluna > 0 && aux_linha < tam_matriz){
                        aux_linha++;
                        aux_coluna = 0;
                    }
                }
            }
            
            arquivoLeitura.close();
            aux_coluna = 0;
            aux_linha = 0;

            for (int i = 0; i < tam_matriz; i++){
                for (int j = 0; j < tam_matriz; j++){
                    arquivoFinal << matriz_aux[i][j] << " ";
                }
                arquivoFinal << endl;
            }
            arquivoFinal << endl;
    }
    arquivoFinal.close();
}