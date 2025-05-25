# Creating Triangles

In OpenGL everything is in 3D space, however what you see on the screen is 2D. Which means, OpenGL is all about transforming 3D Coordinates to 2D Pixels that fit on the screen.
This process is called the graphics pipeline of OpenGL.
There are two parts to this pipeline:
1. The first part transforms your 3D Coordinates into 2D Coordinates
2. The second part transforms your 2D Coordinates into actual coloured pixels.

**The Graphics Pipeline**
- Takes as input a set of 3D coordinates and outputs coloured 2D pixels on the screen.
- Can be split into several steps (where each step has one specific function) and all the steps lead into one another.
	- These steps can happen in parallel (and thus graphics cards todays can quickly process this data). Using the GPU's many cores to run small programs for each step of the pipeline.
	- These small programs are called **shaders.**
	- **Shaders** are written in the OpenGL Shading Language (GLSL).

**Forming a Triangle**
- As input to the graphics pipeline we pass in a list of three 3D coordinates that form a triangle. We pass it through an array called `Vertex Data;`. This vertex data is a collection of vertices.
	- A **vertex** is a collection of data per 3D coordinate. The data can be represented using vertex attributes (so basically any data we would like, but most likely just a color value and a 3D position).
- How does OpenGL know to form a Triangle out of the given vertices?
	- When drawing using the collection of coordinates/vertices, we give a hint to OpenGL to signify whether our vertices should draw out a collection of points, collection of triangles, or just one line.
	These hints are called **primatives** and are given to OpenGL when drawing. Some of the primatives are: `GL_POINTS, GL_TRIANGLES, GL_LINE_STRIP`

![PipelineSteps](https://learnopengl.com/img/getting-started/pipeline.png)
- **Vertex Shader:** Takes as input a single vertex; with the purpose of transforming the 3D coordinates into different 3D coordinates.
The vertex shader gives you control over how each vertex is positioned and what data it carries forward. It's essential for transforming
3D models into the correct space for rendering and for enabling custom visual effects. The output of the vertex shader stage is optionally
passed to the **geometry shader stage**.
- **Geometry Shader:** Takes as input a collection of vertices that form a primitive and has the ability to generate other shpaes by making/emitting new vertices.
As an example, a second triangle could be made out of a given shape (this shape being a collection of vertices that form a primitive).
- **Primative/Shape Assembly:** Takes as input all the vertices (either from the Vertex Shader stage or the Geometry Shader stage) and forms one or more primitives and assembles all 
the poitns in the primitive shape given. Example: two triangles
- **Rasterization:** Takes as input the output of the primative assembly stage where it maps the resulting primitives to the corresponding pixels on the screen. Resulting in fragments
for the fragment shader to use. Before this occurs though, clipping is performed; clipping discards all fragments that are outside the view (increasing performance)
- **Fragment Shader:** Calculates the final colour of a pixel, including shading and other effects.
- **Alpha Tests and Blending Stage:** This stage checks for corresponding depth (and stencil) value of the fragment to check if the fragment is in front or behind other objects and if it should be discarded.
- 


