#include "ShaderReader.h"
#include <iostream>
#include "glad/glad.h"

unsigned int compileShader(unsigned int type, const std::string& context)
{
	unsigned int shaderId = glCreateShader(type);
	const char* scr = context.c_str();
	glShaderSource(shaderId, 1, &scr, nullptr);
	glCompileShader(shaderId);

	int status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		int length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shaderId, length, &length, message);
		std::cout << "[ERROR] " << message << std::endl;
		glDeleteShader(shaderId);
		return 0;
	}

	return shaderId;
}

unsigned int createProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();

	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(fs);
	glDeleteShader(vs);

	return program;
}