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
		-0.5, -0.5f,
		0.0f,  0.5f,
		0.5f, -0.5f
	};
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, );	

	// main loop
	while(not glfwWindowShouldClose(window.get()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window.get());

		glfwPollEvents();
	}

	return 0;
}
