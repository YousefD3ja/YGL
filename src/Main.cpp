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

const double PI = 3.141592653589793;

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window, Viewport* viewport);


int main() 
{
	Viewport viewport(2);


	// Initialize a Renderer object
	Renderer renderer(SCR_WIDTH, SCR_HEIGHT, "OpenGL", &viewport);


	viewport.viewport = new float[8] {};
	viewport.makeArray();

	
	
	//glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(renderer.window, framebuffer_size_callback);
	

	float vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
		-0.5f / 2,  0.5f * float(sqrt(3)) / 6, 0.0f,
		 0.5f / 2,  0.5f * float(sqrt(3)) / 6, 0.0f,
		 0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	};

	float vertices2[] =
	{
		0.0f, 0.0f, 0.0f, 0.8f, 0.3f, 0.02f,
		0.5f, 0.0f, 0.0f, 0.6f, 0.9f, 0.03f,
		Math::RotateX(0.5f, 0.0f, 45.0), Math::RotateY(0.5f, 0.0f, 45.5), 0.0f, 0.5f, 0.9f, 0.07f,
		Math::RotateX(0.5f, 0.0f, 90.0), Math::RotateY(0.5f, 0.0f, 90.0), 0.0f, 0.1f, 0.7f, 0.05f,
		Math::RotateX(0.5f, 0.0f, 135.0), Math::RotateY(0.5f, 0.0f, 135.0), 0.0f, 0.4f, 0.4f, 0.02f,
		Math::RotateX(0.5f, 0.0f, 180.0), Math::RotateY(0.5f, 0.0f, 180.0), 0.0f, 0.4f, 0.2f, 0.02f,
	};

	/*float vertices3[] =
	{
		-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		 -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	};*/

	float vertices3[] =
	{
		-1.0f, -1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		 -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	};

	unsigned int indices3[] =
	{
		0, 1, 2,
		0, 3, 2,
	};

	unsigned int indices2[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
	};

	unsigned int indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};

	Texture2D texture("res/textures/download.png", 1, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA,GL_UNSIGNED_BYTE, GL_NEAREST);
	Texture2D texture1("res/textures/test.png", 1, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA,GL_UNSIGNED_BYTE, GL_NEAREST);

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
	VBO vbo1(vertices3, sizeof(vertices3));


	// Generate element buffer object and links it to indices
	EBO ebo1(indices3, sizeof(indices3));

	// Link VBO to ABO
	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao1.LinkAttrib(vbo1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind All Buffers
	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();

	shader.Avtivate();
	//GLint uniID = glGetUniformLocation(shader.ID, "scale");

	texture.textureUnit(shader, "tex0", 0);
	texture1.textureUnit(shader, "tex1", 0);

	

	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap the back buffer with the front buffer
	glfwSwapBuffers(renderer.window);

	bool hi = true;

	std::cout << vao1.ID << std::endl;

	int n;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &n);
	std::cout << "Max number of vertex attributes supported: " << n << std::endl;
	

	

	// Main while loop
	while (!glfwWindowShouldClose(renderer.window))
	{
		processInput(renderer.window, &viewport);

		
		
		if(hi)
		{
			for (int i = 0; i < 2 * 4; i++)
			{
				std::cout << viewport.viewport[i] << std::endl;
			}
			hi = false;

			//std::cout << "uniID:" << uniID << std::endl;
		}

		

		

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		viewport.setViewportf(0, 0.0f, 0.0f, SCR_WIDTH, SCR_HEIGHT);

		viewport.currentViewport[0] = (float)SCR_WIDTH / 2;
		viewport.currentViewport[1] = 0.0f;
		viewport.currentViewport[2] = (float)SCR_WIDTH / 2;
		viewport.currentViewport[3] = (float)SCR_HEIGHT;
		viewport.setViewportfv(1);

		// Binds the texture to be used
		texture.Bind();
		// Activates the shader program
		shader.Avtivate();

		float time = glfwGetTime();
		float r = static_cast<float>((sin(time) / 2) + 0.5);
		int color1 = Shader::getUniformLocation(shader.ID, "color1");
		
		float g = static_cast<float>((sin(time) / 2) + 0.5);

		float b = static_cast<float>((sin(time) / 2) + 0.5);
		glUniform4f(color1, r, g, b, 1.0f);
		// Bind the VAO so OpenGL knows to use it
		vao1.Bind();
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		texture.Unbind();

		// Sets the viewport to the current viewport
		viewport.setCurrentViewport(1);

		// Binds the texture to be used
		texture1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		texture1.Unbind();

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(renderer.window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
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

void processInput(GLFWwindow* window, Viewport* viewport)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}