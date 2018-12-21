#include "Universe.h"
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#define PI 3.14159265
using namespace std;
static float g = 0;
Universe uni;
double alpha =PI/90;
static float normalx=0, normaly=1, normalz=0;
static float posx=0.0f,posz=-1800.0f,posy=-500.0f;
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	GLfloat fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
    gluPerspective(35.0f, fAspect, 1.0, 10000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}
void timer(int value) {
  uni.update(0.001);
  glutPostRedisplay();
  glutTimerFunc(0.01, timer, 1);
}

void setup()
{   
    uni.file_read("./nbodys.txt");
	GLfloat  ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat  diffuseLight[] = {0.3, 0.3f, 0.3f, 1.0f };
    GLfloat  specular[] = { 0.9f, 0.9f, 0.9f, 1.0f};
    GLfloat  lightPos[] = { 500.0f, 500.0f, 30.0f, 1.0f };
    GLfloat  specref[] =  { 0.9f, 0.9f, 0.9f, 1.0f };
        glEnable(GL_DEPTH_TEST);    // Hidden surface removal
        glEnable(GL_CULL_FACE);        // Do not calculate inside of solid object
        glFrontFace(GL_CCW);

       // Enable lighting
       glEnable(GL_LIGHTING);

    // Setup light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);

//    Position and turn on the light
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);

//    Enable color tracking

    glEnable(GL_COLOR_MATERIAL);

//    Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

//    All materials hereafter have full specular reflectivity
 //   with a moderate shine
    glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
    glMateriali(GL_FRONT,GL_SHININESS,64);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
void draw_body(Body x, int i){
    glPushMatrix();
    glTranslatef(x.posision_x, x.posision_y, 0);
    float s = 255;
    switch(i){
        case 0:
            glColor3f(236.0/s, 247/s, 139/s);
            glutSolidSphere(20,50,50);
        break;
        case 1:
            glColor3f(150/s, 247/s, 139/s);
            glutSolidSphere(10,50,50);
        break;
        case 2:
            glColor3f(30/s, 158/s, 158/s);
            glutSolidSphere(10,50,50);
        break;
        case 3:
            glColor3f(30/s, 90/s, 158/s);
            glutSolidSphere(10,50,50);
        break;
        case 4:
            glColor3f(158/s, 30/s, 128/s);
            glutSolidSphere(10,50,50);
        break;
        case 5:
            glColor3f(222, 0, 0);
            glutSolidSphere(8,50,50);
        break;
        case 6:
            glColor3f(18/s, 200/s, 0);
            glutSolidSphere(4,50,50);
        break;
    }
    
    glPopMatrix();
}
void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
    gluLookAt(	posx+500, posy+500, posz,
			500, 500, 0,
			normalx, normaly, normalz); 

    for(int i=0; i < 7; i++){
       draw_body(uni.planet[i], i);
    }
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(100,0);
    glutCreateWindow("Universe");   
    glutReshapeFunc(resize);
    glutDisplayFunc(myDisplay);
    setup();
    glutTimerFunc(33, timer, 1);
    glutMainLoop();
    return 0;
}