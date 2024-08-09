#version 100
//https://www.youtube.com/watch?v=x7ti3AEhV18
precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec3 fragPosition;
// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;
varying vec3 normal;

// Input uniform values
uniform float min_rock_slope;
uniform float max_grass_slope;
uniform float min_rockgrass_height;
uniform float max_sand_height;


uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;


/*void main()
{
    float normalizedHeight = clamp((fragPosition.y-minHeight)/(maxHeight-minHeight), 0.0, 1.0);



}*/

void main()
{
    vec4 snowTex = texture2D(texture0, fragTexCoord);
    vec4 grassTex = texture2D(texture1, fragTexCoord);
    vec4 rockTex = texture2D(texture2, fragTexCoord);
    vec4 sandTex = texture2D(texture3, fragTexCoord);
    
    //float normalizedHeight = clamp((fragPosition.y-0.0)/(10.0-0), 0.0, 1.0);

    float rock_grass_weight = normal.y;

    float sand_rockgrass_weight = fragPosition.y;

    rock_grass_weight = max(min_rock_slope, rock_grass_weight);
    rock_grass_weight = min(max_grass_slope, rock_grass_weight);
    rock_grass_weight -= min_rock_slope;
    rock_grass_weight /= max_grass_slope - min_rock_slope;

    sand_rockgrass_weight = max(min_rockgrass_height, sand_rockgrass_weight);
    sand_rockgrass_weight = min(max_sand_height, sand_rockgrass_weight);
    sand_rockgrass_weight -= min_rockgrass_height;
    sand_rockgrass_weight /= max_sand_height - min_rockgrass_height;

    vec4 c = mix(snowTex,grassTex,rock_grass_weight);
    //vec4 b = mix(sandTex,c,normalizedHeight);
    //vec4 b = mix(sandTex,c,0.0);

    if(fragPosition.y< 20.0)
       c=sandTex;
    gl_FragColor = c;
}