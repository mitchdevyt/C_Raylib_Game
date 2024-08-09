#include "Includes.h"

void InGameUpdate();
void InGameRender();
void ResetGame();
void CheckShouldFullScreen();

void InitTerrain();
void UpdateTerrainLogic();
void RenderTerrain();

void InitPlayerTestCollisions();
void UpdatePlayerTestCollisions();
void RenderPlayerTestCollisions();


struct Game game;
float deltaTime;

Scene3DTerrain terrainGameplayScene;
Vector3 heigtMapModelPosition = { 0.0f, -20.0f, 0.0f };

void Init()
{
    deltaTime = 0.0f;

    game.state = inGame;
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Renderer");

    Init();
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    InitTerrain();
    InitPlayerTestCollisions();
    

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
            
            UpdateTerrainLogic();
            UpdatePlayerTestCollisions();

            CheckShouldFullScreen();
            //----------------------------------------------------------------------------------               
            // Draw
            //----------------------------------------------------------------------------------
            RenderTerrain();
            RenderPlayerTestCollisions();
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


//--------------------------------------------------------------------------------------
//State logic
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
//End State logic
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
//Window controls

void CheckShouldFullScreen()
{
    if (IsKeyPressed(KEY_P))
    {
        // see what display we are on right now
        int display = GetCurrentMonitor();


        if (IsWindowFullscreen())
        {
            // if we are full screen, then go back to the windowed size
            SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
        }
        else
        {
            // if we are not full screen, set the window size to match the monitor we are on
            SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
        }

        // toggle the state
        ToggleFullscreen();
    }
}

//End State logic
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
//Terrain Logic

void InitTerrain()
{
    terrainGameplayScene = SetupTerrainGameplayScene();

    float tris = terrainGameplayScene.terrain.meshes[0].triangleCount;
}


void UpdateTerrainLogic()
{
    UpdateCamera(&terrainGameplayScene.mainCamera, CAMERA_FREE);
}

void RenderTerrain()
{
    BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(terrainGameplayScene.mainCamera);
            rlDisableBackfaceCulling();
            rlDisableDepthMask();
                DrawModel(terrainGameplayScene.skybox, (Vector3) { 0, 0, 0 }, 1.0f, WHITE);
            rlEnableBackfaceCulling();
            rlEnableDepthMask();

        DrawModel(terrainGameplayScene.terrain, heigtMapModelPosition, 1.0f, RED);
        DrawGrid(10, 1.0);

    EndMode3D();

        DrawFPS(10, 10);
        DrawText(TextFormat("dt: %f", deltaTime), 10, 30, 20, RED);
        DrawText(TextFormat("min: %f  max: %f", minY,maxY), 10, 70, 20, RED);
    EndDrawing();
}
//End Terrain Logic
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Collision Player Controller Logic

void InitPlayerTestCollisions()
{

}

void UpdatePlayerTestCollisions()
{

}

void RenderPlayerTestCollisions()
{

}

// End Collision Player Controller Logic
//--------------------------------------------------------------------------------------