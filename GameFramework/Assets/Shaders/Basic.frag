#version 460 core
out vec4 FragColor;

in vec3 fColor;
in vec2 fTexCoord;
uniform float green;
uniform sampler2D texture1;
uniform sampler2D texture2;



void main(){
	FragColor = texture(texture1, fTexCoord);
}