<div align="center">

# 🌳 ADA 07: Árboles Binarios de Búsqueda (BST)

<img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B" />
<img src="https://img.shields.io/badge/Structure-Binary%20Search%20Tree-forestgreen?style=flat-square" />
<img src="https://img.shields.io/badge/Pattern-Recursion-important?style=flat-square" />

</div>

---

## 📄 Descripción Técnica
Implementación de un **Árbol Binario de Búsqueda (BST)**, una estructura fundamental donde cada nodo cumple la condición: *todos los elementos a su izquierda son menores y los de la derecha son mayores*.

El proyecto se divide en dos partes: la construcción base del árbol mediante inserción dinámica y la implementación de algoritmos de recorrido (traversal) para visualizar la información de diferentes formas.

## 💻 Funcionalidades y Algoritmos
* **Inserción Recursiva:** Función que navega el árbol hasta encontrar una posición nula (`NULL`) adecuada para el nuevo valor.
* **Recorridos (Traversals):**
    * *InOrden:* Imprime los valores ordenados de menor a mayor (Izq-Raíz-Der).
    * *PreOrden:* Útil para copiar árboles (Raíz-Izq-Der).
    * *PostOrden:* Útil para eliminar árboles (Izq-Der-Raíz).

## 📂 Estructura de Archivos
| Archivo | Descripción |
| :--- | :--- |
| `ADA07_AP1.c++` | Implementación base del nodo y funciones de inserción. |
| `ADA07_AP2.C++` | Extensión con funciones de búsqueda y casos de prueba complejos. |

## 🧠 Reflexión y Análisis Personal
**Aprendizajes:**


Esta práctica consolidó mi entendimiento de la **recursividad**. Fue fascinante ver cómo una función de 4 líneas puede recorrer una estructura compleja completa. También aprendí la importancia del balanceo; si insertamos datos ordenados (1, 2, 3...) el árbol se degenera en una lista, perdiendo su eficiencia.

**Retos Enfrentados:**
La visualización mental de la recursión (el "stack trace") fue difícil. Entender cuándo una función termina y regresa el control a su nodo "padre" nos costó trabajo al principio, especialmente en los recorridos PostOrden. Usar diagramas en papel para seguir la ejecución paso a paso fue vital para depurar el código.

