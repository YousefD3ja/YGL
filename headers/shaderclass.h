#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H


#include <glad/gl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glm/glm.hpp>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLCLearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLCLearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")> " <<
			function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

class Shader
{
	public:

		unsigned int ID;
		struct ShaderProgramSource
		{
			std::string Vertex;
			std::string Fragment;
		};

		// Create shader program
		Shader(const std::string filepath, ShaderProgramSource* shaders);
		
		// Parse shaders from file
		void parseShaders(const std::string filepath, ShaderProgramSource* shaders);

		// Compile shaders
		unsigned int CompiledShader(unsigned int type, const std::string& source);

		// Activate shader program
		void Avtivate();
		
		// Delete shader program
		void DeleteShader();

		static int getUniformLocation(int shaderID, const char* uniform);

		// utility uniform functions
	// ------------------------------------------------------------------------
		void setBool(const std::string& name, bool value) const;
		// ------------------------------------------------------------------------
		void setInt(const std::string& name, int value) const;
		// ------------------------------------------------------------------------
		void setFloat(const std::string& name, float value) const;
		// ------------------------------------------------------------------------
		void setVec2(const std::string& name, const glm::vec2& value) const;
		void setVec2(const std::string& name, float x, float y) const;
		// ------------------------------------------------------------------------
		void setVec3(const std::string& name, const glm::vec3& value) const;
		void setVec3(const std::string& name, float x, float y, float z) const;
		// ------------------------------------------------------------------------
		void setVec4(const std::string& name, const glm::vec4& value) const;
		void setVec4(const std::string& name, float x, float y, float z, float w) const;
		// ------------------------------------------------------------------------
		void setMat2(const std::string& name, const glm::mat2& mat) const;
		// ------------------------------------------------------------------------
		void setMat3(const std::string& name, const glm::mat3& mat) const;
		// ------------------------------------------------------------------------
		void setMat4(const std::string& name, const glm::mat4& mat) const;
};

#endif