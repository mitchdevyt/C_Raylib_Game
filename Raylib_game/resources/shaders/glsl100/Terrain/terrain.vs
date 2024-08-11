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
    fragPosition = vertexPosition;
    normal = vertexNormal;
    // Calculate final vertex position
    gl_Position = mvp*vec4(vertexPosition, 1.0);

    //rotate uv
    //fragTexCoord = vertexTexCoord*2.0-1.0;
    //float rotMod = mod(fragPosition.x * fragPosition.y * fragPosition.z,360.0);
    //float c = cos(rotMod);
    //float s = sin(rotMod);
    //
    //mat2 rotMat;
    //rotMat[0] = vec2(c,-s);
    //rotMat[1] = vec2(s,c);
    //
    //fragTexCoord = rotMat * vertexTexCoord;
    //fragTexCoord = fragTexCoord *0.5+0.5;
    fragTexCoord = vertexTexCoord;
}