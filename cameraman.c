#include <GL/glut.h> 
#include "cameraman.h"
#include <math.h> 

float cam_x = 0.0f;
float cam_y = 5.0f;
float cam_z = 15.0f;

float alvoX =0.0f;
float alvoy =0.0f;
float alvoz =0.0f;

int filtro_camera = 1; // // 1 = atrás da raquete, 2 = lado, 3 = cima

int estado_mouse = 0; 
int mouse_x_antigo = 0, mouse_y_antigo = 0;
float angulo_x = 0.0f, angulo_y = 0.0f;

float raio_camera = 15.0f;

void controle_mouse(int button, int state, int x, int y) {
    if (filtro_camera == 4) {
        if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN) {
                estado_mouse = 1;
                mouse_x_antigo = x;
                mouse_y_antigo = y;
            } else {
                estado_mouse = 0;
            }
        }
    }

    else if (button == 3 && state == GLUT_DOWN) { 
            raio_camera -= 1.0f;
            if (raio_camera < 5.0f) raio_camera = 5.0f; 
            glutPostRedisplay();
        }

        else if (button == 4 && state == GLUT_DOWN) { 
            raio_camera += 1.0f;
            if (raio_camera > 40.0f) raio_camera = 40.0f; 
            glutPostRedisplay();
        }
    }

void movimento_mouse(int x, int y) {
    if (estado_mouse && filtro_camera == 4) {
        
        angulo_x += (x - mouse_x_antigo) * 0.01f;
        angulo_y -= (y - mouse_y_antigo) * 0.01f; 

        if (angulo_y > 1.5f) angulo_y = 1.5f;
        if (angulo_y < -1.5f) angulo_y = -1.5f;

        mouse_x_antigo = x;
        mouse_y_antigo = y;

        cam_x = raio_camera * sin(angulo_x) * cos(angulo_y);
        cam_y = raio_camera * sin(angulo_y);
        cam_z = raio_camera * cos(angulo_x) * cos(angulo_y);

        glutPostRedisplay(); 
    }
}

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
    if (key >= '1' && key <= '4') {
        filtro_camera = key - '0'; 
    }
    glutPostRedisplay();
}