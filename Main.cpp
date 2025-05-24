#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// These are notes made by Rudra Dey. Currently studying at the University of Toronto. Today's date is: 2025-05-24, 3:00 PM. 

// GLFW is a Graphics Library Framework used with OpenGL, OpenGL ES, and Vulkan. It allows developers to create and manage OpenGL
// contexts, and handle all sorts of input including: joystick, keyboard, mouse, controller, etc.

int main() {
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// This is the window object for GLFW, parameters are: width, height, name of window, fullscreen boolean, last one not important
	GLFWwindow* window = glfwCreateWindow(800, 800, "TutorialOpenGL", NULL, NULL);

	// This runs if the window objects fails to be created.
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// This function makes the window part of the current context, where the context is the whole of OpenGL. 
	glfwMakeContextCurrent(window);

	// To stop the window from closing, and have the program running indefinetely, we need a while loop.
	while (!glfwWindowShouldClose(window)) {
		// This function actively polls the events happening to the window; this includes window movement, mouse movements, and sort of
		// input, etc. Without this, the window will be in state of "not responding".
		glfwPollEvents(); 
	}


	// This function destoys the window.
	glfwDestroyWindow(window);

	// This function terminates the glfw API
	glfwTerminate();
	return 0;
}