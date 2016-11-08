#ifndef SHADER_H
#define SHADER_H

#include<iostream>
#include<sstream>
#include<fstream>
#include <string>
#include "GL/glew.h"
using namespace std;

class Shader{
public:
	Shader(const char * vertex_path,const char* fragment_path);
	virtual ~Shader();

public:
	void ShaderProgramUse();

public:
	const char * vertexsource_path;
	const char * fragmentsource_path;
	GLuint  ShaderProgram;


};


#endif