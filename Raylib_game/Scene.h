#ifndef SCENE_H
#define SCENE_H

#include "Includes.h"

typedef struct Scene3DTerrain
{
    Camera3D mainCamera;
    Model skybox;
    Model terrain;
    //Inputs inputs;
    //InputMap inputMap;
}Scene3DTerrain;

//void StartScene3D(struct Scene3DTerrain* scene);
//void UpdateScene3D(struct Scene3DTerrain* scene);
//void RenderScene3D(struct Scene3DTerrain* scene);
//void ResetScene3D(struct Scene3DTerrain* scene);
//void ExitScene3D(struct Scene3DTerrain* scene);

#endif