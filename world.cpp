#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#include "map_loader.h"
#include "wallCollider.cpp"

#include <iostream>
using namespace std;

GLfloat posx=850.0,posz=1000.0;
GLfloat tempx=850.0,tempz=1000.0;
GLfloat visibility=100.0;
GLfloat step_length=3.0;
GLfloat pRotationz=0;
levelMap myMap;

void init(void)
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	myMap.loadCoordinates();
	myMap.loadVertices();	
	cout<<myMap.vertices[20];
}

void Rotate(int x,int y){
	
	pRotationz += 0.01*(-x+1364.0/2.0);
	glutPostRedisplay();
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glColor3f(0.3,0.3,0.3);
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer (3, GL_INT, 0, &myMap.coords[0]);
	glLoadIdentity ();
	gluLookAt (posx, 10.0, posz, posx*(1-sin(pRotationz)), 10.0, posz*(1-cos(pRotationz)), 0.0, 1.0, 0.0);
	static GLint allIndices[]={0,1,5,4,4,5,7,6,8,9,11,10,10,11,13,12,12,13,19,18};	
	glDrawElements(GL_QUADS, myMap.vertices.size(), GL_UNSIGNED_BYTE, &myMap.vertices[0]);
	glutWarpPointer(1364/2,742/2);
	glutSwapBuffers();
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 'w':
			tempz=posz-step_length*cos(pRotationz);
			tempx=posx-step_length*sin(pRotationz);
			break;
		case 'a':
			tempz=posz+step_length*sin(pRotationz);
			tempx=posx-step_length*cos(pRotationz);
			break;
		case 's':
			tempz=posz+step_length*cos(pRotationz);
			tempx=posx+step_length*sin(pRotationz);
			break;
		case 'd':
			tempz=posz-step_length*sin(pRotationz);
			tempx=posx+step_length*cos(pRotationz);
			break;
		
		default:
			break;
	}
	collide();
	glutPostRedisplay();
}

void reshape (int w, int h)
{
	GLfloat aspect=(GLfloat)w/(GLfloat)h;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(45,(GLdouble)w/h,1,3000);
	glMatrixMode (GL_MODELVIEW);
}


int main(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize (1364, 742);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("Test Map");
	init ();
	glutFullScreen();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(Rotate);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
