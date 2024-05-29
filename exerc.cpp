#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

vector<pair<int, int>> itemRecipiente; // pair<item, recipiente>
float temperatura = 0;
int minRecipientes = 0;

vector<float> temperaturaPlot;
vector<int> iteracoes;
vector<int> recipientesPlot;
vector<int> melhoresSolucoesVizinhancas;

vector<int> trocarVizinhanca(vector<int> solucaoInicial, int capacidadeRecipiente, int* custo, int* recipientes){
    vector<int> solucaoFinal = solucaoInicial;
    int deltaEInicial = 0;
    for(int i = 0; i < solucaoInicial.size(); i++){
        if(solucaoInicial[i] != 15 && solucaoInicial[i] != 0){
            deltaEInicial += 1;
        }
    }


    bool gerar = true;
    int index1 = rand() % itemRecipiente.size(); // 5
    int index2 = rand() % itemRecipiente.size();
    // int rec1 = itemRecipiente[index1].second;
    int rec1 = rand() % solucaoInicial.size();
    int rec2 = itemRecipiente[index2].second;
    int capacidadeRec1 = solucaoInicial[rec1];
    int capacidadeRec2 = solucaoInicial[rec2];
    
    while(gerar){
        index2 = rand() % itemRecipiente.size();
        rec1 = rand() % solucaoInicial.size();
        rec2 = itemRecipiente[index2].second;
        capacidadeRec1 = solucaoInicial[rec1];
        capacidadeRec2 = solucaoInicial[rec2];

        if(rec1 != rec2 && (capacidadeRec1 - itemRecipiente[index2].first) >= 0){
            cout<<"capacidade do primeiro para a troca: "<< capacidadeRec1 - itemRecipiente[index2].first << endl;
            gerar = false;
        }
    }
    int deltaE = 0;

    itemRecipiente[index2].second = rec1;
    solucaoFinal[rec1] -= itemRecipiente[index2].first;
    solucaoFinal[rec2] += itemRecipiente[index2].first;

    cout << "S: "; 
    for(int i = 0; i < solucaoFinal.size(); i++){
        (*recipientes) += 1;
        if(solucaoFinal[i] != 15 && solucaoFinal[i] != 0){
            deltaE += 1;
        }
        if(solucaoFinal[i] != 15){
            *custo += 1;
        }
        cout << solucaoFinal[i] << " ";
    }
    cout << endl;

    cout << "DeltaE: " << deltaE - deltaEInicial << endl;
    if((deltaE - deltaEInicial) > 0){
        float divisao = (float)-(deltaE-deltaEInicial)/temperatura;
        float pE = exp(divisao);
        cout << "pE: " << pE << endl;

        float p = (float)rand() / RAND_MAX;
        cout << "p: " << p << endl;
        if(pE > p){
            cout << "Aceitou" << endl;
            cout << "Recipiente " << rec1 << " vai receber o item " << itemRecipiente[index2].first << endl;
            cout << "Recipiente " << rec2 << " vai perder o item " << itemRecipiente[index2].first << endl;
            return solucaoFinal;
        } else {
            cout << "Rejeitou" << endl;
            itemRecipiente[index2].second = rec2;
            *custo = 0;
            for(int i = 0; i < solucaoInicial.size(); i++){
                if(solucaoInicial[i] != 15){
                    *custo += 1;
                }
            }
            return solucaoInicial;
        }
    } else {
        cout << "Recipiente " << rec1 << " vai receber o item " << itemRecipiente[index2].first << endl;
        cout << "Recipiente " << rec2 << " vai perder o item " << itemRecipiente[index2].first << endl;
        return solucaoFinal;
    }
}

void buscaGulosa(int capacidade, int numItens, vector<int> itens){
    vector<int> solucaoInicial; // vetor[numItens] onde cada item é igual a capacidade
    int recipienteAtual = 0;

    int counter = 0;

    while (numItens != 0){
        if (!itens.empty()) {
            if(solucaoInicial.empty()) {
                solucaoInicial.push_back(capacidade);
                minRecipientes += 1;
            }

            int index = rand() % itens.size(); // sorteia um valor de 0 a 19
            int itemSorteado = itens[index];
            itens.erase(itens.begin() + index); // remove o valor sorteado
            numItens--;
            if (itemSorteado <= solucaoInicial[recipienteAtual]) {
                itemRecipiente.push_back(make_pair(itemSorteado, recipienteAtual));
                solucaoInicial[recipienteAtual] -= itemSorteado;
                //cout << "Item sorteado: " << itemSorteado << " | Recipiente " << recipienteAtual+1 << " valor: " << solucaoInicial[recipienteAtual] << endl;
            } else {
                solucaoInicial.push_back(capacidade);
                minRecipientes += 1;
                recipienteAtual++;
                itemRecipiente.push_back(make_pair(itemSorteado, recipienteAtual));
                solucaoInicial[recipienteAtual] -= itemSorteado;
                //cout << "Item sorteado: " << itemSorteado << " | Recipiente " << recipienteAtual+1 << " valor: " << solucaoInicial[recipienteAtual] << endl;
            }
        }
    }

    cout << "solucaoInicial: ";
    for (int i = 0; i < solucaoInicial.size(); i++) {
        cout << solucaoInicial[i] << " ";
    }
    cout << endl;

    int saMax = 3;
    float recipientesTotais = 0;
    float alfa = 0.95;

    int melhorSolucaoVizinhanca = (int)INFINITY;

    do {
        int localCounter = 0;
        if(temperatura != 0){
            temperatura *= alfa;
            temperaturaPlot.push_back(temperatura);
            recipientesPlot.push_back(minRecipientes);
            cout << "Melhor solucao da vizinhanca" << melhorSolucaoVizinhanca << endl;
            melhoresSolucoesVizinhancas.push_back(melhorSolucaoVizinhanca);

            counter += 1;
            iteracoes.push_back(counter);
            melhorSolucaoVizinhanca = (int)INFINITY;
        }
        for(int i = 0; i < saMax; i++){
            int custoIndividual = 0;
            int recipienteIndividual = 0;
            solucaoInicial = trocarVizinhanca(solucaoInicial, capacidade, &custoIndividual, &recipienteIndividual);

            
            for(int i = 0; i < solucaoInicial.size(); i++){
                if(solucaoInicial[i] != 15){
                    localCounter += 1;
                }
            }
            if(localCounter < minRecipientes){
                minRecipientes = localCounter;
            }
            localCounter = 0;

            if(custoIndividual < melhorSolucaoVizinhanca){
                melhorSolucaoVizinhanca = custoIndividual;
            }
            recipientesTotais += recipienteIndividual;
        }


        if(temperatura == 0){
            temperatura = recipientesTotais / saMax;
        }
        cout << "Temperatura final: " << temperatura << endl;
    } while(temperatura > 0.005);

    return;
}

void chamarPlotagem(){
    string command = "python plot.py";
    for(float temperatura : temperaturaPlot){
        command += " temp_" + to_string(temperatura);
    }
    for(int iteracao : iteracoes){
        command += " iter_" + to_string(iteracao);
    }
    for(int recipiente : recipientesPlot){
        command += " rec_" + to_string(recipiente);
    }
    for(int melhorSolucao : melhoresSolucoesVizinhancas){
        command += " ms_" + to_string(melhorSolucao);
    }
    system(command.c_str());
}

int main (){
    srand(time(NULL));
    ifstream file("./entradasParaTeste/PEU2.txt"); // abrindo o .txt

    string line; // variável para armazenar a linha do arquivo
    int capacidadesolucaoInicial, numItens; // váriavel para armazenar a primeira e segunda linha do arquivo
    vector<int> tamanhoItens; // vetor para armazenar a terceira linha do arquivo

    if (file.is_open()) {
        if (getline(file, line)) {
            capacidadesolucaoInicial = stoi(line); // convertendo a string para int
        }
        if (getline(file, line)) {
            numItens = stoi(line);
        }
        if (getline(file, line)) {
            stringstream ss(line); // convertendo a string para vetor de inteiros
            int num;
            while (ss >> num) { 
                tamanhoItens.push_back(num); // adicionando os valores no vetor
            }
        }
        file.close();
    } else {
        cout << "Não foi possível abrir o arquivo";
    }

    buscaGulosa(capacidadesolucaoInicial, numItens, tamanhoItens);
    chamarPlotagem();

    // verificando valores
    
    // cout << "Primeira linha: " << capacidadesolucaoInicial << endl;
    // cout << "Segunda linha: " << numItens << endl;
    // cout << "Terceira linha: ";
    // for (int i = 0; i < tamanhoItens.size(); i++) {
        // cout << tamanhoItens[i] << " ";
    // }
    // cout << endl;
}