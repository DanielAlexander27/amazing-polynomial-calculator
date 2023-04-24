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

/*
 
 
 */
void deconstruirPolinomio(string& polinomio) {
    string expresion;
    int posicionInicio = -1, posicionFinal = -1;
//    bool isNumAsigned = false, isExponentAsigned = false;
    
    for (int i = 0; i < polinomio.size(); i++) {
        if (i == 0 && (polinomio.at(i) == '*' || polinomio.at(i) == 'x')) {
            expresion = "1";
            cout << expresion << endl;
            continue;
        }
        
        bool isNumberOrSign = polinomio.at(i) == '+' || polinomio.at(i) == '-' || (polinomio.at(i) >= '0' && polinomio.at(i) <= '9');
        
        if (posicionInicio == -1) {
            /**
             Condicional para establecer que el valor del exponente sea igual a 1 en dos casos:
                Caso 1. Similar al Caso 1, pero la incognita va al final de la ecuación [...] + x
                Caso 2. Cuando el input contiene la incognita sin el exponente explicito: x + 3
            */
                        
            if (polinomio.at(i) == 'x' && i == (polinomio.size()-1)) {
                expresion = "1";
                cout << expresion << endl;
            } else if (polinomio.at(i) == 'x' && (polinomio.at(i+1) == '+' || polinomio.at(i+1) == '-')) {
                expresion = "1";
                cout << expresion << endl;
            }
            
            /**Condicional para almacenar la posición inicial que señala el  comienza del numero. Se agrege un if anidado ya que existe casos en
                donde el la ultima posicion contiene un unico digito, por lo que resulta imposible obtenerlo mediante slicing.
             */
            if (isNumberOrSign) {
                posicionInicio = i;
                
                if (posicionInicio == polinomio.size() - 1) {
                    expresion = polinomio.at(i);
                    cout << expresion << endl;

                }
            }
        } else if (polinomio.at(i) == '+' || polinomio.at(i) == '-' || polinomio.at(i) == 'x' || polinomio.at(i) == '*') {
            posicionFinal = i;
            expresion = {polinomio.begin() + posicionInicio, polinomio.begin() + posicionFinal};
            
            /**Condicional para almacenar el coeficiente 1 cuando esta implicito como en el caso [...]+x+[....]*/
            if (polinomio.at(i) == 'x' && (polinomio.at(i-1) == '+' || polinomio.at(i-1) == '-')) {
                expresion += "1";
            }
            
            posicionInicio = -1;
            posicionFinal = -1;
            i--;
            cout << expresion << endl;
        } else if (i == (polinomio.size()-1)) {
            expresion = {polinomio.begin() + posicionInicio, polinomio.end()};
            cout << expresion << endl;
        }
        
    }
}
