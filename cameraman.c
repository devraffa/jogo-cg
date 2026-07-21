#include <GL/glut.h> 
#include "cameraman.h"

float cam_x = 0.0f;
float cam_y = 5.0f;
float cam_z = 15.0f;

float alvoX =0.0f;
float alvoy =0.0f;
float alvoz =0.0f;

int filtro_camera = 1; // // 1 = atrás da raquete, 2 = lado, 3 = cima

void config_camera(int altura, int largura){

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (filtro_camera == 1) {
        
        gluLookAt(0.0, 5.0, 15.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
    } 
    else if (filtro_camera == 2) {

        gluLookAt(20.0, 5.0, 0.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
    } 
    else if (filtro_camera == 3) {

        gluLookAt(0.0, 20.0, 0.0,  0.0, 0.0, 0.0,  0.0, 0.0, -1.0);
    }
    else {

        gluLookAt(cam_x, cam_y, cam_z, alvoX, alvoy, alvoz, 0.0, 1.0, 0.0);
    }
}

void teclado_especial(int key, int x, int y) {
    float vel = 0.5f;
    switch (key) {
        case GLUT_KEY_UP:    cam_z -= vel; break;
        case GLUT_KEY_DOWN:  cam_z += vel; break;
        case GLUT_KEY_LEFT:  cam_x -= vel; break;
        case GLUT_KEY_RIGHT: cam_x += vel; break;
    }
    glutPostRedisplay();
}

void teclado_comum(unsigned char key, int x, int y) {
    if (key >= '1' && key <= '3') {
        filtro_camera = key - '0'; 
    }
    glutPostRedisplay();
}