/*
This project uses the Raylib framework to provide us functionality for math, graphics, GUI, input etc.
See documentation here: https://www.raylib.com/, and examples here: https://www.raylib.com/examples.html
*/

#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "game.h"

const unsigned int TARGET_FPS = 50; //frames/second
float dt = 1.0f / TARGET_FPS; //seconds/frame
float time = 0;

float speed = 100;
float angle = 0;

//Vector2 startPos = { 100, GetScreenHeight() - 100 };

float launchPos_X = 100;
float launchPos_Y = 0;

//Vector2 position = {500, 500}; // We gonna use launchPos_X and launchPos_Y
Vector2 velocity = { 0, 0 };
Vector2 accelerationGravity = { 0, 9 };

float screenWidth = 0;
float screenHeight = 0;

//Changes world state
void update()
{
	dt = 1.0f / TARGET_FPS;
	time += dt;
}

//Display world state
void draw()
{
	BeginDrawing();
	ClearBackground(BLUE);
	DrawText("GAME2005 Paul Bernard-Hall 101031336", 10, float(GetScreenHeight() - 30), 20, WHITE);

	//GuiSliderBar(Rectangle{ 100, 15, 500, 20 }, "Time", TextFormat("%.2f", time), &time, 0, 240);

	GuiSliderBar(Rectangle{ 100, 40, 500, 30 }, "Speed", TextFormat("%.0f", speed), &speed, -1000, 1000);

	GuiSliderBar(Rectangle{ 100, 80, 500, 30 }, "Angle", TextFormat("%.0f Degrees", angle), &angle, -180, 180);

	GuiSliderBar(Rectangle{ 100, 120, 500, 30 }, "POS X", TextFormat("%.0f X", launchPos_X), &launchPos_X, 100, screenWidth);

	GuiSliderBar(Rectangle{ 100, 160, 500, 30 }, "POS Y", TextFormat("%.0f Y", launchPos_Y), &launchPos_Y, 300, screenHeight);

	DrawText(TextFormat("T: %6.2f", time), GetScreenWidth() - 140, 10, 30, WHITE);

	Vector2 startPos = { launchPos_X, launchPos_Y };

	// Our angle is set in degrees but cos() and sin() need rad 
	Vector2 velocity = { speed * cos(angle * DEG2RAD), -speed * sin(angle * DEG2RAD) };

	// draw line ex lets us set witdth i remember
	DrawLineEx(startPos, startPos + velocity, 5, RED);

	EndDrawing();
}

int main()
{
	InitWindow(InitialWidth, InitialHeight, "GAME2005 Paul Bernard-Hall 101031336");
	SetTargetFPS(TARGET_FPS);

	launchPos_Y = GetScreenHeight() - 100;

	screenWidth = GetScreenWidth() - 100;
	screenHeight = GetScreenHeight() - 100;

	//mserrat = LoadFont("Montserrat-Regular.ttf");

	//******************************//
	// Loading custom font - created resources dir and put ttf there
	// resource: https://www.raylib.com/examples/text/loader.html?name=text_font_loading
	// 
	// Font resource: 
	// https://fonts.google.com/specimen/Montserrat
	//******************************//
	Font mserrat = LoadFontEx("resources/Montserrat-Regular.ttf", 32, 0, 250); // Load font and set defaults
	GuiSetFont(mserrat); // Use montserrat font as the... default font I guess?
	GuiSetStyle(DEFAULT, TEXT_SIZE, 32); // Set text size 
	GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0xFFFFFFFF); // Set normal font white (as an int lol)

	while (!WindowShouldClose()) // Loops TARGET_FPS times per second
	{
		update();
		draw();
	}

	CloseWindow();
	return 0;
}