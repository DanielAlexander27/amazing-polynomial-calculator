//
//  main.cpp
//  ProyectoFinal
//
//

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#define INCOGNITA_VALOR_DEFECTO ' '

using namespace std;

struct tPolimonios {
    char incognitaGlobal = INCOGNITA_VALOR_DEFECTO;
    vector<string> listaPolinomios;
    map<int, vector<double>> coeficientesPorGrado;
    map<int, double> polinomioSuma;
};

// Prototipo de Funciones
void sumarNPolinomios(tPolimonios& polinomiosASumar);
vector<string> solicitarPolinomios(char& incognita);
void limpiarEspaciosPolinomio(string& polinomio);
bool verificarPolinomio(string& polinomio, char& incognita);
void deconstruirPolinomio(map<int, vector<double>>& coeficientesPorGrado, string& polinomio);
void clasificarCoefPorGrado(vector<double>& numeros, string& polinomio, map<int, vector<double>>& coeficientesPorGrado);
map<int, double> sumarTerminosSemajantes(map<int, vector<double>>& coeficientesPorGrado);
void imprimirResultadoSuma(map<int, double> polinomioSuma);

// Main
int main(int argc, const char * argv[]) {
    tPolimonios estructuraPolinomios;
    sumarNPolinomios(estructuraPolinomios);
    
    return 0;
}

/****
    Implementacion de Logica en Funciones
 */

void sumarNPolinomios(tPolimonios& polinomiosASumar) {
    polinomiosASumar.listaPolinomios = solicitarPolinomios(polinomiosASumar.incognitaGlobal);
    
    polinomiosASumar.listaPolinomios.at(0);
    
    for (int i = 0; i < polinomiosASumar.listaPolinomios.size(); i++) {
        deconstruirPolinomio(polinomiosASumar.coeficientesPorGrado, polinomiosASumar.listaPolinomios.at(i));
    }
    
    polinomiosASumar.polinomioSuma = sumarTerminosSemajantes(polinomiosASumar.coeficientesPorGrado);
    imprimirResultadoSuma(polinomiosASumar.polinomioSuma);
}

/**
    La función solicitarPolinomios() se encarga de solicitar una cantidad N de polinomios ingresados por el usuario. Verifica que el polinomio introducido sea correcto
    y devuelve un vector<string> que contiene aquellos polinomios.
 */
vector<string> solicitarPolinomios(char& incognita) {
    vector<string> listaPolinomios;
    string polinomio;
    int cantidad;
    
    cout << "Introduzca la cantidad de polinomios a sumar: ";
    
    // El primer condiconal evalua si el input introducido es incorrecto. El segundo detecta si el input es una mezcla de números
    // como: "12 ab"
    while(true) {
        if (!(cin >> cantidad)) {
            cout << "Por favor solo ingresa números" << endl;
            cout << "Introduzca la cantidad de polinomios a sumar: ";
            // Codigo hecho con ayuda de ChatGPT
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (cin.peek() != '\n' && !isdigit(cin.peek())) {
            cout << "Por favor solo ingresa números" << endl;
            cout << "Introduzca la cantidad de polinomios a sumar: ";
            // Codigo hecho con ayuda de ChatGPT
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    
    // Codigo hecho con ayuda de ChatGPT
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;
    
    for(int i = 0; i < cantidad; i++) {
        cout << "Polinomio " << (i+1) << ": ";
        getline(cin, polinomio);
        
        if (verificarPolinomio(polinomio, incognita)) {
            listaPolinomios.push_back(polinomio);
        } else {
            i--;
        }
    }
    
    return listaPolinomios;
}


/**
    La función limpiarEspaciosPolinomio() se encarga de eliminar caracteres de espacios.
 */
void limpiarEspaciosPolinomio(string& polinomio) {
    // Código realizado con ayuda de ChatGPT
    polinomio.erase(remove_if(polinomio.begin(), polinomio.end(), ::isspace), polinomio.end());
}

/**
    La función verificarPolinomio() se encarga de comprobrar que el polinomio introducido cumpla con la estructura necesaria como los símbolos empleados (no se aceptan operaciones como multiplicaciones entre coeficintes ni divisiones) y que los exponentes de las incognitas sean numeros naturales. Sumado a lo anterior verifica que existe una sola variable en la ecuación.
 */
bool verificarPolinomio(string& polinomio, char& incognita) {
    limpiarEspaciosPolinomio(polinomio);
    
    if (polinomio.empty()) {
        cout << "Input vacío. Introduzca un polinomio" << endl << endl;
        return false;
    }
    
    
    for(int i = 0; i < polinomio.size(); i++) {
        bool evaluadorLetra = (incognita == ' ') ? isalpha(polinomio.at(i)) : polinomio.at(i) == incognita;
        bool isSign = polinomio.at(i) == '+' || polinomio.at(i) == '-';
        
        // Condicional que evita casos donde el input sea algo como ++3 o --4.
        if (isSign) {
            if (i == polinomio.size() - 1) {
                cout << "Error. No se aceptan signos de + o - al final del polinomio. Vuelva a introducir" << endl << endl;
            } else if (polinomio.at(i+1) == '+' || polinomio.at(i+1) == '-' ) {
                cout << "Error. No se aceptan signos de + o - seguidos. Vuelva a introducir" << endl << endl;
            } else {
                continue;
            }
            return false;
        }
        
        
        // Condicional que evita casos donde el exponente contenga incógnitas como x22x.
        if (evaluadorLetra) {
            for (int j = i+1; j < polinomio.size(); j++) {
                if (isalpha(polinomio.at(j))) {
                    cout << "Error. No se aceptan incognitas en el exponente. Vuelva a introducir" << endl << endl;
                    return false;
                } else if (polinomio.at(j) == '+' || polinomio.at(j) == '-') {
                    break;
                }
            }
            continue;
        }
        
        // Condicional que opera en caso de que la posicion actual no cumple con ser numero, ni signo (+-), ni letra.
        if (!(isdigit(polinomio.at(i)) || isSign || evaluadorLetra)) {
            if (isalpha(polinomio.at(i)) && (polinomio.at(i) != incognita)) {
                cout << "Error. Solo se aceptan polinomios de una incógnita. Vuelva a introducir" << endl << endl;
                return false;
            }
            
            
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
void deconstruirPolinomio(map<int, vector<double>>& coeficientesPorGrado, string& polinomio) {
    vector<double> numeros;
    string stringCoef;
    int posicionInicio = -1, posicionFinal = -1;
    
    for (int i = 0; i < polinomio.size(); i++) {
        if (i == 0 && isalpha(polinomio.at(i))) {
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
            if (isalpha(polinomio.at(i)) && (i == (polinomio.size()-1) || polinomio.at(i+1) == '+' || polinomio.at(i+1) == '-')) {
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
        } else if (polinomio.at(i) == '+' || polinomio.at(i) == '-' || isalpha(polinomio.at(i)) || polinomio.at(i) == '*') {
            posicionFinal = i;
            stringCoef = {polinomio.begin() + posicionInicio, polinomio.begin() + posicionFinal};
            
            /**Condicional para almacenar el coeficiente 1 cuando esta implicito como en el caso [...]+x+[....]*/
            if (isalpha(polinomio.at(i)) && (polinomio.at(i-1) == '+' || polinomio.at(i-1) == '-')) {
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
    
//    cout << "[";
//
//    for (auto num : numeros) {
//        cout << num << ", ";
//    }
//
//    cout << "]" << endl;
    
    clasificarCoefPorGrado(numeros, polinomio, coeficientesPorGrado);
}

/**
    La función clasificarCoefPorGrado() se encarga de clasificar los coeficientes según el grado al que pertenencen.  Esto lo hace almacenando en un map,
    donde el key indica el grado y el vector anidado contiene los coeficientes correspondientes a tal grado.
 */
void clasificarCoefPorGrado(vector<double>& numeros, string& polinomio, map<int, vector<double>>& coeficientesPorGrado) {
    unsigned int temp = 0;
    bool detectarIncognita = false;
    
    // Para clasificar se lee nuevamente el polinomio. Se detiene cada vez que encuentra un + o - y verifica si encontró
    // una x (o incógnita). En caso de haber encontrado la x, sabe que el elemento i es coeficiente y el elemento i+1 el grado al que
    // pertenece. Caso contrario, se toma únicamente el elemento i, el cual pertenece al grado 0.
    for (int i = 0; i < polinomio.size(); i++) {
        if (isalpha(polinomio.at(i))) {
            detectarIncognita = true;
        }
        
        if ((i != 0 && (polinomio.at(i) == '+' or polinomio.at(i) == '-')) or i == polinomio.size() - 1) {
            double coef = numeros.at(temp);
            if (detectarIncognita) {
                int exp = numeros.at(temp + 1);
                coeficientesPorGrado[exp].push_back(coef);
                temp += 2;
            } else {
                coeficientesPorGrado[0].push_back(coef);
                temp += 1;
            }
            
            if (detectarIncognita)
                detectarIncognita = !detectarIncognita;
        }
    }
    
//    for (const auto& grado: coeficientesPorGrado ) {
//        cout << "Grado " << grado.first << ": ";
//        for(const auto& num: grado.second){
//            cout << num <<" ";
//        }
//        cout<<endl;
//    }
}

/**
    La función sumarTerminosSemejantes() devuelve un nuevo map<int, double> que contiene los resultados tras haber sumado los coeficientes del vector de vectores. De igual manera, el valor de key indica el grado al que el coeficiente pertenece.
 */
map<int, double> sumarTerminosSemajantes(map<int, vector<double>>& coeficientesPorGrado){
    map<int, double> resultadosSuma;
    
    // Se recorre el map y se va sumando cada uno de sus valores.
    for (const auto& val : coeficientesPorGrado) {
        double result = 0;
        for (const auto& num : val.second) {
            result += num;
        }
        // Si la suma es 0 se descarta aquel grado.
        if (result != 0)
            resultadosSuma[val.first] = result;
        
    }


//    for(int i=0; i < resultadosSuma.size(); i++) {
//        cout << "Suma - Grado " << i << ": ";
//        cout << resultadosSuma[i] << " ";
//        cout << endl;
//    }
    
    return resultadosSuma;
}

/**
    La función imprimirResultadoSuma() imprime los resultados de la suma de polinomois.
 */
void imprimirResultadoSuma(map<int, double> polinomioSuma) {
    cout << endl;
    // Código hecho con ayuda de ChatGPT
    cout << "El polinomo suma es de grado " << (polinomioSuma.rbegin())->first << ": " << endl;
    
    // En caso de que la respuesta final tras la suma sea 0
    if (polinomioSuma.empty()) {
        cout << 0 << endl << endl;
        return;
    }
    
    bool primerElemento = true;
    for (const auto& val : polinomioSuma) {
        if (val.second < 0) {
            cout << "- " << val.second * (-1);
        } else if (val.second > 0) {
            
            if(!primerElemento) {
                cout << "+ " << val.second;
            } else {
                cout << val.second;
            }
        }
        
        if (val.first != 0) {
            cout << "*x" << val.first << " ";
        } else {
            cout << " ";
        }
        primerElemento = false;
    }
    
    cout << endl;
}
