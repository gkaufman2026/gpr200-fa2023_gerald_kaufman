#version 450
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 uUV;
out vec2 UV;

uniform vec2 _aspectRatio, _imageSize;
uniform float _posX, _posY;
uniform float iTime, _yAxisMovement, _xAxisMovement;

void main() {
    UV = uUV;
    float newX = (vPos.x + _posX + _xAxisMovement) * (_imageSize.x / _aspectRatio.x);
    float newY = (vPos.y + _posY + _yAxisMovement) * (_imageSize.y / _aspectRatio.y);

    gl_Position = vec4(newX, newY, vPos.z, 1.0);
}