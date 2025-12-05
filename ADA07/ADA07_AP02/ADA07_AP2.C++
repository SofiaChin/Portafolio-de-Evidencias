#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <limits>

using namespace std;

long long leerEnteroSeguro(const string& mensaje) {
    long long valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            return valor;
        } else {
            cout << ">> ERROR: Entrada invalida. Por favor ingrese solo numeros.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
}

struct Simbolo {
    string id;
    string tipo;
    string ambito;
    string valor;
};

class TablaSimbolos {
private:
    vector<list<Simbolo>> tabla;
    int capacidad;

    int funcionHash(string clave) {
        unsigned long hash = 5381;
        for (char c : clave) hash = ((hash << 5) + hash) + c;
        return hash % capacidad;
    }

public:
    TablaSimbolos(int tamano) : capacidad(tamano) {
        tabla.resize(capacidad);
    }

    void agregar(string id, string tipo, string ambito, string valor) {
        int indice = funcionHash(id);
        
        for (auto &simbolo : tabla[indice]) {
            if (simbolo.id == id) {
                cout << ">> Error: El ID '" << id << "' ya existe.\n";
                return;
            }
        }
        tabla[indice].push_back({id, tipo, ambito, valor});
        cout << ">> Exito: Simbolo agregado en lista del indice " << indice << ".\n";
    }

    void buscar(string id) {
        int indice = funcionHash(id);
        bool encontrado = false;
        
        for (auto &simbolo : tabla[indice]) {
            if (simbolo.id == id) {
                cout << "---------------------------------\n";
                cout << " [ENCONTRADO] en lista indice " << indice << "\n";
                cout << " ID:     " << simbolo.id << "\n";
                cout << " Tipo:   " << simbolo.tipo << "\n";
                cout << " Ambito: " << simbolo.ambito << "\n";
                cout << " Valor:  " << simbolo.valor << "\n";
                cout << "---------------------------------\n";
                encontrado = true;
                break;
            }
        }
        if (!encontrado) cout << ">> El identificador '" << id << "' no existe.\n";
    }

    void eliminar(string id) {
        int indice = funcionHash(id);
        for (auto it = tabla[indice].begin(); it != tabla[indice].end(); ++it) {
            if (it->id == id) {
                tabla[indice].erase(it);
                cout << ">> Simbolo '" << id << "' eliminado.\n";
                return;
            }
        }
        cout << ">> Error: No se encontro el simbolo.\n";
    }

    void visualizarTabla() {
        cout << "\n=== ESTADO VISUAL DE LA TABLA ===\n";
        cout << "Indice | Estructura \n";
        cout << "------------------------------------------------\n";
        
        for (int i = 0; i < capacidad; i++) {
            cout << "  " << i << "   | ";
            
            if (tabla[i].empty()) {
                cout << "[VACIO]";
            } else {
                for (auto it = tabla[i].begin(); it != tabla[i].end(); ++it) {
                    cout << "[" << it->id << "] -> ";
                }
                cout << "NULL";
            }
            cout << "\n";
        }
        cout << "------------------------------------------------\n";
    }
};

int main() {
    int tam, opcion;
    string id, tipo, ambito, valor;

    cout << "\n--- CONFIGURACION INICIAL ---\n";
    tam = (int)leerEnteroSeguro("Ingrese el tamanio de la tabla (ej. 5 o 7 para ver colisiones rapido): ");
    TablaSimbolos app(tam);

    do {
        cout << "\n=== MENU: TABLA DE SIMBOLOS ===\n";
        cout << "1. Agregar Identificador\n";
        cout << "2. Buscar Identificador\n";
        cout << "3. Eliminar Identificador\n";
        cout << "4. Visualizar Tabla \n";
        cout << "5. Salir\n";
        
        opcion = (int)leerEnteroSeguro("Opcion: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                cout << "Ingrese ID (nombre): "; getline(cin, id);
                cout << "Ingrese Tipo (int, float): "; getline(cin, tipo);
                cout << "Ingrese Ambito (global, local): "; getline(cin, ambito);
                cout << "Ingrese Valor inicial: "; getline(cin, valor);
                app.agregar(id, tipo, ambito, valor);
                break;
            case 2:
                cout << "Ingrese ID a buscar: "; getline(cin, id);
                app.buscar(id);
                break;
            case 3:
                cout << "Ingrese ID a eliminar: "; getline(cin, id);
                app.eliminar(id);
                break;
            case 4:
                app.visualizarTabla();
                break;
            case 5:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 5);

    return 0;
}