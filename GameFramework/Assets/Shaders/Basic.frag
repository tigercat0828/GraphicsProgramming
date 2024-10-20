#version 460 core
out vec4 FragColor;

in vec2 fTexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
	FragColor = mix(texture(texture1, fTexCoord),texture(texture2, fTexCoord),0.8);
}