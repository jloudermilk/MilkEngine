// MilkEngine.cpp : Defines the entry point for the console application.
//
#define GLEW_STATIC
#include "GL/glew.h"

#include "GLFW/glfw3.h"
#include <stdio.h>
#include "GLLog.h"

#include "Sprite.h"
#include "FontManager.h"





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

	Orthographic(0.f, (float)g_gl_width, (float)g_gl_height, 0.f, -1.f, 1.f, Ortho);
	FontManager::Instance().LoadFont("../resources/NESish.xml");
//	Sprite * tester = new Sprite();

//	tester->LoadTexture("../resources/MegamanXSheet.png");
//	tester->m_Animator.ImportSheet("../resources/MegamanXSheet.xml");
//	tester->m_Animator.SetAnimation("run", LOOP);

	while (!glfwWindowShouldClose(window))
	{

		update_fps_counter(window);
		//put this in your render loop
		glViewport(0, 0, g_gl_width, g_gl_height);


		// wipe the drawing surface clean
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		FontManager::Instance().DrawString("Hello, my name is Inigo Montoya.\nYou killed my father.\nPrepare to die!",float2(0, g_gl_height / 2), 1);

//		tester->Update(.1f);

		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
		// update other events like input handling
		
		glfwPollEvents();
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, 1);
		}
		resetDeltaTime();
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