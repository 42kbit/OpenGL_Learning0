#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void glfw_window_size_callback(GLFWwindow*, int width, int height)
{
	glViewport(0,0,width,height);
}

int main(void)
{
    GLFWwindow* windowPtr;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    windowPtr = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!windowPtr)
    {
        glfwTerminate();
        return -1;
    }

	glfwSetWindowSizeCallback(windowPtr, glfw_window_size_callback);

	/* Make the window's context current */
    glfwMakeContextCurrent(windowPtr);
	
	if(!gladLoadGL())
	{
		std::cout << "Cannot load GLAD" << std::endl;
		exit(-1);
	}
	std::cout << "[OpenGL] VERSION: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "[OpenGL] RENDERER: " << glGetString(GL_RENDERER) << std::endl;
	
	float verts[] = {0,0, 1,0, 0,1};
	
	uint32_t vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
		
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(windowPtr))
    {
        /* Render here */
		glClearColor(0,1,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
		
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(windowPtr);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}