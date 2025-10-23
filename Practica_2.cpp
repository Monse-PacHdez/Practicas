//Editor de textos basico//
//Practica #2//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void llenarTexto(char *texto, int tam) {
    printf("Ingrese el texto: ", tam - 1);
    fgets(texto, tam, stdin);

    if (texto[strlen(texto) - 1] != '\n') {
        printf("Se alcanzó el límite del tamaño permitido.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    } else {
        texto[strcspn(texto, "\n")] = '\0';
    }
}

void mostrarTexto(char *texto) {
    printf("\nTexto actual:\n%s\n", texto);
}

void buscarYReemplazar(char *texto, char *buscar, char *reemplazar) {
    char *resultado = (char *)malloc(500 * sizeof(char));
    if (resultado == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        return;
    }

    resultado[0] = '\0';  // Inicializa el arreglo resultado vacío

    char *pos;
    char *inicio = texto;
    int lenBuscar = strlen(buscar);

    while ((pos = strstr(inicio, buscar)) != NULL) {
        int segmento = pos - inicio;

        strncat(resultado, inicio, segmento);  // Copia la parte antes de la coincidencia
        strcat(resultado, reemplazar);          // Agrega la palabra de reemplazo
        inicio = pos + lenBuscar;               // Avanza el puntero
    }

    strcat(resultado, inicio);   // Copia la parte restante
    strcpy(texto, resultado);    // Copia el resultado final al texto original

    free(resultado); // Libera memoria usada
}

int main() {
    char *texto = (char *)malloc(500 * sizeof(char));
    char *buscar = (char *)malloc(50 * sizeof(char));
    char *reemplazar = (char *)malloc(50 * sizeof(char));

    if (!texto || !buscar || !reemplazar) {
        printf("Error al asignar memoria.\n");
        free(texto);
        free(buscar);
        free(reemplazar);
        return 1;
    }

    llenarTexto(texto, 500);
    mostrarTexto(texto);

    printf("\nIngrese el texto a buscar: ");
    fgets(buscar, 50, stdin);
    buscar[strcspn(buscar, "\n")] = '\0';

    printf("Ingrese el texto de reemplazo: ");
    fgets(reemplazar, 50, stdin);
    reemplazar[strcspn(reemplazar, "\n")] = '\0';

    buscarYReemplazar(texto, buscar, reemplazar);

    printf("\nTexto final:\n%s\n", texto);

    free(texto);
    free(buscar);
    free(reemplazar);

    return 0;
}

