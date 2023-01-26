#include <iostream>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cassert>

namespace {
	constexpr uint16_t windowHeight { 480 };
	constexpr uint16_t windowWidth { 640 };
}

// custom deleter
auto glfwDeleter {
	[](auto _) {
		glfwTerminate();
	}
};


int main() {
	std::unique_ptr<GLFWwindow, decltype(glfwDeleter)> window{nullptr, glfwDeleter};
	// initialize
	if(not glfwInit()) {
		assert("Could not initialize GLFW3!");
	}

	// create the window
	window.reset(glfwCreateWindow(windowWidth, windowHeight, "Window1", nullptr, nullptr));
	// if window not created
	if(not window) {
		glfwTerminate();
		assert(false);
	}

	// make window current cntext
	glfwMakeContextCurrent(window.get());

	// initialize glew
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
  		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}	
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	std::cout << glGetString(GL_VERSION) << '\n';

	unsigned int buffer{};
	float position[6] {
		// x    y
		-0.5, -0.5f, // vertex 1 position
		0.0f,  0.5f, // vertex 2 position
 		0.5f, -0.5f  // vertex 3 position
	};
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);	

	// enable the array
	glEnableVertexAttribArray(0);
	// declare gl attributs pointers
	glVertexAttribPointer(
		0 /* we only have one attrib*/, 
		2, /* size in elements of the attrib */ 
		GL_FLOAT /* type used */,
		GL_FALSE /* normalized */,
		sizeof(float) * 2 /* stride */, 
		0 // position in the struct
	);

	// main loop
	while(not glfwWindowShouldClose(window.get()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window.get());

		glfwPollEvents();
	}

	return 0;
}
