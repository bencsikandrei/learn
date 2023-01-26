#include <iostream>
#include <memory>

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

	// main loop
	while(not glfwWindowShouldClose(window.get()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// legacy opengl
		glBegin(GL_TRIANGLES);
		// vanilla vertices
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		
		glEnd();

		glfwSwapBuffers(window.get());

		glfwPollEvents();
	}

	return 0;
}
