#version 460 core
out vec4 FragColor;
in vec3 fColor;
//in vec2 fTexCoord;
//uniform sampler2D uTexture;

void main(){
	//FragColor = texture(uTexture, fTexCoord);
	FragColor = vec4(fColor, 1.0f);
}