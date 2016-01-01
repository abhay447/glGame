#include <iostream>
#include <fstream>
#include <cstdio>

#include <GL/gl.h>

GLuint LoadTexture(const char * filename)
{
	GLuint texture;
	int width, height;
	unsigned char * data;
	FILE * file;
	file = fopen( filename, "rb" );
	if ( file == NULL ) return 0;
	width  = 256;
	height = 256;
	data = (unsigned char *)malloc( width * height * 3 );
	//int size = fseek(file,);
	fseek(file,54,SEEK_SET);
   // skip palette - two rgb quads, 8 bytes
    fseek(file, 8, SEEK_CUR);

	fread( data, width * height * 3, 1, file );
	fclose( file );

	for(int i = 0; i < width * height ; ++i)
	{
		int index = i*3;
		unsigned char B,R;
		B = data[index];
		R = data[index+2];
		data[index] = R;
		data[index+2] = B;
	}
	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );

	return texture;
}
