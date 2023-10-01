#version 450
out vec4 FragColor;
in vec2 UV;

uniform sampler2D _backgroundTexture, _noiseTexture;
uniform float iTime, _noiseRate;

void main() {
    vec2 noiseUV = UV + (iTime * _noiseRate);
    float noiseValue = texture(_noiseTexture, noiseUV).r;

    vec2 backgroundUV = UV + noiseValue * _noiseRate;
    vec4 backgroundColor = texture(_backgroundTexture, backgroundUV);

    FragColor = backgroundColor;
}