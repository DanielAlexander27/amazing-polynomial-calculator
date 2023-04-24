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
    
//    vector<int> vector1 {1, 2, 3, 4,5};
//    vector<int> vector2 {vector1.begin()+2, vector1.end()};
//
//    for(auto num : vector2) {
//        cout << num << endl;
//    }
//
    
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
    string expresion;
    int posicionInicio = -1, posicionFinal = -1;
//    bool isNumAsigned = false, isExponentAsigned = false;
    
    for (int i = 0; i < polinomio.size(); i++) {
        bool isNumberOrSign = polinomio.at(i) == '+' || polinomio.at(i) == '-' || (polinomio.at(i) >= '0' && polinomio.at(i) <= '9');
        
        if (i == 0 && (polinomio.at(i) == '*' || polinomio.at(i) == 'x')) {
            expresion = "1";
            cout << expresion << endl;
            continue;
        } else if (posicionInicio == -1 && i == (polinomio.size()-1) && polinomio.at(i) == 'x') {   
            expresion = "1";
            cout << expresion << endl;
            continue;
        } else if (posicionInicio == -1 && polinomio.at(i) == 'x' && (polinomio.at(i+1) == '+' || polinomio.at(i+1) == '-')) {
            expresion = "1";
            cout << expresion << endl;
            continue;
        }
        
        if (posicionInicio == -1 && isNumberOrSign) {
            posicionInicio = i;
        } else if (posicionInicio != -1 && (polinomio.at(i) == '+' || polinomio.at(i) == '-' || polinomio.at(i) == 'x' || polinomio.at(i) == '*')) {
            posicionFinal = i;
            
            expresion = {polinomio.begin() + posicionInicio, polinomio.begin() + posicionFinal};
            
            if (polinomio.at(i) == 'x' && (polinomio.at(i-1) == '+' || polinomio.at(i-1) == '-')) {
                expresion += "1";
            }
            
            posicionInicio = -1;
            posicionFinal = -1;
            i--;
            cout << expresion << endl;
        } else if (posicionInicio != -1 && i == (polinomio.size()-1)) {
            expresion = {polinomio.begin() + posicionInicio, polinomio.end()};
            cout << expresion << endl;
        }
    }
}
