#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

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

struct Game game;
float deltaTime;

void Init()
{
    deltaTime = 0.0f;
   
    game.state = inGame;
}

void InitCamera(Camera* camera)
{
    camera->position = (Vector3){ 18.0f, 21.0f, 18.0f };     // Camera position
    camera->target = (Vector3){ 0.0f, 0.0f, 0.0f };          // Camera looking at point
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

    // Define our custom camera to look into our 3d world
    Camera camera = { 0 };
    InitCamera(&camera);
    
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
                //----------------------------------------------------------------------------------               
                // Draw
                //----------------------------------------------------------------------------------
                InGameRender();
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


