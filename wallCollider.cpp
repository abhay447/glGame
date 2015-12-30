#include<iostream>
#include <GL/gl.h>
using namespace std;

int XRestriction,ZRestriction;
extern GLfloat posx,posz,tempx,tempz;
extern levelMap myMap;
void collide()
{
	XRestriction = 0;
	ZRestriction = 0;
	for(int i=0;i<myMap.walls.size();i++)
	{
		int result = myMap.walls[i].checkCollision(tempx,tempz);
		switch(result)
		{
			case 0:
				break;
			case 1:
				ZRestriction++;
			case 2:
				XRestriction++;
		}
	}
	if(XRestriction==0)
		posx=tempx;
	if(ZRestriction==0)
		posz=tempz;
	return;
}
