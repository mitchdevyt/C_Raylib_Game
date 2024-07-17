#pragma once
#include "raylib.h"

//return 1 for true and 0 for false
static int CheckRectCollsion(Rectangle a, Rectangle b)
{
    if (a.x + a.width > b.x &&
        a.x < b.x + 10 &&
        a.y + a.height  > b.y &&
        a.y < b.y + 10)
    {
        return 1;
    }
    return 0;
}

static int CheckPointInRect(Vector2 point, Rectangle rect)
{
    if (point.x > rect.x &&
        point.x < rect.x + rect.width &&
        point.y > rect.y &&
        point.y < rect.y + rect.height)
        return 1;
    return 0;
}

