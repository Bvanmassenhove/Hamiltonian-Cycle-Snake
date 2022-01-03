#include "pch.h"
#include "Snake.h"
#include "utils.h"


Snake::Snake(int nrCols, int nrRows, float cellSize)
	:m_NrOfCol{ nrCols },
	m_CellSize{cellSize}
{
	m_Snake.push_back(GetIndex(nrRows/2,nrCols/2,nrCols));
	m_Snake.push_back(GetIndex(nrRows / 2, nrCols / 2 + 1, nrCols));
	m_SnakeSize = 2;
	m_Direction = Direction::left
	;
}
Snake::~Snake()
{
	
}
void Snake::Update(float elapsedSec)
{
	if(m_elapsedSec > 0.2f)
	{
		if(m_Direction == Direction::left)
		{
			for (int i = m_SnakeSize-1; i > 0; --i)
			{
				m_Snake[i] = m_Snake[i-1];
			}
			m_Snake[0] -= 1;
			
		}
		else if(m_Direction == Direction::right)
		{
			for (int i = m_SnakeSize - 1; i > 0; --i)
			{
				m_Snake[i] = m_Snake[i - 1];
			}
			m_Snake[0] += 1;
		}
		else if (m_Direction == Direction::up)
		{
			for (int i = m_SnakeSize - 1; i > 0; --i)
			{
				m_Snake[i] = m_Snake[i - 1];
			}
			m_Snake[0] += m_NrOfCol;
		}
		else if (m_Direction == Direction::down)
		{
			for (int i = m_SnakeSize - 1; i > 0; --i)
			{
				m_Snake[i] = m_Snake[i - 1];
			}
			m_Snake[0] -= m_NrOfCol;
		}
		m_elapsedSec = 0.f;
	}
	else
	{
		m_elapsedSec += elapsedSec;
	}
}
bool Snake::AppleOverlap(int idx)
{
	if (m_elapsedSec > 0.2f)
	{
		if (m_Snake[0] == idx)
		{
			ExtendSnake(idx);
			return true;
		}
	}
	return false;
}