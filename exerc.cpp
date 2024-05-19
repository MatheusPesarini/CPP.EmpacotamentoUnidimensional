#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void buscaGulosa(int capacidade, int numItens, vector<int> itens){
    vector<int> recipientes(1, capacidade); // vetor[numItens] onde cada item é igual a capacidade
    srand(time(0));
    int recipienteAtual = 0;

    while (numItens != 0){
        if (!itens.empty()) {
            int index = rand() % itens.size(); // sorteia um valor
            int itemSorteado = itens[index];
            itens.erase(itens.begin() + index); // remove o valor sorteado
            numItens--;
            if (itemSorteado <= recipientes[recipienteAtual]) {
                recipientes[recipienteAtual] -= itemSorteado;
                //cout << "Item sorteado: " << itemSorteado << " | Recipiente " << recipienteAtual+1 << " valor: " << recipientes[recipienteAtual] << endl;
            } else {
                recipientes.push_back(capacidade);
                recipienteAtual++;
                recipientes[recipienteAtual] -= itemSorteado;
                //cout << "Item sorteado: " << itemSorteado << " | Recipiente " << recipienteAtual+1 << " valor: " << recipientes[recipienteAtual] << endl;
            }
        }
    }

    cout << "Recipientes: ";
    for (int i = 0; i < recipientes.size(); i++) {
        cout << recipientes[i] << " ";
    }
    cout << endl;

    return;
}

int main (){
    ifstream file("./entradasParaTeste/PEU1.txt"); // abrindo o .txt

    string line; // variável para armazenar a linha do arquivo
    int firstLine, secondLine; // váriavel para armazenar a primeira e segunda linha do arquivo
    vector<int> thirdLine; // vetor para armazenar a terceira linha do arquivo

    if (file.is_open()) {
        if (getline(file, line)) {
            firstLine = stoi(line); // convertendo a string para int
        }
        if (getline(file, line)) {
            secondLine = stoi(line);
        }
        if (getline(file, line)) {
            stringstream ss(line); // convertendo a string para vetor de inteiros
            int num;
            while (ss >> num) { 
                thirdLine.push_back(num); // adicionando os valores no vetor
            }
        }
        file.close();
    } else {
        cout << "Não foi possível abrir o arquivo";
    }

    buscaGulosa(firstLine, secondLine, thirdLine);

    // verificando valores
    cout << "Primeira linha: " << firstLine << endl;
    cout << "Segunda linha: " << secondLine << endl;
    cout << "Terceira linha: ";
    for (int i = 0; i < thirdLine.size(); i++) {
        cout << thirdLine[i] << " ";
    }
    cout << endl;
}