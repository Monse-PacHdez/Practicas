#include <cstdio>    // Se utiliza para las funciones de entrada y salida como printf() y scanf().
#include <cstdlib>  // Se usa para manejar memoria dinámica con malloc() y free().

// Se guarda la informacion de un alumno.
struct Alumno {
    char nombre[50];
};

// Guardamos la informacion de una tarea con un tamaño de 100. 
struct Tarea {
    char descripcion[100];
};

// Registro de calificaciones (quién hizo qué y cuánto obtuvo).
struct Calificacion {
    int posicionAlumno;    
    int posicionTarea;     
    float calificacion;    //Calificacion que se asigna.
};

// Reserva de memoria dinámica usando malloc.
// - Se reservan 50 espacios para alumnos.
// - Se reservan 50 espacios para tareas.
// - Se reservan 100 espacios para calificaciones.
// malloc() devuelve un apuntador al bloque de memoria asignado.
Alumno* alumnos = (Alumno*)malloc(sizeof(Alumno) * 50);
Tarea* tareas = (Tarea*)malloc(sizeof(Tarea) * 50);
Calificacion* calificaciones = (Calificacion*)malloc(sizeof(Calificacion) * 100);

//Contadores.
int totalAlumnos = 0;
int totalTareas = 0;
int totalCalificaciones = 0;

// Agregar un alumno.
void agregarAlumno() {
    printf("\n=== AGREGAR ALUMNO ===\n");
    printf("Nombre del alumno: ");
    scanf(" %49[^\n]", alumnos[totalAlumnos].nombre); //49 porque lee un maximo de 49 caracteres.
    
    totalAlumnos++;
    printf("Alumno ingresado correctamente.\n\n");
}

// Mostrar lista de alumnos.
void mostrarAlumnos() {
    printf("\n=== LISTA DE ALUMNOS ===\n");

    if (totalAlumnos == 0) {
        printf("No hay alumnos registrados.\n\n");
        return;
    }

    // Muestra al alumno con un numero (id)
    for (int i = 0; i < totalAlumnos; i++) {
        printf("[%d] %s\n", i, alumnos[i].nombre);
    }
    printf("\n");
}

// Agrega una nueva tarea
void agregarTarea() {
    printf("\n=== AGREGAR TAREA ===\n");
    printf("Nombre de la tarea: ");
    scanf(" %99[^\n]", tareas[totalTareas].descripcion); // de igual manera funciona como el de 49
    
    totalTareas++;
    printf("Tarea registrada correctamente.\n\n");
}

// Mostrar las tareas registradas.
void mostrarTareas() {
    printf("\n=== LISTA DE TAREAS ===\n");

    if (totalTareas == 0) { // si no hay ninguna se imprime el siguiente mensaje
        printf("No hay tareas registradas.\n\n");
        return;
    }

    // Id tareas.
    for (int i = 0; i < totalTareas; i++) {
        printf("[%d] %s\n", i, tareas[i].descripcion);
    }
    printf("\n");
}

// Asignar calificacion a una tarea.
void asignarCalificacion() {
    printf("\n=== ASIGNAR CALIFICACION ===\n");

    // Primero necesitamos alumnos y tareas
    if (totalAlumnos == 0 || totalTareas == 0) {
        printf("Es necesario tener alumnos y tareas registradas antes de asignar calificaciones.\n\n");
        return;
    }

    // Menu para elegir un alumno.
    mostrarAlumnos();
    printf("Seleccione el numero del alumno: ");
    int alumno;
    scanf("%d", &alumno);

    // Menu para elegir una tarea.
    mostrarTareas();
    printf("Seleccione el numero de la tarea: ");
    int tarea;
    scanf("%d", &tarea);

    // Coloca la calificacion.
    printf("Ingrese la calificacion: ");
    float nota;
    scanf("%f", &nota);

    // Guardamos todos los datos regristrados .
    calificaciones[totalCalificaciones].posicionAlumno = alumno;
    calificaciones[totalCalificaciones].posicionTarea = tarea;
    calificaciones[totalCalificaciones].calificacion = nota;
    totalCalificaciones++;

    printf("Calificacion asignada correctamente.\n\n");
}

//Muestra las calificaiones de cada alumno .
void mostrarResultados() {
    printf("\n========== RESULTADOS FINALES ==========\n");

    if (totalCalificaciones == 0) {
        printf("No hay calificaciones registradas.\n\n");
        return;
    }

    // Mostrar cada calificación con nombre del alumno su tarea y su calificación final.
    for (int i = 0; i < totalCalificaciones; i++) {
        int a = calificaciones[i].posicionAlumno;  // Posición del alumno.
        int t = calificaciones[i].posicionTarea;   // Posición de la tarea.

        printf("Alumno: %s | Tarea: %s | Calificacion: %.2f\n",
               alumnos[a].nombre,
               tareas[t].descripcion,
               calificaciones[i].calificacion);
    }
    printf("\n");
}

//Menu principal.
void menu() {
    int opcion;

    do {
        // Opciones que puede realizar el usuario.
        printf("=== MENU PRINCIPAL ===\n");
        printf("1. Agregar alumno\n");
        printf("2. Agregar tarea\n");
        printf("3. Asignar calificacion\n");
        printf("4. Mostrar resultados\n");
        printf("5. Terminar\n");
        printf("\nOpcion: ");
        scanf("%d", &opcion);

        //switch para el menu.
        switch (opcion) {
            case 1:
                agregarAlumno();
                break;
            case 2:
                agregarTarea();
                break;
            case 3:
                asignarCalificacion();
                break;
            case 4:
                mostrarResultados();
                break;
            case 5:
                printf("Cerrando el programa...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 5);  // se repite hasta que se coloque una opcion
}

 // Inicio
int main() {
    menu();

    // Liberamos la memoria dinámica creada al inicio.
    free(alumnos);
    free(tareas);
    free(calificaciones);

    return 0;
}
