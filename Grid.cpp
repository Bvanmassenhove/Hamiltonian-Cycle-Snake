#include "pch.h"
#include "Grid.h"
#include "utils.h"

Grid::Grid(int nrCols, int nrRows,float cellSize,float windowWidth, float windowHeight)
	:m_NrCols{nrCols},
	m_NrRows{nrRows},
	m_CellSize{cellSize}
{
	for (int i = 0; i < m_NrCols; ++i)
	{
		for (int j = 0; j < m_NrRows; ++j)
		{
			m_Grid.push_back(Tile{ cellSize , false, false,Color4f{0.1f,0.1f,0.1f,1.f}});
		}
	}
	m_GridBgRect.left = windowWidth / 2 - (m_CellSize * m_NrCols / 2);
	m_GridBgRect.bottom = (windowHeight / 2 - m_CellSize * m_NrRows / 2);
	m_GridBgRect.width = (m_CellSize * m_NrCols);
	m_GridBgRect.height = (m_CellSize * m_NrRows);
}
Grid::~Grid()
{
}
void Grid::ResetGrid()
{
	for (int i = 0; i < int(m_Grid.size()); ++i)
	{
		m_Grid[i].isSnake = false;
		m_Grid[i].isApple = false;
		m_Grid[i].color = Color4f{ 0.1f,0.1f,0.1f,1.f };
	}
}
void Grid::DrawGrid(float windowWidth,float windowHeight)
{
	SetColor(m_GridBackgroundColor);
	FillRect(m_GridBgRect);

	for (int i = 0; i < m_NrCols; ++i)
	{
		for (int j = 0; j < m_NrRows; ++j)
		{
			int idx{ utils::GetIndex(j,i,m_NrCols) };
			Rectf rect{ (windowWidth / 2 - m_Grid[idx].size * m_NrCols / 2) + m_Grid[idx].size * i,(windowHeight / 2 - m_Grid[idx].size * m_NrRows / 2) + m_Grid[idx].size * j,m_Grid[idx].size,m_Grid[idx].size };
			
			if(m_Grid[idx].isSnake || m_Grid[idx].isApple)
			{
				SetColor(m_Grid[idx].color);
				FillRect(rect);
			}
			else
			{
				utils::SetColor(m_Grid[idx].color);
				utils::DrawRect(rect);
			}
		}
	}
}
void Grid::SetCellSnake(std::vector<int> indexes)
{
	for (auto idx : indexes)
	{
		m_Grid[idx].isSnake = true;
		m_Grid[idx].color = Color4f{ 0.1f,1.0f,0.1f,1.f };
	}
}
void Grid::SetCellApple(int idx)
{
	m_Grid[idx].isApple = true;
	m_Grid[idx].color = Color4f{ 1.0f,0.1f,0.1f,1.f };
}


void Grid::ShowMaze(std::vector<int>maze)
{
	for (int i = 0; i < int(maze.size()); ++i)
	{
		m_Grid[maze[i]].isSnake = true;
		m_Grid[maze[i]].color = Color4f{ 0.1f,1.0f,0.1f,1.f };
			
		
	}
}