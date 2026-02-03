#include <stdio.h>
#include <string.h>

#define MAX_CURSOS 10
#define MAX_NOTAS 5

// Estructura para organizar los datos
struct Curso {
    char nombre[50];
    float notas[MAX_NOTAS];
    int cantidadNotas;
};

int main() {
    struct Curso academia[MAX_CURSOS];
    int totalCursos = 0;
    int opcion;

    do {
        printf("\n--- ADMINISTRADOR DE NOTAS ---");
        printf("\n1. Registrar nuevo curso y notas");
        printf("\n2. Mostrar cursos registrados");
        printf("\n3. Salir");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer del salto de linea

        switch(opcion) {
            case 1:
                if (totalCursos < MAX_CURSOS) {
                    printf("\nNombre del curso: ");
                    fgets(academia[totalCursos].nombre, 50, stdin);
                    academia[totalCursos].nombre[strcspn(academia[totalCursos].nombre, "\n")] = 0;

                    printf("Cuantas notas desea registrar para este curso? (Max %d): ", MAX_NOTAS);
                    scanf("%d", &academia[totalCursos].cantidadNotas);

                    for (int i = 0; i < academia[totalCursos].cantidadNotas; i++) {
                        printf("  Ingrese nota %d: ", i + 1);
                        scanf("%f", &academia[totalCursos].notas[i]);
                    }
                    
                    totalCursos++;
                    printf("\nCurso registrado con exito.\n");
                } else {
                    printf("\n Error: Limite de cursos alcanzado.\n");
                }
                break;

            case 2:
                printf("\n--- LISTADO DE CURSOS ---");
                for (int i = 0; i < totalCursos; i++) {
                    printf("\nCurso: **%s**", academia[i].nombre);
                    printf("\nNotas: ");
                    for (int j = 0; j < academia[i].cantidadNotas; j++) {
                        printf("[%.2f] ", academia[i].notas[j]);
                    }
                    printf("\n-----------------------");
                }
                if (totalCursos == 0) printf("\nNo hay cursos registrados.\n");
                break;

            case 3:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 3);

    return 0;
}