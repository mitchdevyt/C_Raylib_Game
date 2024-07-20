#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "Input.h"
#include "perlin.h"

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
Mesh GenMesh(void);

struct Game game;
float deltaTime;
int rowCount = 100;

void Init()
{
    deltaTime = 0.0f;

    game.state = inGame;
}

void InitCamera(Camera* camera)
{
    camera->position = (Vector3){ 0.0f, 5.0f, 0.0f };     // Camera position
    camera->target = (Vector3){ -1.0f, 0.0f, -1.0f };          // Camera looking at point
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
    //const int c = rowCount * rowCount;
    //float vertsList[c];
    P_SEED = 1010101;

    Image checked = GenImageChecked(2, 2, 1, 1, RED, GREEN);
    Texture2D texture = LoadTextureFromImage(checked);
    UnloadImage(checked);

    // Define our custom camera to look into our 3d world
    Camera camera = { 0 };
    InitCamera(&camera);

    Mesh mesh = GenMesh();
    Model model = LoadModelFromMesh(mesh);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    Vector3 position = { 0.0f, -20.0f, 0.0f };

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

            //----------------------------------------------------------------------------------               
            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();
            ClearBackground(BLACK);

            BeginMode3D(camera);

            DrawModel(model, position, 1.0f, RED);
            DrawGrid(10, 1.0);

            EndMode3D(); 
           
            DrawFPS(10, 10);
            DrawText(TextFormat("dt: %f", deltaTime), 10, 30, 20, RED);
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


Mesh GenMesh(void)
{

    Mesh mesh = { 0 };
    // NOTE: One vertex per pixel
    int r = rowCount * 2;
    mesh.triangleCount = r * r;    // One quad every four pixels

    mesh.vertexCount = mesh.triangleCount * 3;

    mesh.vertices = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    mesh.normals = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    mesh.texcoords = (float*)MemAlloc(mesh.vertexCount * 2 * sizeof(float));

    int texLength = mesh.vertexCount * 2;

    int vCounter = 0;       // Used to count vertices float by float
    int tcCounter = 0;      // Used to count texcoords float by float
    int nCounter = 0;       // Used to count normals float by float

    Vector3 scaleFactor = { 5, 5, 5 };

    Vector3 vA = { 0 };
    Vector3 vB = { 0 };
    Vector3 vC = { 0 };
    Vector3 vN = { 0 };

    float xx = 0;
    float zz = 0;
    
    float freq = 0.4;
    int depth = 10;
    int yDown = 10;
    for (int z = 0; z < rowCount; z++)
    {
        for (int x = 0; x < rowCount; x++)
        {
            // Fill vertices array with data
            //----------------------------------------------------------

            // one triangle - 3 vertex
            xx = (float)x * scaleFactor.x;
            zz = (float)z * scaleFactor.z;
            mesh.vertices[vCounter] = xx;
            float p = perlin2d(xx, zz, freq, depth) * yDown;
            mesh.vertices[vCounter + 1] = p;
            mesh.vertices[vCounter + 2] = zz;

            xx = (float)x * scaleFactor.x;
            zz = (float)(z + 1) * scaleFactor.z;
            mesh.vertices[vCounter + 3] = xx;
            mesh.vertices[vCounter + 4] = perlin2d(xx, zz, freq, depth) * yDown;
            mesh.vertices[vCounter + 5] = zz;

            xx = (float)(x + 1) * scaleFactor.x;
            zz = (float)z * scaleFactor.z;
            mesh.vertices[vCounter + 6] = xx;
            mesh.vertices[vCounter + 7] = perlin2d(xx, zz, freq, depth) * yDown;
            mesh.vertices[vCounter + 8] = zz;

            // Another triangle - 3 vertex
            xx = mesh.vertices[vCounter + 6];
            zz = mesh.vertices[vCounter + 8];
            mesh.vertices[vCounter + 9] = mesh.vertices[vCounter + 6];
            mesh.vertices[vCounter + 10] = perlin2d(xx, zz, freq, depth) * yDown;// mesh.vertices[vCounter + 7];
            mesh.vertices[vCounter + 11] = mesh.vertices[vCounter + 8];

            xx = mesh.vertices[vCounter + 3];
            zz = mesh.vertices[vCounter + 5];
            mesh.vertices[vCounter + 12] = mesh.vertices[vCounter + 3];
            mesh.vertices[vCounter + 13] = perlin2d(xx, zz, freq, depth) * yDown;// mesh.vertices[vCounter + 4];
            mesh.vertices[vCounter + 14] = mesh.vertices[vCounter + 5];

            xx = (float)(x + 1) * scaleFactor.x;
            zz = (float)(z + 1) * scaleFactor.z;
            mesh.vertices[vCounter + 15] = xx;
            mesh.vertices[vCounter + 16] = perlin2d(xx, zz, freq, depth) * yDown;
            mesh.vertices[vCounter + 17] = zz;
            vCounter += 18;     // 6 vertex, 18 floats

            // Fill texcoords array with data
            //--------------------------------------------------------------
            mesh.texcoords[tcCounter] = 0;
            mesh.texcoords[tcCounter + 1] = 0;

            mesh.texcoords[tcCounter + 2] = 0;
            mesh.texcoords[tcCounter + 3] = 1;

            mesh.texcoords[tcCounter + 4] = 1;
            mesh.texcoords[tcCounter + 5] = 0;

            mesh.texcoords[tcCounter + 6] = 1;
            mesh.texcoords[tcCounter + 7] = 0;

            mesh.texcoords[tcCounter + 8] = 0;
            mesh.texcoords[tcCounter + 9] = 1;

            mesh.texcoords[tcCounter + 10] = 1;
            mesh.texcoords[tcCounter + 11] = 1;
            tcCounter += 12;    // 6 texcoords, 12 floats

            mesh.normals[nCounter ] = 0;
            mesh.normals[nCounter + 1] = 1;
            mesh.normals[nCounter + 2] = 0;

            mesh.normals[nCounter + 3] = 0;
            mesh.normals[nCounter + 4] = 1;
            mesh.normals[nCounter + 5] = 0;

            mesh.normals[nCounter + 6] = 0;
            mesh.normals[nCounter + 7] = 1;
            mesh.normals[nCounter + 8] = 0;
            // Fill normals array with data
            //--------------------------------------------------------------
            for (int i = 0; i < 18; i += 9)
            {
                mesh.normals[nCounter + i] = 0;
                mesh.normals[nCounter + i + 1] = 1;
                mesh.normals[nCounter + i + 2] = 0;

                mesh.normals[nCounter + i + 3] = 0;
                mesh.normals[nCounter + i + 4] = 1;
                mesh.normals[nCounter + i + 5] = 0;

                mesh.normals[nCounter + i + 6] = 0;
                mesh.normals[nCounter + i + 7] = 1;
                mesh.normals[nCounter + i + 8] = 0;
            }

            nCounter += 18;     // 6 vertex, 18 floats
        }
    }


    // Upload vertex data to GPU (static mesh)
    UploadMesh(&mesh, false);

    return mesh;
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


