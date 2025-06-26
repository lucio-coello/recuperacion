#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    struct biblioteca biblio;
    biblio.numLibros = 0;

    int opcion;

    do {
        printf("\n--- Menu Biblioteca (Espacio disponible: %d/%d) ---\n", MAXLIBROS - biblio.numLibros, MAXLIBROS);
        printf("1. Registrar libro\n");
        printf("2. Mostrar libros\n");
        printf("3. Buscar libro por ID\n");
        printf("4. Actualizar estado de un libro\n");
        printf("5. Eliminar libro\n");
        printf("6. Buscar libros por autor\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); 
        switch (opcion) {
            case 1:
                agregarLibro(&biblio);
                break;
            case 2:
                mostrarLibros(&biblio);
                break;
            case 3:
                buscarLibro(&biblio);
                break;
            case 4:
                actualizarEstado(&biblio);
                break;
            case 5:
                eliminarLibro(&biblio);
                break;
            case 6: {
                char autor[50];
                printf("Ingrese el nombre del autor a buscar: ");
                fgets(autor, sizeof(autor), stdin);
                autor[strcspn(autor, "\n")] = 0; 
                buscarPorAutor(&biblio, autor);
                break;
            }
            case 7:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }
    } while (opcion != 7);

    return 0;
}
