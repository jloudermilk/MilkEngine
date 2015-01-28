#ifndef _UTILITIES_H_
#define _UTILITIES_H_


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" 
#include "GLFW/glfw3.h"


extern glm::mat4  Ortho;


// keep track of window size for things like the viewport and the mouse cursor
extern int g_gl_width;
extern int g_gl_height;
extern double fps;



struct Vertex
{
	union
	{
		struct
		{
			glm::vec3 Pos;
			glm::vec4 Color;
			glm::vec2 UV;
		};
		struct
		{
			float X, Y, Z;
			float R, G, B, A;
			float U, V;
		};
	};
	bool operator == (const Vertex& rhs){
		return (X == rhs.X && Y == rhs.Y && Z == rhs.Z
			&& R == rhs.R && G == rhs.G && B == rhs.B && A == rhs.A
			&& U == rhs.U && V == rhs.V);
	}
};

struct UV
{
	float U, V;
};

struct Transform
{
	glm::mat4 viewTranslate;
	glm::mat4 viewRotateZ;
	glm::mat4 modelScale;
	glm::mat4 MVP;
};


enum PlayType
{
	ONCE,
	LOOP,
	LOOPSECTION,
	PINGPONG,
	REVERSE,
	RANDOMLOOP,
	RANDOM,
	SINGLE
};


void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar, glm::mat4 & mat);

void Orthographic(float a_fWidth, float a_fHeight, float a_fNear, float a_fFar, glm::mat4 * mat);

void Perspective(float a_fUpFOV, float a_fAspectRatio, float a_fNear, float a_fFar, glm::mat4 * mat);


double getDeltaTime();
void resetDeltaTime();


#endif //_UTILITIES_H_