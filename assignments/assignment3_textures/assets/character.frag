#version 450
out vec4 FragColor;
in vec2 UV;

uniform sampler2D _characterTexture;
uniform float iTime, _transparencyRate;
void main() {
    vec4 characterColor = texture(_characterTexture, UV);

    float alpha = 0.5 + 0.5 * sin(_transparencyRate * iTime);
    characterColor.a *= alpha;
    
    FragColor = characterColor;
}