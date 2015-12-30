#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#include "wall.h"

using namespace std;

class levelMap
{
	public:
	levelMap()
	{
		coordFile="maps/level"+to_string(LEVEL)+".coords";
		vertexFile="maps/level"+to_string(LEVEL)+".mpf";
	}
	string coordFile,vertexFile;
	int LEVEL=1;
	vector<GLfloat> coords;
	vector<GLubyte> vertices;
	vector<wall> walls;
	void loadCoordinates();
	void loadVertices();
};
void levelMap::loadCoordinates()
{
	GLfloat x,y,z;
	ifstream ifs;
	ifs.open(coordFile.c_str());
	string line;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		iss>>x>>y>>z;
		coords.push_back(x);		
		coords.push_back(y);
		coords.push_back(z);
	}
}

void levelMap::loadVertices()
{
	int a,b,c,d;
	ifstream ifs;
	ifs.open(vertexFile.c_str());
	string line;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		iss>>a>>b>>c>>d;
		vertices.push_back((GLubyte)a);		
		vertices.push_back((GLubyte)b);
		vertices.push_back((GLubyte)c);
		vertices.push_back((GLubyte)d);
		
		GLfloat x1 = coords[a*3+0];
		GLfloat z1 = coords[a*3+2];
		GLfloat x2 = coords[c*3+0];
		GLfloat z2 = coords[c*3+2];
		wall thisWall(x1,x2,z1,z2);
		walls.push_back(thisWall);
	}
}






