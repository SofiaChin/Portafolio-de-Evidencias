Universidad Autónoma de Yucatán
Facultad de Matemáticas
Licenciatura en Ciencias de la Computación

Ian Paredes Vázquez
Anna Sofía Chin Chan

═══════════════════════════════════════════════════════
ADA07_AP1: Registro de Estudiantes (Hashing)
═══════════════════════════════════════════════════════

Este proyecto implementa un sistema de registro para universidades
utilizando una Tabla Hash con Direccionamiento Abierto para organizar
a los estudiantes por su número de matrícula.

El programa gestiona las colisiones mediante Sondeo Lineal,
asegurando que todos los datos sean recuperables.

El programa permite:
- Insertar estudiantes (Matrícula, Nombre, Carrera).
- Buscar estudiantes eficientemente por matrícula.
- Eliminar estudiantes (marcado lógico para no romper búsquedas).
- Visualizar el estado interno de la tabla (índices y colisiones).
- Validar que las matrículas sean de máximo 6 dígitos.

═══════════════════════════════════════════════════════
 ◈ COMPILACIÓN
═══════════════════════════════════════════════════════

Para compilar el programa, necesitarás un compilador de C++ como G++.

En Windows (usando MinGW/MSYS2):

    g++ -Wall -Wextra ADA07_AP1.cpp -o ADA07_AP1

-----------------------------------------------

En Linux/MacOS:

    g++ -Wall -Wextra ADA07_AP1.cpp -o ADA07_AP1

Esto generará un ejecutable llamado "ADA07_AP1".

════════════════════════════════════════════════════════
 ➣ EJECUCIÓN
════════════════════════════════════════════════════════

Una vez compilado, puedes ejecutar el programa desde la terminal.

En Windows:

    ADA07_AP1.exe

-----------------------------------------------
En Linux/Mac:

    ./ADA07_AP1

════════════════════════════════════════════════════════
 » INSTRUCCIONES DE USO
════════════════════════════════════════════════════════

Al iniciar, se solicitará el tamaño de la tabla hash (se sugiere
un número primo para mejorar la distribución).

- Todas las operaciones se realizan a través de un menú numérico.
- La matrícula debe ser un número entero entre 0 y 999999.
- El programa no guarda datos en archivos; la información reside
  en memoria RAM y se perderá al cerrar la aplicación.