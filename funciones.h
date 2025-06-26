#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAXLIBROS 10

struct libros {
    int id;
    char titulo[100];
    char autor[50];
    int anio;
    char estado[15];
};

struct biblioteca {
    struct libros libro[MAXLIBROS];
    int numLibros;
};

int id_unico(struct biblioteca *biblio, int id);
void agregarLibro(struct biblioteca *biblio);
void mostrarLibros(struct biblioteca *biblio);
void buscarLibro(struct biblioteca *biblio);
void buscarPorAutor(struct biblioteca *biblio, const char *autor);
void actualizarEstado(struct biblioteca *biblio);
void eliminarLibro(struct biblioteca *biblio);

#endif
