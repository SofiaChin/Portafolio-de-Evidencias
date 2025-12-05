#include <iostream>
#include <string>
#include <vector>
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

struct Estudiante {
    int matricula; 
    string nombre;
    string carrera;
};

enum EstadoCelda { VACIO, OCUPADO, BORRADO };

struct Celda {
    Estudiante dato;
    EstadoCelda estado;
    Celda() : estado(VACIO) { dato.matricula = -1; }
};

class TablaHashEstudiantes {
private:
    vector<Celda> tabla;
    int capacidad;
    int cantidad;

    int funcionHash(int matricula) {
        return matricula % capacidad;
    }

public:
    TablaHashEstudiantes(int tamano) : capacidad(tamano), cantidad(0) {
        tabla.resize(capacidad);
    }

    void agregar(int matricula, string nombre, string carrera) {
        if (matricula > 999999 || matricula < 0) {
            cout << ">> Error: Matricula fuera de rango (0-999999).\n";
            return;
        }
        if (cantidad >= capacidad) {
            cout << ">> Error: La tabla esta llena.\n";
            return;
        }

        int indice = funcionHash(matricula);
        int indiceInicial = indice;
        int colisiones = 0;

        while (tabla[indice].estado == OCUPADO) {
            if (tabla[indice].dato.matricula == matricula) {
                cout << ">> Error: La matricula " << matricula << " ya existe.\n";
                return;
            }
            indice = (indice + 1) % capacidad;
            colisiones++;
            if (indice == indiceInicial) return;
        }

        tabla[indice].dato = {matricula, nombre, carrera};
        tabla[indice].estado = OCUPADO;
        cantidad++;
        cout << ">> Exito: Estudiante registrado en indice [" << indice << "]";
        if (colisiones > 0) cout << " (Colisiones resueltas: " << colisiones << ")";
        cout << "\n";
    }

    void buscar(int matricula) {
        int indice = funcionHash(matricula);
        int indiceInicial = indice;

        while (tabla[indice].estado != VACIO) {
            if (tabla[indice].estado == OCUPADO && tabla[indice].dato.matricula == matricula) {
                cout << "---------------------------------\n";
                cout << " [ENCONTRADO] en indice " << indice << "\n";
                cout << " Matricula: " << tabla[indice].dato.matricula << "\n";
                cout << " Nombre:    " << tabla[indice].dato.nombre << "\n";
                cout << " Carrera:   " << tabla[indice].dato.carrera << "\n";
                cout << "---------------------------------\n";
                return;
            }
            indice = (indice + 1) % capacidad;
            if (indice == indiceInicial) break;
        }
        cout << ">> No se encontro ningun estudiante con esa matricula.\n";
    }

    void eliminar(int matricula) {
        int indice = funcionHash(matricula);
        int indiceInicial = indice;

        while (tabla[indice].estado != VACIO) {
            if (tabla[indice].estado == OCUPADO && tabla[indice].dato.matricula == matricula) {
                tabla[indice].estado = BORRADO;
                cantidad--;
                cout << ">> Estudiante eliminado (Marcado como BORRADO).\n";
                return;
            }
            indice = (indice + 1) % capacidad;
            if (indice == indiceInicial) break;
        }
        cout << ">> Error: Matricula no encontrada.\n";
    }

    void visualizarTabla() {
        cout << "\n=== ESTADO VISUAL DE LA TABLA ===\n";
        cout << "Indice | Estado   | Datos\n";
        cout << "------------------------------------------------\n";
        for (int i = 0; i < capacidad; i++) {
            cout << "  " << i << "   | ";
            switch (tabla[i].estado) {
                case VACIO:   cout << "[VACIO]  | -"; break;
                case OCUPADO: cout << "[OCUPADO]| " << tabla[i].dato.matricula << " (" << tabla[i].dato.nombre << ")"; break;
                case BORRADO: cout << "[BORRADO]| *Disponible*"; break;
            }
            cout << "\n";
        }
        cout << "------------------------------------------------\n";
    }
};

int main() {
    int tam, opcion;
    long long inputMatricula;
    string nombre, carrera;
    
    cout << "\n--- CONFIGURACION INICIAL ---\n";
    tam = (int)leerEnteroSeguro("Ingrese el tamanio de la tabla (ej. 7, 11): ");
    TablaHashEstudiantes app(tam);

    do {
        cout << "\n=== MENU: REGISTRO DE ESTUDIANTES ===\n";
        cout << "1. Agregar Estudiante\n";
        cout << "2. Buscar Estudiante\n";
        cout << "3. Eliminar Estudiante\n";
        cout << "4. Visualizar Tabla \n";
        cout << "5. Salir\n";
        
        opcion = (int)leerEnteroSeguro("Opcion: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        switch (opcion) {
            case 1:
                while (true) {
                    inputMatricula = leerEnteroSeguro("Ingrese Matricula (max 6 digitos): ");
                    if (inputMatricula >= 0 && inputMatricula <= 999999) break;
                    else cout << ">> ERROR: Rango 0 - 999999.\n";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ingrese Nombre: "; getline(cin, nombre);
                cout << "Ingrese Carrera: "; getline(cin, carrera);
                app.agregar((int)inputMatricula, nombre, carrera);
                break;
            case 2:
                inputMatricula = leerEnteroSeguro("Ingrese Matricula a buscar: ");
                app.buscar((int)inputMatricula);
                break;
            case 3:
                inputMatricula = leerEnteroSeguro("Ingrese Matricula a eliminar: ");
                app.eliminar((int)inputMatricula);
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