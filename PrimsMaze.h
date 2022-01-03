#pragma once
#include "utils.h"

class Maze
{
public:
	Maze(int nrCols, int nrRows);
	~Maze();
	std::vector<bool> GenerateMaze();
	bool OneVisitedCellAround(int wall);
private:
	std::vector<int>WallList{};
	std::vector<bool>maze{};
	int m_NrCols{};
};

Maze::Maze(int nrCols, int nrRows)
{
	for (int i = 0; i < nrCols; ++i)
	{
		for (int j = 0; j < nrRows; ++j)
		{
			maze.push_back(false);
		}
	}
	m_NrCols = nrCols;
}
Maze::~Maze()
{
	
}

std::vector<bool> Maze::GenerateMaze()
{
	maze[0] = true;
	WallList.push_back(2);
	WallList.push_back(m_NrCols);

	while(WallList.size() != 0)
	{
		int wallidx(utils::GetRand(0, WallList.size()));
		if (OneVisitedCellAround(wallidx))
		{
			maze[wallidx] = true;
			if (wallidx - 1 > 0)
			{
				if (maze[wallidx - 1] == false)
				{
					WallList.push_back(wallidx - 1);
				}
			}
			if (wallidx + 1 < int(maze.size()))
			{
				if (maze[wallidx + 1] == false)
				{
					WallList.push_back(wallidx + 1);
				}
			}
			if (wallidx - m_NrCols > 0)
			{
				if (maze[wallidx - m_NrCols] == false)
				{
					WallList.push_back(wallidx - m_NrCols);
				}
			}
			if (wallidx + m_NrCols < int(maze.size()))
			{
				if (maze[wallidx + m_NrCols] == false)
				{
					WallList.push_back(wallidx + m_NrCols);
				}
			}
		}
	}

	return maze;
}

bool Maze::OneVisitedCellAround(int wall)
{
	int nrOfVisitedCells{};
	if(wall - 1 > 0)
	{
		if (maze[wall - 1] == true)
		{
			++nrOfVisitedCells;
		}
	}
	if (wall + 1 < int(maze.size()))
	{
		if (maze[wall + 1] == true)
		{
			++nrOfVisitedCells;
		}
	}
	if (wall - m_NrCols > 0)
	{
		if (maze[wall - m_NrCols] == true)
		{
			++nrOfVisitedCells;
		}
	}
	if (wall + m_NrCols < int(maze.size()))
	{
		if (maze[wall + m_NrCols] == true)
		{
			++nrOfVisitedCells;
		}
	}

	if(nrOfVisitedCells == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}