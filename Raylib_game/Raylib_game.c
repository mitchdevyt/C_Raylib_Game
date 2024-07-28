#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "Input.h"
#include "perlin.h"
#include "TerrainMeshGen.h"

#include "Engine/EngineTypes.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

void InGameUpdate();
void InGameRender();
void ResetGame();
Model GetHeigtMapMesh();
Model LoadSkyBox();

struct Game game;
float deltaTime;
int rowCount = 100;

float heightMapY = 10;

void Init()
{
    deltaTime = 0.0f;

    game.state = inGame;
}

void InitCamera(Camera* camera)
{
    camera->position = (Vector3){ 10.0f, 10.0f, 10.0f };     // Camera position
    camera->target = (Vector3){ -1.0f, -1.0f, -1.0f };          // Camera looking at point
    camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };              // Camera up vector (rotation towards target)
    camera->fovy = 45.0f;                                    // Camera field-of-view Y
    camera->projection = CAMERA_PERSPECTIVE;
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Renderer");

    Init();
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    P_SEED = 1010101;

    //Image checked = GenImageChecked(2, 2, 1, 1, RED, GREEN);
    //Texture2D texture = LoadTextureFromImage(checked);
    //UnloadImage(checked);

    // Define our custom camera to look into our 3d world
    Camera camera = { 0 };
    InitCamera(&camera);

    // Load skybox model
    Model skybox = LoadSkyBox();

    Model heightMapModel = GetHeigtMapMesh();
    float tris = heightMapModel.meshes[0].triangleCount;
    Vector3 heigtMapModelPosition = { 0.0f, 0.0f, 0.0f };

    DisableCursor();                    // Limit cursor to relative movement inside the windowd
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        //set delta time
        deltaTime = GetFrameTime();

        switch (game.state)
        {
        case mainMenu:

            break;
        case inGame:
            //----------------------------------------------------------------------------------
            // LOGIC
            //----------------------------------------------------------------------------------
            InGameUpdate();
            //built in camera controller
            UpdateCamera(&camera, CAMERA_FREE);
            if (IsKeyDown(KEY_Y))
                heigtMapModelPosition.y -= 10;
            if (IsKeyDown(KEY_U))
                heigtMapModelPosition.y += 10;
            //----------------------------------------------------------------------------------               
            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();
            ClearBackground(BLACK);

            BeginMode3D(camera);
                rlDisableBackfaceCulling();
                rlDisableDepthMask();
                    DrawModel(skybox, (Vector3) { 0, 0, 0 }, 1.0f, WHITE);
                rlEnableBackfaceCulling();
                rlEnableDepthMask();

            DrawModel(heightMapModel, heigtMapModelPosition, 1.0f, RED);
            DrawGrid(10, 1.0);

            EndMode3D();

            DrawFPS(10, 10);
            DrawText(TextFormat("dt: %f", deltaTime), 10, 30, 20, RED);
            DrawText(TextFormat("dt: %f", tris), 10, 60, 20, RED);
            EndDrawing();
            //InGameRender();
            break;
        case reset:
            ResetGame();
            break;
        }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}



void InGameUpdate()
{
}

void InGameRender()
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawFPS(10, 10);
    DrawText(TextFormat("dt: %f", deltaTime), 10, 30, 20, RED);
    EndDrawing();

}

void ResetGame()
{

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

Model GetHeigtMapMesh()
{
    Image hmap = LoadImage("resources/TerrainMap2.png");     // Load heightmap image (RAM)
    //Image redimage = LoadImage("resources/terrain/TFF_Terrain_Grass_1A_D.png");     // Load heightmap image (RAM)
    //Image greenimage = LoadImage("resources/terrain/TFF_Terrain_Earth_2A_D.png");     // Load heightmap image (RAM)
    //Image yellowimage = LoadImage("resources/terrain/TFF_Terrain_Grass_2A_D.png");     // Load heightmap image (RAM)
    //Image blueimage = LoadImage("resources/terrain/TFF_Terrain_Sand_1A_D.png");     // Load heightmap image (RAM)
  
    Image redimage = LoadImage("resources/terrain/red.png");     // Load heightmap image (RAM)
    Image greenimage = LoadImage("resources/terrain/green.png");     // Load heightmap image (RAM)
    Image yellowimage = LoadImage("resources/terrain/blue.png");     // Load heightmap image (RAM)
    Image blueimage = LoadImage("resources/terrain/yellow.png");     // Load heightmap image (RAM)


    Texture2D redTexture = LoadTextureFromImage(redimage);        // Convert image to texture (VRAM)
    Texture2D greenTexture = LoadTextureFromImage(greenimage);        // Convert image to texture (VRAM)
    Texture2D yellowTexture = LoadTextureFromImage(yellowimage);        // Convert image to texture (VRAM)
    Texture2D blueTexture = LoadTextureFromImage(blueimage);        // Convert image to texture (VRAM)

    Mesh mesh = GenMeshHeightmap2(hmap, (Vector3) { 50, heightMapY, 50 }); // Generate heightmap mesh (RAM and VRAM)
    Model model = LoadModelFromMesh(mesh);

    model.materials[0].shader = LoadShader(TextFormat("resources/shaders/glsl%i/Terrain/terrain.vs", GLSL_VERSION),
        TextFormat("resources/shaders/glsl%i/Terrain/Terrain2.fs", GLSL_VERSION));
    //model.materials[0].shader = LoadShader(0,TextFormat("resources/shaders/glsl%i/Terrain/terrain.fs", GLSL_VERSION));

    model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = redTexture;
    model.materials[0].maps[MATERIAL_MAP_METALNESS].texture = greenTexture;
    model.materials[0].maps[MATERIAL_MAP_NORMAL].texture = yellowTexture;
    model.materials[0].maps[MATERIAL_MAP_ROUGHNESS].texture = blueTexture;

    // Get shader locations
    int min_rock_slope = GetShaderLocation(model.materials[0].shader, "min_rock_slope");
    int max_grass_slope = GetShaderLocation(model.materials[0].shader, "max_grass_slope");
    int min_rockgrass_height = GetShaderLocation(model.materials[0].shader, "min_rockgrass_height");
    int max_sand_height = GetShaderLocation(model.materials[0].shader, "max_sand_height");

    float rockSlope = 0.5;
    float grassSlope = 0.9;
    float rockGrassHeight = 2.0;
    float sandHeight = 1.0;

    // Set shader values (they can be changed later)
    SetShaderValue(model.materials[0].shader, min_rock_slope, &rockSlope, SHADER_UNIFORM_FLOAT);
    SetShaderValue(model.materials[0].shader, max_grass_slope, &grassSlope, SHADER_UNIFORM_FLOAT);
    SetShaderValue(model.materials[0].shader, min_rockgrass_height, &rockGrassHeight, SHADER_UNIFORM_FLOAT);
    SetShaderValue(model.materials[0].shader, max_sand_height, &sandHeight, SHADER_UNIFORM_FLOAT);

    UnloadImage(redimage);             // Unload heightmap image from RAM, already uploaded to VRAM
    UnloadImage(greenimage);             // Unload heightmap image from RAM, already uploaded to VRAM
    UnloadImage(yellowimage);             // Unload heightmap image from RAM, already uploaded to VRAM
    UnloadImage(blueimage);             // Unload heightmap image from RAM, already uploaded to VRAM

    return model;
}
//https://crystallotus.itch.io/skybox-textures
Model LoadSkyBox()
{
    // Load skybox model
    Mesh cube = GenMeshCube(1.0f, 1.0f, 1.0f);
    Model skybox = LoadModelFromMesh(cube);

    // Set this to true to use an HDR Texture, Note that raylib must be built with HDR Support for this to work SUPPORT_FILEFORMAT_HDR

    // Load skybox shader and set required locations
    // NOTE: Some locations are automatically set at shader loading
    skybox.materials[0].shader = LoadShader(TextFormat("resources/shaders/glsl%i/SkyBox/skybox.vs", GLSL_VERSION),
        TextFormat("resources/shaders/glsl%i/SkyBox/skybox.fs", GLSL_VERSION));

    SetShaderValue(skybox.materials[0].shader, GetShaderLocation(skybox.materials[0].shader, "environmentMap"), (int[1]) { MATERIAL_MAP_CUBEMAP }, SHADER_UNIFORM_INT);
    SetShaderValue(skybox.materials[0].shader, GetShaderLocation(skybox.materials[0].shader, "doGamma"), (int[1]) { 0 }, SHADER_UNIFORM_INT);
    SetShaderValue(skybox.materials[0].shader, GetShaderLocation(skybox.materials[0].shader, "vflipped"), (int[1]) { 0 }, SHADER_UNIFORM_INT);



    Image img = LoadImage("resources/Skyboxes/skybox.png");
    skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);    // CUBEMAP_LAYOUT_PANORAMA
    UnloadImage(img);

    return skybox;
}


