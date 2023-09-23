#version 450
out vec4 FragColor;
in vec2 UV;
// UNIFORMS 
uniform vec3 iResolution;
uniform float iTime;
uniform float iScale; // 1.75
uniform vec3 iSunColor; // 1.0, 0.5, 0.0
uniform float iSunPosY; // 18
uniform float iSunSpeed; // 0.5
uniform float iSunGlow; // 5.0
uniform float iSunGlowBlur; // 0.25
uniform float iSunGlowRadius; // 0.05
uniform float iSunPosX; // -1.75
uniform float iStrength; // 0.5
uniform float iFrontForegroundHeight; // 2.5
uniform float iBackForegroundHeight; // 3.0
uniform float iForegroundSlope; // 0.1
uniform float iFrontForegroundVary; // 3.5
uniform float iBackForegroundVary; // 4.0
uniform vec3 iForegroundColor; // 0.55, 0.3, 0.1
uniform float iForegroundTopColor; // 1.0, 1.0, 1.0
uniform vec3 iSunGradient; // 1.0, 0.8, 0.6

void main(){
	vec2 uv = (iScale * UV - iResolution.xy) / min(iResolution.x, iResolution.y * (iScale / 10.0));

    float sunMovement = iSunPosY * abs(sin(iSunSpeed * iTime)) - iSunPosY;
    float sunDistance = distance(uv, vec2(iSunPosX, sunMovement));
    float sunPosition = clamp(sunDistance, 0.0, 0.3);

    vec3 sunColor = mix(iSunColor, iSunColor, sunPosition);

    float sunGlowSize = sunDistance / iSunGlow;
    float sunGlowBlur = abs(cos(iSunGlowBlur * iTime));
    float sunGlowRadius = abs(cos(iSunGlowRadius * iTime));
    
    float glow = iStrength * (1.0 - sunGlowSize * sunGlowBlur * sunGlowRadius);
    
    float foreground = step(iFrontForegroundHeight, -uv.y + iForegroundSlope * sin(uv.x * iFrontForegroundVary)); 
    float foregroundTwo = step(iBackForegroundHeight, -uv.y + iForegroundSlope * sin(uv.x * iBackForegroundVary));
    
    vec3 foregroundColor = mix(vec3(clamp(0.0, 1.0, uv.y)), iForegroundColor, foregroundTwo); 

    vec3 finalOutput = mix(sunColor + glow * iSunGradient, foregroundColor, foreground);

    FragColor = vec4(finalOutput, 1.0);
}