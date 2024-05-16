#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

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

    buscaGulosa();

    // verificando valores
    cout << "Primeira linha: " << firstLine << endl;
    cout << "Segunda linha: " << secondLine << endl;
    cout << "Terceira linha: ";
    for (int i = 0; i < thirdLine.size(); i++) {
        cout << thirdLine[i] << " ";
    }
    cout << endl;
}

void buscaGulosa(){
    // criar um vetor com valores 20 (no caso desse .txt) e ir subtraindo pelos valores da terceira linha, caso tenha
    // opção de troca de item por recipiente, terá que ser feito de um jeito diferente para permitir a troca dos itens
    return;
}