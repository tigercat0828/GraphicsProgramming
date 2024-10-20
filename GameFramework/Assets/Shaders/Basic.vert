#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;


out vec3 fColor;
out vec2 fTexCoord;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;


void main(){
	//gl_Position = transform * vec4(aPos, 1.0);
	gl_Position = projMat*viewMat*modelMat * vec4(aPos, 1.0);
	fTexCoord = aTexCoord;
}