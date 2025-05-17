#include <camera.h>


PlayerObject::PlayerObject(glm::vec3 position, Texture2D* textureList, int textureListSize)
{
	Position = position;
	WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Yaw = YAW;
	Pitch = PITCH;
	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVITY;
	fov = ZOOM;
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	Hight = position.y;
	currentBlock = ChunkManager::blockTypes::GRASS;
	currentChunk = nullptr;
	textures = textureList;
	textureListSize = textureListSize;
	updateCameraVectors();
}

void PlayerObject::setCameraView()
{
	view = glm::lookAt(Position, Position + Front, Up);
}

void PlayerObject::SetPerspective(float angle, float screenWidth, float screenHeight, float nearf, float farf)
{
	projection = glm::perspective(glm::radians(angle), screenWidth / screenHeight, nearf, farf);
}

void PlayerObject::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);

	glm::vec3 Crosshair;
	front.x = cos(glm::radians(-Yaw)) * cos(glm::radians(-Pitch));
	front.y = sin(glm::radians(-Pitch));
	front.z = sin(glm::radians(-Yaw)) * cos(glm::radians(-Pitch));
	CrosshairFront = glm::normalize(Crosshair);


	uFront = front;

	// also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));
	Position.y = Hight;

}

void PlayerObject::ProcessKeyboard(cameraMovement direction, float deltaTime) 
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position -= glm::normalize(glm::cross(glm::cross(Front, Up), WorldUp)) * velocity;
	if (direction == BACKWARD)
		Position += glm::normalize(glm::cross(glm::cross(Front, Up), WorldUp)) * velocity;
	if (direction == LEFT)
		Position -= glm::normalize(glm::cross(Front, Up)) * velocity;
	if (direction == RIGHT)
		Position += glm::normalize(glm::cross(Front, Up)) * velocity;
	if (direction == UP)
		Hight = Position.y + 10 * deltaTime;
	if (direction == DOWN)
		Hight = Position.y - 10 * deltaTime;
	Position.y = Hight;

}

void PlayerObject::ProcessCameraPos()
{

	if (Position.y > 2.5)
	{
		Hight = 2;
		Position.y = 2;
	}
	else if (Position.y < 2)
	{
		Hight = 2;
		Position.y = 2;
	} 
	
	Position.y = Hight;
}