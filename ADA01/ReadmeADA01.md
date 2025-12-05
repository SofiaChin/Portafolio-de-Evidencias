<div align="center">

# 🥞 ADA 01: Analizador de Expresiones (Pilas)

<img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B" />
<img src="https://img.shields.io/badge/Topic-Stack%20%2F%20Pilas-orange?style=flat-square" />
<img src="https://img.shields.io/badge/Algorithm-Shunting%20Yard-blueviolet?style=flat-square" />

</div>

---

## 📄 Descripción
Software desarrollado para la conversión y evaluación de expresiones matemáticas. Transforma notación **Infija** (común) a **Postfija** (Polaca Inversa) y calcula el resultado utilizando una estructura de datos LIFO (Last In, First Out).

## 💻 Detalles Técnicos
* **Entrada:** Lectura de archivo `infijas.txt`.
* **Proceso:** Uso de `std::stack` para ordenamiento de operadores.
* **Salida:** Evaluación numérica de la expresión.

## 📂 Estructura
| Archivo | Descripción |
| :--- | :--- |
| `InfijoAPostfijoApp.cpp` | Código fuente principal. |
| `infijas.txt` | Dataset de pruebas matemáticas. |

## 🧠 Reflexión Personal
> **Aprendizaje:** (Aquí explica cómo entendiste que la pila "apila" los operadores hasta que se necesita usarlos).
>
> **Reto:** (Aquí menciona si te costó manejar los paréntesis anidados).
