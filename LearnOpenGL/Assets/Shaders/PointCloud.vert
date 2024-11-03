#version 460 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vColor;
out vec3 fColor;

uniform mat4 uModelMat;
uniform mat4 uViewMat;
uniform mat4 uProjMat;


void main(){
	
	gl_Position =uProjMat * uViewMat * uModelMat* vec4(vPos.x,-vPos.y,vPos.z, 1.0f);
	fColor = vColor;
}

