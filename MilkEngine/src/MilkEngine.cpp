// MilkEngine.cpp : Defines the entry point for the console application.
//
#define GLEW_STATIC
#include "GL/glew.h"

#include "GLFW/glfw3.h"
#include <stdio.h>
#include "GLLog.h"

#include "Sprite.h"





// a call-back function
void glfw_window_size_callback(GLFWwindow* window, int width, int height);

//call back before initalization of GLFW
void glfw_error_callback(int error, const char* description);

void update_fps_counter(GLFWwindow* window);

int main()
{
	//open an OS window using GLFW

	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3!\n");
		return 1;
	}

	GLFWwindow * window = glfwCreateWindow(g_gl_width,g_gl_height, "Hello Triangle", NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "ERROR: could not open window with GLFW3!\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	//start Glew
	glewExperimental = GLU_TRUE;
	glewInit();
	//get version info 
	const GLubyte * renderer = glGetString(GL_RENDERER);
	const GLubyte * version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
	
	
	// tells openGL to only draw onto pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/*
	//Other stuff goes here next
	float points[] =
	{
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};
	GLuint VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);

	glfwWindowHint(GLFW_SAMPLES, 4);


	const char* vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"void main (){"
		" gl_Position = vec4(vp,1.0);"
		"}";
	const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_color;"
		"void main (){"
		"frag_color = vec4(.5,0.0,0.5,1.0);"
		"}";
	// this creates a handle for my Vertex shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	//put the source into the shader
	glShaderSource(vs, 1, &vertex_shader, NULL);
	//Compile the shader
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	//put the source into the shader
	glShaderSource(fs, 1, &fragment_shader, NULL);
	//Compile the shader
	glCompileShader(fs);
	//generate a shader container
	GLuint shaderProgram = glCreateProgram ();
	//attach the shader to your program
	glAttachShader(shaderProgram, fs);
	glAttachShader(shaderProgram, vs);
	//"Link" the shaders together, its like a compile
	glLinkProgram(shaderProgram);
	*/




	//Ortho = glm::ortho(0, g_gl_width, g_gl_height, 0,-1,1);

	Orthographic(0.f, (float)g_gl_width, (float)g_gl_height, 0.f, -1.f, 1.f, Ortho);
	//Ortho = glm::mat4();

	Sprite * tester = new Sprite();
	tester->LoadTexture("../resources/megamanx.png");
	while (!glfwWindowShouldClose(window))
	{

		update_fps_counter(window);
		//put this in your render loop
		glViewport(0, 0, g_gl_width, g_gl_height);


		// wipe the drawing surface clean
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*	
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//draw points 0-3 from the currently bound VAO with currnet in-use shader
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		*/
		
	
		tester->Update(.1f);

		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
		// update other events like input handling
		glfwPollEvents();
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, 1);
		}
	}
	glfwTerminate();
	return 0;
}

void update_fps_counter(GLFWwindow* window) {
	static double previous_seconds = glfwGetTime();
	static int frame_count;
	double current_seconds = glfwGetTime();
	double elapsed_seconds = current_seconds - previous_seconds;
	if (elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		char tmp[128];
		sprintf(tmp, "opengl @ fps: %.2lf", fps);
		glfwSetWindowTitle(window, tmp);
		frame_count = 0;
	}
	frame_count++;
}

// a call-back function
void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
	g_gl_width = width;
	g_gl_height = height;

	/* update any perspective matrices used here */
}


//call back before initalization of GLFW
void glfw_error_callback(int error, const char* description) {
	fputs(description, stderr);
	gl_log(description, __FILE__, __LINE__);
}