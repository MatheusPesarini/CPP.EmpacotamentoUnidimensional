#include <iostream>

using namespace std;

int main() {
    srand(time(NULL));

    while(true) {
        int num = rand() % 1;
        cout << num << endl;

        if(num >= 1 || num < 0){
            cout << "Número inválido" << endl;
            break;
        }

    }
}