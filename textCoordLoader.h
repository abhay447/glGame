#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std;
vector<GLfloat> textureCoordinates;
extern levelMap myMap;
void load_texCoords()
{
	for(int i=0;i<myMap.vertices.size();i++)
	{
		switch(i%4){
			case 1:
				textureCoordinates.push_back(0.0);
				textureCoordinates.push_back(0.0);
				break;
			case 0:
				textureCoordinates.push_back(0.0);
				textureCoordinates.push_back(2.0);
				break;
			case 2:
				textureCoordinates.push_back(2.0);
				textureCoordinates.push_back(2.0);
				break;
			case 3:
				textureCoordinates.push_back(2.0);
				textureCoordinates.push_back(0.0);
				break;
		}
	}
}
