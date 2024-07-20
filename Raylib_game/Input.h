#ifndef INPUT_H
#define INPUT_H
#include "raylib.h"

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

void UpdateInput(Inputs* input)
{
	if (input->gamePadOrMnK)
        UpdateMnkInput(input);
}

void UpdateMnkInput(Inputs* input)
{
	input->inputPressed = 0;
	Vector2 mousePos = GetMousePosition();
	
    input->lookHorizontal = mousePos.x;
    input->lookVertical = mousePos.y;

    input->moveVertical = 0;
    input->moveHorizontal = 0;

    if (IsKeyDown(input->inputMap.forward_move))
        input->moveVertical = -1;
    if (IsKeyDown(input->inputMap.backwards_move))
        input->moveVertical = 1;

    if (IsKeyDown(input->inputMap.right_move))
        input->moveHorizontal = 1;
    if (IsKeyDown(input->inputMap.left_move))
        input->moveHorizontal = -1;

	//Set button presses
	SetKeyPressd(input, ACTION_D_UP, IsKeyDown(input->inputMap.d_up));
	SetKeyPressd(input, ACTION_D_DOWN, IsKeyDown(input->inputMap.d_down));
	SetKeyPressd(input, ACTION_D_LEFT, IsKeyDown(input->inputMap.d_left));
	SetKeyPressd(input, ACTION_D_RIGHT, IsKeyDown(input->inputMap.d_right));
	SetKeyPressd(input, ACTION_A, IsKeyDown(input->inputMap.a));
	SetKeyPressd(input, ACTION_B, IsKeyDown(input->inputMap.b));
	SetKeyPressd(input, ACTION_X, IsKeyDown(input->inputMap.x));
	SetKeyPressd(input, ACTION_Y, IsKeyDown(input->inputMap.y));
	SetKeyPressd(input, ACTION_START, IsKeyDown(input->inputMap.start));
	SetKeyPressd(input, ACTION_SELECT, IsKeyDown(input->inputMap.select));
	SetKeyPressd(input, ACTION_R1, IsKeyDown(input->inputMap.r1));
	SetKeyPressd(input, ACTION_R2, IsKeyDown(input->inputMap.r2));
	SetKeyPressd(input, ACTION_R3, IsKeyDown(input->inputMap.r3));
	SetKeyPressd(input, ACTION_L1, IsKeyDown(input->inputMap.l1));
	SetKeyPressd(input, ACTION_L2, IsKeyDown(input->inputMap.l2));
	SetKeyPressd(input, ACTION_L3, IsKeyDown(input->inputMap.l3));

	//set sticks and mouse
}

void SetKeyPressd(Inputs* input, InputAction action, bool isKeyDown)
{
	if (!isKeyDown)
		input->inputDown = input->inputDown & !action;
	else
	{
		if (!IsInputPressed(input, action))
			input->inputPressed |= action;
		input->inputDown |= action;
	}
}

bool IsInputDown(Inputs* input, InputAction action)
{
	int inputValue = input->inputDown & action;
	if (inputValue > 0)
		return true;
	return false;
}

bool IsInputPressed(Inputs* input, InputAction action)
{
	int inputValue = input->inputPressed & action;
	if (inputValue > 0)
		return true;
	return false;
}

void SetGamePadInput(Inputs* input)
{
    //int gamepad = 0;
    //for (int i = 0; i < 3; i++)
    //{
    //    if (IsGamepadAvailable(i))
    //    {
    //        gamepad = i;
    //        break;
    //    }
    //}
    //
    //if (TextIsEqual(GetGamepadName(gamepad), XBOX360_LEGACY_NAME_ID) || TextIsEqual(GetGamepadName(gamepad), XBOX360_NAME_ID))
    //{

    //    // Draw buttons: xbox home
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE)) DrawCircle(394, 89, 19, RED);

    //    // Draw buttons: basic
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT)) DrawCircle(436, 150, 9, RED);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_LEFT)) DrawCircle(352, 150, 9, RED);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) DrawCircle(501, 151, 15, BLUE);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) DrawCircle(536, 187, 15, LIME);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) DrawCircle(572, 151, 15, MAROON);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP)) DrawCircle(536, 115, 15, GOLD);

    //    // Draw buttons: d-pad
    //    DrawRectangle(317, 202, 19, 71, BLACK);
    //    DrawRectangle(293, 228, 69, 19, BLACK);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP)) DrawRectangle(317, 202, 19, 26, RED);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) DrawRectangle(317, 202 + 45, 19, 26, RED);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) DrawRectangle(292, 228, 25, 19, RED);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) DrawRectangle(292 + 44, 228, 26, 19, RED);

    //    // Draw buttons: left-right back
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) DrawCircle(259, 61, 20, RED);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) DrawCircle(536, 61, 20, RED);

    //    // Draw axis: left joystick

    //    Color leftGamepadColor = BLACK;
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_THUMB)) leftGamepadColor = RED;
    //    DrawCircle(259, 152, 39, BLACK);
    //    DrawCircle(259, 152, 34, LIGHTGRAY);
    //    DrawCircle(259 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) * 20),
    //        152 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) * 20), 25, leftGamepadColor);

    //    // Draw axis: right joystick
    //    Color rightGamepadColor = BLACK;
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_THUMB)) rightGamepadColor = RED;
    //    DrawCircle(461, 237, 38, BLACK);
    //    DrawCircle(461, 237, 33, LIGHTGRAY);
    //    DrawCircle(461 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X) * 20),
    //        237 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y) * 20), 25, rightGamepadColor);

    //    // Draw axis: left-right triggers
    //    DrawRectangle(170, 30, 15, 70, GRAY);
    //    DrawRectangle(604, 30, 15, 70, GRAY);
    //    DrawRectangle(170, 30, 15, (int)(((1 + GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER)) / 2) * 70), RED);
    //    DrawRectangle(604, 30, 15, (int)(((1 + GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER)) / 2) * 70), RED);

    //    //DrawText(TextFormat("Xbox axis LT: %02.02f", GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER)), 10, 40, 10, BLACK);
    //    //DrawText(TextFormat("Xbox axis RT: %02.02f", GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER)), 10, 60, 10, BLACK);
    //}
    //else if (TextIsEqual(GetGamepadName(gamepad), PS3_NAME_ID))
    //{

    //    // Draw buttons: ps
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE)) DrawCircle(396, 222, 13, RED);

    //    // Draw buttons: basic
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_LEFT)) DrawRectangle(328, 170, 32, 13, RED);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT)) DrawTriangle((Vector2) { 436, 168 }, (Vector2) { 436, 185 }, (Vector2) { 464, 177 }, RED);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP)) DrawCircle(557, 144, 13, LIME);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) DrawCircle(586, 173, 13, RED);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) DrawCircle(557, 203, 13, VIOLET);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) DrawCircle(527, 173, 13, PINK);

    //    // Draw buttons: d-pad
    //    DrawRectangle(225, 132, 24, 84, BLACK);
    //    DrawRectangle(195, 161, 84, 25, BLACK);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP)) DrawRectangle(225, 132, 24, 29, RED);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) DrawRectangle(225, 132 + 54, 24, 30, RED);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) DrawRectangle(195, 161, 30, 25, RED);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) DrawRectangle(195 + 54, 161, 30, 25, RED);

    //    // Draw buttons: left-right back buttons
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) DrawCircle(239, 82, 20, RED);
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) DrawCircle(557, 82, 20, RED);

    //    // Draw axis: left joystick
    //    Color leftGamepadColor = BLACK;
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_THUMB)) leftGamepadColor = RED;
    //    DrawCircle(319, 255, 35, leftGamepadColor);
    //    DrawCircle(319, 255, 31, LIGHTGRAY);
    //    DrawCircle(319 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) * 20),
    //        255 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) * 20), 25, leftGamepadColor);

    //    // Draw axis: right joystick
    //    Color rightGamepadColor = BLACK;
    //    if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_THUMB)) rightGamepadColor = RED;
    //    DrawCircle(475, 255, 35, BLACK);
    //    DrawCircle(475, 255, 31, LIGHTGRAY);
    //    DrawCircle(475 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X) * 20),
    //        255 + (int)(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y) * 20), 25, rightGamepadColor);

    //    // Draw axis: left-right triggers
    //    DrawRectangle(169, 48, 15, 70, GRAY);
    //    DrawRectangle(611, 48, 15, 70, GRAY);
    //    DrawRectangle(169, 48, 15, (int)(((1 - GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER)) / 2) * 70), RED);
    //    DrawRectangle(611, 48, 15, (int)(((1 - GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER)) / 2) * 70), RED);
    //}
}
#endif