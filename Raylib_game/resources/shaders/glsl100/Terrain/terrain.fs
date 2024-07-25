#version 100

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec3 fragPosition;
// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;

// Input uniform values
uniform float maxHeight;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

void main()
{
    float h = lerp(0,maxHeight,fragPosition.y);

    // Texel color fetching from texture sampler
    vec4 texelColor = texture2D(texture0, fragTexCoord);

    // Calculate final fragment color
    gl_FragColor = texelColor;
}


float lerp(foat a, float b, float t)
{
    return a + t * (b - a);
}

float normalize(float min, float max, float v)
{
    return (v-min)/(max-min);
}