#include <iostream>
#include <math.h>
#include <GL/gl.h>

using namespace std;

int THRESHOLD=1;

class wall
{
	public:
		wall(GLint x1,GLint x2,GLint z1,GLint z2)
		{
			Xmin = (x1<x2)?x1:x2;
			Xmax = (x1>x2)?x1:x2;
			Zmin = (z1<z2)?z1:z2;
			Zmax = (z1>z2)?z1:z2;
		}
		GLint Xmin,Xmax,Zmin,Zmax;
		
		int checkCollision(GLint x, GLint z);
};


/*===================================**
**	Return codes for check collision **
**	0: free all						 **
**	1: free x only					 **
**	2: free z only					 **
**===================================*/
int wall::checkCollision(GLint x, GLint z)
{
	if(Xmin==Xmax) //Wall parallel to z axis
	{
		int distance = abs(Xmin-x);
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
		int distance = abs(Zmin-z);
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
