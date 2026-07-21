#ifndef OBJETO3D_H
#define OBJETO3D_H

typedef struct {
    float x;
    float y;
    float z;
} Vertice3D;

typedef struct {
    int vertices[16];
    int total_vertices;
} Face3D;

typedef struct {
    Vertice3D *vertices;
    int total_vertices;
    int capacidade_vertices;
    Face3D *faces;
    int total_faces;
    int capacidade_faces;
} Objeto3D;

Objeto3D *carregar_objeto_3d(const char *caminho);
void desenhar_objeto_3d(const Objeto3D *objeto);
void liberar_objeto_3d(Objeto3D *objeto);

#endif
