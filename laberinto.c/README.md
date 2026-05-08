Maze Solver (DFS & Backtracking)
Este proyecto implementa un algoritmo de búsqueda en profundidad (DFS) con Backtracking para encontrar una salida en un laberinto representado por una matriz. El código está desarrollado en C++ y utiliza recursividad para explorar los caminos posibles.

🚀 Funcionalidades
Representación Matricial: El laberinto se define mediante una matriz de constantes donde 1 representa muros y 0 caminos libres.

Algoritmo DFS: Explora cada camino hasta el límite antes de retroceder.

Backtracking: Si el algoritmo llega a un callejón sin salida, "desmarca" la celda para permitir nuevas rutas.

Visualización: Muestra el camino solución marcado con * y los muros con #.

🛠️ Requisitos
Compilador C++ (GCC/G++, Clang o MSVC).

Entorno Linux (como Linux Mint) o Windows.

💻 Ejecución
Para compilar y ejecutar el programa desde la terminal:

Bash
g++ laberinto.cpp -o laberinto
./laberinto
📝 Lógica del Algoritmo
El algoritmo sigue estos pasos matemáticos y lógicos:

Validación: Comprueba límites de la matriz y colisiones con muros.

Marcado: Cambia el valor de la celda de 0 a 2 para evitar bucles infinitos.

Recursión: Intenta moverse en 4 direcciones (Arriba, Abajo, Izquierda, Derecha).

Limpieza: Si no hay salida, devuelve la celda a 0 para liberar el camino.

Desarrollado por carlos-balbuena
Estudiante en Penguin Academy | Paraguay