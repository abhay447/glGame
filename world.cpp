#include <iostream>
#include <thread>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#include "map_loader.h"
#include "wallCollider.cpp"
#include "controls.h"
#include "sounds.h"
#include "texture_loader.h"
#include "textCoordLoader.h"

using namespace std;

GLfloat posx=850.0,posz=996.0;
GLfloat tempx=850.0,tempz=1000.0;
GLfloat visibility=100.0;
GLfloat step_length=0.4;
GLfloat pRotationz=0;
bool* keyStates = new bool[256];

levelMap myMap;

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	myMap.loadCoordinates();
	myMap.loadVertices();	
	cout<<myMap.vertices[20];
	
	GLuint texture = LoadTexture("images/Dungeon_wall1.bmp");
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, texture);
    load_texCoords();
}

void display(void)
{
	move();
	glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	//glColor3f(0.3,0.3,0.3);
	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, &textureCoordinates[0]);
	glVertexPointer (3, GL_FLOAT, 0, &myMap.coords[0]);
	glLoadIdentity ();
	gluLookAt (posx, 10.0, posz, posx*(1-sin(pRotationz)), 10.0, posz*(1-cos(pRotationz)), 0.0, 1.0, 0.0);
	glDrawElements(GL_QUADS, myMap.vertices.size(), GL_UNSIGNED_BYTE, &myMap.vertices[0]);
	glutWarpPointer(1365/2,767/2);
	glutSwapBuffers();
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
	glutInitWindowSize (1365, 767);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("Beat the maze");
	init ();
	glutFullScreen();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(Rotate);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	initializeKeyboard();
	thread sound(backgroundMusic);
	glutMainLoop();
	sound.join();
	return 0;
}
