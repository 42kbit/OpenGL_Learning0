#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Modules/FileReader/FileReader.h"
#include "Modules/ShaderReader/ShaderReader.h"

void glfw_window_size_callback(GLFWwindow*, int width, int height)
{
	glViewport(0,0,width,height);
}

int main(void)
{
    GLFWwindow* windowPtr;

    if (!glfwInit())
        return -1;

    windowPtr = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!windowPtr)
    {
        glfwTerminate();
        return -1;
    }

	glfwSetWindowSizeCallback(windowPtr, glfw_window_size_callback);

    glfwMakeContextCurrent(windowPtr);

	if(!gladLoadGL())
	{
		std::cout << "Cannot load GLAD" << std::endl;
		exit(-1);
	}
	std::cout << "[OpenGL] VERSION: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "[OpenGL] RENDERER: " << glGetString(GL_RENDERER) << std::endl;

	float verts[] =
	{
		0,0,0,
		1,0,0,
		0,1,0
	};

	uint32_t programID = createProgram(readFile("res/shaders/vertex.glsl"), readFile("res/shaders/flat_color.glsl"));

	uint32_t vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(windowPtr))
    {
		glClearColor(0,1,0,1);
        glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

        glfwSwapBuffers(windowPtr);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
