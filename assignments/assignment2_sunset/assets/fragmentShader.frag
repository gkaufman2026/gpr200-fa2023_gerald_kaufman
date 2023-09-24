#version 450
out vec4 FragColor;
in vec2 UV;
// UNIFORMS 
uniform vec3 iResolution;
uniform float iTime;
uniform float iScale;
uniform vec3 iSunColor;
uniform float iSunPosY;
uniform float iSunSpeed;
uniform float iSunGlow;
uniform float iSunGlowBlur;
uniform float iSunGlowRadius;
uniform float iSunPosX;
uniform float iStrength;
uniform float iFrontForegroundHeight;
uniform float iBackForegroundHeight;
uniform float iForegroundSlope;
uniform float iFrontForegroundVary;
uniform float iBackForegroundVary;
uniform vec3 iForegroundColor;
uniform float iForegroundTopColor;
uniform vec3 iSunGradient;

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