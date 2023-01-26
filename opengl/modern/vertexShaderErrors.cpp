#include <iostream>
#include <memory>
#include <optional>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../abstractions/GlUtils.hpp"
#include "../abstractions/ShaderUtil.hpp"

#include <cassert>

namespace {
	constexpr uint16_t windowHeight { 480 };
	constexpr uint16_t windowWidth { 640 };
}

using ShaderType = unsigned;
using ShaderId = unsigned;

static std::optional<ShaderType> compileShader(ShaderType type, std::string const& source) {
	unsigned id { glCreateShader(type) };
	char const* src { source.c_str() };
	
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result {};
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if(result == GL_FALSE) {
		int length {};
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		std::unique_ptr<char[]> log { new char[length] }; 

		glGetShaderInfoLog(id, length, &length, log.get());
		std::cout << "Failed to compile shader!";
		std::cout << log.get() << '\n';

		return std::nullopt;
	}

	return id;	
}

static unsigned createShader(std::string const& vertexShader, std::string const& fragmentShader) {
	unsigned program { glCreateProgram() };
	

	std::optional<ShaderId> vs { compileShader(GL_VERTEX_SHADER, vertexShader) };
	if(vs)
		glAttachShader(program, *vs);
	std::optional<ShaderId> fs { compileShader(GL_FRAGMENT_SHADER, fragmentShader) }; 
	if(fs)
	 	glAttachShader(program, *fs);

	glLinkProgram(program);

	int result{};
	int length{};
	// Check the program
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
	if ( length > 0 ){
		std::vector<char> errorMessage(length+1);
		glGetProgramInfoLog(program, length, nullptr, &errorMessage[0]);
		std::cout << &errorMessage[0] << '\n';
	}

	glValidateProgram(program);

	glDetachShader(program, *vs);
	glDetachShader(program, *fs);

	glDeleteShader(*vs); // marks for deletion
	glDeleteShader(*fs);	

	return program;
}

static void checkArgs(int argc, char** argv) {
	if(argc < 3) {
		std::cerr << "Program usage: " << argv[0] << " vertexShader.shdr fragmentShader.shdr\n";
		exit(1);
	}
}

static void initialize(int major, int minor) {
// initialize
	if(not glfwInit()) {
		assert("Could not initialize GLFW3!");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

static GLFWwindow* 
getWindow(unsigned width, unsigned height) {
	GLFWwindow* window{ glfwCreateWindow(width, height, "Window1", nullptr, nullptr) };
	// if window not created
	if(not window) {
		glfwTerminate();
		assert(false);
	}	
	return window;
}

int main(int argc, char** argv) {
	// args
	checkArgs(argc, argv);
	initialize(3, 3);	

	GLFWwindow* window = getWindow(windowWidth, windowHeight);
	// make window current cntext
	glfwMakeContextCurrent(window);

	
	// initialize glew
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
  		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}	
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	std::cout << glGetString(GL_VERSION) << '\n';
	
	// the Vertex Array ( before any other GL call ) && after context init
	unsigned vertexArrayId{};
	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);

	float position[] {
		// x    y
		-0.5, -0.5f, // vertex 1 position
		0.5f,  -0.5f, // vertex 2 position
 		0.5f, 0.5f,  // vertex 3 position
		-0.5f, 0.5f, // vertex 4 position
		-1.0f, 0.0f, // vertex 5 position
		1.0f, 0.0f // vertex 6 position
	};

	unsigned indices[] {
		// draw in this order
		0, 1, 2, 
		2, 3, 0,
		0, 4, 3,
		1, 5, 2
	};

	// the Buffers	
	unsigned int buffer{}; // identify the vertex buffer
	glGenBuffers(1, &buffer); // generate 1 buffer, put identifier in buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer); 
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), position, GL_STATIC_DRAW);	// give it to OpenGL

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
	
	// the Buffers	
	unsigned int indexBufferObj{}; // identify the vertex buffer
	glGenBuffers(1, &indexBufferObj); // generate 1 buffer, put identifier in buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObj); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * sizeof(unsigned), indices, GL_STATIC_DRAW);	// give it to OpenGL

	std::optional<std::string> vertexShaderCode { graphix::ShaderUtil::readShader(argv[1]) };
	std::optional<std::string> fragmentShaderCode { graphix::ShaderUtil::readShader(argv[2]) };
	
	if(not vertexShaderCode or not fragmentShaderCode) {
		std::cerr << "Was not able to read one of the shaders\n";
		assert(false);
	}

	unsigned int shader { createShader(*vertexShaderCode, *fragmentShaderCode) };

	glUseProgram(shader);

	// main loop
	while(not glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
		// glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
		GLCall(glDrawElements(GL_TRIANGLES, 12, GL_INT, nullptr));
	
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteProgram(shader);

	glfwTerminate();

	return 0;
}
