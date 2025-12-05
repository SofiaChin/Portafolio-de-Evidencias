<div align="center">

# 🎬 ADA 03: Bases de Datos y Parsing de Archivos

<img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B" />
<img src="https://img.shields.io/badge/Format-CSV-success?style=flat-square&logo=microsoft-excel" />
<img src="https://img.shields.io/badge/Technique-String%20Parsing-yellow?style=flat-square" />

</div>

---

## 📄 Descripción Técnica
El objetivo fue desarrollar un sistema capaz de leer y estructurar información proveniente de una fuente externa plana (`Movies.csv`). Implementamos un "parser" manual que lee el archivo línea por línea, identifica el separador (coma), y extrae los tokens para llenar objetos de tipo `Movie` en memoria.

Se utilizaron vectores de la STL (`std::vector`) para almacenar dinámicamente los registros leídos, permitiendo que el programa se adapte a cualquier cantidad de películas en el archivo sin recomplilar.

## 💻 Detalles de Implementación
* **Librería `fstream`:** Para abrir flujos de lectura (`ifstream`).
* **Librería `sstream`:** Para convertir cadenas de texto numéricas ("1998") a enteros reales (`int`) utilizables en cálculos u ordenamientos.
* **Struct Movie:** Diseño de una estructura personalizada para encapsular los datos.

## 📂 Estructura de Archivos
| Archivo | Función |
| :--- | :--- |
| `ADA03.cpp` | Algoritmo principal de lectura y consulta. |
| `Movies.csv` | Dataset con títulos, años y géneros de películas. |

## 🧠 Reflexión y Análisis Personal
**Aprendizajes:**
Aprendí que el manejo de datos en el mundo real rara vez es limpio. La necesidad de "sanitizar" o limpiar los datos antes de usarlos fue clave. También profundicé en el uso de `getline` con delimitadores personalizados, una herramienta muy potente para leer formatos estructurados.

**Retos Enfrentados:**
El problema principal fue manejar las excepciones en el formato CSV. Por ejemplo, algunas películas tenían comas dentro de sus títulos (ej. "Batman, The Dark Knight"), lo que nuestro código interpretaba erróneamente como un cambio de columna. Tuvimos que refinar la lógica de lectura para ignorar comas que estuvieran encerradas entre comillas dobles.
