// headers/camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <objects.h>

namespace ChunkTest
{
	class Chunk;
	typedef struct chunk;
	enum blockTypes;
}

enum cameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 10.0f;
const float SENSITIVITY = 0.2f;
const float ZOOM = 45.0f;




class Camera
{
	public:
		// euler Angles
		float Yaw;
		float Pitch;
		// camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;
		float Hight;
		bool isRunning;

		Camera(glm::vec3 position);

		// camera position
		glm::vec3 Position;
		// the point where the camera is looking
		glm::vec3 CameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

		// the z axis of the camera
		glm::vec3 CameraDirection = glm::normalize(Position - CameraTarget);

		// y axis
		glm::vec3 WorldUp;
	
		/// Geting the cross product of the y and z axis aka the x axis of the camera
		glm::vec3 Right;

		// Getting the crss product of the z and x axis aka the y axis of the camera
		glm::vec3 Up;

		glm::vec3 Front;
		glm::vec3 uFront;

		glm::vec3 FrontBlock;

		glm::vec3 placeableBlock;

		int range = 2;

		glm::vec3 direction;


		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);


		ChunkTest::chunk* currentChunk;

		ChunkTest::blockTypes currentBlock;

		bool placedBlock;

		float fov;


		void setCameraView();

		void SetPerspective(float angle, float screenWidth, float screenHeight, float nearf, float farf);

		void InitializeView(glm::vec3 vector);

		void ProcessKeyboard(cameraMovement direction, float deltaTime);

		void ProcessCameraPos();


	private:
		void updateCameraVectors();
		

};

#endif