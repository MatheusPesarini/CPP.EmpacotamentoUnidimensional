#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int trocarVizinhanca(vector<int> solucaoInicial, vector<pair<int, int>> itemRecipiente, vector<int> itens){
    int custo = 0;

    bool gerar = true;
    int index1 = rand() % itemRecipiente.size(); // 5
    int index2 = rand() % itemRecipiente.size();
    int rec1 = itemRecipiente[index1].second;
    int rec2 = itemRecipiente[index2].second;
    int capacidadeRec1 = solucaoInicial[rec1];
    int capacidadeRec2 = solucaoInicial[rec2];
    
    while(gerar){
        index1 = rand() % itemRecipiente.size();
        index2 = rand() % itemRecipiente.size();
        rec1 = itemRecipiente[index1].second;
        rec2 = itemRecipiente[index2].second;
        capacidadeRec1 = solucaoInicial[rec1];
        capacidadeRec2 = solucaoInicial[rec2];

        if(rec1 != rec2 && (capacidadeRec1 + itemRecipiente[index1].first - itemRecipiente[index2].first) >= 0 && (capacidadeRec2 + itemRecipiente[index2].first - itemRecipiente[index1].first) >= 0){
            gerar = false;
        }
    }

    // cout << "Recipiente " << rec1 << " = " << capacidadeRec1 << " + " << itemRecipiente[index1].first << " - " << itemRecipiente[index2].first << endl;
    // cout << "Recipiente " << rec2 << " = " << capacidadeRec2 << " + " << itemRecipiente[index2].first << " - " << itemRecipiente[index1].first << endl;

    solucaoInicial[rec1] = capacidadeRec1 + itemRecipiente[index1].first - itemRecipiente[index2].first;
    solucaoInicial[rec2] = capacidadeRec2 + itemRecipiente[index2].first - itemRecipiente[index1].first;
    swap(itemRecipiente[index1].second, itemRecipiente[index2].second);

    cout << "S: "; 
    for(int i = 0; i < solucaoInicial.size(); i++){
        cout << solucaoInicial[i] << " ";
        custo += solucaoInicial[i];
    }
    cout << endl;

    return custo;
}

void buscaGulosa(int capacidade, int numItens, vector<int> itens){
    srand(time(NULL));

    vector<int> solucaoInicial; // vetor[numItens] onde cada item é igual a capacidade
    int recipienteAtual = 0;

    vector<pair<int, int>> itemRecipiente; // pair<item, recipiente>

    while (numItens != 0){
        if (!itens.empty()) {
            if(solucaoInicial.empty()) {
                solucaoInicial.push_back(capacidade);
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

    int numVizinhos = 3;
    int custoTotal = 0;
    int temperatura;

    for(int i = 0; i < numVizinhos; i++){
        vector<int> solucaoInicialCopy = solucaoInicial;
        vector<pair<int, int>> itemRecipienteCopy = itemRecipiente;

        custoTotal += trocarVizinhanca(solucaoInicialCopy, itemRecipienteCopy, itens);
    }
    temperatura = custoTotal / numVizinhos;
    cout << "Temperatura inicial: " << temperatura << endl;

    return;
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

    // verificando valores
    
    // cout << "Primeira linha: " << capacidadesolucaoInicial << endl;
    // cout << "Segunda linha: " << numItens << endl;
    // cout << "Terceira linha: ";
    // for (int i = 0; i < tamanhoItens.size(); i++) {
        // cout << tamanhoItens[i] << " ";
    // }
    // cout << endl;
}