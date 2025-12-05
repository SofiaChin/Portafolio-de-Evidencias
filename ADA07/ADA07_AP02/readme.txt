Universidad Autónoma de Yucatán
Facultad de Matemáticas
Licenciatura en Ciencias de la Computación

Ian Paredes Vázquez
Anna Sofía Chin Chan

═══════════════════════════════════════════════════════
ADA07_AP2: Tabla de Símbolos (Compilador)
═══════════════════════════════════════════════════════

Este proyecto simula una Tabla de Símbolos utilizada en las fases
de análisis de un compilador o intérprete. Utiliza una Tabla Hash
para almacenar identificadores y sus atributos asociados.

El manejo de colisiones se realiza mediante Encadenamiento (Listas
Ligadas), permitiendo múltiples elementos en el mismo índice hash.

El programa permite:
- Agregar identificadores con atributos (Tipo, Ámbito, Valor).
- Buscar identificadores y verificar sus atributos.
- Eliminar identificadores específicos de la tabla.
- Gestionar colisiones añadiendo elementos a la lista correspondiente.

═══════════════════════════════════════════════════════
 ◈ COMPILACIÓN
═══════════════════════════════════════════════════════

Para compilar el programa, necesitarás un compilador de C++ como G++.

En Windows (usando MinGW/MSYS2):

    g++ -Wall -Wextra ADA07_AP2.cpp -o ADA07_AP2

-----------------------------------------------

En Linux/MacOS:

    g++ -Wall -Wextra ADA07_AP2.cpp -o ADA07_AP2

Esto generará un ejecutable llamado "ADA07_AP2".

════════════════════════════════════════════════════════
 ➣ EJECUCIÓN
════════════════════════════════════════════════════════

Una vez compilado, puedes ejecutar el programa desde la terminal.

En Windows:

    ADA07_AP2.exe

-----------------------------------------------
En Linux/Mac:

    ./ADA07_AP2

════════════════════════════════════════════════════════
 » INSTRUCCIONES DE USO
════════════════════════════════════════════════════════

Al iniciar, define el tamaño de la tabla (ej. 53, 97).

- El ID (identificador) actúa como la clave única.
- El sistema utiliza una función hash polinomial optimizada para
  cadenas de texto (strings).
- Si dos identificadores caen en el mismo índice, se almacenan
  en una lista enlazada en esa posición.
- Los datos son volátiles y se pierden al salir del programa.