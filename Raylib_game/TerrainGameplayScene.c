#include "TerrainGameplayScene.h"

void InitTerrainGamplayCamera(Camera* camera);
void SetupInput(Inputs* input);
void GetHeightMapMesh(Model* model);
void LoadSkyBox(Model* model);

float heightMapY = 1;
Scene3DTerrain SetupTerrainGameplayScene()
{
    Scene3DTerrain scene = { 0 };
    InitTerrainGamplayCamera(&scene.mainCamera);
    //SetupInput(&scene.inputs);
    GetHeightMapMesh(&scene.terrain);
    LoadSkyBox(&scene.skybox);

    return scene;
}

void InitTerrainGamplayCamera(Camera* camera)
{
    camera->position = (Vector3){ 10.0f, 10.0f, 10.0f };     // Camera position
    camera->target = (Vector3){ -1.0f, -1.0f, -1.0f };          // Camera looking at point
    camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };              // Camera up vector (rotation towards target)
    camera->fovy = 45.0f;                                    // Camera field-of-view Y
    camera->projection = CAMERA_PERSPECTIVE;
}

void SetupInput(Inputs* input)
{
    input->gamePadOrMnK = false;
    input->inputMap.forward_move = KEY_W;
    input->inputMap.backwards_move = KEY_S;
    input->inputMap.right_move = KEY_D;
    input->inputMap.left_move = KEY_A;

    input->inputMap.d_up = KEY_Y;
    input->inputMap.d_down = KEY_Y;
    input->inputMap.d_left = KEY_Y;
    input->inputMap.d_right = KEY_Y;
    input->inputMap.a = KEY_Q;
    input->inputMap.b = KEY_E;
    input->inputMap.x = KEY_Y;
    input->inputMap.y = KEY_Y;
    input->inputMap.start = KEY_Y;
    input->inputMap.select = KEY_Y;
    input->inputMap.r1 = KEY_Y;
    input->inputMap.r2 = KEY_Y;
    input->inputMap.r3 = KEY_LEFT_SHIFT;
    input->inputMap.l1 = KEY_Y;
    input->inputMap.l2 = KEY_Y;
    input->inputMap.l3 = KEY_Y;
}

void GetHeightMapMesh(Model* model)
{
    Image hmap = LoadImage("resources/heightMap.png");     // Load heightmap image (RAM)
    Image redimage = LoadImage("resources/terrain/TFF_Terrain_Grass_1A_D.png");     // Load heightmap image (RAM)
    Image greenimage = LoadImage("resources/terrain/TFF_Terrain_Earth_2A_D.png");     // Load heightmap image (RAM)
    Image yellowimage = LoadImage("resources/terrain/TFF_Terrain_Grass_2A_D.png");     // Load heightmap image (RAM)
    Image blueimage = LoadImage("resources/terrain/TFF_Terrain_Sand_1A_D.png");     // Load heightmap image (RAM)

    //Image redimage = LoadImage("resources/terrain/red.png");     // Load heightmap image (RAM)
    //Image greenimage = LoadImage("resources/terrain/green.png");     // Load heightmap image (RAM)
    //Image yellowimage = LoadImage("resources/terrain/blue.png");     // Load heightmap image (RAM)
    //Image blueimage = LoadImage("resources/terrain/yellow.png");     // Load heightmap image (RAM)


    Texture2D redTexture = LoadTextureFromImage(redimage);        // Convert image to texture (VRAM)
    Texture2D greenTexture = LoadTextureFromImage(greenimage);        // Convert image to texture (VRAM)
    Texture2D yellowTexture = LoadTextureFromImage(yellowimage);        // Convert image to texture (VRAM)
    Texture2D blueTexture = LoadTextureFromImage(blueimage);        // Convert image to texture (VRAM)

    Mesh mesh = GenMeshHeightmap2(hmap, (Vector3) { 1, heightMapY, 1 }); // Generate heightmap mesh (RAM and VRAM)
    *model = LoadModelFromMesh(mesh);

    model->materials[0].shader = LoadShader(TextFormat("resources/shaders/glsl%i/Terrain/terrain.vs", GLSL_VERSION),
        TextFormat("resources/shaders/glsl%i/Terrain/Terrain2.fs", GLSL_VERSION));
    //model.materials[0].shader = LoadShader(0,TextFormat("resources/shaders/glsl%i/Terrain/terrain.fs", GLSL_VERSION));

    model->materials[0].maps[MATERIAL_MAP_ALBEDO].texture = redTexture;
    model->materials[0].maps[MATERIAL_MAP_METALNESS].texture = greenTexture;
    model->materials[0].maps[MATERIAL_MAP_NORMAL].texture = yellowTexture;
    model->materials[0].maps[MATERIAL_MAP_ROUGHNESS].texture = blueTexture;

    // Get shader locations
    int min_rock_slope = GetShaderLocation(model->materials[0].shader, "min_rock_slope");
    int max_grass_slope = GetShaderLocation(model->materials[0].shader, "max_grass_slope");
    int min_rockgrass_height = GetShaderLocation(model->materials[0].shader, "min_rockgrass_height");
    int max_sand_height = GetShaderLocation(model->materials[0].shader, "max_sand_height");

    float rockSlope = 0.5;
    float grassSlope = 0.9;
    float rockGrassHeight = 2.0;
    float sandHeight = 1.0;

    // Set shader values (they can be changed later)
    SetShaderValue(model->materials[0].shader, min_rock_slope, &rockSlope, SHADER_UNIFORM_FLOAT);
    SetShaderValue(model->materials[0].shader, max_grass_slope, &grassSlope, SHADER_UNIFORM_FLOAT);
    SetShaderValue(model->materials[0].shader, min_rockgrass_height, &rockGrassHeight, SHADER_UNIFORM_FLOAT);
    SetShaderValue(model->materials[0].shader, max_sand_height, &sandHeight, SHADER_UNIFORM_FLOAT);

    model->materials[0].shader.locs[SHADER_LOC_MAP_NORMAL] = GetShaderLocation(model->materials[0].shader, "texture2");
    model->materials[0].shader.locs[SHADER_LOC_MAP_ROUGHNESS] = GetShaderLocation(model->materials[0].shader, "texture3");

    UnloadImage(redimage);             // Unload heightmap image from RAM, already uploaded to VRAM
    UnloadImage(greenimage);             // Unload heightmap image from RAM, already uploaded to VRAM
    UnloadImage(yellowimage);             // Unload heightmap image from RAM, already uploaded to VRAM
    UnloadImage(blueimage);             // Unload heightmap image from RAM, already uploaded to VRAM

}

//https://crystallotus.itch.io/skybox-textures
void LoadSkyBox(Model *model)
{
    // Load skybox model
    Mesh cube = GenMeshCube(1.0f, 1.0f, 1.0f);
    *model = LoadModelFromMesh(cube);

    // Set this to true to use an HDR Texture, Note that raylib must be built with HDR Support for this to work SUPPORT_FILEFORMAT_HDR

    // Load skybox shader and set required locations
    // NOTE: Some locations are automatically set at shader loading
    model->materials[0].shader = LoadShader(TextFormat("resources/shaders/glsl%i/SkyBox/skybox.vs", GLSL_VERSION),
        TextFormat("resources/shaders/glsl%i/SkyBox/skybox.fs", GLSL_VERSION));

    SetShaderValue(model->materials[0].shader, GetShaderLocation(model->materials[0].shader, "environmentMap"), (int[1]) { MATERIAL_MAP_CUBEMAP }, SHADER_UNIFORM_INT);
    SetShaderValue(model->materials[0].shader, GetShaderLocation(model->materials[0].shader, "doGamma"), (int[1]) { 0 }, SHADER_UNIFORM_INT);
    SetShaderValue(model->materials[0].shader, GetShaderLocation(model->materials[0].shader, "vflipped"), (int[1]) { 0 }, SHADER_UNIFORM_INT);



    Image img = LoadImage("resources/Skyboxes/skybox.png");
    model->materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);    // CUBEMAP_LAYOUT_PANORAMA
    UnloadImage(img);

}
