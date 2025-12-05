#include <iostream>
#include <fstream>
#include <stack>
#include <cctype>
#include <cmath>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

int prioridad(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

bool esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

string infijoAPostfijo(const string &infijo) {
    stack<char> pila;
    stringstream postfijo;
    int n = infijo.size();
    for (int i = 0; i < n; i++) {
        char c = infijo[i];
        if (isdigit(c)) {
            while (i < n && isdigit(infijo[i])) {
                postfijo << infijo[i];
                i++;
            }
            postfijo << " ";
            i--;
        }
        else if (c == '(') {
            pila.push(c);
        }
        else if (c == ')') {
            while (!pila.empty() && pila.top() != '(') {
                postfijo << pila.top() << " ";
                pila.pop();
            }
            if (!pila.empty()) pila.pop();
        }
        else if (esOperador(c)) {
            while (!pila.empty() && prioridad(pila.top()) >= prioridad(c)) {
                postfijo << pila.top() << " ";
                pila.pop();
            }
            pila.push(c);
        }
    }
    while (!pila.empty()) {
        postfijo << pila.top() << " ";
        pila.pop();
    }
    return postfijo.str();
}

float evaluarPostfijo(const string &postfijo, ofstream &fout) {
    stack<float> pila;
    stringstream ss(postfijo);
    string token;
    while (ss >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            pila.push(atof(token.c_str()));
        }
        else if (esOperador(token[0]) && token.size() == 1) {
            if (pila.size() < 2) {
                fout << "Error: Expresión postfija inválida\n";
                return 0;
            }
            float b = pila.top(); pila.pop();
            float a = pila.top(); pila.pop();
            float res = 0;
            switch (token[0]) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/':
                    if (b == 0) {
                        fout << "Error división por cero\n";
                        return 0;
                    }
                    res = a / b; break;
                case '^': res = pow(a, b); break;
            }
            pila.push(res);
        }
    }
    return pila.top();
}

void mostrarPila(stack<float> pila, ofstream &fout) {
    while (!pila.empty()) {
        fout << pila.top() << " ";
        pila.pop();
    }
    fout << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " infijas.txt" << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin.is_open()) {
        cerr << "No se pudo abrir el archivo de entrada.\n";
        return 1;
    }

    ofstream fout("postfijas.txt");
    if (!fout.is_open()) {
        cerr << "No se pudo crear el archivo de salida.\n";
        return 1;
    }

    string linea;
    while (getline(fin, linea)) {
        size_t pos = linea.find(';');
        if (pos != string::npos) linea = linea.substr(0, pos);

        if (linea.empty()) continue;

        string postfijo = infijoAPostfijo(linea);
        double resultado = evaluarPostfijo(postfijo, fout);
    fout << postfijo << ";Resultado: " << resultado << endl;
    }

    fin.close();
    fout.close();
    return 0;
}
