#ifndef RENDERER_H
#define RENDERER_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <viewport.h>
#include <iostream>
#include <windows.h>

class Renderer
{
public:
	int viewportIndex;
	float Rviewport[4];
	GLFWwindow* window;
	GLFWmonitor* monitor = nullptr;
	const GLFWvidmode* vidMode = nullptr;
	int Width;
	int Height;

	bool isFullScreen;
	bool updateViewport;
	bool screenChanged = false;

	Renderer(unsigned int width, unsigned int height, const char* title, bool FullScreen, Viewport* viewport);
	~Renderer();
	void SetWindowFullScreen(Viewport& viewport);
	void SetWindowWindowed(Viewport& viewport, int screenWidth, int screenHeight);
		/*void clear();
		void swapBuffers();
		void pollEvents();
		void terminate();
		GLFWwindow* getWindow();*/
};

//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
//
//// Clean the back buffer and assign the new color to it
//glClear(GL_COLOR_BUFFER_BIT);
//shader.Avtivate();
//texture.Bind();
//
//glUniform1f(uniID, (float)(SCR_WIDTH / SCR_HEIGHT));
//
//glUseProgram(shader.ID);
//VAO.Bind();
////glDrawArrays(GL_TRIANGLES, 0, 3);
//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//// Swap the back buffer with the front buffer
//glfwSwapBuffers(window);
//
//// Take care of all GLFW events
//glfwPollEvents();

#endif