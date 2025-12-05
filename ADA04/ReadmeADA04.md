<div align="center">

# 🔗 ADA 04: Listas Enlazadas Simples

<img src="https://img.shields.io/badge/Language-C-A8B9CC?style=flat-square&logo=c" />
<img src="https://img.shields.io/badge/Structure-Linked%20List-blue?style=flat-square" />
<img src="https://img.shields.io/badge/Memory-Dynamic-green?style=flat-square" />

</div>

---

## 📄 Descripción Técnica
Implementación desde cero de una **Lista Enlazada Simple (Singly Linked List)**. A diferencia de los arreglos contiguos, esta estructura utiliza nodos dispersos en memoria, conectados lógicamente mediante punteros `next`.

El programa gestiona una colección de datos permitiendo operaciones CRUD (Create, Read, Update, Delete) sin limitaciones de tamaño fijo. Cada nodo contiene un dato y la dirección de memoria del siguiente elemento.

## 💻 Funciones Clave
* `InsertarInicio()` / `InsertarFinal()`: Lógica para actualizar el puntero `Head` o recorrer hasta `NULL`.
* `EliminarNodo()`: Algoritmo de búsqueda y re-enlazado de punteros para aislar el nodo a borrar.
* `ImprimirLista()`: Recorrido iterativo de la estructura.

## 📂 Estructura de Archivos
| Archivo | Función |
| :--- | :--- |
| `ADA04_E04.c` | Definición del `struct Nodo` y funciones de manejo de lista. |

## 🧠 Reflexión y Análisis Personal
**Aprendizajes:**
Esta ADA fue fundamental para entender cómo funcionan las estructuras de datos dinámicas. La mayor lección fue comprender que perder la referencia al primer nodo (`Head`) significa perder toda la lista (basura en memoria). La flexibilidad de poder agregar elementos infinitamente (mientras haya RAM) es una ventaja clara sobre los arrays estáticos.

**Retos Enfrentados:**
La lógica de eliminación fue compleja. Al principio, olvidábamos crear un puntero auxiliar (`anterior`) para guardar la referencia del nodo previo al que queríamos eliminar. Esto causaba que la lista se "rompiera" en dos. Dibujar los punteros en papel antes de codificar fue la única forma de visualizar correctamente las conexiones.
