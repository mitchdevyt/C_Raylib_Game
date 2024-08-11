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
uniform float min_sand_height;
uniform float max_sand_height;


uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

void main()
{
    vec4 snowTex = texture2D(texture0, fragTexCoord);
    vec4 grassTex = texture2D(texture1, fragTexCoord);
    vec4 rockTex = texture2D(texture2, fragTexCoord);
    vec4 sandTex = texture2D(texture3, fragTexCoord);
    
    float rock_grass_weight = normal.y;

    rock_grass_weight = max(min_rock_slope, rock_grass_weight);
    rock_grass_weight = min(max_grass_slope, rock_grass_weight);
    rock_grass_weight -= min_rock_slope;
    rock_grass_weight /= max_grass_slope - min_rock_slope;

    //if we are below the sand hieght return 0
    float h = (fragPosition.y - max_sand_height) / abs(fragPosition.y - max_sand_height + 1.0);
    float sand_rockgrass_weight = clamp(h, 0.0, 1.0);

    vec4 c = mix(grassTex,snowTex,rock_grass_weight);
    vec4 b = mix(sandTex,c,sand_rockgrass_weight);

    //if(fragPosition.y< 20.0)
       //b=sandTex;
    gl_FragColor = b;
}