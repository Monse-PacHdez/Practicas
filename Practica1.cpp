//Practica 1. Uso de arreglos bidimensionales y funciones
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;
    int matriz[10][10]; //Arreglo bidimensional
    int suma = 0, pares = 0, impares = 0, div = 0;

    srand(time(NULL)); // Inicializa la semilla para generar números aleatorios

    // Se asigna un número aleatorio a n entre 1 y 10
    n = rand() % 10 + 1;
    printf("El tamaño de la matriz es: %d x %d\n\n", n, n); // Imprime el tamaño de la matriz generada

    // Llenar la matriz con números aleatorios y realizar las operaciones
    printf("Matriz generada:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = rand() % 100 + 1;	// Números entre 1 y 100
            printf("%4d", matriz[i][j]);		// Mostrar la matriz

            suma += matriz[i][j];              // Se acumula la suma de los elementos
            if (matriz[i][j] % 2 == 0) pares++; // Si es divisible entre 2, es par
            else impares++;                     // Si no es par, entonces es impar
            if (matriz[i][j] % 7 == 0) div++;  // Si es divisible entre 7, se cuenta
        }
        printf("\n");
    }

    // Mostrar los resultados
    printf("\nSuma de todos los elementos: %d\n", suma);
    printf("Cantidad de números pares: %d\n", pares);
    printf("Cantidad de números impares: %d\n", impares);
    printf("Cantidad de números divisibles entre 7: %d\n\n", div);

    // Mostrar la matriz transpuesta
    printf("Matriz transpuesta:\n");
    for (int i = 0; i < n; i++) {            // Recorre filas de la transpuesta
        for (int j = 0; j < n; j++) {        // Recorre columnas de la transpuesta
            printf("%4d", matriz[j][i]);     // Intercambio de fila por columna
        }
        printf("\n");
    }

    return 0;
}
