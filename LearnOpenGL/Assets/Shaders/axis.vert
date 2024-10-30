#version 460 core
layout(location =0) in vec3 vPos;
layout(location =1) in vec3 vColor;
uniform mat4 uModelMat;
uniform mat4 uViewMat;
uniform mat4 uProjMat;

out vec3 fColor;

void main(){
	fColor = vColor;
	gl_Position =uProjMat * uViewMat * uModelMat* vec4(vPos, 1.0f);
}