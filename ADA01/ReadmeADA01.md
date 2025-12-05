<div align="center">

# 🥞 ADA 01: Analizador de Expresiones Aritméticas

<img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B" />
<img src="https://img.shields.io/badge/Data%20Structure-Stack%20(Pila)-orange?style=flat-square" />
<img src="https://img.shields.io/badge/Algorithm-Shunting%20Yard-blueviolet?style=flat-square" />

</div>

---

## 📄 Descripción Técnica
En esta actividad desarrollamos un intérprete de expresiones matemáticas capaz de procesar cadenas de texto en notación infija (ej. `(A+B)*C`) y convertirlas a notación postfija (ej. `AB+C*`).

El núcleo del programa se basa en la estructura de datos **Pila (Stack)** de la librería estándar `<stack>`. El algoritmo recorre la expresión carácter por carácter; si encuentra un número, lo envía a la salida o pila de evaluación, y si encuentra un operador, decide si apilarlo o desapilar elementos basándose en su **jerarquía de precedencia** (definida en la función `prioridad`).

## 💻 Funcionalidades Implementadas
1.  **Validación de Jerarquía:** Distinción correcta entre potencias `^`, multiplicación/división `*/` y suma/resta `+-`.
2.  **Manejo de Paréntesis:** Algoritmo para vaciar la pila parcialmente cuando se encuentra un cierre de paréntesis `)`.
3.  **Evaluación Numérica:** Cálculo final del resultado procesando la cadena postfija resultante.

## 📂 Estructura de Archivos
| Archivo | Función |
| :--- | :--- |
| `InfijoAPostfijoApp.cpp` | Contiene el `main`, la función `prioridad()` y la lógica de conversión. |
| `infijas.txt` | Archivo de entrada con casos de prueba variados. |

## 🧠 Reflexión y Análisis Personal
**Aprendizajes:**
Lo más valioso de esta práctica fue comprender la utilidad real de una estructura LIFO (Last In, First Out). Antes de esto, la evaluación de expresiones parecía mágica, pero al implementarlo, entendí cómo los compiladores usan pilas para "recordar" operaciones pendientes. También aprendí a manipular flujos de archivos (`ifstream`) para procesar lotes de datos masivos.

**Retos Enfrentados:**
El mayor desafío fue la lógica de los operadores con la misma precedencia. Tuvimos un error lógico donde la pila no se vaciaba correctamente al encontrar operadores de igual jerarquía, lo que alteraba el resultado. Lo solucionamos ajustando la condición del bucle `while` dentro de la función de conversión para comparar `prioridad(op) <= prioridad(stack.top())`.
