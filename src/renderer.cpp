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

	SCR_Width = width;
	SCR_Height = height;


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

void Renderer::setWindowTitle(std::string title)
{
	glfwSetWindowTitle(window,title.c_str());
}

void Renderer::getFrames(double* current, double* last, unsigned int* counter, double* retValue)
{
	float timeDiff = *current - *last;
	(*counter)++;
	if (timeDiff >= 1.0f / 30.0)
	{
		*retValue = (1.0f / timeDiff) * *counter;
		*last = *current;
		counter = 0;
	}
}


//void Renderer::Draw(
//	Renderer* renderer, Camera* camera, Viewport* viewport, 
//	ChunkTest::Chunk* chunklist, Shader* shader, VAO* vao, Texture2D* textures, void* input)
//{
//	//glfwMakeContextCurrent(renderer->window);
//	while(!renderer->ShouldClose)
//	{
//
//		std::thread loadBlocks(ChunkTest::Chunk::thread, chunklist, camera);
//		
//		loadBlocks.join();
//
//		if (renderer->screenChanged && renderer->isFullScreen == false)
//		{
//			renderer->isFullScreen = true;
//			renderer->SetWindowFullScreen(*viewport);
//			renderer->screenChanged = false;
//		}
//		else if (renderer->screenChanged && renderer->isFullScreen == true)
//		{
//			renderer->isFullScreen = false;
//			renderer->SetWindowWindowed(*viewport, renderer->SCR_Width, renderer->SCR_Height);
//			renderer->screenChanged = false;
//		}
//
//		//renderer->getFrames(&currentFrame, &lastFrame, &counter, &FPS);
//
//		// Specify the color of the background
//		// Clean the back buffer and assign the new color to it
//		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//
//
//		// Activates the shader program
//		shader->Avtivate();
//
//		camera->SetPerspective(camera->fov, renderer->Width, renderer->Height, 0.1f, 500.0f);
//		camera->view = glm::translate(camera->view, glm::vec3(0.0f, 0.0f, -3.0f));
//
//		camera->setCameraView();
//
//		shader->setMat4("projection", camera->projection);
//		shader->setMat4("view", camera->view);
//
//
//		for (unsigned int c = 0; c < chunklist->chunks.size(); c++)
//		{
//			ChunkTest::chunk_t* ck = &chunklist->chunks.at(c);
//			ChunkTest::block* b;
//
//
//			for (unsigned int i = 0; i < ck->blocks.size(); i++)
//			{
//				b = &ck->blocks.at(i);
//				
//				shader->Avtivate();
//
//				shader->setMat4("model", b->model);
//				shader->setMat4("ChunkModel", b->chunkModel);
//
//				for (unsigned int i = 0; i < 6; i++)
//				{
//					if (b->renderFaces[i])
//					{
//						vao[i].Bind();
//
//						if (b->type == ChunkTest::blockTypes::GRASS)
//						{
//							textures[0].Bind();
//						}
//						else if (b->type == ChunkTest::blockTypes::DIRT)
//						{
//							textures[1].Bind();
//						}
//						else
//						{
//							textures[2].Bind();
//						}
//
//						glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//						vao[i].Unbind();
//						//std::cout << i << std::endl;
//					}
//				}
//
//				std::cout << ck->ID << "/" << b->ID << std::endl;
//				Sleep(0.5);
//
//			}
//		}
//		
//
//		for (int i = 0; i <= 4; i++)
//		{
//			vao[6].Bind();
//			shader->Avtivate();
//			glm::mat4 model = glm::mat4(1.0f);
//
//			if (i == 0)
//			{
//				model = glm::translate(model, glm::vec3(camera->Position.x + 90, camera->Position.y, camera->Position.z));
//				model = glm::rotate(model, (float)glm::radians(270.0f), glm::vec3(0.0, 1.0f, 0.0f));
//			}
//			if (i == 1)
//			{
//				model = glm::translate(model, glm::vec3(camera->Position.x, camera->Position.y, camera->Position.z + 90));
//				model = glm::rotate(model, (float)glm::radians(180.0f), glm::vec3(0.0, 1.0f, 0.0f));
//			}
//			if (i == 2)
//			{
//				model = glm::translate(model, glm::vec3(camera->Position.x - 90, camera->Position.y, camera->Position.z));
//				model = glm::rotate(model, (float)glm::radians(90.0f), glm::vec3(0.0, 1.0f, 0.0f));
//			}
//			if (i == 3)
//			{
//				model = glm::translate(model, glm::vec3(camera->Position.x, camera->Position.y, camera->Position.z - 90));
//				//model = glm::rotate(model, (float)glm::radians(180.0f), glm::vec3(0.0, 1.0f, 0.0f));
//			}
//			if (i == 4)
//			{
//				model = glm::translate(model, glm::vec3(camera->Position.x, camera->Position.y + 100, camera->Position.z));
//				model = glm::rotate(model, (float)glm::radians(90.0f), glm::vec3(1.0, 0.0f, 0.0f));
//			}
//
//			//model = glm::rotate(model, (float)90 * i, glm::vec3(0.0, 1.0f, 1.0f));
//
//			shader->setMat4("model", model);
//			shader->setMat4("Chunkmodel", 1.0f);
//
//			textures[3].Bind();
//			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//			vao[6].Unbind();
//			textures[3].Unbind();
//		}
//
//
//
//		vao[7].Bind();
//		shader->setMat4("model", glm::mat4(1.0f));
//		textures[2].Bind();
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		vao[7].Unbind();
//		textures[2].Unbind();
//
//		glfwSwapBuffers(renderer->window);
//
//		(input);
//
//	}
//
//}