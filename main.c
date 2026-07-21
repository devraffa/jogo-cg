#include <GL/glut.h>
#include "cameraman.h"

extern void config_camera(int altura, int largura);
extern void teclado_especial(int key, int x, int y);
extern void teclado_comum(unsigned char key, int x, int y);

typedef struct {
    GLfloat ambiente[4];
    GLfloat difusa[4];
    GLfloat especular[4];
    GLfloat brilho;
} MaterialSimples;

static MaterialSimples material_vermelho = {
    {0.30f, 0.05f, 0.05f, 1.0f},
    {0.85f, 0.20f, 0.20f, 1.0f},
    {0.40f, 0.30f, 0.30f, 1.0f},
    18.0f
};

static MaterialSimples material_azul = {
    {0.05f, 0.10f, 0.30f, 1.0f},
    {0.20f, 0.45f, 0.90f, 1.0f},
    {0.30f, 0.35f, 0.45f, 1.0f},
    20.0f
};

static MaterialSimples material_verde = {
    {0.05f, 0.20f, 0.08f, 1.0f},
    {0.20f, 0.55f, 0.25f, 1.0f},
    {0.10f, 0.15f, 0.10f, 1.0f},
    10.0f
};

static MaterialSimples material_branco = {
    {0.20f, 0.20f, 0.20f, 1.0f},
    {0.92f, 0.92f, 0.92f, 1.0f},
    {0.50f, 0.50f, 0.50f, 1.0f},
    28.0f
};

static MaterialSimples material_cinza = {
    {0.18f, 0.18f, 0.18f, 1.0f},
    {0.45f, 0.45f, 0.45f, 1.0f},
    {0.35f, 0.35f, 0.35f, 1.0f},
    14.0f
};

void aplicar_material(MaterialSimples material, float r, float g, float b) {
    glColor3f(r, g, b);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.difusa);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.especular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.brilho);
}

void desenhar_mesa() {
    glPushMatrix();
    aplicar_material(material_verde, 0.20f, 0.55f, 0.25f);
    glScalef(8.0f, 0.35f, 4.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    aplicar_material(material_branco, 0.95f, 0.95f, 0.95f);
    glTranslatef(0.0f, 0.19f, 0.0f);
    glScalef(8.05f, 0.02f, 0.10f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    aplicar_material(material_branco, 0.95f, 0.95f, 0.95f);
    glTranslatef(0.0f, 0.19f, 0.0f);
    glScalef(0.10f, 0.02f, 4.55f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    aplicar_material(material_cinza, 0.45f, 0.45f, 0.45f);
    glTranslatef(-3.5f, -1.3f, -1.8f);
    glScalef(0.25f, 2.6f, 0.25f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    aplicar_material(material_cinza, 0.45f, 0.45f, 0.45f);
    glTranslatef(3.5f, -1.3f, -1.8f);
    glScalef(0.25f, 2.6f, 0.25f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    aplicar_material(material_cinza, 0.45f, 0.45f, 0.45f);
    glTranslatef(-3.5f, -1.3f, 1.8f);
    glScalef(0.25f, 2.6f, 0.25f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    aplicar_material(material_cinza, 0.45f, 0.45f, 0.45f);
    glTranslatef(3.5f, -1.3f, 1.8f);
    glScalef(0.25f, 2.6f, 0.25f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void desenhar_bola() {
    glPushMatrix();
    aplicar_material(material_branco, 0.96f, 0.96f, 0.96f);
    glTranslatef(0.0f, 0.35f, 0.0f);
    glutSolidSphere(0.22f, 24, 24);
    glPopMatrix();
}

void desenhar_raquete_caixa(float x, float z, MaterialSimples material, float r, float g, float b) {
    glPushMatrix();
    aplicar_material(material, r, g, b);
    glTranslatef(x, 0.45f, z);
    glScalef(0.35f, 0.20f, 1.05f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void desenhar_cenario() {
    desenhar_mesa();
    desenhar_bola();
    desenhar_raquete_caixa(-2.6f, 0.0f, material_vermelho, 0.85f, 0.20f, 0.20f);
    desenhar_raquete_caixa(2.6f, 0.0f, material_azul, 0.20f, 0.45f, 0.90f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    config_camera(600, 800);
    desenhar_cenario();

    glutSwapBuffers();
}

void reshape(int largura, int altura) {
    if (altura == 0) {
        altura = 1;
    }

    glViewport(0, 0, largura, altura);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float) largura / (float) altura, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void iniciar_cena() {
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0f);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ping Pong 3D");

    iniciar_cena();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(teclado_especial);
    glutKeyboardFunc(teclado_comum);

    glutMainLoop();
    return 0;
}
