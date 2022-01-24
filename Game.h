#pragma once
using namespace utils;
#include "utils.h"
#include "Grid.h"
#include "Snake.h"
#include "Apple.h"
#include "Maze.h"

#define Size 20 //size of grid
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Project name - Name, firstname - 1DAExx" };

// Change the window dimensions here
float g_WindowWidth{ 1280 };
float g_WindowHeight{ 720 };
#pragma endregion gameInformation

Grid* m_pGrid{};
Snake* m_pSnake{};
Apple* m_pApple{};

Maze* m_pMaze{};
std::vector<std::pair<int, int>> m_HamiltonianCycle;

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling
