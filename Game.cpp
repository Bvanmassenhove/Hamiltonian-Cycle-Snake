#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	m_pGrid = new Grid{ Size,Size,25.f,g_WindowWidth ,g_WindowHeight };
	m_pApple = new Apple{ Size,Size };
	m_pMaze = new Maze{ Size/2 ,Size/2 };
	do
	{
		m_HamiltonianCycle = m_pMaze->Generatecycle();

	} while (m_HamiltonianCycle.size() != 400 || std::find_if(m_HamiltonianCycle.begin(), m_HamiltonianCycle.end(), [&](const auto& pair) { return pair.second < 0; }) != m_HamiltonianCycle.end());
	m_pSnake = new Snake{ Size,Size ,25.f,m_HamiltonianCycle };
	m_pApple->AddApple(m_pSnake->GetSnake());
}

void Draw()
{
	ClearBackground(.2f, .2f, .2f);
	//m_pGrid->ShowCycle(m_HamiltonianCycle);
	m_pGrid->DrawGrid(g_WindowWidth, g_WindowHeight);
}

void Update(float elapsedSec)
{
	m_pGrid->ResetGrid();
	m_pGrid->SetCellSnake(m_pSnake->GetSnake());
	m_pGrid->SetCellApple(m_pApple->GetApple());

	m_pSnake->CycleUpdate(elapsedSec);
	
	if (m_pSnake->AppleOverlap(m_pApple->GetApple()))
	{
		m_pApple->AddApple(m_pSnake->GetSnake());
	}

	if(m_pSnake->GetSnakeSize() >= 25*25)
	{
		std::cout << "won";
	}
}

void End()
{
	delete m_pGrid;
	delete m_pSnake;
	delete m_pApple;
	delete m_pMaze;
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_LEFT:
		m_pSnake->SetDirection(Direction::left);
		break;
	case SDLK_RIGHT:
		m_pSnake->SetDirection(Direction::right);
		break;
	case SDLK_UP:
		m_pSnake->SetDirection(Direction::up);
		break;
	case SDLK_DOWN:
		m_pSnake->SetDirection(Direction::down);
		break;
	}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	////std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//switch (e.button)
	//{
	//case SDL_BUTTON_LEFT:
	//{
	//	//std::cout << "Left mouse button released\n";
	//	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
	//	break;
	//}
	//case SDL_BUTTON_RIGHT:
	//	//std::cout << "Right mouse button released\n";
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	//std::cout << "Middle mouse button released\n";
	//	break;
	//}
}
#pragma endregion inputHandling
