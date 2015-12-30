#include <iostream>

extern GLfloat posx,posz;
extern GLfloat tempx,tempz;
extern GLfloat visibility;
extern GLfloat step_length;
extern GLfloat pRotationz;
extern bool* keyStates;
using namespace std;

void initializeKeyboard()
{
	for(int i=0;i<255;i++)
		keyStates[i]=false;
}

void Rotate(int x,int y){
	
	pRotationz += 0.005*(-x+1364.0/2.0);
	glutPostRedisplay();
}

void move()
{
	if(keyStates['w']||keyStates['W'])
	{
		tempz=posz-step_length*cos(pRotationz);
		tempx=posx-step_length*sin(pRotationz);
	}
	if(keyStates['a']||keyStates['A'])
	{
		tempz=posz+step_length*sin(pRotationz);
		tempx=posx-step_length*cos(pRotationz);
	}
	if(keyStates['s']||keyStates['S'])
	{
		tempz=posz+step_length*cos(pRotationz);
		tempx=posx+step_length*sin(pRotationz);
	}
	if(keyStates['d']||keyStates['D'])
	{
		tempz=posz-step_length*sin(pRotationz);
		tempx=posx+step_length*cos(pRotationz);
	}
	if((keyStates['w']||keyStates['W'])&&(keyStates['a']||keyStates['A']))
	{
		tempz=posz-step_length*cos(pRotationz);
		tempx=posx-step_length*sin(pRotationz);
		tempz=tempz+step_length*sin(pRotationz);
		tempx=tempx-step_length*cos(pRotationz);
	}
	if((keyStates['w']||keyStates['W'])&&(keyStates['d']||keyStates['D']))
	{
		tempz=posz-step_length*cos(pRotationz);
		tempx=posx-step_length*sin(pRotationz);
		tempz=tempz-step_length*sin(pRotationz);
		tempx=tempx+step_length*cos(pRotationz);
	}
	if((keyStates['w']||keyStates['W'])&&(keyStates['d']||keyStates['D']))
	{
		tempz=posz-step_length*cos(pRotationz);
		tempx=posx-step_length*sin(pRotationz);
		tempz=tempz-step_length*sin(pRotationz);
		tempx=tempx+step_length*cos(pRotationz);
	}
	if((keyStates['s']||keyStates['S'])&&(keyStates['a']||keyStates['A']))
	{
		tempz=posz+step_length*cos(pRotationz);
		tempx=posx+step_length*sin(pRotationz);
		tempz=tempz+step_length*sin(pRotationz);
		tempx=tempx-step_length*cos(pRotationz);
	}
	if((keyStates['s']||keyStates['S'])&&(keyStates['d']||keyStates['D']))
	{
		tempz=posz+step_length*cos(pRotationz);
		tempx=posx+step_length*sin(pRotationz);
		tempz=tempz-step_length*sin(pRotationz);
		tempx=tempx+step_length*cos(pRotationz);
	}
	
	collide();
	glutPostRedisplay();
}
void keyDown (unsigned char key, int x, int y)
{
	keyStates[key]=true;	
}
void keyUp (unsigned char key, int x, int y)
{
	keyStates[key]=false;
}

