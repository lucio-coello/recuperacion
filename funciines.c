#include <stdio.h>
#include <string.h>
#include "funciones.h"

int id_unico(struct biblioteca *biblio, int id) {
    for (int i = 0; i < biblio->numLibros; i++) {
        if (biblio->libro[i].id == id) {
            return 0;
        }
    }
    return 1;
}

void agregarLibro(struct biblioteca *biblio) {
    int disponibles = MAXLIBROS - biblio->numLibros;

    if (disponibles == 0) {
        printf("No se pueden agregar mas libros. Biblioteca llena.\n");
        return;
    }

    int cantidad;
    printf("Cuantos libros desea agregar? (Maximo disponible: %d): ", disponibles);
    scanf("%d", &cantidad);

    if (cantidad <= 0 || cantidad > disponibles) {
        printf("Cantidad invalida. Puede agregar hasta %d libros.\n", disponibles);
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        struct libros nuevoLibro;

        printf("\n--- Libro %d ---\n", biblio->numLibros + 1);

        do {
            printf("Ingrese ID del libro (entero positivo): ");
            scanf("%d", &nuevoLibro.id);
            getchar(); 

            if (nuevoLibro.id <= 0) {
                printf("El ID debe ser un numero entero positivo.\n");
            } else if (!id_unico(biblio, nuevoLibro.id)) {
                printf("El ID ya existe. Intente con otro.\n");
                nuevoLibro.id = -1; 
            }

        } while (nuevoLibro.id <= 0);

        printf("Ingrese titulo del libro: ");
        fgets(nuevoLibro.titulo, sizeof(nuevoLibro.titulo), stdin);
        nuevoLibro.titulo[strcspn(nuevoLibro.titulo, "\n")] = 0;

        
        printf("Ingrese autor del libro: ");
        fgets(nuevoLibro.autor, sizeof(nuevoLibro.autor), stdin);
        nuevoLibro.autor[strcspn(nuevoLibro.autor, "\n")] = 0;

        do {
            printf("Ingrese anio de publicacion (positivo): ");
            scanf("%d", &nuevoLibro.anio);
            getchar();
            if (nuevoLibro.anio <= 0) {
                printf("El anio debe ser un numero entero positivo.\n");
            }
        } while (nuevoLibro.anio <= 0);

        strcpy(nuevoLibro.estado, "Disponible");

        biblio->libro[biblio->numLibros++] = nuevoLibro;

        printf("Libro agregado exitosamente.\n");
    }
}

void mostrarLibros(struct biblioteca *biblio) {
    if (biblio->numLibros == 0) {
        printf("No hay libros registrados en la biblioteca.\n");
        return;
    }

    printf("\n%-5s | %-30s | %-20s | %-6s | %-10s\n", "ID", "Título", "Autor", "Año", "Estado");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < biblio->numLibros; i++) {
        printf("%-5d | %-30s | %-20s | %-6d | %-10s\n",
               biblio->libro[i].id,
               biblio->libro[i].titulo,
               biblio->libro[i].autor,
               biblio->libro[i].anio,
               biblio->libro[i].estado);
    }
}


void buscarLibro(struct biblioteca *biblio) {
    if (biblio->numLibros == 0) {
        printf("No hay libros para buscar.\n");
        return;
    }

    int id;
    do {
        printf("Ingrese ID del libro a buscar (positivo): ");
        scanf("%d", &id);
        if (id <= 0) {
            printf("El ID debe ser un número positivo.\n");
        }
    } while (id <= 0);

    for (int i = 0; i < biblio->numLibros; i++) {
        if (biblio->libro[i].id == id) {
            printf("\nLibro encontrado:\n");
            printf("%-5s | %-30s | %-20s | %-6s | %-10s\n", "ID", "Título", "Autor", "Año", "Estado");
            printf("-------------------------------------------------------------------------------\n");
            printf("%-5d | %-30s | %-20s | %-6d | %-10s\n",
                   biblio->libro[i].id,
                   biblio->libro[i].titulo,
                   biblio->libro[i].autor,
                   biblio->libro[i].anio,
                   biblio->libro[i].estado);
            return;
        }
    }

    printf("Libro no encontrado.\n");
}

void buscarPorAutor(struct biblioteca *biblio, const char *autor) {
    if (biblio->numLibros == 0) {
        printf("No hay libros registrados en la biblioteca.\n");
        return;
    }

    if (strlen(autor) == 0) {
        printf("El nombre del autor no puede estar vacío.\n");
        return;
    }

    int encontrado = 0;
    printf("\nResultados para el autor '%s':\n", autor);
    printf("%-5s | %-30s | %-6s | %-10s\n", "ID", "Título", "Año", "Estado");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < biblio->numLibros; i++) {
        if (strcmp(biblio->libro[i].autor, autor) == 0) {
            printf("%-5d | %-30s | %-6d | %-10s\n",
                   biblio->libro[i].id,
                   biblio->libro[i].titulo,
                   biblio->libro[i].anio,
                   biblio->libro[i].estado);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("No se encontraron libros del autor '%s'.\n", autor);
    }
}


void actualizarEstado(struct biblioteca *biblio) {
    if (biblio->numLibros == 0) {
        printf("No hay libros registrados para actualizar.\n");
        return;
    }

    int cantidad;
    printf("¿Cuantos libros desea actualizar de estado? ");
    scanf("%d", &cantidad);

    for (int i = 0; i < cantidad; i++) {
        int id;
        printf("Ingrese ID del libro %d: ", i + 1);
        scanf("%d", &id);
        getchar(); // Limpiar buffer

        int encontrado = 0;
        for (int j = 0; j < biblio->numLibros; j++) {
            if (biblio->libro[j].id == id) {
                encontrado = 1;

                printf("Estado actual: %s\n", biblio->libro[j].estado);
                printf("¿Desea cambiar a:\n");
                printf("1. Disponible\n");
                printf("2. Prestado\n");
                printf("Seleccione una opcion: ");

                int opcion_estado;
                scanf("%d", &opcion_estado);
                getchar(); // Limpiar buffer

                if (opcion_estado == 1) {
                    strcpy(biblio->libro[j].estado, "Disponible");
                    printf("Estado actualizado a Disponible.\n");
                } else if (opcion_estado == 2) {
                    strcpy(biblio->libro[j].estado, "Prestado");
                    printf("Estado actualizado a Prestado.\n");
                } else {
                    printf("Opcion invalida. No se realizo el cambio.\n");
                }
                break;
            }
        }

        if (!encontrado) {
            printf("No se encontro un libro con ID %d.\n", id);
        }
    }
}

void eliminarLibro(struct biblioteca *biblio) {
    if (biblio->numLibros == 0) {
        printf("No hay libros registrados para eliminar.\n");
        return;
    }

    int cantidad;
    printf("¿Cuántos libros desea eliminar?: ");
    scanf("%d", &cantidad);

    for (int c = 0; c < cantidad; c++) {
        int id;
        printf("Ingrese ID del libro %d a eliminar: ", c + 1);
        scanf("%d", &id);

        int encontrado = 0;
        for (int i = 0; i < biblio->numLibros; i++) {
            if (biblio->libro[i].id == id) {
                for (int j = i; j < biblio->numLibros - 1; j++) {
                    biblio->libro[j] = biblio->libro[j + 1];
                }
                biblio->numLibros--;
                printf("Libro con ID %d eliminado exitosamente.\n", id);
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("No se encontró un libro con ID %d.\n", id);
        }
    }
}
