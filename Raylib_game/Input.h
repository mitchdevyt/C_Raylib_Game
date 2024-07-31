#ifndef INPUT_H
#define INPUT_H
#include "Includes.h"

#define XBOX360_LEGACY_NAME_ID  "Xbox Controller"
#define XBOX360_NAME_ID     "Xbox 360 Controller"
#define PS3_NAME_ID         "Sony PLAYSTATION(R)3 Controller"

typedef enum
{
    ACTION_D_UP = 1 << 0,
    ACTION_D_DOWN = 1 << 1,
    ACTION_D_LEFT = 1 << 2,
    ACTION_D_RIGHT = 1 << 3,
    ACTION_A = 1 << 4,
    ACTION_B = 1 << 5,
    ACTION_X = 1 << 6,
    ACTION_Y = 1 << 7,
    ACTION_START = 1 << 8,
    ACTION_SELECT = 1 << 9,
    ACTION_R1 = 1 << 10,
    ACTION_R2 = 1 << 11,
    ACTION_R3 = 1 << 12,
    ACTION_L1 = 1 << 13,
	ACTION_L2 = 1 << 14,
	ACTION_L3 = 1 << 15

}InputAction;

typedef struct InputMap
{
    int forward_move;
    int backwards_move;
    int right_move;
    int left_move;
	int d_up;
	int d_down;
	int d_left;
	int d_right;
	int a;
	int b;
	int x;
	int y;
	int start;
	int select;
	int r1;
	int r2;
	int r3;
	int l1;
	int l2;
	int l3;
}InputMap;

typedef struct Inputs
{
	bool gamePadOrMnK;
	InputMap inputMap;

	float moveVertical;
	float moveHorizontal;
	
	float lookVertical;
	float lookHorizontal;

	int inputDown;
	int inputPressed;
}Inputs;

void UpdateMnkInput(Inputs* input);
void SetKeyPressd(Inputs* input, InputAction action, bool isKeyDown);
bool IsInputDown(Inputs* input, InputAction action);
bool IsInputPressed(Inputs* input, InputAction action);
void SetGamePadInput(Inputs* input);

#endif