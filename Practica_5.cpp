#include <stdio.h>
#include <string.h>
#include <stdlib.h>

	/* Estructura que guarda los datos de cada persona */
struct Persona {
    char nombre[50];
    char cargo[50];
};

	/* Editor con texto dinámico que puede crecer con realloc */
struct Editor {
    char *mensaje;
    int tam;
};

  /* CREAR MENSAJE.- Permite capturar texto libre, expandiendo memoria con realloc */
void crearMensaje(Editor *ed) {
    char buffer[256];
    int nuevaLong;
    ed->tam = 1;
    ed->mensaje = (char*)malloc(1);
    ed->mensaje[0] = '\0';

    printf("Ingrese el mensaje (doble ENTER para finalizar):\n");

    while (1) {
        fgets(buffer, 256, stdin);
        if (strcmp(buffer, "\n") == 0) break;

        buffer[strcspn(buffer, "\n")] = '\0';
        nuevaLong = strlen(ed->mensaje) + strlen(buffer) + 2;

        ed->mensaje = (char*)realloc(ed->mensaje, nuevaLong);
        if (!ed->mensaje) {
            printf("Error al reasignar memoria.\n");
            exit(1);
        }

        if (strlen(ed->mensaje) == 0)
            strcpy(ed->mensaje, buffer);
        else {
            strcat(ed->mensaje, " ");
            strcat(ed->mensaje, buffer);
        }

        ed->tam = nuevaLong;
    }
}

	/* Mostramos el mensaje. */
void mostrarMensaje(Editor ed) {
    printf("\n--- MENSAJE ACTUAL ---\n%s\n", ed.mensaje);
}


	/* BUSCAR Y REEMPLAZAR.- Construye un texto nuevo reemplazando coincidencias.
		Se usa un texto RESULTADO que va creciendo con realloc. */
void buscarReemplazar(Editor *ed, const char *buscar, const char *reemplazar) {
    char *resultado = (char*)malloc(1);
    resultado[0] = '\0';

    int lenBuscar = strlen(buscar);
    int lenReemplazar = strlen(reemplazar);
    int tamNuevo = 1;

    char *inicio = ed->mensaje;
    char *pos;

    while ((pos = strstr(inicio, buscar)) != NULL) {
        int largoAntes = pos - inicio;
        tamNuevo += largoAntes + lenReemplazar + 1;

        resultado = (char*)realloc(resultado, tamNuevo);

        strncat(resultado, inicio, largoAntes);
        strcat(resultado, reemplazar);

        inicio = pos + lenBuscar;
    }

    tamNuevo += strlen(inicio) + 1;
    resultado = (char*)realloc(resultado, tamNuevo);
    strcat(resultado, inicio);

    free(ed->mensaje);
    ed->mensaje = resultado;
    ed->tam = tamNuevo;

    printf("\n[Reemplazo exitoso]\n");
}

	/* Captura de personas. */
void capturarPersonas(Persona *lista, int total) {
    for (int i = 0; i < total; i++) {
        printf("\nPersona #%d\n", i + 1);

        printf("Nombre: ");
        fgets(lista[i].nombre, 50, stdin);
        lista[i].nombre[strcspn(lista[i].nombre, "\n")] = '\0';

        printf("Cargo: ");
        fgets(lista[i].cargo, 50, stdin);
        lista[i].cargo[strcspn(lista[i].cargo, "\n")] = '\0';
    }
}

	/* GenerarDocumento.- Mezcla mensaje + datos de la persona para 
		mostrar un documento */
void generarDocumento(Editor ed, Persona p) {
    printf("\n============================================\n");
    printf("DESTINATARIO:\n");
    printf("Nombre : %s\n", p.nombre);
    printf("Cargo  : %s\n", p.cargo);
    printf("--------------------------------------------\n");
    printf("MENSAJE:\n%s\n", ed.mensaje);
    printf("============================================\n");
}

	/* Programa principal. */
int main() {
    Editor editor;
    editor.mensaje = NULL;
    editor.tam = 0;

    int totalPersonas = 0;
    Persona *lista = NULL;

    int opcion;

    do {
        printf("\n========== MENU ==========\n");
        printf("1. Crear mensaje\n");
        printf("2. Mostrar mensaje\n");
        printf("3. Buscar y reemplazar\n");
        printf("4. Capturar personas\n");
        printf("5. Mostrar documentos finales\n");
        printf("0. Salir\n");
        printf("Seleccione: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {

        case 1:
            crearMensaje(&editor);
            break;

        case 2:
            mostrarMensaje(editor);
            break;

        case 3: {
            char buscar[50], reemplazar[50];

            printf("Texto a buscar: ");
            fgets(buscar, 50, stdin);
            buscar[strcspn(buscar, "\n")] = '\0';

            printf("Texto de reemplazo: ");
            fgets(reemplazar, 50, stdin);
            reemplazar[strcspn(reemplazar, "\n")] = '\0';

            buscarReemplazar(&editor, buscar, reemplazar);
            break;
        }

        case 4:
            printf("¿Cuantas personas registrar?: ");
            scanf("%d", &totalPersonas);
            getchar();

			/* Reserva memoria para la lista completa de personas */
            lista = (Persona*)malloc(totalPersonas * sizeof(Persona));
            capturarPersonas(lista, totalPersonas);
            break;

        case 5:
            if (lista == NULL || editor.mensaje == NULL) {
                printf("Debe capturar mensaje y personas primero.\n");
            } else {
                for (int i = 0; i < totalPersonas; i++)
                    generarDocumento(editor, lista[i]);
            }
            break;
        }

    } while (opcion != 0);

    free(editor.mensaje);
    if (lista) free(lista);

    return 0;
}
