#version 330
in vec4 vColor;
in vec2 UV;
out vec4 outColour;
uniform sampler2D diffuseTexture;
void main () {

//outColour =  vColor;
outColour =  texture2D(diffuseTexture, UV) *vColor;
}