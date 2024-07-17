#ifndef ENGINETYPES_H_
#define ENGINETYPES_H_

#include "raylib.h"

enum State
{
    mainMenu,
    inGame,
    reset
};

typedef struct Game
{
    enum State state;
   
}Game;
#endif