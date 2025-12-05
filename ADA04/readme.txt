Universidad Autónoma de Yucatán
Facultad de Matemáticas
Ingeniería en Computación
Estructura de Datos

Anna Sofia Chin Chan
Ian Paredes Vázquez

═══════════════════════════════════════════════════════
ADA04: Gestión de Alumnos con Árboles Binarios de Búsqueda
═══════════════════════════════════════════════════════

Este proyecto implementa un sistema de gestión de estudiantes
utilizando un Árbol Binario de Búsqueda (ABB) para organizar
los datos por número de matrícula.

El programa permite:
- Insertar nuevos estudiantes.
- Generar reportes de estudiantes ordenados por matrícula o promedio.
- Filtrar estudiantes según su promedio.
- Eliminar estudiantes por matrícula.
- Actualizar calificaciones.
- Visualizar la estructura del árbol en la consola.

═══════════════════════════════════════════════════════
 ◈ COMPILACIÓN
═══════════════════════════════════════════════════════

Para compilar el programa, necesitarás un compilador de C como GCC.

En Windows (usando MinGW/MSYS2):

    gcc -Wall -Wextra tu_archivo.c -o gestion_alumnos -lm

-----------------------------------------------

En Linux/MacOS:

    gcc -Wall -Wextra tu_archivo.c -o gestion_alumnos -lm

Esto generará un ejecutable llamado "gestion_alumnos". La bandera '-lm'
es importante para enlazar la biblioteca de matemáticas, necesaria
para la función de visualización del árbol.

════════════════════════════════════════════════════════
 ➣ EJECUCIÓN
════════════════════════════════════════════════════════

Una vez compilado, puedes ejecutar el programa desde la terminal.

En Windows:

    gestion_alumnos.exe

-----------------------------------------------
En Linux/Mac:

    ./gestion_alumnos

════════════════════════════════════════════════════════
 » INSTRUCCIONES DE USO
════════════════════════════════════════════════════════

Al iniciar el programa, se presentará un menú interactivo.
Todas las operaciones se realizan a través de las opciones
numéricas del menú.

El programa no carga ni guarda datos de archivos; toda la
información se maneja en memoria y se pierde al cerrar la
aplicación.