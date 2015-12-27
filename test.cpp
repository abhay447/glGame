#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#include <iostream>
using namespace std;

GLfloat posx=50.0,posz=250.0;
GLfloat visibility=100.0;
GLfloat step_length=10.0;
GLfloat pRotationz=0;

void init(void)
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glClearDepth(1.0);
	glShadeModel (GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);

}

void Rotate(int x,int y){
	
	pRotationz += 0.01*(-x+1364.0/2.0);
	cout<<x<<","<<y<<endl;
	glutPostRedisplay();
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	static GLint vertices[] = {0,0,0,
		100, 0, 0,
		100, 100, 0,
		0, 100, 0,
		0, 0, 100,
		100, 0, 100,
		100, 100, 100,
		0, 100, 100 ,
		//side limb
		100, 0, 0,
		200, 0 ,0,
		200, 100, 0,
		100, 100, 0,
		100, 0, 50,
		200, 0 ,50,
		200, 100, 50,
		100, 100, 50,
		};
		
	static GLfloat colors[] = {1.0, 0.2, 0.2,
		0.2, 0.2, 1.0,
		0.8, 1.0, 0.2,
		0.5, 0.75, 0.075,
		0.035, 0.35, 0.35,
		1.0, 0.0, 1.0,
		0.5, 0.5, 0.5,
		0.0, 0.4, 0.0,
		//second limb
		0.2, 0.2, 1.0,
		1.0, 0.8, 0.4,
		0.8, 1.0, 0.2,
		0.75, 0.75, 0.075,
		0.035, 0.35, 0.35,
		1.0, 0.0, 1.0,
		0.5, 0.5, 0.5,
		0.0, 0.4, 0.0};
	glEnableClientState (GL_COLOR_ARRAY);
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer (3, GL_INT, 0, vertices);
	glColorPointer (3, GL_FLOAT, 0, colors);
	glLoadIdentity ();
	gluLookAt (posx, 50.0, posz, posx*(1-sin(pRotationz)), 50.0, posz*(1-cos(pRotationz)), 0.0, 1.0, 0.0);
	
	/*glTranslatef(-posx,-50,-posz);
	glPushMatrix();
		glTranslatef(posx,50,posz);
		glRotatef(pRotationz,0.0,1.0,0.0);
		glTranslatef(-posx,-50,-posz);*/
	//glPopMatrix();
	static GLubyte allIndices[]={4,5,6,7,
		1, 2, 6, 5,
		0, 1, 5, 4,
		0, 3, 2, 1,
		0, 4, 7, 3, 
		2, 3, 7, 6,
		12,13,14,15,
		9,10,14,13,
		8,9,13,12,
		8,11,10,9,
		8,12,15,11,
		10,11,15,14};
	//glPopMatrix();
	//glPushMatrix();
	glDrawElements(GL_QUADS, 48, GL_UNSIGNED_BYTE, allIndices);
	//glPopMatrix();	
	//glPopMatrix();
	glutWarpPointer(1364/2,742/2);
	glutSwapBuffers();
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 'w':
			posz=posz-step_length*cos(pRotationz);
			posx=posx-step_length*sin(pRotationz);
			glutPostRedisplay();
			break;
		case 'a':
			posz=posz+step_length*sin(pRotationz);
			posx=posx-step_length*cos(pRotationz);
			glutPostRedisplay();
			break;
		case 's':
			posz=posz+step_length*cos(pRotationz);
			posx=posx+step_length*sin(pRotationz);
			glutPostRedisplay();
			break;
		case 'd':
			posz=posz-step_length*sin(pRotationz);
			posx=posx+step_length*cos(pRotationz);
			glutPostRedisplay();
			break;
		
		case '4':
			pRotationz += 90;
			glutPostRedisplay();
			break;
		
		case '6':
			pRotationz -= 90;
			glutPostRedisplay();
			break;
		
		default:
			break;
	}
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
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (1364, 742);
	glutInitWindowPosition (0, 0);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(Rotate);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
