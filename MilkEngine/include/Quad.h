#ifndef _QUAD_H_
#define _QUAD_H_

#include "GL/glew.h"
#include "GLLog.h" //For logging… stuff
#include "TextFileReader.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Utilities.h"

class Quad
{
public:
	static Quad& Instance();
	void Draw();

	glm::mat4 m_MVP;
	GLuint m_ShaderProgram;
	GLuint m_VAO; //Vertex Buffer

private:
	Quad();
	~Quad();
	
	GLuint m_EBO; //Element Buffer
	GLuint m_VBO; //Vertex Attributes 

	static Quad* MInstance;
	static void CleanUp();
};
#endif  //QUAD
