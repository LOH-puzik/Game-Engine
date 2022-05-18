#pragma once
#include <glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "..\Shaders\shader.h"

struct Vertex 
{
	glm::vec3 pos;
	glm::vec3 normals;
	glm::vec2 textureCoords;

	Vertex() {}

	Vertex(float pos_x, float pos_y, float pos_z)
	{
		pos.x = pos_x;
		pos.y = pos_y;
		pos.z = pos_z;
	}

	Vertex(float pos_x, float pos_y, float pos_z, float norm_x, float norm_y, float norm_z)
	{
		pos.x = pos_x;
		pos.y = pos_y;
		pos.z = pos_z;

		normals.x = norm_x;
		normals.y = norm_y;
		normals.z = norm_z;
	}

	Vertex(float pos_x, float pos_y, float pos_z, float text_x, float text_y)
	{
		pos.x = pos_x;
		pos.y = pos_y;
		pos.z = pos_z;

		textureCoords.x = text_x;
		textureCoords.y = text_y;
	}

	Vertex(float pos_x, float pos_y, float pos_z, float norm_x, float norm_y, float norm_z, float text_x, float text_y)
	{
		pos.x = pos_x;
		pos.y = pos_y;
		pos.z = pos_z;

		normals.x = norm_x;
		normals.y = norm_y;
		normals.z = norm_z;

		textureCoords.x = text_x;
		textureCoords.y = text_y;
	}
};

struct Texture 
{
	unsigned int id;
	std::string type;
};

class Mesh
{
	public:
		std::vector<Vertex> vertices;
		std::vector<int> indices;
		std::vector<Texture> textures;

		unsigned int vao, vbo, ibo;

		Mesh();	
		Mesh(std::vector<Vertex> vertices, std::vector<int> indices, std::vector<Texture> textures);
		Mesh(std::vector<Vertex> vertices, std::vector<int> indices);
		~Mesh();

		void setTextures(std::vector<Texture> textures);
		void setup();
		void setup2();
		void draw(Shader shader);
};

