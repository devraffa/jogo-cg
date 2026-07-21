#include <GL/glut.h>
#include "cameraman.h"

extern void config_camera(int altura, int largura);
extern void teclado_especial(int key, int x, int y);
extern void teclado_comum(unsigned char key, int x, int y);

void desenharObjetoTeste() {
    glColor3f(1.0f, 0.0f, 0.0f); 
    glutWireCube(2.0f);         
    
    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(-5.0f, 0.0f, 0.0f);
        glVertex3f(5.0f, 0.0f, 0.0f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    config_camera(600, 800); 

    desenharObjetoTeste();

    glutSwapBuffers();
}

void reshape(int largura, int altura) {
    if (altura == 0) altura = 1; 
    
    glViewport(0, 0, largura, altura); 

    float aspect = (float)largura / (float)altura;
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();

    gluPerspective(60.0, aspect, 0.1, 100.0);
    
    glMatrixMode(GL_MODELVIEW); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ping Pong 3D - Camera e Projecao");

    glEnable(GL_DEPTH_TEST); 

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(teclado_especial);
    glutKeyboardFunc(teclado_comum);

    glutMainLoop(); 
    return 0;
}