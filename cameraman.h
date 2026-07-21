#ifndef CAMERAMAN_H
#define CAMERAMAN_H

void config_camera(int altura, int largura);
void teclado_especial(int key, int x, int y);
void teclado_comum(unsigned char key, int x, int y);

extern float cam_x, cam_y, cam_z;
extern float alvoX, alvoy, alvoz;
extern int filtro_camera;

#endif