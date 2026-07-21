#include "objeto3d.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Objeto3D *criar_objeto_vazio() {
    Objeto3D *objeto = (Objeto3D *) malloc(sizeof(Objeto3D));
    if (objeto == NULL) {
        return NULL;
    }

    objeto->vertices = NULL;
    objeto->total_vertices = 0;
    objeto->capacidade_vertices = 0;
    objeto->faces = NULL;
    objeto->total_faces = 0;
    objeto->capacidade_faces = 0;
    return objeto;
}

static int aumentar_vertices(Objeto3D *objeto) {
    int nova_capacidade = objeto->capacidade_vertices == 0 ? 32 : objeto->capacidade_vertices * 2;
    Vertice3D *novo_vetor = (Vertice3D *) realloc(objeto->vertices, sizeof(Vertice3D) * nova_capacidade);
    if (novo_vetor == NULL) {
        return 0;
    }

    objeto->vertices = novo_vetor;
    objeto->capacidade_vertices = nova_capacidade;
    return 1;
}

static int aumentar_faces(Objeto3D *objeto) {
    int nova_capacidade = objeto->capacidade_faces == 0 ? 32 : objeto->capacidade_faces * 2;
    Face3D *novo_vetor = (Face3D *) realloc(objeto->faces, sizeof(Face3D) * nova_capacidade);
    if (novo_vetor == NULL) {
        return 0;
    }

    objeto->faces = novo_vetor;
    objeto->capacidade_faces = nova_capacidade;
    return 1;
}

static int adicionar_vertice(Objeto3D *objeto, float x, float y, float z) {
    if (objeto->total_vertices >= objeto->capacidade_vertices && !aumentar_vertices(objeto)) {
        return 0;
    }

    objeto->vertices[objeto->total_vertices].x = x;
    objeto->vertices[objeto->total_vertices].y = y;
    objeto->vertices[objeto->total_vertices].z = z;
    objeto->total_vertices++;
    return 1;
}

static int adicionar_face(Objeto3D *objeto, Face3D face) {
    if (objeto->total_faces >= objeto->capacidade_faces && !aumentar_faces(objeto)) {
        return 0;
    }

    objeto->faces[objeto->total_faces] = face;
    objeto->total_faces++;
    return 1;
}

static int ler_indice(const char *texto) {
    char copia[64];
    int i = 0;

    while (texto[i] != '\0' && texto[i] != '/' && i < 63) {
        copia[i] = texto[i];
        i++;
    }

    copia[i] = '\0';
    return atoi(copia) - 1;
}

Objeto3D *carregar_objeto_3d(const char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    char linha[256];
    Objeto3D *objeto;

    if (arquivo == NULL) {
        return NULL;
    }

    objeto = criar_objeto_vazio();
    if (objeto == NULL) {
        fclose(arquivo);
        return NULL;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (linha[0] == 'v' && linha[1] == ' ') {
            float x;
            float y;
            float z;
            if (sscanf(linha, "v %f %f %f", &x, &y, &z) == 3) {
                if (!adicionar_vertice(objeto, x, y, z)) {
                    liberar_objeto_3d(objeto);
                    fclose(arquivo);
                    return NULL;
                }
            }
        } else if (linha[0] == 'f' && linha[1] == ' ') {
            Face3D face;
            char *parte;
            char *contexto = NULL;

            memset(&face, 0, sizeof(Face3D));
            parte = strtok_s(linha + 2, " \t\r\n", &contexto);
            while (parte != NULL && face.total_vertices < 16) {
                face.vertices[face.total_vertices] = ler_indice(parte);
                face.total_vertices++;
                parte = strtok_s(NULL, " \t\r\n", &contexto);
            }

            if (face.total_vertices >= 3) {
                if (!adicionar_face(objeto, face)) {
                    liberar_objeto_3d(objeto);
                    fclose(arquivo);
                    return NULL;
                }
            }
        }
    }

    fclose(arquivo);
    return objeto;
}

static void calcular_normal(const Vertice3D *a, const Vertice3D *b, const Vertice3D *c, float *nx, float *ny, float *nz) {
    float ux = b->x - a->x;
    float uy = b->y - a->y;
    float uz = b->z - a->z;
    float vx = c->x - a->x;
    float vy = c->y - a->y;
    float vz = c->z - a->z;
    float tamanho;

    *nx = uy * vz - uz * vy;
    *ny = uz * vx - ux * vz;
    *nz = ux * vy - uy * vx;

    tamanho = sqrtf((*nx * *nx) + (*ny * *ny) + (*nz * *nz));
    if (tamanho > 0.0f) {
        *nx /= tamanho;
        *ny /= tamanho;
        *nz /= tamanho;
    }
}

void desenhar_objeto_3d(const Objeto3D *objeto) {
    int i;

    if (objeto == NULL) {
        return;
    }

    for (i = 0; i < objeto->total_faces; i++) {
        const Face3D *face = &objeto->faces[i];
        const Vertice3D *a = &objeto->vertices[face->vertices[0]];
        const Vertice3D *b = &objeto->vertices[face->vertices[1]];
        const Vertice3D *c = &objeto->vertices[face->vertices[2]];
        float nx;
        float ny;
        float nz;
        int j;

        calcular_normal(a, b, c, &nx, &ny, &nz);

        glBegin(GL_POLYGON);
        glNormal3f(nx, ny, nz);
        for (j = 0; j < face->total_vertices; j++) {
            const Vertice3D *vertice = &objeto->vertices[face->vertices[j]];
            glVertex3f(vertice->x, vertice->y, vertice->z);
        }
        glEnd();
    }
}

void liberar_objeto_3d(Objeto3D *objeto) {
    if (objeto == NULL) {
        return;
    }

    free(objeto->vertices);
    free(objeto->faces);
    free(objeto);
}
