#include <shaderclass.h>

void Shader::parseShaders(const std::string filepath, ShaderProgramSource* shaders)
{
	std::fstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#Shader") != std::string::npos)
		{
			if (line.find("Vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("Fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}
	(*shaders).Vertex = ss[(int)ShaderType::VERTEX].str();
	(*shaders).Fragment = ss[(int)ShaderType::FRAGMENT].str();
}

unsigned int Shader::CompiledShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	if (source.c_str() == NULL)
	{
		printf("source does'nt exsist!");
		return -1;
	}
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}


	return id;
}

Shader::Shader(const std::string filepath, Shader::ShaderProgramSource* shaders)
{
	parseShaders(filepath, shaders);
	ID = glCreateProgram();
	unsigned int vs = CompiledShader(GL_VERTEX_SHADER, shaders->Vertex);
	unsigned int fs = CompiledShader(GL_FRAGMENT_SHADER, shaders->Fragment);

	GLCall(glAttachShader(ID, vs));
	GLCall(glAttachShader(ID, fs));
	GLCall(glLinkProgram(ID));
	GLCall(glValidateProgram(ID));

	glDeleteShader(vs);
	glDeleteShader(fs);
}

void Shader::Avtivate()
{
	glUseProgram(ID);
}

void Shader::DeleteShader()
{
	glDeleteProgram(ID);
}

int Shader::getUniformLocation(int ShaderID, const char* uniform)
{
	return glGetUniformLocation(ShaderID, uniform);
}