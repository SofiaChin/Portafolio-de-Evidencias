Universidad Autónoma de Yucatán
Facultad de Matemáticas
Ingeniería en Computación
Estructura de Datos

Chin Chan Anna Sofia
Paredes Vázquez Ian

═══════════════════════════════════════════════════════
ADA04: Gestión de Películas con Listas Doblemente Ligadas
═══════════════════════════════════════════════════════

Este proyecto implementa un sistema de gestión de películas.
El programa permite:
- Cargar datos de películas desde archivos CSV.
- Buscar películas por título.
- Buscar películas por ID exacto.
- Insertar nuevas películas al inicio, final o posición específica.
- Eliminar películas con confirmación del usuario.
- Actualizar datos de películas existentes.
- Guardar la lista completa a archivo CSV.
- Mostrar todas las películas en formato resumido.

Estructura del proyecto
La carpeta debe contener:
- El archivo del programa (ADA03.cpp)
- Archivo CSV de ejemplo (Movies.csv)

═══════════════════════════════════════════════════════
 ◈ COMPILACIÓN
═══════════════════════════════════════════════════════

Para compilar el programa en Windows:

    g++ -Wall -Wextra -g3 ADA03.cpp -o gestion_peliculas -std=c++11

-----------------------------------------------

En Linux/MacOS:

    g++ -Wall -Wextra ADA03.cpp -o gestion_peliculas -std=c++11

Esto generará un ejecutable llamado gestion_peliculas.

════════════════════════════════════════════════════════
 ➣ EJECUCIÓN
════════════════════════════════════════════════════════

En Windows (MSYS2/MinGW instalado):

    gestion_peliculas.exe

-----------------------------------------------
En Linux/Mac:

    ./gestion_peliculas

════════════════════════════════════════════════════════
 » INSTRUCCIONES DE USO
════════════════════════════════════════════════════════

Al ejecutar el programa, lo primero que debe hacer es:
1. Seleccionar la opción 1 del menú: "Cargar desde CSV"
2. Ingresar el nombre del archivo (por defecto 'Movies.csv')
3. Presionar Enter para cargar los datos

Sin este paso, la lista estará vacía y no se podrán realizar
búsquedas, eliminaciones, actualizaciones ni mostrar películas.

════════════════════════════════════════════════════════
 » FORMATO DEL ARCHIVO CSV
════════════════════════════════════════════════════════

El archivo CSV debe tener la siguiente estructura (ejemplo):
id,title,genre,year,duration
1,The Shawshank Redemption,Drama,1994,142
2,The Godfather,Crime,1972,175

Campos soportados:
- id: Identificador único (entero)
- title: Título de la película (texto)
- genre: Género cinematográfico (texto)
- year: Año de estreno (entero)
- duration: Duración en minutos (entero)

Nota: El apartado "ID" en el programa corresponde directamente
a la primera columna del archivo CSV que debe llamarse "id".

════════════════════════════════════════════════════════