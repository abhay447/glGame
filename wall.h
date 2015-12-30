#include <iostream>
#include <math.h>
#include <GL/gl.h>

using namespace std;

float THRESHOLD=0.6;

class wall
{
	public:
		wall(GLfloat x1,GLfloat x2,GLfloat z1,GLfloat z2)
		{
			Xmin = (x1<x2)?x1:x2;
			Xmax = (x1>x2)?x1:x2;
			Zmin = (z1<z2)?z1:z2;
			Zmax = (z1>z2)?z1:z2;
		}
		GLfloat Xmin,Xmax,Zmin,Zmax;
		
		int checkCollision(GLfloat x, GLfloat z);
};


/*===================================**
**	Return codes for check collision **
**	0: free all						 **
**	1: free x only					 **
**	2: free z only					 **
**===================================*/
int wall::checkCollision(GLfloat x, GLfloat z)
{
	if(Xmin==Xmax) //Wall parallel to z axis
	{
		float distance = fabs(Xmin-x);
		if(distance > THRESHOLD)
			return 0;
		else
		{
			if(z > Zmax+THRESHOLD || z < Zmin-THRESHOLD)
				return 0;
			else
				return 2;
		}
	}
	
	if(Zmin==Zmax) //Wall parallel to x axis
	{
		float distance = fabs(Zmin-z);
		if(distance > THRESHOLD)
			return 0;
		else
		{
			if(x > Xmax+THRESHOLD || x < Xmin-THRESHOLD)
				return 0;
			else
				return 1;
		}
	}
}
