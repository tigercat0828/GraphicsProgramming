#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
//layout (location = 1) in vec2 aTexCoord;

//out vec2 fTexCoord;
out vec3 fColor;
uniform mat4 uModelMat;
uniform mat4 uViewMat;
uniform mat4 uProjMat;

void main(){
	//gl_Position = transform * vec4(aPos, 1.0);
	//fTexCoord = aTexCoord;
	
	gl_Position = uProjMat*uViewMat*uModelMat * vec4(aPos, 1.0);
	fColor = aColor;
}