#include<windows.h>
#ifdef __APPLE__
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

#include <math.h>
#include <iostream>
using namespace std;

#define FPS 120
#define TO_RADIANS 3.14/180.0

//  Anggota Kelompok 7
//  Natalia Mega Hapsari    (672019051)
//  Nopan                   (672020079)
//  Reynaldo Jordy L        (672020116)
//  Candra Setyadi          (672020228)
//  Nicola Van Robert J     (672020297)

const int width = 1280;
const int height = 720;
int i;
float sudut;
double x_geser, y_geser, z_geser;

float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 0.0, terbang = 25.0;

void display();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void camera();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

struct Motion {
    bool Forward, Backward, Left, Right, Naik, Turun;
};
Motion motion = { false,false,false,false,false,false };

void init() {
    glClearColor(0.529, 0.807, 0.921, 0.0);
    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glutWarpPointer(width / 2, height / 2);
}

void ground() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-1000.0, 0, -1000.0);

    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(1000.0, 0, -1000.0);

    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(1000.0, 0, 1000.0);

    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-1000.0, 0, 1000.0);
    glEnd();
}

void dasar() {
    //depan
    glBegin(GL_POLYGON);
    glVertex3f(-150, 0, 150);
    glVertex3f(-150, 50, 150);
    glVertex3f(350, 50, 150);
    glVertex3f(350, 0, 150);
    glEnd();

    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-150, 0, -250);
    glVertex3f(-150, 50, -250);
    glVertex3f(350, 50, -250);
    glVertex3f(350, 0, -250);
    glEnd();

    //Kanan
    glBegin(GL_POLYGON);
    glVertex3f(350, 50, 150);
    glVertex3f(350, 0, 150);
    glVertex3f(350, 0, -250);
    glVertex3f(350, 50, -250);
    glEnd();

    //Kiri
    glBegin(GL_POLYGON);
    glVertex3f(-150, 50, 150);
    glVertex3f(-150, 0, 150);
    glVertex3f(-150, 0, -250);
    glVertex3f(-150, 50, -250);
    glEnd();

    //atas
    glBegin(GL_POLYGON);
    glVertex3f(-150, 50, 150);
    glVertex3f(-150, 50, -250);
    glVertex3f(350, 50, -250);
    glVertex3f(350, 50, 150);
    glEnd();
}
void lantai1() {
    //depan
    glBegin(GL_POLYGON);
    glVertex3f(-50, 0, 70);
    glVertex3f(-50, 150, 70);
    glVertex3f(250, 150, 70);
    glVertex3f(250, 0, 70);
    glEnd();

    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-50, 0, -170);
    glVertex3f(-50, 150, -170);
    glVertex3f(250, 150, -170);
    glVertex3f(250, 0, -170);
    glEnd();

    //Kanan
    glBegin(GL_POLYGON);
    glVertex3f(250, 150, 70);
    glVertex3f(250, 0, 70);
    glVertex3f(250, 0, -170);
    glVertex3f(250, 150, -170);
    glEnd();

    //Kiri
    glBegin(GL_POLYGON);
    glVertex3f(-50, 150, 70);
    glVertex3f(-50, 0, 70);
    glVertex3f(-50, 0, -170);
    glVertex3f(-50, 150, -170);
    glEnd();

}

void lantai2() {
    //depan
    glBegin(GL_POLYGON);
    glVertex3f(-10, 0, 70);
    glVertex3f(-10, 200, 70);
    glVertex3f(200, 200, 70);
    glVertex3f(200, 0, 70);
    glEnd();

    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-10, 0, -170);
    glVertex3f(-10, 200, -170);
    glVertex3f(200, 200, -170);
    glVertex3f(200, 0, -170);
    glEnd();

    //Kanan
    glBegin(GL_POLYGON);
    glVertex3f(200, 200, 70);
    glVertex3f(200, 0, 70);
    glVertex3f(200, 0, -170);
    glVertex3f(200, 200, -170);
    glEnd();

    //Kiri
    glBegin(GL_POLYGON);
    glVertex3f(-10, 200, 70);
    glVertex3f(-10, 0, 70);
    glVertex3f(-10, 0, -170);
    glVertex3f(-10, 200, -170);
    glEnd();
}

void lantai3() {
    //depan
    glBegin(GL_POLYGON);
    glVertex3f(-10, 0, 70);
    glVertex3f(-10, 200, 70);
    glVertex3f(200, 200, 70);
    glVertex3f(200, 0, 70);
    glEnd();

    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-10, 0, -170);
    glVertex3f(-10, 200, -170);
    glVertex3f(200, 200, -170);
    glVertex3f(200, 0, -170);
    glEnd();

    //Kanan
    glBegin(GL_POLYGON);
    glVertex3f(200, 200, 70);
    glVertex3f(200, 0, 70);
    glVertex3f(200, 0, -170);
    glVertex3f(200, 200, -170);
    glEnd();

    //Kiri
    glBegin(GL_POLYGON);
    glVertex3f(-10, 200, 70);
    glVertex3f(-10, 0, 70);
    glVertex3f(-10, 0, -170);
    glVertex3f(-10, 200, -170);
    glEnd();
}

void lantai4() {
    //depan
    glBegin(GL_POLYGON);
    glVertex3f(-10, 0, 70);
    glVertex3f(-10, 200, 70);
    glVertex3f(200, 200, 70);
    glVertex3f(200, 0, 70);
    glEnd();

    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-10, 0, -170);
    glVertex3f(-10, 200, -170);
    glVertex3f(200, 200, -170);
    glVertex3f(200, 0, -170);
    glEnd();

    //Kanan
    glBegin(GL_POLYGON);
    glVertex3f(200, 200, 70);
    glVertex3f(200, 0, 70);
    glVertex3f(200, 0, -170);
    glVertex3f(200, 200, -170);
    glEnd();

    //Kiri
    glBegin(GL_POLYGON);
    glVertex3f(-10, 200, 70);
    glVertex3f(-10, 0, 70);
    glVertex3f(-10, 0, -170);
    glVertex3f(-10, 200, -170);
    glEnd();
}

void atap1() {

    glBegin(GL_POLYGON);
    glVertex3f(-150, 50, 150);
    glVertex3f(-150, 50, -250);
    glVertex3f(350, 50, -250);
    glVertex3f(350, 50, 150);
    glEnd();
}

void atap2() {

    //depan
    glBegin(GL_POLYGON);
    glVertex3f(-150, 0, 150);
    glVertex3f(-10, 50, 70);
    glVertex3f(200, 50, 70);
    glVertex3f(350, 0, 150);
    glEnd();

    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-150, 0, -250);
    glVertex3f(-10, 50, -170);
    glVertex3f(200, 50, -170);
    glVertex3f(350, 0, -250);
    glEnd();

    //Kanan
    glBegin(GL_POLYGON);
    glVertex3f(200, 50, 70);
    glVertex3f(350, 0, 150);
    glVertex3f(350, 0, -250);
    glVertex3f(200, 50, -170);
    glEnd();

    //Kiri
    glBegin(GL_POLYGON);
    glVertex3f(-10, 50, 70);
    glVertex3f(-150, 0, 150);
    glVertex3f(-150, 0, -250);
    glVertex3f(-10, 50, -170);
    glEnd();


}
void atap2a() {
    glBegin(GL_POLYGON);
    glVertex3f(-150, 50, 150);
    glVertex3f(-150, 50, -250);
    glVertex3f(350, 50, -250);
    glVertex3f(350, 50, 150);
    glEnd();
}

void atap3() {
    //depan
    glBegin(GL_POLYGON);
    glVertex3f(-150, 0, 130);
    glVertex3f(-10, 50, 70);
    glVertex3f(200, 50, 70);
    glVertex3f(350, 0, 130);
    glEnd();

    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-150, 0, -230);
    glVertex3f(-10, 50, -170);
    glVertex3f(200, 50, -170);
    glVertex3f(350, 0, -230);
    glEnd();

    //Kanan
    glBegin(GL_POLYGON);
    glVertex3f(200, 50, 70);
    glVertex3f(350, 0, 130);
    glVertex3f(350, 0, -230);
    glVertex3f(200, 50, -170);
    glEnd();

    //Kiri
    glBegin(GL_POLYGON);
    glVertex3f(-10, 50, 70);
    glVertex3f(-150, 0, 130);
    glVertex3f(-150, 0, -230);
    glVertex3f(-10, 50, -170);
    glEnd();

}

void atap3a() {
    glBegin(GL_POLYGON);
    glVertex3f(-150, 50, 130);
    glVertex3f(-150, 50, -230);
    glVertex3f(350, 50, -230);
    glVertex3f(350, 50, 130);
    glEnd();
}
void atap4() {
    //depan
    glBegin(GL_POLYGON);
    glVertex3f(-150, 0, 130);
    glVertex3f(-10, 50, 70);
    glVertex3f(200, 50, 70);
    glVertex3f(350, 0, 130);
    glEnd();

    //Belakang
    glBegin(GL_POLYGON);
    glVertex3f(-150, 0, -230);
    glVertex3f(-10, 50, -170);
    glVertex3f(200, 50, -170);
    glVertex3f(350, 0, -230);
    glEnd();

    //Kanan
    glBegin(GL_POLYGON);
    glVertex3f(200, 50, 70);
    glVertex3f(350, 0, 130);
    glVertex3f(350, 0, -230);
    glVertex3f(200, 50, -170);
    glEnd();

    //Kiri
    glBegin(GL_POLYGON);
    glVertex3f(-10, 50, 70);
    glVertex3f(-150, 0, 130);
    glVertex3f(-150, 0, -230);
    glVertex3f(-10, 50, -170);
    glEnd();

}
void lantaiduduk3() {
    glBegin(GL_POLYGON);
    glVertex3f(-80, 50, 140);
    glVertex3f(-80, 50, -220);
    glVertex3f(280, 50, -220);
    glVertex3f(280, 50, 140);
    glEnd();
}
void lantaiduduk4() {
    glBegin(GL_POLYGON);
    glVertex3f(-80, 50, 140);
    glVertex3f(-80, 50, -220);
    glVertex3f(280, 50, -220);
    glVertex3f(280, 50, 140);
    glEnd();
}

void turunan() {

    glBegin(GL_POLYGON);
    glVertex3f(-50, 0, 140);
    glVertex3f(-50, -80, 300);
    glVertex3f(230, -80, 300);
    glVertex3f(230, 0, 140);
    glEnd();

}

void pagar_lantai1() {
    //belakang
    glBegin(GL_LINE_LOOP);
    glVertex3f(-200, 0, -200);
    glVertex3f(-200, 50, -200);
    glVertex3f(300, 50, -200);
    glVertex3f(300, 0, -200);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(-200, 0, -200);
    glVertex3f(-200, 50, -200);
    glVertex3f(-180, 0, -200);
    glVertex3f(-180, 50, -200);
    glVertex3f(-160, 0, -200);
    glVertex3f(-160, 50, -200);
    glVertex3f(-140, 0, -200);
    glVertex3f(-140, 50, -200);
    glVertex3f(-120, 0, -200);
    glVertex3f(-120, 50, -200);
    glVertex3f(-100, 0, -200);
    glVertex3f(-100, 50, -200);
    glVertex3f(-80, 0, -200);
    glVertex3f(-80, 50, -200);
    glVertex3f(-60, 50, -200);
    glVertex3f(-60, 50, -200);
    glVertex3f(-60, 0, -200);
    glVertex3f(-60, 50, -200);
    glVertex3f(-40, 0, -200);
    glVertex3f(-40, 50, -200);
    glVertex3f(-20, 0, -200);
    glVertex3f(-20, 50, -200);
    glVertex3f(-0, 0, -200);
    glVertex3f(-0, 50, -200);
    glVertex3f(20, 0, -200);
    glVertex3f(20, 50, -200);
    glVertex3f(40, 0, -200);
    glVertex3f(40, 50, -200);
    glVertex3f(60, 0, -200);
    glVertex3f(60, 50, -200);
    glVertex3f(80, 0, -200);
    glVertex3f(80, 50, -200);
    glVertex3f(100, 0, -200);
    glVertex3f(100, 50, -200);
    glVertex3f(120, 0, -200);
    glVertex3f(120, 50, -200);
    glVertex3f(140, 0, -200);
    glVertex3f(140, 50, -200);
    glVertex3f(160, 0, -200);
    glVertex3f(160, 50, -200);
    glVertex3f(180, 0, -200);
    glVertex3f(180, 50, -200);
    glVertex3f(200, 0, -200);
    glVertex3f(200, 50, -200);
    glVertex3f(220, 0, -200);
    glVertex3f(220, 50, -200);
    glVertex3f(240, 0, -200);
    glVertex3f(240, 50, -200);
    glVertex3f(260, 0, -200);
    glVertex3f(260, 50, -200);
    glVertex3f(280, 0, -200);
    glVertex3f(280, 50, -200);
    glEnd();

    //depan kiri
    glBegin(GL_LINE_LOOP);
    glVertex3f(-200, 50, 200);
    glVertex3f(-200, 0, 200);
    glVertex3f(-100, 0, 200);
    glVertex3f(-100, 50, 200);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(-120, 0, 200);
    glVertex3f(-120, 50, 200);
    glVertex3f(-140, 0, 200);
    glVertex3f(-140, 50, 200);
    glVertex3f(-160, 0, 200);
    glVertex3f(-160, 50, 200);
    glVertex3f(-180, 0, 200);
    glVertex3f(-180, 50, 200);
    glEnd();

    //depan kanan
    glBegin(GL_LINE_LOOP);
    glVertex3f(180, 50, 200);
    glVertex3f(180, 0, 200);
    glVertex3f(300, 0, 200);
    glVertex3f(300, 50, 200);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(280, 0, 200);
    glVertex3f(280, 50, 200);
    glVertex3f(260, 0, 200);
    glVertex3f(260, 50, 200);
    glVertex3f(240, 0, 200);
    glVertex3f(240, 50, 200);
    glVertex3f(220, 0, 200);
    glVertex3f(220, 50, 200);
    glVertex3f(200, 0, 200);
    glVertex3f(200, 50, 200);
    glEnd();


    //Kanan
    glBegin(GL_LINE_LOOP);
    glVertex3f(-200, 50, -200);
    glVertex3f(-200, 0, -200);
    glVertex3f(-200, 0, 200);
    glVertex3f(-200, 50, 200);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(300, 0, -180);
    glVertex3f(300, 50, -180);
    glVertex3f(300, 0, -160);
    glVertex3f(300, 50, -160);
    glVertex3f(300, 0, -140);
    glVertex3f(300, 50, -140);
    glVertex3f(300, 0, -120);
    glVertex3f(300, 50, -120);
    glVertex3f(300, 0, -100);
    glVertex3f(300, 50, -100);
    glVertex3f(300, 0, -80);
    glVertex3f(300, 50, -80);
    glVertex3f(300, 0, -60);
    glVertex3f(300, 50, -60);
    glVertex3f(300, 0, -60);
    glVertex3f(300, 50, -60);
    glVertex3f(300, 0, -40);
    glVertex3f(300, 50, -40);
    glVertex3f(300, 0, -20);
    glVertex3f(300, 50, -20);
    glVertex3f(300, 0, -0);
    glVertex3f(300, 50, -0);
    glVertex3f(300, 0, 200);
    glVertex3f(300, 50, 200);
    glVertex3f(300, 0, 180);
    glVertex3f(300, 50, 180);
    glVertex3f(300, 0, 160);
    glVertex3f(300, 50, 160);
    glVertex3f(300, 0, 140);
    glVertex3f(300, 50, 140);
    glVertex3f(300, 0, 120);
    glVertex3f(300, 50, 120);
    glVertex3f(300, 0, 100);
    glVertex3f(300, 50, 100);
    glVertex3f(300, 0, 80);
    glVertex3f(300, 50, 80);
    glVertex3f(300, 0, 60);
    glVertex3f(300, 50, 60);
    glVertex3f(300, 0, 40);
    glVertex3f(300, 50, 40);
    glVertex3f(300, 0, 20);
    glVertex3f(300, 50, 20);
    glEnd();

    //Kiri
    glBegin(GL_LINE_LOOP);
    glVertex3f(300, 50, -200);
    glVertex3f(300, 0, -200);
    glVertex3f(300, 0, 200);
    glVertex3f(300, 50, 200);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(-200, 0, -180);
    glVertex3f(-200, 50, -180);
    glVertex3f(-200, 0, -160);
    glVertex3f(-200, 50, -160);
    glVertex3f(-200, 0, -140);
    glVertex3f(-200, 50, -140);
    glVertex3f(-200, 0, -120);
    glVertex3f(-200, 50, -120);
    glVertex3f(-200, 0, -100);
    glVertex3f(-200, 50, -100);
    glVertex3f(-200, 0, -80);
    glVertex3f(-200, 50, -80);
    glVertex3f(-200, 0, -60);
    glVertex3f(-200, 50, -60);
    glVertex3f(-200, 0, -60);
    glVertex3f(-200, 50, -60);
    glVertex3f(-200, 0, -40);
    glVertex3f(-200, 50, -40);
    glVertex3f(-200, 0, -20);
    glVertex3f(-200, 50, -20);
    glVertex3f(-200, 0, -0);
    glVertex3f(-200, 50, -0);
    glVertex3f(-200, 0, 200);
    glVertex3f(-200, 50, 200);
    glVertex3f(-200, 0, 180);
    glVertex3f(-200, 50, 180);
    glVertex3f(-200, 0, 160);
    glVertex3f(-200, 50, 160);
    glVertex3f(-200, 0, 140);
    glVertex3f(-200, 50, 140);
    glVertex3f(-200, 0, 120);
    glVertex3f(-200, 50, 120);
    glVertex3f(-200, 0, 100);
    glVertex3f(-200, 50, 100);
    glVertex3f(-200, 0, 80);
    glVertex3f(-200, 50, 80);
    glVertex3f(-200, 0, 60);
    glVertex3f(-200, 50, 60);
    glVertex3f(-200, 0, 40);
    glVertex3f(-200, 50, 40);
    glVertex3f(-200, 0, 20);
    glVertex3f(-200, 50, 20);
    glEnd();
}

void pagar_lantai2() {
    //belakang
    glBegin(GL_LINE_LOOP);
    glVertex3f(-200, 0, -200);
    glVertex3f(-200, 50, -200);
    glVertex3f(300, 50, -200);
    glVertex3f(300, 0, -200);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(-200, 0, -200);
    glVertex3f(-200, 50, -200);
    glVertex3f(-180, 0, -200);
    glVertex3f(-180, 50, -200);
    glVertex3f(-160, 0, -200);
    glVertex3f(-160, 50, -200);
    glVertex3f(-140, 0, -200);
    glVertex3f(-140, 50, -200);
    glVertex3f(-120, 0, -200);
    glVertex3f(-120, 50, -200);
    glVertex3f(-100, 0, -200);
    glVertex3f(-100, 50, -200);
    glVertex3f(-80, 0, -200);
    glVertex3f(-80, 50, -200);
    glVertex3f(-60, 50, -200);
    glVertex3f(-60, 50, -200);
    glVertex3f(-60, 0, -200);
    glVertex3f(-60, 50, -200);
    glVertex3f(-40, 0, -200);
    glVertex3f(-40, 50, -200);
    glVertex3f(-20, 0, -200);
    glVertex3f(-20, 50, -200);
    glVertex3f(-0, 0, -200);
    glVertex3f(-0, 50, -200);
    glVertex3f(20, 0, -200);
    glVertex3f(20, 50, -200);
    glVertex3f(40, 0, -200);
    glVertex3f(40, 50, -200);
    glVertex3f(60, 0, -200);
    glVertex3f(60, 50, -200);
    glVertex3f(80, 0, -200);
    glVertex3f(80, 50, -200);
    glVertex3f(100, 0, -200);
    glVertex3f(100, 50, -200);
    glVertex3f(120, 0, -200);
    glVertex3f(120, 50, -200);
    glVertex3f(140, 0, -200);
    glVertex3f(140, 50, -200);
    glVertex3f(160, 0, -200);
    glVertex3f(160, 50, -200);
    glVertex3f(180, 0, -200);
    glVertex3f(180, 50, -200);
    glVertex3f(200, 0, -200);
    glVertex3f(200, 50, -200);
    glVertex3f(220, 0, -200);
    glVertex3f(220, 50, -200);
    glVertex3f(240, 0, -200);
    glVertex3f(240, 50, -200);
    glVertex3f(260, 0, -200);
    glVertex3f(260, 50, -200);
    glVertex3f(280, 0, -200);
    glVertex3f(280, 50, -200);
    glEnd();

    //depan
    glBegin(GL_LINE_LOOP);
    glVertex3f(-200, 0, 200);
    glVertex3f(-200, 50, 200);
    glVertex3f(300, 50, 200);
    glVertex3f(300, 0, 200);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(-200, 0, 200);
    glVertex3f(-200, 25, 200);
    glVertex3f(300, 25, 200);
    glVertex3f(300, 0, 200);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(-200, 0, 200);
    glVertex3f(-200, 50, 200);
    glVertex3f(-180, 0, 200);
    glVertex3f(-180, 50, 200);
    glVertex3f(-160, 0, 200);
    glVertex3f(-160, 50, 200);
    glVertex3f(-140, 0, 200);
    glVertex3f(-140, 50, 200);
    glVertex3f(-120, 0, 200);
    glVertex3f(-120, 50, 200);
    glVertex3f(-100, 0, 200);
    glVertex3f(-100, 50, 200);
    glVertex3f(-80, 0, 200);
    glVertex3f(-80, 50, 200);
    glVertex3f(-60, 50, 200);
    glVertex3f(-60, 50, 200);
    glVertex3f(-60, 0, 200);
    glVertex3f(-60, 50, 200);
    glVertex3f(-40, 0, 200);
    glVertex3f(-40, 50, 200);
    glVertex3f(-20, 0, 200);
    glVertex3f(-20, 50, 200);
    glVertex3f(-0, 0, 200);
    glVertex3f(-0, 50, 200);
    glVertex3f(20, 0, 200);
    glVertex3f(20, 50, 200);
    glVertex3f(40, 0, 200);
    glVertex3f(40, 50, 200);
    glVertex3f(60, 0, 200);
    glVertex3f(60, 50, 200);
    glVertex3f(80, 0, 200);
    glVertex3f(80, 50, 200);
    glVertex3f(100, 0, 200);
    glVertex3f(100, 50, 200);
    glVertex3f(120, 0, 200);
    glVertex3f(120, 50, 200);
    glVertex3f(140, 0, 200);
    glVertex3f(140, 50, 200);
    glVertex3f(160, 0, 200);
    glVertex3f(160, 50, 200);
    glVertex3f(180, 0, 200);
    glVertex3f(180, 50, 200);
    glVertex3f(200, 0, 200);
    glVertex3f(200, 50, 200);
    glVertex3f(220, 0, 200);
    glVertex3f(220, 50, 200);
    glVertex3f(240, 0, 200);
    glVertex3f(240, 50, 200);
    glVertex3f(260, 0, 200);
    glVertex3f(260, 50, 200);
    glVertex3f(280, 0, 200);
    glVertex3f(280, 50, 200);
    glEnd();

    //Kiri
    glBegin(GL_LINE_LOOP);
    glVertex3f(-200, 50, -200);
    glVertex3f(-200, 0, -200);
    glVertex3f(-200, 0, 200);
    glVertex3f(-200, 50, 200);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(300, 0, -180);
    glVertex3f(300, 50, -180);
    glVertex3f(300, 0, -160);
    glVertex3f(300, 50, -160);
    glVertex3f(300, 0, -140);
    glVertex3f(300, 50, -140);
    glVertex3f(300, 0, -120);
    glVertex3f(300, 50, -120);
    glVertex3f(300, 0, -100);
    glVertex3f(300, 50, -100);
    glVertex3f(300, 0, -80);
    glVertex3f(300, 50, -80);
    glVertex3f(300, 0, -60);
    glVertex3f(300, 50, -60);
    glVertex3f(300, 0, -60);
    glVertex3f(300, 50, -60);
    glVertex3f(300, 0, -40);
    glVertex3f(300, 50, -40);
    glVertex3f(300, 0, -20);
    glVertex3f(300, 50, -20);
    glVertex3f(300, 0, -0);
    glVertex3f(300, 50, -0);
    glVertex3f(300, 0, 200);
    glVertex3f(300, 50, 200);
    glVertex3f(300, 0, 180);
    glVertex3f(300, 50, 180);
    glVertex3f(300, 0, 160);
    glVertex3f(300, 50, 160);
    glVertex3f(300, 0, 140);
    glVertex3f(300, 50, 140);
    glVertex3f(300, 0, 120);
    glVertex3f(300, 50, 120);
    glVertex3f(300, 0, 100);
    glVertex3f(300, 50, 100);
    glVertex3f(300, 0, 80);
    glVertex3f(300, 50, 80);
    glVertex3f(300, 0, 60);
    glVertex3f(300, 50, 60);
    glVertex3f(300, 0, 40);
    glVertex3f(300, 50, 40);
    glVertex3f(300, 0, 20);
    glVertex3f(300, 50, 20);
    glEnd();

    //Kanan
    glBegin(GL_LINE_LOOP);
    glVertex3f(300, 50, -200);
    glVertex3f(300, 0, -200);
    glVertex3f(300, 0, 200);
    glVertex3f(300, 50, 200);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(-200, 0, -180);
    glVertex3f(-200, 50, -180);
    glVertex3f(-200, 0, -160);
    glVertex3f(-200, 50, -160);
    glVertex3f(-200, 0, -140);
    glVertex3f(-200, 50, -140);
    glVertex3f(-200, 0, -120);
    glVertex3f(-200, 50, -120);
    glVertex3f(-200, 0, -100);
    glVertex3f(-200, 50, -100);
    glVertex3f(-200, 0, -80);
    glVertex3f(-200, 50, -80);
    glVertex3f(-200, 0, -60);
    glVertex3f(-200, 50, -60);
    glVertex3f(-200, 0, -60);
    glVertex3f(-200, 50, -60);
    glVertex3f(-200, 0, -40);
    glVertex3f(-200, 50, -40);
    glVertex3f(-200, 0, -20);
    glVertex3f(-200, 50, -20);
    glVertex3f(-200, 0, -0);
    glVertex3f(-200, 50, -0);
    glVertex3f(-200, 0, 200);
    glVertex3f(-200, 50, 200);
    glVertex3f(-200, 0, 180);
    glVertex3f(-200, 50, 180);
    glVertex3f(-200, 0, 160);
    glVertex3f(-200, 50, 160);
    glVertex3f(-200, 0, 140);
    glVertex3f(-200, 50, 140);
    glVertex3f(-200, 0, 120);
    glVertex3f(-200, 50, 120);
    glVertex3f(-200, 0, 100);
    glVertex3f(-200, 50, 100);
    glVertex3f(-200, 0, 80);
    glVertex3f(-200, 50, 80);
    glVertex3f(-200, 0, 60);
    glVertex3f(-200, 50, 60);
    glVertex3f(-200, 0, 40);
    glVertex3f(-200, 50, 40);
    glVertex3f(-200, 0, 20);
    glVertex3f(-200, 50, 20);
    glEnd();
}

void pagar_lantai3() {
    //belakang
    glBegin(GL_LINE_LOOP);
    glVertex3f(-120, 0, -180);
    glVertex3f(-120, 50, -180);
    glVertex3f(240, 50, -180);
    glVertex3f(240, 0, -180);
    glEnd();
    glBegin(GL_LINES);

    glVertex3f(-100, 0, -180);
    glVertex3f(-100, 50, -180);
    glVertex3f(-80, 0, -180);
    glVertex3f(-80, 50, -180);
    glVertex3f(-60, 50, -180);
    glVertex3f(-60, 50, -180);
    glVertex3f(-60, 0, -180);
    glVertex3f(-60, 50, -180);
    glVertex3f(-40, 0, -180);
    glVertex3f(-40, 50, -180);
    glVertex3f(-20, 0, -180);
    glVertex3f(-20, 50, -180);
    glVertex3f(-0, 0, -180);
    glVertex3f(-0, 50, -180);
    glVertex3f(20, 0, -180);
    glVertex3f(20, 50, -180);
    glVertex3f(40, 0, -180);
    glVertex3f(40, 50, -180);
    glVertex3f(60, 0, -180);
    glVertex3f(60, 50, -180);
    glVertex3f(80, 0, -180);
    glVertex3f(80, 50, -180);
    glVertex3f(100, 0, -180);
    glVertex3f(100, 50, -180);
    glVertex3f(120, 0, -180);
    glVertex3f(120, 50, -180);
    glVertex3f(140, 0, -180);
    glVertex3f(140, 50, -180);
    glVertex3f(160, 0, -180);
    glVertex3f(160, 50, -180);
    glVertex3f(180, 0, -180);
    glVertex3f(180, 50, -180);
    glVertex3f(200, 0, -180);
    glVertex3f(200, 50, -180);
    glVertex3f(220, 0, -180);
    glVertex3f(220, 50, -180);


    glEnd();

    //depan
    glBegin(GL_LINE_LOOP);
    glVertex3f(-120, 0, 180);
    glVertex3f(-120, 50, 180);
    glVertex3f(240, 50, 180);
    glVertex3f(240, 0, 180);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(-120, 0, 180);
    glVertex3f(-120, 25, 180);
    glVertex3f(240, 25, 180);
    glVertex3f(240, 0, 180);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(-120, 0, 180);
    glVertex3f(-120, 50, 180);
    glVertex3f(-100, 0, 180);
    glVertex3f(-100, 50, 180);
    glVertex3f(-80, 0, 180);
    glVertex3f(-80, 50, 180);
    glVertex3f(-60, 50, 180);
    glVertex3f(-60, 50, 180);
    glVertex3f(-60, 0, 180);
    glVertex3f(-60, 50, 180);
    glVertex3f(-40, 0, 180);
    glVertex3f(-40, 50, 180);
    glVertex3f(-20, 0, 180);
    glVertex3f(-20, 50, 180);
    glVertex3f(-0, 0, 180);
    glVertex3f(-0, 50, 180);
    glVertex3f(20, 0, 180);
    glVertex3f(20, 50, 180);
    glVertex3f(40, 0, 180);
    glVertex3f(40, 50, 180);
    glVertex3f(60, 0, 180);
    glVertex3f(60, 50, 180);
    glVertex3f(80, 0, 180);
    glVertex3f(80, 50, 180);
    glVertex3f(100, 0, 180);
    glVertex3f(100, 50, 180);
    glVertex3f(120, 0, 180);
    glVertex3f(120, 50, 180);
    glVertex3f(140, 0, 180);
    glVertex3f(140, 50, 180);
    glVertex3f(160, 0, 180);
    glVertex3f(160, 50, 180);
    glVertex3f(180, 0, 180);
    glVertex3f(180, 50, 180);
    glVertex3f(200, 0, 180);
    glVertex3f(200, 50, 180);
    glVertex3f(220, 0, 180);
    glVertex3f(220, 50, 180);

    glEnd();



    //Kiri
       //Kanan
    glBegin(GL_LINE_LOOP);
    glVertex3f(240, 50, -180);
    glVertex3f(240, 0, -180);
    glVertex3f(240, 0, 180);
    glVertex3f(240, 50, 180);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(240, 0, -160);
    glVertex3f(240, 50, -160);
    glVertex3f(240, 0, -140);
    glVertex3f(240, 50, -140);
    glVertex3f(240, 0, -120);
    glVertex3f(240, 50, -120);
    glVertex3f(240, 0, -100);
    glVertex3f(240, 50, -100);
    glVertex3f(240, 0, -80);
    glVertex3f(240, 50, -80);
    glVertex3f(240, 0, -60);
    glVertex3f(240, 50, -60);
    glVertex3f(240, 0, -60);
    glVertex3f(240, 50, -60);
    glVertex3f(240, 0, -40);
    glVertex3f(240, 50, -40);
    glVertex3f(240, 0, -20);
    glVertex3f(240, 50, -20);
    glVertex3f(240, 0, -0);
    glVertex3f(240, 50, -0);
    glVertex3f(240, 0, 180);
    glVertex3f(240, 50, 180);
    glVertex3f(240, 0, 160);
    glVertex3f(240, 50, 160);
    glVertex3f(240, 0, 140);
    glVertex3f(240, 50, 140);
    glVertex3f(240, 0, 120);
    glVertex3f(240, 50, 120);
    glVertex3f(240, 0, 100);
    glVertex3f(240, 50, 100);
    glVertex3f(240, 0, 80);
    glVertex3f(240, 50, 80);
    glVertex3f(240, 0, 60);
    glVertex3f(240, 50, 60);
    glVertex3f(240, 0, 40);
    glVertex3f(240, 50, 40);
    glVertex3f(240, 0, 20);
    glVertex3f(240, 50, 20);
    glEnd();

    //Kiri
    glBegin(GL_LINE_LOOP);
    glVertex3f(-120, 50, -180);
    glVertex3f(-120, 0, -180);
    glVertex3f(-120, 0, 180);
    glVertex3f(-120, 50, 180);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(-120, 0, -160);
    glVertex3f(-120, 50, -160);
    glVertex3f(-120, 0, -140);
    glVertex3f(-120, 50, -140);
    glVertex3f(-120, 0, -120);
    glVertex3f(-120, 50, -120);
    glVertex3f(-120, 0, -100);
    glVertex3f(-120, 50, -100);
    glVertex3f(-120, 0, -80);
    glVertex3f(-120, 50, -80);
    glVertex3f(-120, 0, -60);
    glVertex3f(-120, 50, -60);
    glVertex3f(-120, 0, -60);
    glVertex3f(-120, 50, -60);
    glVertex3f(-120, 0, -40);
    glVertex3f(-120, 50, -40);
    glVertex3f(-120, 0, -20);
    glVertex3f(-120, 50, -20);
    glVertex3f(-120, 0, -0);
    glVertex3f(-120, 50, -0);
    glVertex3f(-120, 0, 160);
    glVertex3f(-120, 50, 160);
    glVertex3f(-120, 0, 140);
    glVertex3f(-120, 50, 140);
    glVertex3f(-120, 0, 120);
    glVertex3f(-120, 50, 120);
    glVertex3f(-120, 0, 100);
    glVertex3f(-120, 50, 100);
    glVertex3f(-120, 0, 80);
    glVertex3f(-120, 50, 80);
    glVertex3f(-120, 0, 60);
    glVertex3f(-120, 50, 60);
    glVertex3f(-120, 0, 40);
    glVertex3f(-120, 50, 40);
    glVertex3f(-120, 0, 20);
    glVertex3f(-120, 50, 20);
    glEnd();
}
void pagar_lantai4() {
    //belakang
    glBegin(GL_LINE_LOOP);
    glVertex3f(-120, 0, -180);
    glVertex3f(-120, 50, -180);
    glVertex3f(240, 50, -180);
    glVertex3f(240, 0, -180);
    glEnd();
    glBegin(GL_LINES);

    glVertex3f(-100, 0, -180);
    glVertex3f(-100, 50, -180);
    glVertex3f(-80, 0, -180);
    glVertex3f(-80, 50, -180);
    glVertex3f(-60, 50, -180);
    glVertex3f(-60, 50, -180);
    glVertex3f(-60, 0, -180);
    glVertex3f(-60, 50, -180);
    glVertex3f(-40, 0, -180);
    glVertex3f(-40, 50, -180);
    glVertex3f(-20, 0, -180);
    glVertex3f(-20, 50, -180);
    glVertex3f(-0, 0, -180);
    glVertex3f(-0, 50, -180);
    glVertex3f(20, 0, -180);
    glVertex3f(20, 50, -180);
    glVertex3f(40, 0, -180);
    glVertex3f(40, 50, -180);
    glVertex3f(60, 0, -180);
    glVertex3f(60, 50, -180);
    glVertex3f(80, 0, -180);
    glVertex3f(80, 50, -180);
    glVertex3f(100, 0, -180);
    glVertex3f(100, 50, -180);
    glVertex3f(120, 0, -180);
    glVertex3f(120, 50, -180);
    glVertex3f(140, 0, -180);
    glVertex3f(140, 50, -180);
    glVertex3f(160, 0, -180);
    glVertex3f(160, 50, -180);
    glVertex3f(180, 0, -180);
    glVertex3f(180, 50, -180);
    glVertex3f(200, 0, -180);
    glVertex3f(200, 50, -180);
    glVertex3f(220, 0, -180);
    glVertex3f(220, 50, -180);


    glEnd();

    //depan
    glBegin(GL_LINE_LOOP);
    glVertex3f(-120, 0, 180);
    glVertex3f(-120, 50, 180);
    glVertex3f(240, 50, 180);
    glVertex3f(240, 0, 180);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(-120, 0, 180);
    glVertex3f(-120, 25, 180);
    glVertex3f(240, 25, 180);
    glVertex3f(240, 0, 180);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(-120, 0, 180);
    glVertex3f(-120, 50, 180);
    glVertex3f(-100, 0, 180);
    glVertex3f(-100, 50, 180);
    glVertex3f(-80, 0, 180);
    glVertex3f(-80, 50, 180);
    glVertex3f(-60, 50, 180);
    glVertex3f(-60, 50, 180);
    glVertex3f(-60, 0, 180);
    glVertex3f(-60, 50, 180);
    glVertex3f(-40, 0, 180);
    glVertex3f(-40, 50, 180);
    glVertex3f(-20, 0, 180);
    glVertex3f(-20, 50, 180);
    glVertex3f(-0, 0, 180);
    glVertex3f(-0, 50, 180);
    glVertex3f(20, 0, 180);
    glVertex3f(20, 50, 180);
    glVertex3f(40, 0, 180);
    glVertex3f(40, 50, 180);
    glVertex3f(60, 0, 180);
    glVertex3f(60, 50, 180);
    glVertex3f(80, 0, 180);
    glVertex3f(80, 50, 180);
    glVertex3f(100, 0, 180);
    glVertex3f(100, 50, 180);
    glVertex3f(120, 0, 180);
    glVertex3f(120, 50, 180);
    glVertex3f(140, 0, 180);
    glVertex3f(140, 50, 180);
    glVertex3f(160, 0, 180);
    glVertex3f(160, 50, 180);
    glVertex3f(180, 0, 180);
    glVertex3f(180, 50, 180);
    glVertex3f(200, 0, 180);
    glVertex3f(200, 50, 180);
    glVertex3f(220, 0, 180);
    glVertex3f(220, 50, 180);

    glEnd();



    //Kiri
       //Kanan
    glBegin(GL_LINE_LOOP);
    glVertex3f(240, 50, -180);
    glVertex3f(240, 0, -180);
    glVertex3f(240, 0, 180);
    glVertex3f(240, 50, 180);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(240, 0, -160);
    glVertex3f(240, 50, -160);
    glVertex3f(240, 0, -140);
    glVertex3f(240, 50, -140);
    glVertex3f(240, 0, -120);
    glVertex3f(240, 50, -120);
    glVertex3f(240, 0, -100);
    glVertex3f(240, 50, -100);
    glVertex3f(240, 0, -80);
    glVertex3f(240, 50, -80);
    glVertex3f(240, 0, -60);
    glVertex3f(240, 50, -60);
    glVertex3f(240, 0, -60);
    glVertex3f(240, 50, -60);
    glVertex3f(240, 0, -40);
    glVertex3f(240, 50, -40);
    glVertex3f(240, 0, -20);
    glVertex3f(240, 50, -20);
    glVertex3f(240, 0, -0);
    glVertex3f(240, 50, -0);
    glVertex3f(240, 0, 180);
    glVertex3f(240, 50, 180);
    glVertex3f(240, 0, 160);
    glVertex3f(240, 50, 160);
    glVertex3f(240, 0, 140);
    glVertex3f(240, 50, 140);
    glVertex3f(240, 0, 120);
    glVertex3f(240, 50, 120);
    glVertex3f(240, 0, 100);
    glVertex3f(240, 50, 100);
    glVertex3f(240, 0, 80);
    glVertex3f(240, 50, 80);
    glVertex3f(240, 0, 60);
    glVertex3f(240, 50, 60);
    glVertex3f(240, 0, 40);
    glVertex3f(240, 50, 40);
    glVertex3f(240, 0, 20);
    glVertex3f(240, 50, 20);
    glEnd();

    //Kiri
    glBegin(GL_LINE_LOOP);
    glVertex3f(-120, 50, -180);
    glVertex3f(-120, 0, -180);
    glVertex3f(-120, 0, 180);
    glVertex3f(-120, 50, 180);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(-120, 0, -160);
    glVertex3f(-120, 50, -160);
    glVertex3f(-120, 0, -140);
    glVertex3f(-120, 50, -140);
    glVertex3f(-120, 0, -120);
    glVertex3f(-120, 50, -120);
    glVertex3f(-120, 0, -100);
    glVertex3f(-120, 50, -100);
    glVertex3f(-120, 0, -80);
    glVertex3f(-120, 50, -80);
    glVertex3f(-120, 0, -60);
    glVertex3f(-120, 50, -60);
    glVertex3f(-120, 0, -60);
    glVertex3f(-120, 50, -60);
    glVertex3f(-120, 0, -40);
    glVertex3f(-120, 50, -40);
    glVertex3f(-120, 0, -20);
    glVertex3f(-120, 50, -20);
    glVertex3f(-120, 0, -0);
    glVertex3f(-120, 50, -0);
    glVertex3f(-120, 0, 160);
    glVertex3f(-120, 50, 160);
    glVertex3f(-120, 0, 140);
    glVertex3f(-120, 50, 140);
    glVertex3f(-120, 0, 120);
    glVertex3f(-120, 50, 120);
    glVertex3f(-120, 0, 100);
    glVertex3f(-120, 50, 100);
    glVertex3f(-120, 0, 80);
    glVertex3f(-120, 50, 80);
    glVertex3f(-120, 0, 60);
    glVertex3f(-120, 50, 60);
    glVertex3f(-120, 0, 40);
    glVertex3f(-120, 50, 40);
    glVertex3f(-120, 0, 20);
    glVertex3f(-120, 50, 20);
    glEnd();
}



void tiang_kiri_depanL1() {
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(-140, 150, 140);
    glRotatef(90.0, 1200, -90, 120);
    gluCylinder(gluNewQuadric(), 2.0f, 2.0f, 150.0f, 700, 700);
    glPopMatrix();
}
void tiang_kanan_depanL1() {
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(340, 150, 140);
    glRotatef(90.0, 1200, -90, 120);
    gluCylinder(gluNewQuadric(), 2.0f, 2.0f, 150.0f, 700, 700);
    glPopMatrix();
}
void tiang_kanan_sampingL1() {
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(340, 150, -240);
    glRotatef(90.0, 1200, -90, 120);
    gluCylinder(gluNewQuadric(), 2.0f, 2.0f, 150.0f, 700, 700);
    glPopMatrix();
}
void tiang_kiri_sampingL1() {
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(-140, 150, -240);
    glRotatef(90.0, 1200, -90, 120);
    gluCylinder(gluNewQuadric(), 2.0f, 2.0f, 150.0f, 700, 700);
    glPopMatrix();
}


void tiang_kiri_depanL2() {
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(-140, 150, 140);
    glRotatef(90.0, 1200, -90, 120);
    gluCylinder(gluNewQuadric(), 2.0f, 2.0f, 150.0f, 700, 700);
    glPopMatrix();
}
void tiang_kanan_depanL2() {
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(340, 150, 140);
    glRotatef(90.0, 1200, -90, 120);
    gluCylinder(gluNewQuadric(), 2.0f, 2.0f, 150.0f, 700, 700);
    glPopMatrix();
}
void tiang_kanan_sampingL2() {
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(340, 150, -240);
    glRotatef(90.0, 1200, -90, 120);
    gluCylinder(gluNewQuadric(), 2.0f, 2.0f, 150.0f, 700, 700);
    glPopMatrix();
}
void tiang_kiri_sampingL2() {
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(-140, 150, -240);
    glRotatef(90.0, 1200, -90, 120);
    gluCylinder(gluNewQuadric(), 2.0f, 2.0f, 150.0f, 700, 700);
    glPopMatrix();
}
void pintuL1() {
    glPushMatrix();
    glTranslatef(180, 60, 41);
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    glVertex3f(-20, 0, 0);
    glVertex3f(60, 0, 0);
    glVertex3f(60, 120, 0);
    glVertex3f(-20, 120, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(230, 120, 41);
    glutSolidSphere(5.0, 50, 50);
    glPopMatrix();

}
void pintuL2() {
    glPushMatrix();
    glTranslatef(185, 210, 41);
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    glVertex3f(-20, 0, 0);
    glVertex3f(40, 0, 0);
    glVertex3f(40, 120, 0);
    glVertex3f(-20, 120, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(215, 280, 41);
    glutSolidSphere(5.0, 50, 50);
    glPopMatrix();

}
void pintuL3() {
    glPushMatrix();
    glTranslatef(185, 410, 41);
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    glVertex3f(-20, 20, 0);
    glVertex3f(40, 20, 0);
    glVertex3f(40, 140, 0);
    glVertex3f(-20, 140, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(215, 480, 41);
    glutSolidSphere(5.0, 50, 50);
    glPopMatrix();

}
void pintuL4() {
    glPushMatrix();
    glTranslatef(190, 630, 41);
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    glVertex3f(-20, 0, 0);
    glVertex3f(40, 0, 0);
    glVertex3f(40, 140, 0);
    glVertex3f(-20, 140, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(215, 700, 41);
    glutSolidSphere(5.0, 50, 50);
    glPopMatrix();
}

void draw() {
    //turunan
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(100, 60, -30);
    turunan();
    glPopMatrix();

    //dasar
    glPushMatrix();
    glColor3f(0.28, 0.16, 0.12);
    glTranslatef(100, 10, -30);
    dasar();
    glPopMatrix();

    //Lantai 1
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(100, 60, -30);
    lantai1();
    glPopMatrix();

    //Lantai 2
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(100, 210, -30);
    lantai2();
    glPopMatrix();

    //lantai3
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(100, 410, -30);
    lantai3();
    glPopMatrix();

    //Lantaiduduk3
    glPushMatrix();
    glColor3f(0.91, 0.85, 0.85);
    glTranslatef(100, 380, -30);
    lantaiduduk3();
    glPopMatrix();

    //lantai4
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(100, 610, -30);
    lantai4();
    glPopMatrix();

    //Lantaiduduk4
    glPushMatrix();
    glColor3f(0.91, 0.85, 0.85);
    glTranslatef(100, 580, -30);
    lantaiduduk3();
    glPopMatrix();

    //pagar lantai1
    glPushMatrix();
    glColor3f(0.01, 0.03, 0.17);
    glTranslatef(150, 60, -80);
    pagar_lantai1();
    glPopMatrix();

    //pagar Lantai2
    glPushMatrix();
    glColor3f(0.9, 0.58, 0.02);
    glTranslatef(150, 210, -80);
    pagar_lantai2();
    glPopMatrix();

    //pagar Lantai3
    glPushMatrix();
    glColor3f(0.9, 0.58, 0.02);
    glTranslatef(140, 430, -70);
    pagar_lantai3();
    glPopMatrix();

    //pagar lantai4
    glPushMatrix();
    glColor3f(0.9, 0.58, 0.02);
    glTranslatef(140, 630, -70);
    pagar_lantai4();
    glPopMatrix();

    //atap1
    glPushMatrix();
    glColor3f(0.91, 0.85, 0.85);
    glTranslatef(100, 160, -30);
    atap1();
    glPopMatrix();

    //atap2
    glPushMatrix();
    glColor3f(0.1, 0.52, 0.7);
    glTranslatef(100, 360, -30);
    atap2();
    glPopMatrix();

    //atap2a
    glPushMatrix();
    glColor3f(0.1, 0.52, 0.7);
    glTranslatef(100, 310, -30);
    atap2a();
    glPopMatrix();

    //atap3
    glPushMatrix();
    glColor3f(0.1, 0.52, 0.7);
    glTranslatef(100, 560, -30);
    atap3();
    glPopMatrix();

    //atap3a
    glPushMatrix();
    glColor3f(0.1, 0.52, 0.7);
    glTranslatef(100, 510, -30);
    atap3a();
    glPopMatrix();

    //atap4
    glPushMatrix();
    glColor3f(0.49, 0.24, 0.24);
    glTranslatef(100, 760, -30);
    atap4();
    glPopMatrix();


    //Tiang kiri depan L1
    glPushMatrix();
    glTranslatef(180, 60, -40);
    tiang_kiri_depanL1();
    glPopMatrix();

    //tiang kanan depan L1
    glPushMatrix();
    glTranslatef(0, 60, -40);
    tiang_kanan_depanL1();
    glPopMatrix();

    //tiang kanan samping L1
    glPushMatrix();
    glTranslatef(90, 60, 160);
    tiang_kanan_sampingL1();
    glPopMatrix();

    //tiang kiri belakang L1
    glPushMatrix();
    glTranslatef(100, 60, 160);
    tiang_kiri_sampingL1();
    glPopMatrix();


    //Tiang kiri depan L2
    glPushMatrix();
    glTranslatef(230, 210, -30);
    tiang_kiri_depanL2();
    glPopMatrix();

    //Tiang kanan depan L2
    glPushMatrix();
    glTranslatef(-50, 210, -30);
    tiang_kanan_depanL2();
    glPopMatrix();

    //Tiang samping kanan L2
    glPushMatrix();
    glTranslatef(100, 210, 160);
    tiang_kanan_sampingL2();
    glPopMatrix();

    //Tiang samping kiri L2
    glPushMatrix();
    glTranslatef(90, 210, 160);
    tiang_kiri_sampingL2();
    glPopMatrix();

    //Pintu
    pintuL1();
    pintuL2();
    pintuL3();
    pintuL4();
    ground();
    cout << "X_GESER = " << x_geser << " Y_GESER = " << y_geser << " Z_GESER = " << z_geser << endl;

    glFlush();

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera();
    draw();

    glutSwapBuffers();

    ground();

}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 16.0 / 9.0, 2, 10000);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    glutPostRedisplay();
    glutWarpPointer(width / 2, height / 2);
    glutTimerFunc(1000 / FPS, timer, 0);
}

void passive_motion(int x, int y) {
    int dev_x, dev_y;
    dev_x = (width / 2) - x;
    dev_y = (height / 2) - y;
    yaw += (float)dev_x / 20.0;
    pitch += (float)dev_y / 20.0;
}

void camera() {
    if (motion.Forward) {
        camX += cos((yaw + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90) * TO_RADIANS) * 2;
    }
    if (motion.Backward) {
        camX += cos((yaw + 90 + 180) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 180) * TO_RADIANS) * 2;
    }
    if (motion.Left) {
        camX += cos((yaw + 90 + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 90) * TO_RADIANS) * 2;
    }
    if (motion.Right) {
        camX += cos((yaw + 90 - 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 - 90) * TO_RADIANS) * 2;
    }
    if (motion.Naik) {
        terbang -= 2.0;
    }
    if (motion.Turun) {
        terbang += 2.0;
    }

    if (pitch >= 70)
        pitch = 70;
    if (pitch <= -90)
        pitch = -90;


    glRotatef(-pitch, 1.0, 0.0, 0.0);
    glRotatef(-yaw, 0.0, 1.0, 0.0);

    glTranslatef(-camX, -terbang, -350 - camZ);
    if (terbang < 25)
        terbang = 24;
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = true;
        break;
    case 'A':
    case 'a':
        motion.Left = true;
        break;
    case 'S':
    case 's':
        motion.Backward = true;
        break;
    case 'D':
    case 'd':
        motion.Right = true;
        break;
    case 'E':
    case 'e':
        motion.Naik = true;
        break;
    case 'Q':
    case 'q':
        motion.Turun = true;
        break;
    case '6':
        x_geser += 10.0;
        break;
    case '4':
        x_geser -= 10.0;
        break;
    case '8':
        y_geser += 10.0;
        break;
    case '2':
        y_geser -= 10.0;
        break;
    case '9':
        z_geser -= 10.0;
        break;
    case '1':
        z_geser += 10.0;
        break;
    case '`': // KELUAR DARI PROGRAM
        exit(1);
    }
}

void keyboard_up(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = false;
        break;
    case 'A':
    case 'a':
        motion.Left = false;
        break;
    case 'S':
    case 's':
        motion.Backward = false;
        break;
    case 'D':
    case 'd':
        motion.Right = false;
        break;
    case 'E':
    case 'e':
        motion.Naik = false;
        break;
    case 'Q':
    case 'q':
        motion.Turun = false;
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("TR GRAFKOM KELOMPOK 7");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
