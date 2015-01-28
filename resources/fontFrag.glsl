#version 330
in vec2 UV;
uniform sampler2D tex;
uniform vec4 textColor;
out vec4 fragColor;
void main ()
{
	fragColor = texture(tex,UV) * textColor; 
}