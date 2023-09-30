#version 450
out vec4 FragColor;
in vec2 UV;

uniform sampler2D _backgroundTexture, _characterTexture;
void main() {
	FragColor = texture(_backgroundTexture, UV);
}