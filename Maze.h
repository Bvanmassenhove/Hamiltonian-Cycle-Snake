#pragma once
#include <algorithm>

#include "utils.h"

class Maze
{
public:
	Maze(int nrCols, int nrRows);
	~Maze();
	std::vector<int> GenerateMaze();
	void AddSuroundingCells(int cell);
	int GetMazeCell(int cell);

	std::vector<std::pair<int, int>> GetMazeConnections() { return m_MazeConnection; }
	
private:
	std::vector<int>m_CellList{};
	std::vector<int>m_Maze{};
	std::vector<std::pair<int, int>>m_MazeConnection{};
	int m_NrCols{};
	int m_NrRows{};
	int m_GridSize{};
};

Maze::Maze(int nrCols, int nrRows)
{

	m_NrCols = nrCols;
	m_NrRows = nrRows;
	m_GridSize = m_NrCols * m_NrRows;
}
Maze::~Maze()
{

}

std::vector<int> Maze::GenerateMaze()
{
	int randStartIdx = utils::GetRand(0, m_GridSize - 1);
	m_Maze.push_back(randStartIdx);
	AddSuroundingCells(randStartIdx);

	while(m_CellList.size() != 0)
	{
		int Randidx(utils::GetRand(0, m_CellList.size() - 1));
		int endidx = m_CellList[Randidx];
		int startidx = GetMazeCell(endidx);

		m_MazeConnection.push_back(std::make_pair(startidx, endidx));
		m_Maze.push_back(endidx);
		AddSuroundingCells(endidx);

		m_CellList.erase(std::remove(m_CellList.begin(), m_CellList.end(), endidx), m_CellList.end());
	}
	return m_Maze;
}

void Maze::AddSuroundingCells(int cell)
{
	if (cell - 1 > -1)
	{
		if (cell - 1 >= 0 && (cell % m_NrCols) != 0)
		{
			if (std::find(m_Maze.begin(), m_Maze.end(), cell - 1) == m_Maze.end())
			{
				m_CellList.push_back(cell - 1);
			}
		}
	}
	if (cell + 1 < int(m_GridSize))
	{
		if ((cell + 1) % m_NrCols)
		{
			if (std::find(m_Maze.begin(), m_Maze.end(), cell + 1) == m_Maze.end())
			{
				m_CellList.push_back(cell + 1);
			}
		}
	}
	if (cell - m_NrCols > -1)
	{
		if (cell - m_NrCols >= 0)
		{
			if (std::find(m_Maze.begin(), m_Maze.end(), cell - m_NrCols) == m_Maze.end())
			{
				m_CellList.push_back(cell - m_NrCols);
			}
		}
	}
	if (cell + m_NrCols < int(m_GridSize))
	{
		if (cell + m_NrCols < (m_NrCols * m_NrCols))
		{
			if (std::find(m_Maze.begin(), m_Maze.end(), cell + m_NrCols) == m_Maze.end())
			{
				m_CellList.push_back(cell + m_NrCols);
			}
		}
	}
}

int Maze::GetMazeCell(int cell)
{
	std::vector<int> mazeCells{};

	if (cell - 1 > -1)
	{
		if (cell - 1 >= 0 && (cell % m_NrCols) != 0)
		{
			if (std::find(m_Maze.begin(),m_Maze.end(), cell - 1) != m_Maze.end())
			{
				mazeCells.push_back(cell - 1);
			}
		}
	}
	if (cell + 1 < int(m_GridSize))
	{
		if ((cell + 1) % m_NrCols)
		{
			if (std::find(m_Maze.begin(), m_Maze.end(), cell + 1) != m_Maze.end())
			{
				mazeCells.push_back(cell + 1);
			}
		}
	}
	if (cell - m_NrCols > -1)
	{
		if (cell - m_NrCols >= 0)
		{
			if (std::find(m_Maze.begin(), m_Maze.end(), cell - m_NrCols) != m_Maze.end())
			{
				mazeCells.push_back(cell - m_NrCols);
			}
		}
	}
	if (cell + m_NrCols < m_GridSize)
	{
		if (cell + m_NrCols < (m_NrCols * m_NrCols))
		{
			if (std::find(m_Maze.begin(), m_Maze.end(), cell + m_NrCols) != m_Maze.end())
			{
				mazeCells.push_back(cell + m_NrCols);
			}
		}
	}

	if(mazeCells.size() > 1)
	{
		int Randidx(utils::GetRand(0, mazeCells.size() - 1));
		return mazeCells[Randidx];
	}
	else
	{
		return mazeCells[0];
	}
}
