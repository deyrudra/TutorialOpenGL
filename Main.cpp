#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// These are notes made by Rudra Dey. Currently studying at the University of Toronto. Today's date is: 2025-05-24, 3:00 PM. 

// GLFW is a Graphics Library Framework used with OpenGL, OpenGL ES, and Vulkan. It allows developers to create and manage OpenGL
// contexts, and handle all sorts of input including: joystick, keyboard, mouse, controller, etc.

int main() {
	
	// Initialize GLFW
	glfwInit();

	// Tellilng GLFW which version of OpenGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Telling GLFW that we are going to use the CORE profile, which allows us to use the modern features of OPENGL.
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


	// Using glad and loading configs for OpenGL
	gladLoadGL();

	// Tell OpenGL the viewport/rendering area of our window
	glViewport(0, 0, 800, 800);

	// We will be using the graphics concept of Double Buffering using Front Buffers and Back Buffers

	// Abstract: Telling OpenGL to prepare to clear the colour of a buffer and give it another colour. 
	// The glClearColor function clears and sets new colours to be put onto the Color Buffer. The arguments to the glClearColor function 
	// are R, G, B, and Opacity, where 1.0f is 100%. This function comes before another function known as glClear.
	// The glClear function sets the bitplane area of the window/viewport (selected using glViewPort beforehand) to values selected by:
	// glClearColor, glClearDepth, and glClearStencil (in this case glClearColor). The argument of this function, selects a specific buffer,
	// known as the Color Buffer, which is selected using a bit: GL_COLOR_BUFFER_BIT = 0x00004000.
	// There are other buffers that can be selected, such as: GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT
	// The purpose of the Colour Buffer is to store the colour data for each pixel in the frame being rendered. It is a temporary buffer
	// where the you draw on your scene before it's rendered.
	// The purpose of the Depth Buffer also known as the Z-buffer, is to store depth info about a pixel, this allows us to determine
	// which object should be rendered in front of the other, when multiple objects occupy the same space.
	// The purpose of the Stencil Buffer is to control whihc pixels are drawn and which are to be discarded. Ultimately, used to create
	// visual effects such as outlines, shadows, decaling, etc.
	// The glfwSwapBuffers function takes in the window which you want to render on, and swaps the back buffer with the front buffer.
	glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);


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