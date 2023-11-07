#version 450
#define MAX_LIGHTS 4

out vec4 FragColor;

in Surface{
	vec2 UV;
}fs_in;

struct Light
{
	vec4 position;
	vec3 color;
};
uniform Light _Light;

uniform sampler2D _Texture;

void main(){
	FragColor = texture(_Texture,fs_in.UV);
}