#ifndef TERRAINMESHGEN_H
#define TERRAINMESHGEN_H
#include "Includes.h"
float maxY, minY;

Mesh GenMeshHeightmap2(Image heightmap, Vector3 size);

#endif