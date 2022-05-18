#include "Graphics\window.h"
#include "Camera\camera.h"
#include "Shaders\shader.h"
#include "Model Loading\mesh.h"
#include "Model Loading\texture.h"
#include "Model Loading\meshLoaderObj.h"
#include <Windows.h>

void processKeyboardInput();
void playSound();

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Window window("Game Engine", 1280, 720);

glm::vec3 cameraPos = glm::vec3(-15.0f, -16.5f, 15.0f);
glm::vec3 cameraDir = glm::vec3(-20.0f, 0.0f, 2.2f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

Camera camera(cameraPos, cameraDir, cameraUp);

glm::vec4 lightColor = glm::vec4(0.996, 0.803, 0.560, 1.0f);
glm::vec3 lightPos = glm::vec3(-200.0f, 20.0f, -20.0f);

int main()
{
	
	//feed the srand for randomazation
	srand((unsigned int)time(NULL));

	glClearColor(0.996, 0.803, 0.560, 1.0f);

	//building and compiling shader program
	Shader shader("Shaders/vertex_shader.glsl", "Shaders/fragment_shader.glsl");
	Shader sunShader("Shaders/sun_vertex_shader.glsl", "Shaders/sun_fragment_shader.glsl");
	Shader waveShader("Shaders/waves_vertex_shader.glsl", "Shaders/waves_fragment_shader.glsl");

	//Textures
	GLuint tex1 = loadBMP("Resources/Textures/sand.bmp");
	GLuint tex2 = loadBMP("Resources/Textures/sun.bmp");
	GLuint tex3 = loadBMP("Resources/Textures/rock1.bmp");
	GLuint tex4 = loadBMP("Resources/Textures/rock2.bmp");
	GLuint tex5 = loadBMP("Resources/Textures/sea.bmp");
	GLuint tex6 = loadBMP("Resources/Textures/sunset2.bmp");
	GLuint tex7 = loadBMP("Resources/Textures/wall.bmp");
	GLuint tex8 = loadBMP("Resources/Textures/wood.bmp");


	glEnable(GL_DEPTH_TEST);

	//Test custom mesh loading
	std::vector<Vertex> vert;
	vert.push_back(Vertex());
	vert[0].pos = glm::vec3(10.5f, 10.5f, 0.0f);
	vert[0].textureCoords = glm::vec2(1.0f, 1.0f);

	vert.push_back(Vertex());
	vert[1].pos = glm::vec3(10.5f, -10.5f, 0.0f);
	vert[1].textureCoords = glm::vec2(1.0f, 0.0f);

	vert.push_back(Vertex());
	vert[2].pos = glm::vec3(-10.5f, -10.5f, 0.0f);
	vert[2].textureCoords = glm::vec2(0.0f, 0.0f);

	vert.push_back(Vertex());
	vert[3].pos = glm::vec3(-10.5f, 10.5f, 0.0f);
	vert[3].textureCoords = glm::vec2(0.0f, 1.0f);

	vert[0].normals = glm::normalize(glm::cross(vert[1].pos - vert[0].pos, vert[3].pos - vert[0].pos));
	vert[1].normals = glm::normalize(glm::cross(vert[2].pos - vert[1].pos, vert[0].pos - vert[1].pos));
	vert[2].normals = glm::normalize(glm::cross(vert[3].pos - vert[2].pos, vert[1].pos - vert[2].pos));
	vert[3].normals = glm::normalize(glm::cross(vert[0].pos - vert[3].pos, vert[2].pos - vert[3].pos));

	std::vector<int> ind = { 0, 1, 3,
		1, 2, 3 };

	std::vector<Texture> texture1;
	texture1.push_back(Texture());
	texture1[0].id = tex1;
	texture1[0].type = "texture_diffuse";

	std::vector<Texture> texture2;
	texture2.push_back(Texture());
	texture2[0].id = tex2;
	texture2[0].type = "texture_diffuse";

	std::vector<Texture> texture3;
	texture3.push_back(Texture());
	texture3[0].id = tex3;
	texture3[0].type = "texture_diffuse";

	std::vector<Texture> texture4;
	texture4.push_back(Texture());
	texture4[0].id = tex4;
	texture4[0].type = "texture_diffuse";

	std::vector<Texture> texture5;
	texture5.push_back(Texture());
	texture5[0].id = tex5;
	texture5[0].type = "texture_diffuse";

	std::vector<Texture> texture6;
	texture6.push_back(Texture());
	texture6[0].id = tex6;
	texture6[0].type = "texture_diffuse";

	std::vector<Texture> texture7;
	texture7.push_back(Texture());
	texture7[0].id = tex7;
	texture7[0].type = "texture_diffuse";

	std::vector<Texture> texture8;
	texture8.push_back(Texture());
	texture8[0].id = tex8;
	texture8[0].type = "texture_diffuse";

	// we can add here our textures :)
	MeshLoaderObj loader;	
	Mesh island = loader.loadObj("Resources/Models/island.obj", texture1);
	Mesh sun = loader.loadObj("Resources/Models/sphere.obj", texture2);
	Mesh rock1 = loader.loadObj("Resources/Models/rock1.obj", texture3);
	Mesh rock2 = loader.loadObj("Resources/Models/rock1.obj", texture4);
	Mesh mountain = loader.loadObj("Resources/Models/mountain.obj", texture4);
	Mesh sea = loader.loadObj("Resources/Models/plane.obj", texture5);
	Mesh skybox = loader.loadObj("Resources/Models/sphere2.obj", texture6);
	Mesh lighthouse = loader.loadObj("Resources/Models/lighthouse.obj", texture7);
	Mesh boat = loader.loadObj("Resources/Models/boat.obj", texture8);

	playSound();

	//check if we close the window or press the escape button
	while (!window.isPressed(GLFW_KEY_ESCAPE) &&
		glfwWindowShouldClose(window.getWindow()) == 0)
	{
		window.clear();
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processKeyboardInput();
	
		//test mouse input
		if (window.isMousePressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			std::cout << "Pressing mouse button" << std::endl;
		}
		glm::mat4 ProjectionMatrix = glm::perspective(90.0f, window.getWidth() * 1.0f / window.getHeight(), 0.1f, 10000.0f);
		glm::mat4 ViewMatrix = glm::lookAt(camera.getCameraPosition(), camera.getCameraPosition() + camera.getCameraViewDirection(), camera.getCameraUp());
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;	
		
		//sun
		sunShader.use();
		GLuint MatrixID1 = glGetUniformLocation(shader.getId(), "MVP");
		GLuint ModelMatrixID1 = glGetUniformLocation(shader.getId(), "model");
		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -20.0f, 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID1, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
		sun.draw(sunShader);

		//island
		shader.use();
		GLuint MatrixID2 = glGetUniformLocation(shader.getId(), "MVP");
		GLuint ModelMatrixID2 = glGetUniformLocation(shader.getId(), "model");
		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -20.0f, 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID2, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
		island.draw(shader);

		//rock1
		shader.use();
		GLuint MatrixID3 = glGetUniformLocation(shader.getId(), "MVP");
		GLuint ModelMatrixID3 = glGetUniformLocation(shader.getId(), "model");
		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -20.0f, 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID3, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID3, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
		rock1.draw(shader);

		//rock2
		shader.use();
		GLuint MatrixID4 = glGetUniformLocation(shader.getId(), "MVP");
		GLuint ModelMatrixID4 = glGetUniformLocation(shader.getId(), "model");
		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -20.0f, 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID4, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID4, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
		rock2.draw(shader);

		//mountain
		shader.use();
		GLuint MatrixID5 = glGetUniformLocation(shader.getId(), "MVP");
		GLuint ModelMatrixID5 = glGetUniformLocation(shader.getId(), "model");
		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -20.0f, 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID5, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID5, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
		mountain.draw(shader);

		//sea
		waveShader.use();
		GLuint MatrixID6 = glGetUniformLocation(waveShader.getId(), "MVP");

		float time = float(std::sin(glfwGetTime()));
		glUniform1f(glGetUniformLocation(waveShader.getId(), "time"), time);
		
		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -20.0f, 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID6, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID2, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniform3f(glGetUniformLocation(waveShader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(waveShader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(waveShader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
		sea.draw(waveShader);

		//skybox
		sunShader.use();
		GLuint MatrixID7 = glGetUniformLocation(sunShader.getId(), "MVP");
		GLuint ModelMatrixID7 = glGetUniformLocation(sunShader.getId(), "model");
		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 10.0f, 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID7, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID7, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniform3f(glGetUniformLocation(sunShader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(sunShader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(sunShader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
		skybox.draw(sunShader);

		//lighthouse
		shader.use();
		GLuint MatrixID8 = glGetUniformLocation(shader.getId(), "MVP");
		GLuint ModelMatrixID8 = glGetUniformLocation(shader.getId(), "model");
		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -20.0f, 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID8, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID8, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
		lighthouse.draw(shader);

		//boat
		shader.use();
		GLuint MatrixID9 = glGetUniformLocation(shader.getId(), "MVP");
		GLuint ModelMatrixID9 = glGetUniformLocation(shader.getId(), "model");
		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.2 * sin(0.8 * glfwGetTime()), 0.0f));
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID9, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID9, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
		boat.draw(shader);

		window.update();
	}
}
	
	void playSound()
	{
		PlaySound("Resources/Audio/ocean.wav", NULL, SND_ASYNC);
	}

	void processKeyboardInput()
	{
		float cameraSpeed = 0.01;


		//translation
		if (window.isPressed(GLFW_KEY_W))
			camera.keyboardMoveFront(cameraSpeed);
		if (window.isPressed(GLFW_KEY_S))
			camera.keyboardMoveBack(cameraSpeed);
		if (window.isPressed(GLFW_KEY_A))
			camera.keyboardMoveLeft(cameraSpeed);
		if (window.isPressed(GLFW_KEY_D))
			camera.keyboardMoveRight(cameraSpeed);
		if (window.isPressed(GLFW_KEY_R))
			camera.keyboardMoveUp(cameraSpeed);
		if (window.isPressed(GLFW_KEY_F))
			camera.keyboardMoveDown(cameraSpeed);

		//rotation

		if (window.isPressed(GLFW_KEY_LEFT))
			camera.rotateOy(100 * cameraSpeed);
		if (window.isPressed(GLFW_KEY_RIGHT))
			camera.rotateOy(-100 * cameraSpeed);
		/*if (window.isPressed(GLFW_KEY_UP))
			camera.rotateOx(100 * cameraSpeed);
		if (window.isPressed(GLFW_KEY_DOWN))
			camera.rotateOx(-100 * cameraSpeed);*/
	}
