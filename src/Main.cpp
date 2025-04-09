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
#include <camera.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <thread>
#include <objects.h>
#include <physics.h>

const double PI = 3.141592653589793;

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;

bool firstMouse = true;

float yaw, pitch;

double deltaTime = 0.0f;
double lastFrame = 0.0f;

unsigned int counter;

bool windowState;

double FPS;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void processInput(GLFWwindow* window, Viewport* viewport, Shader* shader);

void groundtest(Shader* shader, VAO* vao);

Viewport viewport(1);
// Initialize a Renderer object
Renderer renderer(SCR_WIDTH, SCR_HEIGHT, "OpenGL", false, &viewport);

Camera camera(glm::vec3(0.0f,5.0f,0.0f));

Texture2D grass("res/textures/GrassBlock.png", 1, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE, GL_NEAREST);
Texture2D dirt("res/textures/DirtBlock.png", 1, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE, GL_NEAREST);
Texture2D wood("res/textures/woodBlock.png", 1, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE, GL_NEAREST);
Texture2D stone("res/textures/stoneBlock.png", 1, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE, GL_NEAREST);

Texture2D skyTexture("res/textures/sky.png", 1, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE, GL_NEAREST);

Texture2D textures[2] = { dirt, grass };

int main()
{
	viewport.viewport = new float[4 * viewport.count] {};
	viewport.makeArray();



	//glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(renderer.window, framebuffer_size_callback);
	glfwSetInputMode(renderer.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(renderer.window, mouse_callback);

	glfwSetScrollCallback(renderer.window, scroll_callback);



	/*float vertices[] =
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
	};*/

	float vertices2[] = {
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	float vertices[5 * 8] =
	{
		// Front square
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
		 // Back square
		 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		  0.5f,  0.5f, -0.5f, 1.0f, 0.0f,
		  0.5f, -0.5f, -0.5f, 1.0f, 1.0f,

	};

	unsigned int indices[3 * 2 * 6] =
	{
		// Front square
		0,1,2,
		0,3,2,
		// Right square
		3,2,6,
		3,7,6,
		// Back square
		4,5,6,
		4,7,6,
		// Left square
		0,1,5,
		0,4,5,
		// Upper square
		1,5,6,
		1,2,6,
		// Lower square
		0,4,7,
		0,3,7
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  15.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f),
		////////////////////
		glm::vec3(0.0f,  5.0f,  0.0f),
		glm::vec3(2.0f, -5.0f, -15.0f),
		glm::vec3(1.5f, -2.2f, 2.5f),
		glm::vec3(3.8f, 2.0f, -12.3f),
		glm::vec3(-2.4f, 0.4f, 3.5f),
		glm::vec3(1.7f,  -3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, 2.5f),
		glm::vec3(-1.5f,  2.0f, -2.5f),
		glm::vec3(-1.5f,  -0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, 1.5f)
	};

	glm::vec3 plane[] =
	{ glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f),glm::vec3(-1.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-1.0f),/**/
		glm::vec3(2.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,2.0f),glm::vec3(-2.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-2.0f),/**/
		glm::vec3(3.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,3.0f),glm::vec3(-3.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-3.0f),/**/
		glm::vec3(4.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,4.0f),glm::vec3(-4.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-4.0f),/**/
		glm::vec3(5.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,5.0f),glm::vec3(-5.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-5.0f),/**/
		glm::vec3(6.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,6.0f),glm::vec3(-6.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-6.0f),/**/
		glm::vec3(7.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,7.0f),glm::vec3(-7.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-7.0f),/**/
		glm::vec3(8.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,8.0f),glm::vec3(-8.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-8.0f),/**/
		glm::vec3(9.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,9.0f),glm::vec3(-9.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-9.0f),/**/

		glm::vec3(1.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,1.0f),glm::vec3(-1.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-1.0f),/**/
		glm::vec3(1.0f,0.0f,2.0f),glm::vec3(2.0f,0.0f,2.0f),glm::vec3(-2.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-2.0f),/**/
		glm::vec3(1.0f,0.0f,3.0f),glm::vec3(2.0f,0.0f,3.0f),glm::vec3(-3.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-3.0f),/**/
		glm::vec3(1.0f,0.0f,4.0f),glm::vec3(2.0f,0.0f,4.0f),glm::vec3(-4.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-4.0f),/**/
		glm::vec3(1.0f,0.0f,5.0f),glm::vec3(2.0f,0.0f,5.0f),glm::vec3(-5.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-5.0f),/**/
		glm::vec3(1.0f,0.0f,6.0f),glm::vec3(2.0f,0.0f,6.0f),glm::vec3(-6.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-6.0f),/**/
		glm::vec3(1.0f,0.0f,7.0f),glm::vec3(2.0f,0.0f,7.0f),glm::vec3(-7.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-7.0f),/**/
		glm::vec3(1.0f,0.0f,8.0f),glm::vec3(2.0f,0.0f,8.0f),glm::vec3(-8.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-8.0f),/**/
		glm::vec3(1.0f,0.0f,9.0f),glm::vec3(2.0f,0.0f,9.0f),glm::vec3(-9.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-9.0f),/**/


		glm::vec3(-1.0f,0.0f,-1.0f),glm::vec3(-2.0f,0.0f,-1.0f),glm::vec3(-1.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-1.0f),/**/
		glm::vec3(-1.0f,0.0f,-2.0f),glm::vec3(-2.0f,0.0f,-2.0f),glm::vec3(-2.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-2.0f),/**/
		glm::vec3(-1.0f,0.0f,-3.0f),glm::vec3(-2.0f,0.0f,-3.0f),glm::vec3(-3.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-3.0f),/**/
		glm::vec3(-1.0f,0.0f,-4.0f),glm::vec3(-2.0f,0.0f,-4.0f),glm::vec3(-4.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-4.0f),/**/
		glm::vec3(-1.0f,0.0f,-5.0f),glm::vec3(-2.0f,0.0f,-5.0f),glm::vec3(-5.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-5.0f),/**/
		glm::vec3(-1.0f,0.0f,-6.0f),glm::vec3(-2.0f,0.0f,-6.0f),glm::vec3(-6.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-6.0f),/**/
		glm::vec3(-1.0f,0.0f,-7.0f),glm::vec3(-2.0f,0.0f,-7.0f),glm::vec3(-7.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-7.0f),/**/
		glm::vec3(-1.0f,0.0f,-8.0f),glm::vec3(-2.0f,0.0f,-8.0f),glm::vec3(-8.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-8.0f),/**/
		glm::vec3(-1.0f,0.0f,-9.0f),glm::vec3(-2.0f,0.0f,-9.0f),glm::vec3(-9.0f,0.0f,1.0f),glm::vec3(2.0f,0.0f,-9.0f),/**/


	};

	float plane2[] =
	{
		-100.0f, -50.0f, -100.0f, 0.0f, 0.0f,
		-100.0f, -50.0f,  100.0f, 0.0f, 1.0f,
		 100.0f, -50.0f,  100.0f, 1.0f, 1.0f,
		 100.0f, -50.0f, -100.0f, 1.0f, 0.0f,
	};

	unsigned int planeIndices[] =
	{
		0,1,2,
		0,2,3
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

	VBO vbo2(vertices2, sizeof(vertices2));
	vao1.LinkAttrib(vbo2, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	vao1.LinkAttrib(vbo2, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind All Buffers
	vao1.Unbind();
	vbo2.Unbind();
	////////////////
	VAO planeVao;
	planeVao.Bind();
	VBO planeVBO(plane2, sizeof(plane2));
	EBO planeEBO(planeIndices, sizeof(planeIndices));
	planeVao.LinkAttrib(planeVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	planeVao.LinkAttrib(planeVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	planeVao.Unbind();
	planeVBO.Unbind();
	planeEBO.Unbind();

	float skyVertices[] =
	{
		-100.0f, -100.0f, 0.0f, 0.0f, 0.0f,
		-100.0f, 100.0f,  0.0f, 0.0f, 1.0f,
		 100.0f, 100.0f,  0.0f, 1.0f, 1.0f,
		 100.0f, -100.0f, 0.0f, 1.0f, 0.0f,
	};

	unsigned int skyIndices[] =
	{
		0,1,2,
		0,2,3
	};

	VAO skyVAO;
	skyVAO.Bind();

	VBO skyVBO(skyVertices, sizeof(skyVertices));
	EBO skyEBO(skyIndices, sizeof(skyIndices));
	skyVAO.LinkAttrib(skyVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	skyVAO.LinkAttrib(skyVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	skyVAO.Unbind();
	skyVBO.Unbind();
	skyEBO.Unbind();


	shader.Avtivate();
	shader.setInt("tex0", 0);

	camera.fov = 120.0f;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);


	viewport.setViewportf(0, 0.0f, 0.0f, (float)SCR_WIDTH, (float)SCR_HEIGHT);

	float faceVertices[] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f, 0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	};

	unsigned int faceIndices[] =
	{
		0,1,2,
		0,2,3
	};

	ChunkTest::Chunk testChunk(glm::vec3(0.0f, 0.0f, 0.0));

	for (unsigned int c = 0; c < testChunk.chunks.size(); c++)
	{
		for (float i = -(testChunk.Width); i < testChunk.Width; i++)
		{
			for (float k = -(testChunk.Depth); k < testChunk.Depth; k++)
			{
				for (float j = -(testChunk.Height); j < testChunk.Height-3; j++)
				{
					if(j > 3)
					{
						testChunk.setBlock(&testChunk.chunks.at(c), ChunkTest::blockTypes::GRASS, glm::vec3(i, j, k), true);
					}
					else
					{
						testChunk.setBlock(&testChunk.chunks.at(c), ChunkTest::blockTypes::DIRT, glm::vec3(i, j, k), true);
					}
				}
			}
		}
	}

	// Front face
	VAO BlocksFrontVAO;
	BlocksFrontVAO.Bind();

	VBO BlocksFrontVBO(testChunk.ChunkVertices[0], sizeof(testChunk.ChunkVertices[0]));
	EBO BlocksFrontEBO(testChunk.ChunkIndices, sizeof(testChunk.ChunkIndices));
	BlocksFrontVAO.LinkAttrib(BlocksFrontVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	BlocksFrontVAO.LinkAttrib(BlocksFrontVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	BlocksFrontVAO.Unbind();
	BlocksFrontVBO.Unbind();
	BlocksFrontEBO.Unbind();

	// Right face
	VAO BlocksRightVAO;
	BlocksRightVAO.Bind();

	VBO BlocksRightVBO(testChunk.ChunkVertices[1], sizeof(testChunk.ChunkVertices[1]));
	EBO BlocksRightEBO(testChunk.ChunkIndices, sizeof(testChunk.ChunkIndices));
	BlocksRightVAO.LinkAttrib(BlocksRightVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	BlocksRightVAO.LinkAttrib(BlocksRightVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	BlocksRightVAO.Unbind();
	BlocksRightVBO.Unbind();
	BlocksRightEBO.Unbind();

	// Back face
	VAO BlocksBackVAO;
	BlocksBackVAO.Bind();

	VBO BlocksBackVBO(testChunk.ChunkVertices[2], sizeof(testChunk.ChunkVertices[2]));
	EBO BlocksBackEBO(testChunk.ChunkIndices, sizeof(testChunk.ChunkIndices));
	BlocksBackVAO.LinkAttrib(BlocksBackVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	BlocksBackVAO.LinkAttrib(BlocksBackVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	BlocksBackVAO.Unbind();
	BlocksBackVBO.Unbind();
	BlocksBackEBO.Unbind();

	// Left face
	VAO BlocksLeftVAO;
	BlocksLeftVAO.Bind();

	VBO BlocksLeftVBO(testChunk.ChunkVertices[3], sizeof(testChunk.ChunkVertices[3]));
	EBO BlocksLeftEBO(testChunk.ChunkIndices, sizeof(testChunk.ChunkIndices));
	BlocksLeftVAO.LinkAttrib(BlocksLeftVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	BlocksLeftVAO.LinkAttrib(BlocksLeftVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	BlocksLeftVAO.Unbind();
	BlocksLeftVBO.Unbind();
	BlocksLeftEBO.Unbind();

	// Upper face
	VAO BlocksUpperVAO;
	BlocksUpperVAO.Bind();

	VBO BlocksUpperVBO(testChunk.ChunkVertices[4], sizeof(testChunk.ChunkVertices[4]));
	EBO BlocksUpperEBO(testChunk.ChunkIndices, sizeof(testChunk.ChunkIndices));
	BlocksUpperVAO.LinkAttrib(BlocksUpperVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	BlocksUpperVAO.LinkAttrib(BlocksUpperVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	BlocksUpperVAO.Unbind();
	BlocksUpperVBO.Unbind();
	BlocksUpperEBO.Unbind();

	// Lower face
	VAO BlocksLowerVAO;
	BlocksLowerVAO.Bind();

	VBO BlocksLowerVBO(testChunk.ChunkVertices[5], sizeof(testChunk.ChunkVertices[5]));
	EBO BlocksLowerEBO(testChunk.ChunkIndices, sizeof(testChunk.ChunkIndices));
	BlocksLowerVAO.LinkAttrib(BlocksLowerVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	BlocksLowerVAO.LinkAttrib(BlocksLowerVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	BlocksLowerVAO.Unbind();
	BlocksLowerVBO.Unbind();
	BlocksLowerEBO.Unbind();


	std::stringstream cameraPosition;
	//std::stringstream FPS;

	
	double currentFrame;

	VAO vao[8] = {
		BlocksFrontVAO ,
		BlocksBackVAO,
		BlocksUpperVAO,
		BlocksLowerVAO,
		BlocksLeftVAO,
		BlocksRightVAO,
		skyVAO,
		planeVao 
	};

	Texture2D textures[5] = { 
		grass,
		dirt,
		skyTexture,
		wood,
		stone,
	};

	std::thread loadChunks(ChunkTest::Chunk::ChunkThread, &testChunk, &camera);

	std::thread playerThread(Physics::Player::checkCurrentChunk, &testChunk, &camera);

	std::thread processInputThread(Physics::Player::Process, &testChunk, &camera);

	std::thread CheckChunks(ChunkTest::Chunk::ChenkPriorityThread, &testChunk, &camera);

	std::thread SortingThread(ChunkTest::Chunk::SortingThread, &testChunk, &camera);

	std::thread loadBlocks(ChunkTest::Chunk::checkChunkThread, &testChunk, &camera);

	std::thread processPlaceablesThread(Physics::Player::ProcessPlaceables, &testChunk, &camera);

	unsigned int renderedCounter = 0;

	std::vector<ChunkTest::chunk_t*> ChunkList;


	// Main while loop
	while (!glfwWindowShouldClose(renderer.window))
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		//lastFrame = currentFrame;
		counter++;

		FPS = (1.0f / deltaTime);
		lastFrame = currentFrame;
		//counter = 0;

		processInput(renderer.window, &viewport, &shader);

		renderedCounter++;
		
		if (renderer.screenChanged && renderer.isFullScreen == false)
		{
			renderer.isFullScreen = true;
			renderer.SetWindowFullScreen(viewport);
			renderer.screenChanged = false;
		}
		else if (renderer.screenChanged && renderer.isFullScreen == true)
		{
			renderer.isFullScreen = false;
			renderer.SetWindowWindowed(viewport, renderer.SCR_Width, renderer.SCR_Height);
			renderer.screenChanged = false;
		}

		// Specify the color of the background
		// Clean the back buffer and assign the new color to it
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Activates the shader program
		shader.Avtivate();

		camera.SetPerspective(camera.fov, renderer.Width, renderer.Height, 0.1f, 500.0f);
		camera.view = glm::translate(camera.view, glm::vec3(0.0f, 0.0f, -3.0f));

		camera.setCameraView();

		shader.setMat4("projection", camera.projection);
		shader.setMat4("view", camera.view);

		if (testChunk.SortedUpdated)
		{
			ChunkList = testChunk.sortedChunks;
			testChunk.SortedUpdated = false;
			renderedCounter = 0;
		}

		for (ChunkTest::chunk_t* ck : ChunkList)
		{
			for (ChunkTest::block* bk : ck->renderedBlocks)
			{
				shader.setMat4("model", bk->model);
				shader.setMat4("ChunkModel", bk->chunkModel);

				for (unsigned int i = 0; i < 6; i++)
				{
					if (bk->renderFaces[i])
					{
						vao[i].Bind();

						if (bk->type == ChunkTest::blockTypes::GRASS)
						{
							textures[0].Bind();
						}
						else if (bk->type == ChunkTest::blockTypes::DIRT)
						{
							textures[1].Bind();
						}
						else if (bk->type == ChunkTest::blockTypes::WOOD)
						{
							textures[3].Bind();
						}
						else if (bk->type == ChunkTest::blockTypes::STONE)
						{
							textures[4].Bind();
						}
						else
						{
							textures[2].Bind();
						}

						glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
						vao[i].Unbind();
					}
				}

				shader.setMat4("model", glm::mat4(1.0));
				shader.setMat4("ChunkModel", glm::mat4(1.0));

			}
		}


		for (int i = 0; i < 5; i++)
		{
			vao[6].Bind();
			shader.Avtivate();
			glm::mat4 model = glm::mat4(1.0f);

			if (i == 0)
			{
				model = glm::translate(model, glm::vec3(camera.Position.x + 90, camera.Position.y, camera.Position.z));
				model = glm::rotate(model, (float)glm::radians(270.0f), glm::vec3(0.0, 1.0f, 0.0f));
			}
			if (i == 1)
			{
				model = glm::translate(model, glm::vec3(camera.Position.x, camera.Position.y, camera.Position.z + 90));
				model = glm::rotate(model, (float)glm::radians(180.0f), glm::vec3(0.0, 1.0f, 0.0f));
			}
			if (i == 2)
			{
				model = glm::translate(model, glm::vec3(camera.Position.x - 90, camera.Position.y, camera.Position.z));
				model = glm::rotate(model, (float)glm::radians(90.0f), glm::vec3(0.0, 1.0f, 0.0f));
			}
			if (i == 3)
			{
				model = glm::translate(model, glm::vec3(camera.Position.x, camera.Position.y, camera.Position.z - 90));
				//model = glm::rotate(model, (float)glm::radians(180.0f), glm::vec3(0.0, 1.0f, 0.0f));
			}
			if (i == 4)
			{
				model = glm::translate(model, glm::vec3(camera.Position.x, camera.Position.y + 100, camera.Position.z));
				model = glm::rotate(model, (float)glm::radians(90.0f), glm::vec3(1.0, 0.0f, 0.0f));
			}

			//model = glm::rotate(model, (float)90 * i, glm::vec3(0.0, 1.0f, 1.0f));

			shader.setMat4("model", model);
			shader.setMat4("Chunkmodel", glm::mat4(1.0f));

			textures[2].Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			vao[6].Unbind();
			textures[2].Unbind();

			shader.setMat4("model", glm::mat4(1.0));
			shader.setMat4("ChunkModel", glm::mat4(1.0));
		}


		/* Placeable Block */

		if (true)
		{
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 ChunkModel = glm::mat4(1.0f);

			glm::vec3 pos = glm::vec3(1.0f);
			pos.x = (int)camera.placeableBlock.x;
			pos.y = (int)camera.placeableBlock.y;
			pos.z = (int)camera.placeableBlock.z;

			model = glm::translate(model, pos);
			ChunkModel = glm::translate(ChunkModel, camera.currentChunk->Position);

			for (unsigned int i = 0; i < 6; i++)
			{
				shader.setMat4("model", glm::mat4(1.0));
				shader.setMat4("ChunkModel", glm::mat4(1.0));
				shader.setMat4("model", model);
				shader.setMat4("ChunkModel", ChunkModel);
				vao[i].Bind();
				textures[2].Bind();
				glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
				vao[i].Unbind();

			}
			shader.setMat4("model", glm::mat4(1.0));

		}

		///////////////////////

		glfwSwapBuffers(renderer.window);


		

		cameraPosition.str("");
		cameraPosition.clear();
		cameraPosition << "X:" << camera.Position.x << "Y:" << camera.Position.y << "Z:" << camera.Position.z
			<< "/FPS:" << (int)FPS << "/" << "X:" << camera.Front.x << "Y:" << camera.Front.y << "Z:" << camera.Front.z/*(1.0f / deltaTime)*counter*/;
		renderer.setWindowTitle(cameraPosition.str().c_str());

		// Take care of all GLFW events
		glfwPollEvents();
	}

	vao1.Delete();
	vbo2.Delete();
	shader.DeleteShader();

	// Delete window before ending the program
	renderer.~Renderer();

	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float offsetX = xpos - lastX;
	float offsetY = ypos - lastY;

	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.2f;
	offsetX *= sensitivity;
	offsetY *= -sensitivity;

	yaw += offsetX;
	pitch += offsetY;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	camera.Front = glm::normalize(direction);
	camera.uFront = direction;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.fov -= (float)yoffset;
	if (camera.fov < 1.0f)
		camera.fov = 1.0f;
	if (camera.fov > 120.0f)
		camera.fov = 120.0f;

	//camera.range += (int)yoffset;

}

void processInput(
	GLFWwindow* window, Viewport* viewport, Shader* shader
)
{
	const float cameraSpeed = 2;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		renderer.ShouldClose = true;
		glfwSetWindowShouldClose(window, true);
	}
	
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		camera.placedBlock = true;
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		camera.currentBlock = ChunkTest::blockTypes::GRASS;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		camera.currentBlock = ChunkTest::blockTypes::DIRT;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		camera.currentBlock = ChunkTest::blockTypes::WOOD;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		camera.currentBlock = ChunkTest::blockTypes::STONE;
	}

	if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS)
	{
		renderer.screenChanged = true;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		//if (camera.Position.y < 3)
		camera.ProcessKeyboard(UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		//if (camera.Position.y > 1)
		camera.ProcessKeyboard(DOWN, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		camera.MovementSpeed = 15.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
	{
		camera.MovementSpeed = 10.0f;
	}
}

void groundtest(Shader* shader, VAO* vao)
{
	
	for (float i = 0; i <= 10; i++)
	{
		for (float j = 0; j <= 10; j++)
		{
			vao->Bind();
			shader->Avtivate();
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(i,0.0,j));

			model = glm::rotate(model, (float)glfwGetTime() , glm::vec3(1.0, 0.3f, 0.5f));

			shader->setMat4("model", model);

			dirt.Bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);
			dirt.Bind();
			glDrawArrays(GL_TRIANGLES, 6, 6);
			dirt.Bind();
			glDrawArrays(GL_TRIANGLES, 12, 6);
			dirt.Bind();
			glDrawArrays(GL_TRIANGLES, 18, 6);
			dirt.Bind();
			glDrawArrays(GL_TRIANGLES, 24, 6);
			grass.Bind();
			glDrawArrays(GL_TRIANGLES, 30, 6);
			//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

			vao->Unbind();
		}
	}

}
