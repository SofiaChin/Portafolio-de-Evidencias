#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int matricula;
    char nombre[50];
    char apellido[50];
    float* calificaciones; 
    int numCalificaciones;
} Alumno;

typedef struct Nodo {
    Alumno alumno;
    struct Nodo* izquierdo;
    struct Nodo* derecho;
} Nodo;

float calcularPromedio(Alumno* al) {
    if (al->numCalificaciones == 0) {
        return 0.0;
    }
    float suma = 0;
    for (int i = 0; i < al->numCalificaciones; i++) {
        suma += al->calificaciones[i];
    }
    return suma / al->numCalificaciones;
}

void imprimirAlumno(Alumno* al) {
    printf("  Matricula: %d\n", al->matricula);
    printf("  Nombre: %s %s\n", al->nombre, al->apellido);
    printf("  Calificaciones: ");
    if (al->numCalificaciones == 0) {
        printf("N/A\n");
    } else {
        for (int i = 0; i < al->numCalificaciones; i++) {
            printf("%.2f ", al->calificaciones[i]);
        }
        printf("\n");
    }
    printf("  Promedio: %.2f\n", calcularPromedio(al));
    printf("----------------------------------------\n");
}

Nodo* crearNodo(Alumno al) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->alumno = al;
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;
    return nuevo;
}

Alumno crearAlumno() {
    Alumno al;
    printf("Ingrese Matricula: ");
    scanf("%d", &al.matricula);
    printf("Ingrese Nombre: ");
    scanf("%s", al.nombre);
    printf("Ingrese Apellido: ");
    scanf("%s", al.apellido);

    printf("Cuantas calificaciones desea ingresar?: ");
    scanf("%d", &al.numCalificaciones);

    al.calificaciones = (float*)malloc(al.numCalificaciones * sizeof(float));
    if (al.calificaciones == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        al.numCalificaciones = 0;
        return al;
    }

    for (int i = 0; i < al.numCalificaciones; i++) {
        printf("Ingrese calificacion %d: ", i + 1);
        scanf("%f", &al.calificaciones[i]);
    }
    return al;
}

Nodo* buscar(Nodo* raiz, int matricula) {
    if (raiz == NULL || raiz->alumno.matricula == matricula) {
        return raiz;
    }
    if (matricula < raiz->alumno.matricula) {
        return buscar(raiz->izquierdo, matricula);
    }
    return buscar(raiz->derecho, matricula);
}

Nodo* encontrarMinimo(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual && actual->izquierdo != NULL) {
        actual = actual->izquierdo;
    }
    return actual;
}

Nodo* insertar(Nodo* raiz, Alumno al) {
    if (raiz == NULL) {
        return crearNodo(al);
    }
    
    if (al.matricula < raiz->alumno.matricula) {
        raiz->izquierdo = insertar(raiz->izquierdo, al);
    } else if (al.matricula > raiz->alumno.matricula) {
        raiz->derecho = insertar(raiz->derecho, al);
    } else {
        printf("Error: La matricula %d ya existe.\n", al.matricula);
    }
    return raiz;
}

Nodo* eliminar(Nodo* raiz, int matricula) {
    if (raiz == NULL) {
        return raiz;
    }
    if (matricula < raiz->alumno.matricula) {
        raiz->izquierdo = eliminar(raiz->izquierdo, matricula);
    } else if (matricula > raiz->alumno.matricula) {
        raiz->derecho = eliminar(raiz->derecho, matricula);
    } else {
        free(raiz->alumno.calificaciones);
        if (raiz->izquierdo == NULL) {
            Nodo* temp = raiz->derecho;
            free(raiz);
            return temp;
        } else if (raiz->derecho == NULL) {
            Nodo* temp = raiz->izquierdo;
            free(raiz);
            return temp;
        }
        Nodo* temp = encontrarMinimo(raiz->derecho);
        raiz->alumno = temp->alumno;
        temp->alumno.calificaciones = NULL; 
        raiz->derecho = eliminar(raiz->derecho, temp->alumno.matricula);
    }
    return raiz;
}

void reportePorMatricula(Nodo* raiz) {
    if (raiz != NULL) {
        reportePorMatricula(raiz->izquierdo);
        imprimirAlumno(&(raiz->alumno));
        reportePorMatricula(raiz->derecho);
    }
}

int compararPorPromedio(const void* a, const void* b) {
    Alumno* alA = (Alumno*)a;
    Alumno* alB = (Alumno*)b;
    float promA = calcularPromedio(alA);
    float promB = calcularPromedio(alB);

    if (promA < promB) return -1;
    if (promA > promB) return 1;
    return 0;
}

void recolectarAlumnos(Nodo* raiz, Alumno** arrayAlumnos, int* count, int* capacity) {
    if (raiz == NULL) {
        return;
    }
    recolectarAlumnos(raiz->izquierdo, arrayAlumnos, count, capacity);
    if (*count == *capacity) {
        *capacity *= 2;
        *arrayAlumnos = (Alumno*)realloc(*arrayAlumnos, *capacity * sizeof(Alumno));
        if (*arrayAlumnos == NULL) {
            printf("Error: Falla en realloc.\n");
            exit(1);
        }
    }
    (*arrayAlumnos)[*count] = raiz->alumno;
    (*count)++;
    recolectarAlumnos(raiz->derecho, arrayAlumnos, count, capacity);
}

void reportePorPromedio(Nodo* raiz) {
    if (raiz == NULL) {
        printf("El arbol esta vacio.\n");
        return;
    }
    int capacity = 10;
    int count = 0;
    Alumno* arrayAlumnos = (Alumno*)malloc(capacity * sizeof(Alumno));
    if (arrayAlumnos == NULL) {
        printf("Error: No se pudo asignar memoria inicial.\n");
        return;
    }
    recolectarAlumnos(raiz, &arrayAlumnos, &count, &capacity);
    qsort(arrayAlumnos, count, sizeof(Alumno), compararPorPromedio);
    printf("\n--- Reporte de Alumnos por Promedio ---\n");
    for (int i = 0; i < count; i++) {
        imprimirAlumno(&arrayAlumnos[i]);
    }
    free(arrayAlumnos);
}

void reporteCondicional(Nodo* raiz, float umbral, int esMenor) {
    if (raiz == NULL) {
        return;
    }
    reporteCondicional(raiz->izquierdo, umbral, esMenor);
    float prom = calcularPromedio(&(raiz->alumno));
    if (esMenor && prom < umbral) {
        imprimirAlumno(&(raiz->alumno));
    } else if (!esMenor && prom >= umbral) {
        imprimirAlumno(&(raiz->alumno));
    }
    reporteCondicional(raiz->derecho, umbral, esMenor);
}

void actualizarCalificacion(Nodo* raiz) {
    int matricula;
    printf("Ingrese la matricula del alumno a actualizar: ");
    scanf("%d", &matricula);
    Nodo* nodo = buscar(raiz, matricula);
    if (nodo == NULL) {
        printf("Alumno con matricula %d no encontrado.\n", matricula);
        return;
    }
    if (nodo->alumno.numCalificaciones == 0) {
        printf("Este alumno no tiene calificaciones para actualizar.\n");
        return;
    }
    printf("Calificaciones actuales de %s %s:\n", nodo->alumno.nombre, nodo->alumno.apellido);
    for (int i = 0; i < nodo->alumno.numCalificaciones; i++) {
        printf("  %d: %.2f\n", i + 1, nodo->alumno.calificaciones[i]);
    }
    int index;
    printf("Que calificacion desea actualizar (1 a %d)?: ", nodo->alumno.numCalificaciones);
    scanf("%d", &index);
    if (index < 1 || index > nodo->alumno.numCalificaciones) {
        printf("Error: Indice invalido.\n");
        return;
    }
    float nuevaCalificacion;
    printf("Ingrese la nueva calificacion: ");
    scanf("%f", &nuevaCalificacion);
    nodo->alumno.calificaciones[index - 1] = nuevaCalificacion;
    printf("Calificacion actualizada con exito.\n");
}

void _contarMenor(Nodo* nodoActual, float promedioObjetivo, int matriculaObjetivo, int* contador) {
    if (nodoActual == NULL) {
        return;
    }
    if (nodoActual->alumno.matricula != matriculaObjetivo) {
        float promActual = calcularPromedio(&(nodoActual->alumno));
        if (promActual < promedioObjetivo) {
            (*contador)++;
        }
    }
    _contarMenor(nodoActual->izquierdo, promedioObjetivo, matriculaObjetivo, contador);
    _contarMenor(nodoActual->derecho, promedioObjetivo, matriculaObjetivo, contador);
}

void contarMenorPromedio(Nodo* raiz) {
    int matricula;
    printf("Ingrese la matricula del alumno de referencia: ");
    scanf("%d", &matricula);
    Nodo* nodoTarget = buscar(raiz, matricula);
    if (nodoTarget == NULL) {
        printf("Alumno con matricula %d no encontrado.\n", matricula);
        return;
    }
    float promedioTarget = calcularPromedio(&(nodoTarget->alumno));
    printf("El promedio del alumno %d es %.2f.\n", matricula, promedioTarget);
    int contador = 0;
    _contarMenor(raiz, promedioTarget, matricula, &contador);
    printf("Numero de alumnos con promedio menor a %.2f: %d\n", promedioTarget, contador);
}

void _mostrarNivel(Nodo* nodo, int nivelBuscado, int nivelActual) {
    if (nodo == NULL) {
        return;
    }
    if (nivelActual == nivelBuscado) {
        printf("  Matricula: %d (%s %s)\n", nodo->alumno.matricula, nodo->alumno.nombre, nodo->alumno.apellido);
    } else {
        _mostrarNivel(nodo->izquierdo, nivelBuscado, nivelActual + 1);
        _mostrarNivel(nodo->derecho, nivelBuscado, nivelActual + 1);
    }
}

void mostrarNivel(Nodo* raiz) {
    int nivel;
    printf("Ingrese el nivel que desea mostrar (0 es la raiz): ");
    scanf("%d", &nivel);

    if (raiz == NULL && nivel >= 0) {
        printf("El arbol esta vacio.\n");
        return;
    }
    
    printf("\n--- Nodos en el Nivel %d ---\n", nivel);
    _mostrarNivel(raiz, nivel, 0);
    printf("-----------------------------\n");
}

int alturaDelArbol(Nodo* nodo) {
    if (nodo == NULL) return 0;
    int alturaIzq = alturaDelArbol(nodo->izquierdo);
    int alturaDer = alturaDelArbol(nodo->derecho);
    return (alturaIzq > alturaDer ? alturaIzq : alturaDer) + 1;
}

void calcularAnchoMaximo(Nodo* nodo, int* anchoMax) {
    if (nodo == NULL) return;
    char buffer[20];
    sprintf(buffer, "%d", nodo->alumno.matricula);
    int anchoActual = strlen(buffer);
    if (anchoActual > *anchoMax) {
        *anchoMax = anchoActual;
    }
    calcularAnchoMaximo(nodo->izquierdo, anchoMax);
    calcularAnchoMaximo(nodo->derecho, anchoMax);
}

void llenarNiveles(Nodo** niveles, Nodo* nodo, int indice, int max_nodos) {
    if (nodo == NULL || indice >= max_nodos) return;
    niveles[indice] = nodo;
    llenarNiveles(niveles, nodo->izquierdo, 2 * indice + 1, max_nodos);
    llenarNiveles(niveles, nodo->derecho, 2 * indice + 2, max_nodos);
}

void imprimirEspacios(int count) {
    for (int i = 0; i < count; i++) printf(" ");
}

void imprimirNodos(Nodo** niveles, int nivel, int altura, int anchoCelda) {
    int nodosEnNivel = 1 << nivel;
    int inicioIndice = nodosEnNivel - 1;
    int espacioEntre = (1 << (altura - nivel)) * anchoCelda;

    imprimirEspacios((espacioEntre / 2));

    for (int i = 0; i < nodosEnNivel; i++) {
        Nodo* actual = niveles[inicioIndice + i];
        if (actual != NULL) {
            char buffer[20];
            sprintf(buffer, "%d", actual->alumno.matricula);
            int paddingIzq = (anchoCelda - strlen(buffer)) / 2;
            imprimirEspacios(paddingIzq);
            printf("%s", buffer);
            imprimirEspacios(anchoCelda - strlen(buffer) - paddingIzq);
        } else {
            imprimirEspacios(anchoCelda);
        }
        if (i < nodosEnNivel - 1) {
            imprimirEspacios(espacioEntre - anchoCelda);
        }
    }
    printf("\n");
}

void mostrarArbolGraficoAlineado(Nodo* raiz) {
    if (raiz == NULL) {
        printf("El arbol esta vacio.\n");
        return;
    }
    int altura = alturaDelArbol(raiz);
    int max_nodos = (1 << altura) - 1;
    int anchoMax = 0;
    calcularAnchoMaximo(raiz, &anchoMax);
    if (anchoMax % 2 == 0) anchoMax++; 

    Nodo** niveles = (Nodo**)calloc(max_nodos, sizeof(Nodo*));
    if (niveles == NULL) return;
    
    llenarNiveles(niveles, raiz, 0, max_nodos);

    for (int i = 0; i < altura; i++) {
        imprimirNodos(niveles, i, altura - 1, anchoMax + 1);
        printf("\n");
    }
    free(niveles);
}

void liberarArbol(Nodo* raiz) {
    if (raiz != NULL) {
        liberarArbol(raiz->izquierdo);
        liberarArbol(raiz->derecho);
        free(raiz->alumno.calificaciones);
        free(raiz);
    }
}

void mostrarMenu() {
    printf("\n--- Sistema de Gestion de Estudiantes ---\n");
    printf("1. Insertar nuevo estudiante\n");
    printf("2. Reporte de estudiantes por Matricula (In-Order)\n");
    printf("3. Reporte de estudiantes por Promedio\n");
    printf("4. Reporte de estudiantes con promedio < 70\n");
    printf("5. Reporte de estudiantes con promedio >= 70\n");
    printf("6. Eliminar estudiante por Matricula\n");
    printf("7. Actualizar calificacion de un estudiante\n");
    printf("8. Contar alumnos con promedio menor (dada una matricula)\n");
    printf("9. Mostrar nodos de un nivel especifico\n");
    printf("10. Mostrar arbol graficamente\n");
    printf("0. Salir\n");
    printf("-----------------------------------------------\n");
    printf("Seleccione una opcion: ");
}

int main() {
    Nodo* raiz = NULL;
    int opcion;
    
    do {
        mostrarMenu();
        if (scanf("%d", &opcion) != 1) {
            opcion = -1; 
        }

        switch (opcion) {
            case 1: {
                printf("\n1. Insertar Estudiante\n");
                Alumno nuevoAlumno = crearAlumno();
                raiz = insertar(raiz, nuevoAlumno);
                break;
            }
            case 2:
                printf("\n2. Reporte por Matricula\n");
                if (raiz == NULL) printf("El arbol esta vacio.\n");
                else reportePorMatricula(raiz);
                break;
            case 3:
                printf("\n3. Reporte por Promedio\n");
                reportePorPromedio(raiz);
                break;
            case 4:
                printf("\n4. Reporte Promedio < 70\n");
                if (raiz == NULL) printf("El arbol esta vacio.\n");
                else reporteCondicional(raiz, 70.0, 1);
                break;
            case 5:
                printf("\n5. Reporte Promedio >= 70\n");
                if (raiz == NULL) printf("El arbol esta vacio.\n");
                else reporteCondicional(raiz, 70.0, 0);
                break;
            case 6: {
                printf("\n6. Eliminar Estudiante\n");
                if (raiz == NULL) {
                    printf("El arbol esta vacio.\n");
                } else {
                    int matriculaEliminar;
                    printf("Ingrese la matricula a eliminar: ");
                    scanf("%d", &matriculaEliminar);
                    raiz = eliminar(raiz, matriculaEliminar);
                }
                break;
            }
            case 7: 
                printf("\n7. Actualizar Calificacion\n");
                if (raiz == NULL) printf("El arbol esta vacio.\n");
                else actualizarCalificacion(raiz);
                break;
            case 8:
                printf("\n8. Contar Alumnos con Promedio Menor\n");
                if (raiz == NULL) printf("El arbol esta vacio.\n");
                else contarMenorPromedio(raiz);
                break;
            case 9:
                printf("\n9. Mostrar Nivel\n");
                mostrarNivel(raiz);
                break;
            case 10:
                printf("\n10. Mostrar Arbol Grafico\n\n");
                mostrarArbolGraficoAlineado(raiz);
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        if (opcion != 0) {
            printf("\nPresione Enter para continuar...");
            getchar();
        }

    } while (opcion != 0);

    liberarArbol(raiz);
    return 0;
}