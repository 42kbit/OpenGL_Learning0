#pragma once
#include <string>
unsigned int compileShader(unsigned int type, const std::string& context);

unsigned int createProgram(const std::string& vertexShader, const std::string& fragmentShader);

