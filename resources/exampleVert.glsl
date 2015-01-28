#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texcoord;
uniform mat4 mvp_matrix;
out vec4 vColor;
out vec2 UV;
void main() {
	vColor = color;
	UV = texcoord;
	gl_Position = mvp_matrix *( vec4 (position, 1.0));
}