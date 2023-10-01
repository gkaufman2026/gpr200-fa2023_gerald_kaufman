#version 450
out vec4 FragColor;
in vec2 UV;

uniform sampler2D _backgroundTexture, _noiseTexture, _secondBackgroundTexture;
uniform float iTime, _noiseRate;

void main() {
    vec2 noiseUV = UV + (iTime * _noiseRate);
    float noiseValue = texture(_noiseTexture, noiseUV).r;

    vec2 backgroundUV = UV + noiseValue * _noiseRate;

    vec4 backImage = texture(_backgroundTexture, backgroundUV);
    vec4 frontImage = texture(_secondBackgroundTexture, backgroundUV);
    vec3 background = mix(backImage.rgb, frontImage.rgb, frontImage.a * 0.85);

    FragColor = vec4(background, 1.0);
}