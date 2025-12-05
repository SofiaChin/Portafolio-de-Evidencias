<div align="center">

# 💾 ADA 02: Memoria Dinámica y Apuntadores

<img src="https://img.shields.io/badge/Language-C-A8B9CC?style=flat-square&logo=c" />
<img src="https://img.shields.io/badge/Topic-Pointers-red?style=flat-square" />
<img src="https://img.shields.io/badge/Concept-Memory%20Allocation-critical?style=flat-square" />

</div>

---

## 📄 Descripción Técnica
Esta práctica se centró en la manipulación de bajo nivel de la memoria RAM. A diferencia de lenguajes de alto nivel, en C debemos gestionar manualmente la asignación y liberación de recursos.

Realizamos ejercicios intensivos sobre **Aritmética de Punteros**, entendiendo cómo navegar a través de arreglos simplemente incrementando direcciones de memoria, y practicamos el paso de parámetros por referencia para modificar variables fuera del alcance local de una función.

## 💻 Competencias Adquiridas
* Uso de `malloc` y `free` para gestión del **Heap**.
* Diferenciación entre el operador de dirección `&` y de indirección `*`.
* Creación de estructuras (`struct`) dinámicas.

## 📂 Estructura de Archivos
| Archivo | Función |
| :--- | :--- |
| `ADA02.c` | Código fuente con ejercicios de punteros y arreglos dinámicos. |

## 🧠 Reflexión y Análisis Personal
**Aprendizajes:**
Entendí que un arreglo en C es básicamente un puntero al primer elemento del bloque de memoria. Esto cambió mi forma de ver las matrices, ya que ahora entiendo que acceder a `arr[i]` es internamente `*(arr + i)`. La eficiencia de pasar punteros a funciones en lugar de copiar estructuras grandes fue una gran lección de optimización.

**Retos Enfrentados:**
El concepto de "fuga de memoria" (Memory Leak) fue algo nuevo. Tuvimos problemas donde el programa se cerraba inesperadamente (Segmentation Fault) por intentar acceder a punteros que ya habían sido liberados o que no estaban inicializados (`NULL`). Aprendimos a ser disciplinados siempre igualando a NULL después de un `free`.
