#version 100

// Input vertex attributes
attribute vec3 vertexPosition;
attribute vec2 vertexTexCoord;
attribute vec3 vertexNormal;
attribute vec4 vertexColor;

// Input uniform values
uniform mat4 mvp;

// Output vertex attributes (to fragment shader)
varying vec2 fragTexCoord;
varying vec3 fragPosition;
varying vec3 normal;
// NOTE: Add here your custom variables

void main()
{
    // Send vertex attributes to fragment shader
    fragTexCoord = vertexTexCoord;
    fragPosition = vertexPosition;
    normal = vertexNormal;
    // Calculate final vertex position
    gl_Position = mvp*vec4(vertexPosition, 1.0);
}