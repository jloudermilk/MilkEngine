#ifndef _QUAD_H_
#define _QUAD_H_

#include "GL/glew.h"
#include "GLLog.h" //For logging� stuff
#include "TextFileReader.h"
#include "Utilities.h"

class Quad
{
public:
	Quad();
	~Quad();
	GLuint m_VBO; //Vertex Buffer
	GLuint m_EBO; //Element Buffer
	GLuint m_VAO; //Vertex Attributes 
	GLuint m_FragmentShader;
	GLuint m_VertexShader;

	GLuint m_ShaderProgram;


	void Draw();
private:
};
#endif  //QUAD
