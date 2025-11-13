#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* --------------------------------------------------------------
   FUNCIÓN: llenarTexto
   -----------------------------------------------------------
   Permite al usuario escribir texto libremente, línea por línea.
   Cada nueva línea se agregara dinámicamente al texto principal 
   usando memoria dinámica (realloc).
   Termina cuando el usuario presiona Enter sin escribir nada.
   --------------------------------------------------------------- */
void llenarTexto(char **texto, int *tam) {
    char buffer[256];           // Guarda temporalmente una línea ingresada
    int longitudTotal = *tam;   // Almacena el tamaño actual del texto en memoria

    printf("Ingrese el texto: _(Dar doble enter cuando finalice)_ \n");

    // Bucle infinito hasta que el usuario ingrese una línea vacía (doble enter)
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);  // Leer una línea del usuario

        // Si el usuario solo presiona ENTER, terminamos la entrada
        if (strcmp(buffer, "\n") == 0) break;

        // Eliminar el salto de línea final '\n'
        buffer[strcspn(buffer, "\n")] = '\0';

        int len = strlen(buffer); // Longitud de la línea actual

        // Calculamos el nuevo tamaño total necesario (+1 espacio y +1 '\0')
        longitudTotal = strlen(*texto) + len + 2;

        // Reasignar memoria dinámica para el nuevo texto
        *texto = (char *) realloc(*texto, longitudTotal * sizeof(char));
        if (*texto == NULL) { // Validar que realloc haya funcionado
            printf("Error al reasignar memoria.\n");
            exit(1);
        }

        // Si el texto está vacío, copiar la primera línea directamente
        if (strlen(*texto) == 0) {
            strcpy(*texto, buffer);
        } else {
            // Si ya había texto, añadir un espacio y luego la nueva línea
            strcat(*texto, " ");
            strcat(*texto, buffer);
        }

        // Actualiza el tamaño total en memoria
        *tam = longitudTotal;

        // Mostrar información de depuración
        printf("[Memoria actual usada: %d bytes]\n", *tam);
    }
}

/* -----------------------------------------------------------
   FUNCIÓN: mostrarTexto

   Imprime en pantalla el contenido actual del texto.
   -----------------------------------------------------------*/
void mostrarTexto(char *texto) {
    printf("\nTexto actual: \n%s\n", texto);
}

/*--------------------------------------------------------------------- 
   FUNCIÓN: buscarYReemplazar

   Busca todas las apariciones de una palabra o frase en el texto
   y las reemplaza por otra palabra o frase.

   - Crea una nueva cadena llamada "resultado" donde se va construyendo el texto modificado.
   - Usamos realloc para ajustar el tamaño del texto nuevo segun sea necesario.
   - Libera la memoria original y la sustituye por el texto modificado.
   --------------------------------------------------------------------------*/
void buscarYReemplazar(char **texto, const char *buscar, const char *reemplazar) {
    char *resultado = (char *) malloc(1 * sizeof(char)); // Nuevo texto resultante
    resultado[0] = '\0';  // Inicializa vacío

    int lenBuscar = strlen(buscar);          // Longitud del texto a buscar
    int lenReemplazar = strlen(reemplazar);  // Longitud del texto de reemplazo
    int nuevoTam = 1;                        // Tamaño actual del texto nuevo

    char *inicio = *texto;  // Puntero para recorrer el texto original
    char *pos;              // Guarda la posición de la coincidencia encontrada

    // Bucle que busca todas las ocurrencias de la palabra a reemplazar
    while ((pos = strstr(inicio, buscar)) != NULL) {
        int lenAntes = pos - inicio; // Longitud del texto antes de la coincidencia
        nuevoTam += lenAntes + lenReemplazar + 1;

        // Amplia la memoria para incluir el nuevo fragmento
        resultado = (char *) realloc(resultado, nuevoTam * sizeof(char));
        if (resultado == NULL) {
            printf("Error al reasignar memoria.\n");
            exit(1);
        }

        // Agrega la parte anterior a la coincidencia al resultado
        strncat(resultado, inicio, lenAntes);

        // Agrega el texto de reemplazo
        strcat(resultado, reemplazar);

        // Avanza el puntero después de la coincidencia
        inicio = pos + lenBuscar;
    }

    // Copiar el resto del texto que queda después de la ultima coincidencia
    nuevoTam += strlen(inicio) + 1;
    resultado = (char *) realloc(resultado, nuevoTam * sizeof(char));
    strcat(resultado, inicio);

    // Liberar el texto anterior y sustituirlo por el nuevo
    free(*texto);
    *texto = resultado;

    // Mostrar tamaño de memoria final
    printf("\n[Memoria usada despues de reemplazar: %d bytes]\n", nuevoTam);
}


int main() {
    // Reserva memoria mínima inicial (1 byte)
    char *texto = (char *) malloc(1 * sizeof(char));
    texto[0] = '\0';  // Inicializar como cadena vacía
    int tam = 1;      // Tamaño inicial de la memoria

    // Paso 1: Llenar el texto dinámicamente
    llenarTexto(&texto, &tam);

    // Paso 2: Mostrar el texto ingresado
    mostrarTexto(texto);

    // Paso 3: Pedir texto a buscar y su reemplazo
    char buscar[50], reemplazar[50];
    printf("\nIngrese el texto a buscar: ");
    fgets(buscar, 50, stdin);
    buscar[strcspn(buscar, "\n")] = '\0';  // Eliminar salto de línea

    printf("Ingrese el texto de reemplazo: ");
    fgets(reemplazar, 50, stdin);
    reemplazar[strcspn(reemplazar, "\n")] = '\0';  // Eliminar salto de línea

    // Paso 4: Reemplazar todas las coincidencias
    buscarYReemplazar(&texto, buscar, reemplazar);

    // Paso 5: Mostrar el texto final modificado
    printf("\n--- Texto final ---\n%s\n-----------------------\n", texto);

    // Paso 6: Libera la memoria usada
    free(texto);
    printf("\n[Memoria liberada correctamente]\n");

    return 0;
}

