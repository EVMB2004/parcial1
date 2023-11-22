#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

const int ROWS = 8;
const int COLS = 8;

// Función para imprimir la matriz
void printMatrix(int** matrix) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Función para encender todos los LEDs
void turnOnAll(int** matrix) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            matrix[i][j] = 1;
        }
    }
    printMatrix(matrix);
}

// Función para apagar todos los LEDs
void turnOffAll(int** matrix) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            matrix[i][j] = 0;
        }
    }
    printMatrix(matrix);
}

// Función para mostrar un patrón en la matriz
void displayPattern(int** matrix, int* pattern) {
    int index = 0;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            matrix[i][j] = pattern[index++];
        }
    }
    printMatrix(matrix);
}

// Función para generar y mostrar los patrones
void generatePatterns(int** matrix) {
    int patterns[4][ROWS * COLS] = {
        {0,0,0,1,1,0,0,0, 0,0,1,1,1,1,0,0, 0,1,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,0, 0,0,1,1,1,1,0,0, 0,0,0,1,1,0,0,0},
        {1,0,0,0,0,0,0,1, 0,1,0,0,0,0,1,0, 0,0,1,0,0,1,0,0, 0,0,0,1,1,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,1,1,0,0,0, 0,0,1,0,0,1,0,0, 1,0,0,0,0,0,0,1},
        {1,1,0,1,1,0,1,1, 1,1,0,1,1,0,1,1, 0,1,1,0,1,1,0,1, 0,0,1,1,0,1,1,0, 0,0,1,1,0,1,1,0, 1,1,0,1,1,0,1,1, 1,1,0,1,1,0,1,1, 1,1,0,1,1,0,1,1},
        {1,1,1,1,0,0,0,0, 0,1,1,1,1,0,0,0, 0,0,1,1,1,1,0,0, 0,0,0,1,1,1,1,0, 0,0,0,0,1,1,1,1, 0,0,0,0,0,1,1,1, 0,0,0,0,1,1,1,1, 1,1,1,1,0,0,0,0}
    };

    for (int i = 0; i < 4; ++i) {
        displayPattern(matrix, patterns[i]);
        cout << "Presiona Enter para continuar...";
        cin.ignore();  // Esperar a que el usuario presione Enter
    }
}

// Función principal para interactuar con el usuario
void publik() {
    int** matrix = new int*[ROWS];
    for (int i = 0; i < ROWS; ++i) {
        matrix[i] = new int[COLS];
    }

    // Inicializar matriz apagada
    turnOffAll(matrix);

    while (true) {
        cout << "Seleccione una opción:" << endl;
        cout << "a. Verificar funcionamiento de LEDs." << endl;
        cout << "b. Mostrar imagen de prueba." << endl;
        cout << "c. Mostrar patrones 1 al 4 de forma alternada." << endl;
        cout << "q. Salir." << endl;

        char choice;
        cin >> choice;

        if (choice == 'a') {
            int delay_sec, sequences;
            cout << "Ingrese el tiempo entre encendido y apagado (en segundos): ";
            cin >> delay_sec;
            cout << "Ingrese el número de secuencias: ";
            cin >> sequences;

            for (int i = 0; i < sequences; ++i) {
                turnOnAll(matrix);
                cout << "Encendido..." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(delay_sec));
                turnOffAll(matrix);
                cout << "Apagado..." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(delay_sec));
            }
        } else if (choice == 'b') {
            cout << "Ingrese el patrón (64 dígitos 0/1): ";
            int pattern[ROWS * COLS];
            for (int i = 0; i < ROWS * COLS; ++i) {
                cin >> pattern[i];
            }
            displayPattern(matrix, pattern);

            int delay_sec;
            cout << "Ingrese el tiempo de visualización (en segundos): ";
            cin >> delay_sec;
            std::this_thread::sleep_for(std::chrono::seconds(delay_sec));
            turnOffAll(matrix);
        } else if (choice == 'c') {
            int delay_sec;
            cout << "Ingrese el tiempo de retardo entre visualizaciones (en segundos): ";
            cin >> delay_sec;
            generatePatterns(matrix);
            std::this_thread::sleep_for(std::chrono::seconds(delay_sec));
            turnOffAll(matrix);
        } else if (choice == 'q') {
            break;
        } else {
            cout << "Opción no válida. Intente de nuevo." << endl;
        }
    }

    // Liberar memoria
    for (int i = 0; i < ROWS; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    publik(); // Iniciar la interacción con el usuario
    return 0;
}
