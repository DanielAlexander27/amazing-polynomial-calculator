//
//  main.cpp
//  ProyectoFinal
//
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

struct tPolimonio {
    int grado;
    vector<double> coef;
};

// Prototipo de Funciones
void solicitarPolinomios();
void limpiarEspaciosPolinomio(string& polinomio);
bool verificarPolinomio(string& polinomio);
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

/****
    Implementacion de Logica en Funciones
 */

/**
    La función solicitarPolinomios() se encarga de ... (pendiente por docuemntar)
 */
void solicitarPolinomios() {
    int cantidad;
    string polinomio;
    
    cout << "Introduzca la cantidad de polinomios a sumar: ";
    cin >> cantidad;
    cin.ignore();
    
    for(int i = 0; i < cantidad; i++) {
        cout << "Polinomio " << (i+1) << ": ";
        getline(cin, polinomio);
        
        limpiarEspaciosPolinomio(polinomio);
        deconstruirPolinomio(polinomio);
    }
}


/**
    La función limpiarEspaciosPolinomio() se encarga de eliminar caracteres de espacios.
 */
void limpiarEspaciosPolinomio(string& polinomio) {
    // Código realizado con ayuda de ChatGPT
    polinomio.erase(std::remove_if(polinomio.begin(), polinomio.end(), ::isspace), polinomio.end());
    cout << polinomio << endl;
}

/**
    La función limpiarEspaciosPolinomio() se encarga de eliminar caracteres de espacios.
 */
bool verificarPolinomio(string& polinomio) {
    static string incognita;
    
    
    
    return true;
}


/**
    La función deconstruirPolinomio() se encarga de devolver un vector el cual contiene coeficientes, constantes y exponentes.
 */
void deconstruirPolinomio(string& polinomio) {
    vector<double> numeros;
    string expresion;
    int posicionInicio = -1, posicionFinal = -1;
    
    for (int i = 0; i < polinomio.size(); i++) {
        if (i == 0 && (polinomio.at(i) == '*' || polinomio.at(i) == 'x')) {
            numeros.push_back(1);
            
            if (polinomio.at(i+1) == '+' || polinomio.at(i+1) == '-')
                numeros.push_back(1);
            
            continue;
        }
        
        bool isNumberOrSign = polinomio.at(i) == '+' || polinomio.at(i) == '-' || (polinomio.at(i) >= '0' && polinomio.at(i) <= '9');
        
        if (posicionInicio == -1) {
            /**
             Condicional para establecer que el valor del exponente sea igual a 1 en dos casos:
                Caso 1. La incognita va al final de la ecuación [...] + x
                Caso 2. Cuando el input contiene la incognita sin el exponente explicito: x + 3
            */
                        
            if (polinomio.at(i) == 'x' && i == (polinomio.size()-1)) {
                numeros.push_back(1);
            } else if (polinomio.at(i) == 'x' && (polinomio.at(i+1) == '+' || polinomio.at(i+1) == '-')) {
                numeros.push_back(1);
            }
            
            /**Condicional para almacenar la posición inicial que señala el  comienza del numero.*/
            if (isNumberOrSign) {
                posicionInicio = i;
                
                /** Se agrege un if anidado para obtener el exponente de la última expresion añadida ya que existe casos en donde el la ultima posicion contiene un
                    unico digito, por lo que resulta imposible obtenerlo mediante slicing. Esto se aplica en los casos cuando [...] + x3.
                */
                if (posicionInicio == polinomio.size() - 1) {
                    expresion = polinomio.at(i);
                    numeros.push_back(stod(expresion));
                }
            }
        } else if (polinomio.at(i) == '+' || polinomio.at(i) == '-' || polinomio.at(i) == 'x' || polinomio.at(i) == '*') {
            posicionFinal = i;
            expresion = {polinomio.begin() + posicionInicio, polinomio.begin() + posicionFinal};
            
            /**Condicional para almacenar el coeficiente 1 cuando esta implicito como en el caso [...]+x+[....]*/
            if (polinomio.at(i) == 'x' && (polinomio.at(i-1) == '+' || polinomio.at(i-1) == '-')) {
                expresion += "1";
            }
            
            numeros.push_back(stod(expresion));
            
            posicionInicio = -1;
            posicionFinal = -1;
            i--;
        } else if (i == (polinomio.size()-1)) {
            expresion = {polinomio.begin() + posicionInicio, polinomio.end()};
            numeros.push_back(stod(expresion));
        }
        
    }
    
    cout << "[";
    
    for (auto num : numeros) {
        cout << num << ", ";
    }
    
    cout << "]" << endl;
}
