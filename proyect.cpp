#include <stdio.h>
#include <stdlib.h> 

// defini una estructura para almacenar la informacion del curso
struct Curso {
    char nombre[50];
    float nota;
};

int main() {
    // se declaro una variable para la estructura del curso
    struct Curso miCurso;

    printf("Administrador de Notas de Cursos\n");
    printf("Registro de un nuevo curso y nota\n");
    printf("----------------------------------------\n\n");

    // 1. registrar el nombre del curso
    printf("Ingrese el nombre del curso (max 49 caracteres): ");
    // Usamos fgets para leer la línea de entrada, incluyendo espacios
    // y para prevenir un desbordamiento de buffer
    if (fgets(miCurso.nombre, sizeof(miCurso.nombre), stdin) == NULL) {
        perror("Error al leer el nombre del curso");
        return 1;
    }
    // eliminar el salto de línea que añade fgets si está presente
    int len = 0;
    while (miCurso.nombre[len] != '\0') {
        if (miCurso.nombre[len] == '\n') {
            miCurso.nombre[len] = '\0';
            break;
        }
        len++;
    }

    // 2. registrar la nota del curso
    printf("Ingrese la nota del curso (ej. 15.5): ");
    // se usa un bucle para asegurar que la entrada sea un número flotante
    while (scanf("%f", &miCurso.nota) != 1) {
        printf("Entrada inválida. Por favor, ingrese un número: ");
        while (getchar() != '\n');
    }

    // 3. mostrar los datos registrados para confirmación
    
    printf("Datos Registrados Correctamente:\n");
    printf("   Curso: **%s**\n", miCurso.nombre);
    printf("   Nota: **%.2f**\n", miCurso.nota);

    // pausar la consola en Windows o Linux para ver la salida
    #ifdef _WIN32
        system("pause");
    #elif defined(__linux__) || defined(__APPLE__)
        printf("Presione ENTER para continuar...\n");
        // limpiar buffer y esperar una entrada
        while (getchar() != '\n');
        getchar();
    #endif

    return 0;
}