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

float lerp(float a, float b, float t)
{
    return a + t * (b - a);
}
float lerpV(vec4 a, vec4 b, float t)
{
    vec4 result;
    result.x = a.x + t * (b.x - a.x);
    result.y = a.y + t * (b.y - a.y);
    result.z = a.z + t * (b.z - a.z);
    result.w = a.w + t * (b.w - a.w);
    return result;
}
float normalize(float min, float max, float v)
{
    return (v-min)/(max-min);
}

void main()
{
    float h = lerp(0.0,maxHeight,fragPosition.y);
    vec4 texelColor0 = texture2D(texture0, fragTexCoord);
    vec4 texelColor1 = texture2D(texture1, fragTexCoord);
    vec4 texelColor2 = texture2D(texture2, fragTexCoord);
    vec4 texelColor3 = texture2D(texture3, fragTexCoord);
    
    vec4 c = vec4(0.0,0.0,0.0,0.0);
    
    if(fragPosition.y<maxHeight)
        c = texelColor0;
    if(fragPosition.y<maxHeight*0.75)
       c = texelColor1;
    if(fragPosition.y<maxHeight*0.5)
        c = texelColor2;
    if(fragPosition.y<maxHeight*0.25)
        c = texelColor3;
    
    gl_FragColor = c;
    
    
    // Texel color fetching from texture sampler
    //vec4 b = vec4(0.2,0.2,0.2,1.0);

    //vec4 c = lerpV(texelColor,vec4(0.2,0.2,0.2,1.0),h);

    // Calculate final fragment color
}



/*vec4 texelColor0 = texture2D(texture0, fragTexCoord);
    vec4 texelColor1 = texture2D(texture1, fragTexCoord);

    float x = fract(fragTexCoord.s);
    float final = smoothstep(divider - 0.1, divider + 0.1, x);

    gl_FragColor = mix(texelColor0, texelColor1, final);
    
    if(h<1.0)
       c = texelColor0;
    if(h<0.75)
       c = texelColor1;
    if(h<0.50)
        c = texelColor2;
    if(h<0.25)
       c = texelColor3;
    */