#pragma once

#include <glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void use();
	int getId();

private:
	unsigned int id;
};

