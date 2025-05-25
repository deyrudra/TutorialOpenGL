#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// These are notes made by Rudra Dey. Currently studying at the University of Toronto. Today's date is: 2025-05-24, 3:00 PM. 

// GLFW is a Graphics Library Framework used with OpenGL, OpenGL ES, and Vulkan. It allows developers to create and manage OpenGL
// contexts, and handle all sorts of input including: joystick, keyboard, mouse, controller, etc.


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";






int main() {
	
	// Initialize GLFW
	glfwInit();

	// Tellilng GLFW which version of OpenGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Telling GLFW that we are going to use the CORE profile, which allows us to use the modern features of OPENGL.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Vertices for Triangle + more coordinates for more triangles sharing same vertices
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	// Creating indices[] array to identify the shapes
	GLuint indices[] =
	{
		0, 3, 5, // Lower Left Triangle
		3, 2, 4, // Lower Right Triangle
		5, 4, 1 // Upper Triangle
	};


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


	// Vertex Shader Stage
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Inputing Vertex Shader Source Code
	glCompileShader(vertexShader); // Need to compile shaders now, since the computer won't understand the source code.

	// Fragment Shader Stage
	GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Inputing Vertex Shader Source Code
	glCompileShader(fragmentShader); // Need to compile shaders now, since the computer won't understand the source code.

	// Basically tells the program to use these shaders.
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Deleting the shaders because they are already in the program.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	
	
	// We want to send data between the CPU and the GPU, but since it is kind've slow, we send it in big batches called Buffers.
	// Binding in OpenGL is all about making an object, the current object.
	// A VBO stands for Vertex Buffer Object. It a memory buffer stored in the GPU that holds vertex data. It's an array with large amounts
	// of data, in this case we only have one set of data (our triangle vertices). 
	// Using glBufferData we can store our data. In there the last parameter is configurable for performance.
	// The config 1 could be, STREAM: vertices are modified once, but used few times; STATIC: vertices are modified once, and used many times
	// ; DYNAMIC: vertices are modified many times, and used many times.
	// The config 2 could be DRAW; READ; COPY.
	// What is a VAO?
	// VAO stands for Vertex Array Object, it stores the configuration of vertex attributes such as which VBOs are bound, how the vertex data
	// is liad out (glVertexAttribPointer) and which vertex attributes are enabled (glEnableVertexAttribArray)
	// What is EBO?
	// EBO stands for Element Buffer Object, it is a buffer that stores indices telling the GPU how to reuse vertices efficiently when drawing
	// geometry (usually triangles). Instead of repeating the same vertex data, you can: Store unique vertices once in a VBO. Use the EBO to
	// specify which vertices make up each triangle by index. This reduces memory usage and improves performance; also saves coding time.
	// What does Binding something mean?
	// Binding means to make an object, the selected object.
	GLuint VAO, VBO, EBO;

	// Generate a Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO);

	// Generate a Vertex Buffer Object (VBO)
	glGenBuffers(1, &VBO);

	// Generating EBO w/ 1 object
	glGenBuffers(1, &EBO);

	// Bind the VAO (stores all vertex attribute configs)
	glBindVertexArray(VAO);

	// Bind the VBO specifiying that it is a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Upload vertex data to GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the EBO, specifying that it is a GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Upload vertices within the indices to the GPU
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// Define vertex attribute layout:
	//    - location 0 (matches layout in vertex shader)
	//    - 3 components (x, y, z)
	//    - data type: float
	//    - not normalized
	//    - stride between vertices: 3 * float
	//    - offset: start at beginning
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Enable the vertex attribute at location 0
	glEnableVertexAttribArray(0);

	// Unbind the VBO (good practice)
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind the VAO (good practice)
	glBindVertexArray(0);

	// Unbind the EBO (good practice): meaning we telling OpenGL we don't want the VAO to use the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



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
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3); // 0 represents the starting index of the vertices, and 3 is the # of vertices
		// Instead of glDrawArrays, we want to instead now use glDrawElements specifying which primative we want to use.
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // 9 represents the indices we want to draw, and 0 is the index


		// Need to swap buffers to update the image.
		glfwSwapBuffers(window);
		
		
		// This function actively polls the events happening to the window; this includes window movement, mouse movements, and sort of
		// input, etc. Without this, the window will be in state of "not responding".
		glfwPollEvents(); 

	}

	// Deleting all objects we've made
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);


	// This function destoys the window.
	glfwDestroyWindow(window);

	// This function terminates the glfw API
	glfwTerminate();
	return 0;
}