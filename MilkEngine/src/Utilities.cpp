#include "Utilities.h"


glm::mat4   Ortho;
int g_gl_width = 640;
int g_gl_height = 480;
double deltaTime = 0;
int frames;
double fps, elapsedTime;




void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar, glm::mat4 & mat)
{

	float deltaX = a_fRight - a_fLeft;
	float deltaY = a_fTop - a_fBottom;
	float deltaZ = a_fNear - a_fFar;

	mat[0].x = 2.f / deltaX;
	mat[0].y = 0.f;
	mat[0].z = 0.f;
	mat[0].w = 0.f;

	mat[1].x = 0.f;
	mat[1].y = 2.f / deltaY;
	mat[1].z = 0.f;
	mat[1].w = 0.f;

	mat[2].x = 0.f;
	mat[2].y = 0.f;
	mat[2].z = 2.f / deltaZ;
	mat[2].w = 0.f;

	mat[3].x = ((a_fLeft + a_fRight) / (a_fLeft - a_fRight));
	mat[3].y = ((a_fBottom + a_fTop) / (a_fBottom - a_fTop));
	mat[3].z = (-(a_fNear + a_fFar) / (a_fFar - a_fNear));
	mat[3].w = 1.f;

}

void Orthographic(float a_fWidth, float a_fHeight, float a_fNear, float a_fFar, glm::mat4 & mat)
{
	mat = glm::ortho(a_fWidth, a_fHeight, a_fNear, a_fFar);
}

void Perspective(float a_fUpFOV, float a_fAspectRatio, float a_fNear, float a_fFar, glm::mat4 & mat)
{
	mat = glm::perspective(a_fUpFOV, a_fAspectRatio, a_fNear, a_fFar);
}

double getDeltaTime()
{
	return deltaTime;
}
void resetDeltaTime()
{

	deltaTime = glfwGetTime();
	elapsedTime += deltaTime;
	frames++;
	if (elapsedTime > 0.25)
	{
		fps = (double)frames / elapsedTime;
		elapsedTime = 0;
		frames = 0;
	}
	glfwSetTime(0);

}