#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <shaderclass.h>
#include <buffers.h>
#include <Ymath.h>
#define STB_IMAGE_IMPLEMENTATION
#include <texture.h>
#include <viewport.h>
#include <renderer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const double PI = 3.141592653589793;

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window, Viewport* viewport, Shader* shader, float* mv);


int main() 
{
	Viewport viewport(1);


	// Initialize a Renderer object
	Renderer renderer(SCR_WIDTH, SCR_HEIGHT, "OpenGL", &viewport);


	viewport.viewport = new float[4*viewport.count] {};
	viewport.makeArray();

	
	
	//glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(renderer.window, framebuffer_size_callback);

	Texture2D texture("res/textures/download.png", 1, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR);
	Texture2D texture1("res/textures/test.png", 1, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR);
	

	float vertices[] =
	{
		-1.0f, -1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		 -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		0, 3, 2,
	};
	
	float flatColor[] = { 0.3f, 0.8f, 0.8f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);


	// Generate shader object using default.shader
	Shader::ShaderProgramSource ShadersSource;
	Shader shader("res/default.shader", &ShadersSource);

	std::cout << ShadersSource.Vertex << std::endl;
	std::cout << ShadersSource.Fragment << std::endl;

	// Generate vertex array object and binds it
	VAO vao1;
	vao1.Bind();
	// Generate vertex buffer object and links it to vertices
	VBO vbo1(vertices, sizeof(vertices));
	// Generate element buffer object and links it to indices
	EBO ebo1(indices, sizeof(indices));

	// Link VBO to ABO
	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao1.LinkAttrib(vbo1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	

	// Unbind All Buffers
	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();

	shader.Avtivate();
	texture.textureUnit(shader, "tex0", 0);
	texture1.textureUnit(shader, "tex1", 1);

	float mv = 0;

	// Main while loop
	while (!glfwWindowShouldClose(renderer.window))
	{
		processInput(renderer.window, &viewport, &shader, &mv);
		viewport.setViewportf(0, 0.0f, 0.0f, SCR_WIDTH, SCR_HEIGHT);

		// Specify the color of the background
		// Clean the back buffer and assign the new color to it
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		

		// Activates the shader program
		shader.Avtivate();
		texture.Activate(0);
		texture1.Activate(1);

		//// render boxes
		vao1.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(renderer.window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	//ebo1.Delete();
	texture.Delete();
	shader.DeleteShader();

	// Delete window before ending the program
	renderer.~Renderer();

	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

void processInput(GLFWwindow* window, Viewport* viewport, Shader* shader, float* mv)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if (*mv >= 1.0) 
		{
			*mv = 1.0f;
		}
		else
		{
			shader->setFloat("mixValue", *mv + 0.01f);
			*mv += 0.01f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if (*mv <= 0.0)
		{
			*mv = 0.0f;
		}
		else
		{
			shader->setFloat("mixValue", *mv - 0.01f);
			*mv -= 0.01f;
		}
	}
}