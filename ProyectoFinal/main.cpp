//
//  main.cpp
//  ProyectoFinal
//
//

#include <iostream>
using namespace std;

struct tPolimonio {
    int grado;
    vector<double> coef;
};

// Prototipo de Funciones
void solicitarPolinomios();
void deconstruirPolinomio(string& polinomio);

// Main
int main(int argc, const char * argv[]) {
    solicitarPolinomios();
    
    return 0;
}

// Implementacion de Logica en Funciones
void solicitarPolinomios() {
    int cantidad;
    string polinomio;
    
    cout << "Introduzca la cantidad de polinomios a sumar: ";
    cin >> cantidad;
    
    for(int i = 0; i < cantidad; i++) {
        cout << "Polinomio " << (i+1) << ": ";
        cin >> polinomio;
        deconstruirPolinomio(polinomio);
    }
}

void deconstruirPolinomio(string& polinomio) {
    int posicionInicio = -1, posicionFinal = -1;
//    bool isNumAsigned = false, isExponentAsigned = false;
    
    for (int i = 0; i < polinomio.size(); i++) {
        bool isNumberOrSign = polinomio.at(i) == '+' || polinomio.at(i) == '-' || (polinomio.at(i) >= '0' && polinomio.at(i) <= '9');
        
        if (posicionInicio == -1 && isNumberOrSign) {
            posicionInicio = i;
        } else if (posicionInicio != -1 && (polinomio.at(i) == '+' || polinomio.at(i) == '-' || polinomio.at(i) == 'x' || polinomio.at(i) == '*')) {
            posicionFinal = i;
            string expresion {polinomio.begin() + posicionInicio, polinomio.begin() + posicionFinal};
            posicionInicio = -1;
            posicionFinal = -1;
            i--;
            cout << expresion << endl;
        }
    }
}
