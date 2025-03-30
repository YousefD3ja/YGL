#include <renderer.h>


Renderer::Renderer(unsigned int width, unsigned int height, const char* title, bool FullScreen, Viewport* viewport)
{
	// Initialize GLFW
	glfwInit();
	// Set GLFW window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	// Set GLFW to use the core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFW window
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	Width = width;
	Height = height;


	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Load GLAD to configure OpenGL
	gladLoadGL(glfwGetProcAddress);

	if (FullScreen)
	{
		screenChanged = true;
	}
	// Specify the viewport of OpenGL in the Window

	// Initialize default viewport
	/*Rviewport[0] = 0.0f;
	Rviewport[1] = 0.0f;
	Rviewport[2] = width;
	Rviewport[3] = height;

	viewport->viewport[0] = Rviewport[0];
	viewport->viewport[1] = Rviewport[1];
	viewport->viewport[2] = Rviewport[2];
	viewport->viewport[3] = Rviewport[3];
	viewport->setViewportfv(0);*/
}

Renderer::~Renderer()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
void clear()
{
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
void swapBuffers()
{
}
//void pollEvents();
//void terminate();
//GLFWwindow* getWindow();

void Renderer::SetWindowFullScreen(Viewport& viewport)
{
	monitor = glfwGetPrimaryMonitor();
	vidMode = glfwGetVideoMode(monitor);
	glfwSetWindowMonitor(window, monitor, 0, 0, vidMode->width, vidMode->height, GLFW_DONT_CARE);

	glfwGetWindowSize(window, &Width, &Height);
	viewport.setViewportf(0, 0, 0, Width, Height);

	Sleep(100);
}
void Renderer::SetWindowWindowed(Viewport& viewport, int screenWidth, int screenHeight)
{
	glfwSetWindowMonitor(window, NULL, 200, 200, (float)screenWidth, (float)screenHeight, GLFW_DONT_CARE);

	glfwGetWindowSize(window, &Width, &Height);
	viewport.setViewportf(0, 0, 0, screenWidth, screenHeight);
	Sleep(100);
}
