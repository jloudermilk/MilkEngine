#include "Quad.h"


Quad::Quad()
{
	//Default Shaders for Default constructor


	const char * VertexShader =  // Vertex Shaders deal with objects in 3D space
		"#version 330\n"
		"layout(location = 0) in vec3 position;"
		"layout(location = 1) in vec4 color;"
		"layout(location = 2) in vec2 texcoord;"
		"uniform mat4 mvp_matrix;"
		"out vec4 vColor;"
		"out vec2 UV;"
		"void main() {"
		"	vColor = color;"
		"	UV = texcoord;"
		"	gl_Position = mvp_matrix *( vec4 (position, 1.0));"
		"}";

	const char * FragmentShader =	// Fragment Shaders deals with pixel data
		"#version 330\n"
		"in vec4 vColor;"
		"in vec2 UV;"
		"out vec4 outColour;"
		"void main () {"
		"	UV;"
		"	outColour = vColor;"
		"}";

	// Compile Vertex Shader
	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &VertexShader, NULL);
	glCompileShader(m_VertexShader);
	printShaderInfoLog(m_VertexShader);

	// Compile Fragment Shader
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &FragmentShader, NULL);
	glCompileShader(m_FragmentShader);
	printShaderInfoLog(m_FragmentShader);


	// Link Shaders into Shader Program
	m_ShaderProgram = glCreateProgram();

	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);

	glLinkProgram(m_ShaderProgram);
	printProgramInfoLog(m_ShaderProgram);

	glUseProgram(m_ShaderProgram);


	GLfloat points[] =
	{
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0,
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0
	};

	
	

	// Create Buffers
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	
	


	// Create VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);


	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	
	// Specify layout of vertex data
	GLint posAttrib = glGetAttribLocation(m_ShaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 7 * (sizeof(float)), 0);

	GLint colAttrib = glGetAttribLocation(m_ShaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 7 * (sizeof(float)), (void*)(3 * sizeof(GLfloat)));

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	GLuint elements[] =
	{
		0, 1, 2, 3
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


	//make an identity matrix


	glm::mat4 viewTranslate = glm::translate(glm::mat4(), glm::vec3((float)g_gl_width / 2, (float)g_gl_height / 2, 1));
	glm::mat4 Model = glm::scale(glm::mat4(), glm::vec3(50,50, 1));

		m_MVP = Ortho * viewTranslate * Model;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindVertexArray(0);

}


Quad::~Quad()
{
}

void Quad::Draw()
{
	glUseProgram(m_ShaderProgram);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	
	GLuint mv_location = glGetUniformLocation(m_ShaderProgram, "mvp_matrix");
	glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr( m_MVP));
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);

}

