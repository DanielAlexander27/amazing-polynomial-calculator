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

char incognita = ' ';
vector<vector<double>> coeficientesPorGrado;

struct tPolimonio {
    int grado;
    vector<double> coef;
};

// Prototipo de Funciones
void solicitarPolinomios();
void limpiarEspaciosPolinomio(string& polinomio);
bool verificarPolinomio(string& polinomio);
void deconstruirPolinomio(string& polinomio);
void clasificarCoefPorGrado(vector<double>& numeros, string& polinomio);
void sumaPolinomios(vector<vector<double>>& ecuacion);


// Main
int main(int argc, const char * argv[]) {
    solicitarPolinomios();
    sumaPolinomios(coeficientesPorGrado);
    
    return 0;
}


/**
    **Implementacion de Logica en Funciones
    **La función solicitarPolinomios() se encarga de ... (pendiente por docuemntar)
 */
void solicitarPolinomios() {
    int cantidad;
    string polinomio;
    
    cout << "Introduzca la cantidad de polinomios a sumar: ";
    
    while(true) {
        if (!(cin >> cantidad)) {
            cout << "Por favor solo ingresa números" << endl;
            cout << "Introduzca la cantidad de polinomios a sumar: ";
            // Codigo hecho con ayud de ChatGPT
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (cin.peek() != '\n' && !isdigit(cin.peek())) {
            cout << "Por favor solo ingresa números" << endl;
            cout << "Introduzca la cantidad de polinomios a sumar: ";
            // Codigo hecho con ayud de ChatGPT
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    
    // Codigo hecho con ayud de ChatGPT
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    for(int i = 0; i < cantidad; i++) {
        cout << "Polinomio " << (i+1) << ": ";
        getline(cin, polinomio);
        
        if (verificarPolinomio(polinomio)) {
            deconstruirPolinomio(polinomio);
        } else {
            i--;
        }
    }
}


/**
    La función limpiarEspaciosPolinomio() se encarga de eliminar caracteres de espacios.
 */
void limpiarEspaciosPolinomio(string& polinomio) {
    // Código realizado con ayuda de ChatGPT
    polinomio.erase(remove_if(polinomio.begin(), polinomio.end(), ::isspace), polinomio.end());
    cout << polinomio << endl;
}

/**
    La función verificarPolinomio() se encarga de comprobrar que el polinomio introducido cumpla con la estructura necesaria como los símbolos empleados (no se aceptan operaciones como multiplicaciones entre coeficintes ni divisiones) y que los exponentes de las incognitas sean numeros naturales. Sumado a lo anterior verifica que existe una sola variable en la ecuación.
 */
bool verificarPolinomio(string& polinomio) {
    limpiarEspaciosPolinomio(polinomio);
    
    for(int i = 0; i < polinomio.size(); i++) {
        bool evaluador = (incognita == ' ') ? isalpha(polinomio.at(i)) : polinomio.at(i) == incognita;
        bool isSign = polinomio.at(i) == '+' || polinomio.at(i) == '-';
        
        // Condicional que opera en caso de que la posicion actual no cumple con ser numero, ni signo (+-), ni letra.
        if (!(isdigit(polinomio.at(i)) || isSign || evaluador)) {
            
            // En caso de que el char actual sea punto, se evalua que sea empleado correctamente. Los aspectos a considerar son:
            //   1. No se aceptan puntos al inicio ni al final del polinomio.
            //   2. El punto debe estar entre dos digitos. A lo que se procede a evaluar si aquel numero es coeficiente o exponenete.
            //   3. No se aceptan numeros con puntos decimales como 12.23.4
            if (polinomio.at(i) == '.') {
                // Caso 1
                if (i == 0 || i == polinomio.size()-1) {
                    cout << "Error. No se aceptan puntos decimales al inicio ni al final del polinomio. Vuelva a introducir" << endl << endl;
                    return false;
                }
                                
                // Caso 2
                if (isdigit(polinomio.at(i-1)) && isdigit(polinomio.at(i+1))) {
                    // Se lee la expresion en reversa con el fin de encontrar si el elemento previo es un signo +- o una incognita.
                    for (int j = i-1; j >= 0; j--) {
                        if (polinomio.at(j) == incognita) {
                            cout << "Error. Los grados del polinomio (exponentes) deben ser numeros naturales. Vuelva a introducir." << endl << endl;
                            return false;
                        } else if (polinomio.at(j) == '.') {
                            cout << "Error. Existen varios puntos decimales en un solo numero." << endl << endl;
                            return false;
                        } else if (polinomio.at(j) == '+' || polinomio.at(j) == '-') {
                            break;
                        }
                    }
                    continue;
                } else {
                    cout << "Error. El punto decimal debe estar entre dos digitos. No se aceptan valores como .24. Vuelva a introducir" << endl << endl;
                    return false;
                }
            }

            // En caso de que el char actual sea *, se evalua que sea empleado correctamente. Los aspectos a considerar son:
            //   1. No se aceptan * al inicio ni al final del polinomio.
            //   2. El * debe estar entre un numero previo y con una incognita posterior. No se aceptan multiplicaciones.
            if (polinomio.at(i) == '*') {
                
                if (i == 0 || i == polinomio.size()-1) {
                    cout << "Error. No se aceptan * al inicio ni al final del polinomio. Vuelva a introducir" << endl << endl;
                    return false;
                }
                
                if (isdigit(polinomio.at(i-1)) && isalpha(polinomio.at(i+1))) {
                    continue;
                } else {
                    cout << "Error. El * debe estar entre un numero previo y con una incognita posterior. No se aceptan multiplicaciones. Vuelva a introducir" << endl << endl;
                    return false;
                }
            }
            
            // Un error comun suele ser introducir numeros de punto flotante con la coma (,).
            if (polinomio.at(i) == ',') {
                cout << "Error. Los numeros de punto flotante van con punto (.), no con coma(,)." << endl << endl;
                return false;
            }
            
            // Mensaje de error genérico
            cout << "Error. Tan solo se aceptan numeros, letras y signos como (*, +, -). Vuelva a introducir" << endl << endl;
            return false;
        }
        
        // Establece el caracter de la incognita.
        if (isalpha(polinomio.at(i)) && incognita == ' ') {
            incognita = polinomio.at(i);
        }
    }

    return true;
}

/**
    La función deconstruirPolinomio() se encarga de devolver un vector el cual contiene coeficientes, constantes y exponentes.
 */
void deconstruirPolinomio(string& polinomio) {
    vector<double> numeros;
    string stringCoef;
    int posicionInicio = -1, posicionFinal = -1;
    
    for (int i = 0; i < polinomio.size(); i++) {
        if (i == 0 && polinomio.at(i) == incognita) {
            numeros.push_back(1);
            
            if (i == polinomio.size() - 1 || (polinomio.at(i+1) == '+' || polinomio.at(i+1) == '-'))
                numeros.push_back(1);
            
            continue;
        }
        
        bool isSign = polinomio.at(i) == '+' || polinomio.at(i) == '-';
        
        if (posicionInicio == -1) {
            /**
             Condicional para establecer que el valor del exponente sea igual a 1 en dos casos:
             Caso 1. La incognita va al final de la ecuación [...] + x
             Caso 2. Cuando el input contiene la incognita sin el exponente explicito: x + 3
             */
            if (polinomio.at(i) == incognita && (i == (polinomio.size()-1) || polinomio.at(i+1) == '+' || polinomio.at(i+1) == '-')) {
                numeros.push_back(1);
            }
            
            // Condicional para almacenar la posición inicial que señala el  comienza del numero.
            if (isdigit(polinomio.at(i)) || isSign) {
                posicionInicio = i;
                
                /** Se agrege un if anidado para obtener el exponente de la última expresion añadida ya que existe casos en donde el la ultima posicion contiene un
                 unico digito, por lo que resulta imposible obtenerlo mediante slicing. Esto se aplica en los casos cuando [...] + x3.
                 */
                if (posicionInicio == polinomio.size() - 1) {
                    stringCoef = polinomio.at(i);
                    numeros.push_back(stod(stringCoef));
                }
            }
        } else if (polinomio.at(i) == '+' || polinomio.at(i) == '-' || polinomio.at(i) == incognita|| polinomio.at(i) == '*') {
            posicionFinal = i;
            stringCoef = {polinomio.begin() + posicionInicio, polinomio.begin() + posicionFinal};
            
            /**Condicional para almacenar el coeficiente 1 cuando esta implicito como en el caso [...]+x+[....]*/
            if (polinomio.at(i) == incognita && (polinomio.at(i-1) == '+' || polinomio.at(i-1) == '-')) {
                stringCoef += "1";
            }
            
            numeros.push_back(stod(stringCoef));
            
            posicionInicio = -1;
            posicionFinal = -1;
            i--;
        } else if (i == (polinomio.size()-1)) {
            stringCoef = {polinomio.begin() + posicionInicio, polinomio.end()};
            numeros.push_back(stod(stringCoef));
        }
        
    }
    
    cout << "[";
    
    for (auto num : numeros) {
        cout << num << ", ";
    }
    
    cout << "]" << endl;
    
    clasificarCoefPorGrado(numeros, polinomio);
}

void clasificarCoefPorGrado(vector<double>& numeros, string& polinomio) {
    unsigned int temp = 0;
    bool detectarx = false;

    for (int i = 0; i < polinomio.size(); i++) {
        if (polinomio.at(i) == incognita) {
            detectarx = true;
        }
        
        if (polinomio.at(i) == '+' or polinomio.at(i) == '-' or i == polinomio.size() - 1 ) {
            double coef = numeros.at(temp);
            if (detectarx == true) {
                double exp = numeros.at(temp + 1);
                if (coeficientesPorGrado.size() == 0 ||  exp > (coeficientesPorGrado.size() - 1)) {
                    
                    double tester124 = coeficientesPorGrado.size();
                    double condiition = exp - (tester124 - 1);
                    for (int j = 0; j < condiition; j++) {
                        vector<double> tempVector;
                        coeficientesPorGrado.push_back(tempVector);
                    }
                }
                coeficientesPorGrado.at(exp).push_back(coef);
                temp += 2;
            } else {
                if (coeficientesPorGrado.size() == 0) {
                    vector<double> tempVector;
                    coeficientesPorGrado.push_back(tempVector);
                }
                coeficientesPorGrado.at(0).push_back(coef);
                temp += 1;
            }
            
            if (detectarx)
                detectarx = !detectarx;
        }
    }
    
    int gradoNum = 0;
    
    cout << "Vector de Vectores" << endl;
    for (auto grado: coeficientesPorGrado ) {
        cout << "Grado " << gradoNum << ": ";
        for(auto num: grado){
            cout<<num<<" ";
        }
        gradoNum++;
        cout<<endl;
    }
}

void sumaPolinomios(vector<vector<double>> &ecuacion){
    vector<double>resultados_suma;
    
    for(int i=0; i<ecuacion.size(); i++){
        double result=0;
        for(int j=0; j<ecuacion.at(i).size(); j++){
            result+=ecuacion.at(i).at(j);
        }
        resultados_suma.push_back(result);
    }
    
    for(int i=0; i<resultados_suma.size(); i++) {
        cout << "Suma - Grado " << i+1 << ": ";
        cout << resultados_suma[i] << " ";
        cout << endl;
    }
}
