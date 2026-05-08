#include <iostream>
#include <vector>
#include <algorithm> // Para usar random_shuffle
#include <ctime>     // Para el tiempo y el azar
#include <cstdlib>   // Para rand() y srand()

using namespace std;

// --- CONFIGURACIÓN GLOBAL DEL MAPA ---
int cantidad_total_de_filas;
int cantidad_total_de_columnas;
vector<vector<char>> matriz_del_laberinto;
vector<vector<bool>> registro_de_celdas_visitadas;

// Movimientos posibles: Arriba, Abajo, Izquierda, Derecha
int desplazamiento_en_fila[] = {-1, 1, 0, 0};
int desplazamiento_en_columna[] = {0, 0, -1, 1};

// Función para verificar si una posición está dentro de los límites
bool la_posicion_es_valida(int fila_actual, int columna_actual) {
    return (fila_actual >= 0 && fila_actual < cantidad_total_de_filas && 
            columna_actual >= 0 && columna_actual < cantidad_total_de_columnas);
}

// --- SECCIÓN 1: GENERACIÓN DEL LABERINTO ---
void generar_estructura_del_laberinto(int fila_actual, int columna_actual) {
    registro_de_celdas_visitadas[fila_actual][columna_actual] = true;
    matriz_del_laberinto[fila_actual][columna_actual] = ' '; 

    vector<int> opciones_de_direccion = {0, 1, 2, 3};
    random_shuffle(opciones_de_direccion.begin(), opciones_de_direccion.end());

    for (int i = 0; i < 4; i++) {
        int direccion_elegida = opciones_de_direccion[i];
        int fila_del_vecino_lejano = fila_actual + desplazamiento_en_fila[direccion_elegida] * 2;
        int columna_del_vecino_lejano = columna_actual + desplazamiento_en_columna[direccion_elegida] * 2;

        if (la_posicion_es_valida(fila_del_vecino_lejano, columna_del_vecino_lejano) && 
            !registro_de_celdas_visitadas[fila_del_vecino_lejano][columna_del_vecino_lejano]) {
            
            int fila_del_muro = fila_actual + desplazamiento_en_fila[direccion_elegida];
            int columna_del_muro = columna_actual + desplazamiento_en_columna[direccion_elegida];
            
            matriz_del_laberinto[fila_del_muro][columna_del_muro] = ' ';
            generar_estructura_del_laberinto(fila_del_vecino_lejano, columna_del_vecino_lejano);
        }
    }
}

// --- SECCIÓN 2: RESOLUCIÓN CON BACKTRACKING ---
bool encontrar_camino_a_la_salida(int fila_actual, int columna_actual) {
    if (fila_actual == cantidad_total_de_filas - 1 && columna_actual == cantidad_total_de_columnas - 1) {
        matriz_del_laberinto[fila_actual][columna_actual] = 'S';
        return true;
    }

    registro_de_celdas_visitadas[fila_actual][columna_actual] = true;
    matriz_del_laberinto[fila_actual][columna_actual] = '*'; 

    for (int i = 0; i < 4; i++) {
        int proxima_fila = fila_actual + desplazamiento_en_fila[i];
        int proxima_columna = columna_actual + desplazamiento_en_columna[i];

        if (la_posicion_es_valida(proxima_fila, proxima_columna) && 
            !registro_de_celdas_visitadas[proxima_fila][proxima_columna] && 
            (matriz_del_laberinto[proxima_fila][proxima_columna] == ' ' || 
             matriz_del_laberinto[proxima_fila][proxima_columna] == 'S')) {
            
            if (encontrar_camino_a_la_salida(proxima_fila, proxima_columna)) return true;
        }
    }

    matriz_del_laberinto[fila_actual][columna_actual] = ' '; 
    return false;
}

// --- SECCIÓN 3: DIBUJO ---
void mostrar_laberinto_en_consola() {
    for (int i = 0; i < cantidad_total_de_filas; i++) {
        for (int j = 0; j < cantidad_total_de_columnas; j++) {
            cout << matriz_del_laberinto[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));

    // --- CAMBIO: VALORES POR DEFECTO ---
    cout << "=== CONFIGURACION DEL LABERINTO ===" << endl;
    cout << "Ingrese filas (0 para usar valor por defecto 11): ";
    cin >> cantidad_total_de_filas;
    if (cantidad_total_de_filas <= 0) {
        cantidad_total_de_filas = 11;
        cout << "-> Usando valor por defecto de filas: " << cantidad_total_de_filas << endl;
    }

    cout << "Ingrese columnas (0 para usar valor por defecto 11): ";
    cin >> cantidad_total_de_columnas;
    if (cantidad_total_de_columnas <= 0) {
        cantidad_total_de_columnas = 11;
        cout << "-> Usando valor por defecto de columnas: " << cantidad_total_de_columnas << endl;
    }

    matriz_del_laberinto.assign(cantidad_total_de_filas, vector<char>(cantidad_total_de_columnas, '#'));
    registro_de_celdas_visitadas.assign(cantidad_total_de_filas, vector<bool>(cantidad_total_de_columnas, false));

    generar_estructura_del_laberinto(0, 0);
    
    matriz_del_laberinto[0][0] = 'E';
    matriz_del_laberinto[cantidad_total_de_filas - 1][cantidad_total_de_columnas - 1] = ' ';

    cout << "\nLABERINTO GENERADO:\n";
    mostrar_laberinto_en_consola();

    registro_de_celdas_visitadas.assign(cantidad_total_de_filas, vector<bool>(cantidad_total_de_columnas, false));

    // --- CAMBIO: CRONÓMETRO DE RESOLUCIÓN ---
    cout << "\nRESOLVIENDO LABERINTO..." << endl;
    clock_t tiempo_inicio = clock(); // Inicia el reloj

    if (encontrar_camino_a_la_salida(0, 0)) {
        clock_t tiempo_final = clock(); // Detiene el reloj
        
        // Calculamos los segundos transcurridos
        double segundos_totales = double(tiempo_final - tiempo_inicio) / CLOCKS_PER_SEC;

        matriz_del_laberinto[0][0] = 'E';
        mostrar_laberinto_en_consola();
        
        cout << "\n¡Resuelto en " << segundos_totales << " segundos!" << endl;
    } else {
        cout << "\nNo se encontro una solucion." << endl;
    }

    return 0;
}