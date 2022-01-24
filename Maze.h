#pragma once
#include <algorithm>
#include <iostream>

#include "utils.h"

class Maze
{
public:
	Maze(int nrCols, int nrRows);
	~Maze();
	std::vector<int> GenerateMaze();
	std::vector<std::pair<int, int>> Generatecycle();
	Direction FindRelativeDirection(Direction CurrentDirection, std::pair<int, int> newconnection, int currentNode);
	void AddFirstForwardCycleConnections(int Mazeidx);
	void AddForwardCycleConnections();
	void AddLeftTurnCycleConnections();
	void AddRightTurnCycleConnections();
	void AddSuroundingCells(int cell);
	int GetMazeCell(int cell);

	std::vector<std::pair<int, int>> GetMazeConnections() { return m_MazeConnection; }
	
private:
	std::vector<int>m_CellList{};
	std::vector<int>m_Maze{};
	std::vector<std::pair<int, int>>m_MazeConnection{};
	std::vector<std::pair<int, int>>m_CycleConnections;
	int m_CurrentMazeNode{ -1 };
	int m_NrCols{};
	int m_NrRows{};
	int m_GridSize{};
	int m_startidx{};
	Direction m_direction{};
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
	m_startidx = utils::GetRand(0, m_GridSize - 1);
	m_Maze.push_back(m_startidx);
	AddSuroundingCells(m_startidx);

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
std::vector<std::pair<int, int>> Maze::Generatecycle()
{
	m_CellList.clear();
	m_Maze.clear();
	m_MazeConnection.clear();
	m_CycleConnections.clear();
	m_CurrentMazeNode = -1;
	m_direction = Direction::forward;

	GenerateMaze();
	std::vector<int> cycle;
	std::vector<std::pair<int, int>> TempMazeConnections;
	bool looping{ true };
	Direction tempDirection;
	int nextConnectionidx{ 0 };
	std::vector<std::pair<int, Direction>> storedIdxAndDirections;

	m_direction = FindRelativeDirection(Direction::forward, m_MazeConnection[0], m_startidx);
	AddFirstForwardCycleConnections(0);
	while (looping)
	{
		int temp = m_CurrentMazeNode;
		auto it = std::find_if(m_CycleConnections.begin(), m_CycleConnections.end(), [&](const auto& pair) { return pair.second == m_CycleConnections.begin()->first; });
		if (it != m_CycleConnections.end())
		{
			int overflow = m_CycleConnections.size() - std::distance(m_CycleConnections.begin(), it) - 1;

			for (int i = 0; i < overflow; ++i)
			{
				m_CycleConnections.pop_back();
			}
			looping = false;
			break;
		}

		for (auto connection : m_MazeConnection)
		{
			if (connection.first == m_CurrentMazeNode || connection.second == m_CurrentMazeNode)
			{
				TempMazeConnections.push_back(connection);
			}
		}
		if (TempMazeConnections.size() == 1)
		{
			//end of the line turn back
			std::pair<int, int>tempConnection;

			tempConnection.first = m_CycleConnections.back().second;
			switch (m_direction)
			{
			case Direction::left:
				tempConnection.second = m_CycleConnections.back().second + m_NrCols * 2;
				m_CycleConnections.push_back(tempConnection);
				tempConnection.first = tempConnection.second;
				tempConnection.second = tempConnection.second + 1;
				m_CycleConnections.push_back(tempConnection);
				tempConnection.first = tempConnection.second;
				tempConnection.second = tempConnection.second + 1;
				m_CycleConnections.push_back(tempConnection);
				tempConnection.first = tempConnection.second;
				tempConnection.second = tempConnection.second + 1;
				m_CycleConnections.push_back(tempConnection);
				m_CurrentMazeNode += 1;
				m_direction = Direction::right;
				break;
			case Direction::right:
				tempConnection.second = m_CycleConnections.back().second - m_NrCols * 2;
				m_CycleConnections.push_back(tempConnection);
				tempConnection.first = tempConnection.second;
				tempConnection.second = tempConnection.second - 1;
				m_CycleConnections.push_back(tempConnection);
				tempConnection.first = tempConnection.second;
				tempConnection.second = tempConnection.second - 1;
				m_CycleConnections.push_back(tempConnection);
				tempConnection.first = tempConnection.second;
				tempConnection.second = tempConnection.second - 1;
				m_CycleConnections.push_back(tempConnection);
				m_CurrentMazeNode -= 1;
				m_direction = Direction::left;
				break;
			case Direction::up:
				tempConnection.second = m_CycleConnections.back().second + 1;
				m_CycleConnections.push_back(tempConnection);
				tempConnection.first = tempConnection.second;
				tempConnection.second = tempConnection.second - m_NrCols * 2;
				m_CycleConnections.push_back(tempConnection);
				tempConnection.first = tempConnection.second;
				tempConnection.second = tempConnection.second - m_NrCols * 2;
				m_CycleConnections.push_back(tempConnection);
				tempConnection.first = tempConnection.second;
				tempConnection.second = tempConnection.second - m_NrCols * 2;
				m_CycleConnections.push_back(tempConnection);
				m_CurrentMazeNode -= m_NrCols;
				m_direction = Direction::down;
				break;
			case Direction::down:
				tempConnection.second = m_CycleConnections.back().second - 1;
				m_CycleConnections.push_back(tempConnection);
				tempConnection.first = tempConnection.second;
				tempConnection.second = tempConnection.second + m_NrCols * 2;
				m_CycleConnections.push_back(tempConnection);
				tempConnection.first = tempConnection.second;
				tempConnection.second = tempConnection.second + m_NrCols * 2;
				m_CycleConnections.push_back(tempConnection);
				tempConnection.first = tempConnection.second;
				tempConnection.second = tempConnection.second + m_NrCols * 2;
				m_CycleConnections.push_back(tempConnection);
				m_CurrentMazeNode += m_NrCols;
				m_direction = Direction::up;
				break;
			}
		}
		else
		{
			for (auto MazeConnection : TempMazeConnections)
			{
				tempDirection = FindRelativeDirection(m_direction, MazeConnection, m_CurrentMazeNode);
				auto it = std::find(TempMazeConnections.begin(), TempMazeConnections.end(), MazeConnection);
				storedIdxAndDirections.push_back(std::pair<int, Direction>{it - TempMazeConnections.begin(), tempDirection});
			}
			if (std::count_if(storedIdxAndDirections.begin(), storedIdxAndDirections.end(), [&](const auto& pair) { return pair.second == Direction::left; }))
			{
				auto it = std::find_if(storedIdxAndDirections.begin(), storedIdxAndDirections.end(), [&](const auto& pair) { return pair.second == Direction::left; });
				nextConnectionidx = it->first;
				tempDirection = Direction::left;
			}
			else if (std::count_if(storedIdxAndDirections.begin(), storedIdxAndDirections.end(), [&](const auto& pair) { return pair.second == Direction::forward; }))
			{
				auto it = std::find_if(storedIdxAndDirections.begin(), storedIdxAndDirections.end(), [&](const auto& pair) { return pair.second == Direction::forward; });
				nextConnectionidx = it->first;
				tempDirection = Direction::forward;
			}
			else if (std::count_if(storedIdxAndDirections.begin(), storedIdxAndDirections.end(), [&](const auto& pair) { return pair.second == Direction::right; }))
			{
				auto it = std::find_if(storedIdxAndDirections.begin(), storedIdxAndDirections.end(), [&](const auto& pair) { return pair.second == Direction::right; });
				nextConnectionidx = it->first;
				tempDirection = Direction::right;
			}

			if (tempDirection == Direction::left)
			{
				AddLeftTurnCycleConnections();
				switch (m_direction)
				{
				case Direction::left:
					m_direction = Direction::down;
					break;
				case Direction::right:
					m_direction = Direction::up;
					break;
				case Direction::up:
					m_direction = Direction::left;
					break;
				case Direction::down:
					m_direction = Direction::right;
					break;
				}
			}
			else if (tempDirection == Direction::forward)
			{
				AddForwardCycleConnections();
			}
			else if (tempDirection == Direction::right)
			{
				AddRightTurnCycleConnections();
				switch (m_direction)
				{
				case Direction::left:
					m_direction = Direction::up;
					break;
				case Direction::right:
					m_direction = Direction::down;
					break;
				case Direction::up:
					m_direction = Direction::right;
					break;
				case Direction::down:
					m_direction = Direction::left;
					break;
				}
			}
		}
		storedIdxAndDirections.clear();
		TempMazeConnections.clear();
	}
	return m_CycleConnections;
}
Direction Maze::FindRelativeDirection(Direction CurrentDirection, std::pair<int, int> newconnection, int currentNode)
{
	if(currentNode == newconnection.first)
	{
		if(newconnection.first - newconnection.second == 1)
		{
			//connection goes left
			switch (CurrentDirection)
			{
			case Direction::left:
				return Direction::forward;
				break;
			case Direction::right:
				//std::cout << "invalid relative direction: from left to right into itself";
				return Direction::down;
				break;
			case Direction::up:
				return Direction::left;
				break;
			case Direction::down:
				return Direction::right;
				break;
			case Direction::forward:
				return Direction::left;
				break;
			}
		}
		else if (newconnection.first - newconnection.second == -1)
		{
			//connection goes right
			switch (CurrentDirection)
			{
			case Direction::left:
				//std::cout << "invalid relative direction: from right to left into itself";
				return Direction::down;
				break;
			case Direction::right:
				return Direction::forward;
				break;
			case Direction::up:
				
				return Direction::right;
				break;
			case Direction::down:
				return Direction::left;
				break;
			case Direction::forward:
				return Direction::right;
				break;
			}
		}
		else if (newconnection.first - newconnection.second == m_NrCols)
		{
			//connection goes down
			switch (CurrentDirection)
			{
			case Direction::left:
				return Direction::left;
				break;
			case Direction::right:
				return Direction::right;
				break;
			case Direction::up:
				//std::cout << "invalid relative direction: from down to up into itself";
				return Direction::down;
				break;
			case Direction::down:
				return Direction::forward;
				break;
			case Direction::forward:
				return Direction::down;
				break;
			}
		}
		else if (newconnection.first - newconnection.second == -m_NrCols)
		{
			//connection goes up
			switch (CurrentDirection)
			{
			case Direction::left:
				return Direction::right;
				break;
			case Direction::right:
				return Direction::left;
				break;
			case Direction::up:
				return Direction::forward;
				break;
			case Direction::down:
				//std::cout << "invalid relative direction: from up to down into itself";
				return Direction::down;
				break;
			case Direction::forward:
				return Direction::up;
				break;
			}
		}
	}
	else if (currentNode == newconnection.second)
	{
		if (newconnection.first - newconnection.second == 1)
		{
			//connection goes right
			switch (CurrentDirection)
			{
			case Direction::left:
				//std::cout << "invalid relative direction: from right to left into itself";
				return Direction::down;
				break;
			case Direction::right:
				return Direction::forward;
				break;
			case Direction::up:

				return Direction::right;
				break;
			case Direction::down:
				return Direction::left;
				break;
			case Direction::forward:
				return Direction::right;
				break;
			}
		}
		else if (newconnection.first - newconnection.second == -1)
		{
			//connection goes left
			switch (CurrentDirection)
			{
			case Direction::left:
				return Direction::forward;
				break;
			case Direction::right:
				//std::cout << "invalid relative direction: from left to right into itself";
				return Direction::down;
				break;
			case Direction::up:
				return Direction::left;
				break;
			case Direction::down:
				return Direction::right;
				break;
			case Direction::forward:
				return Direction::left;
				break;
			}
		}
		else if (newconnection.first - newconnection.second == m_NrCols)
		{
			//connection goes up
			switch (CurrentDirection)
			{
			case Direction::left:
				return Direction::right;
				break;
			case Direction::right:
				return Direction::left;
				break;
			case Direction::up:
				return Direction::forward;
				break;
			case Direction::down:
				//std::cout << "invalid relative direction: from up to down into itself";
				return Direction::down;
				break;
			case Direction::forward:
				return Direction::up;
				break;
			}
		}
		else if (newconnection.first - newconnection.second == -m_NrCols)
		{
			//connection goes down
			switch (CurrentDirection)
			{
			case Direction::left:
				return Direction::left;
				break;
			case Direction::right:
				return Direction::right;
				break;
			case Direction::up:
				//std::cout << "invalid relative direction: from down to up into itself";
				return Direction::down;
				break;
			case Direction::down:
				return Direction::forward;
				break;
			case Direction::forward:
				return Direction::down;
				break;
			}
		}
	}
	std::cout << "invalid relative direction: current node not in new direction";
	return Direction::down;
}
void Maze::AddFirstForwardCycleConnections(int Mazeidx)
{
	std::pair<int, int>tempConnection;
	int temp1 = (m_MazeConnection[Mazeidx].first % m_NrCols);
	switch (m_direction)
	{
	case Direction::left:
		tempConnection.first = ((m_MazeConnection[Mazeidx].first / m_NrCols) * (m_NrCols * 4)) + (temp1 * 2);
		tempConnection.second = tempConnection.first - 1;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.first - 1;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode = m_MazeConnection[Mazeidx].second;
		break;
	case Direction::right:
		tempConnection.first = ((m_MazeConnection[Mazeidx].first / m_NrCols) * (m_NrCols * 4)) + (temp1 * 2) + m_NrCols * 2 + 1;
		tempConnection.second = tempConnection.first + 1;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.first + 1;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode = m_MazeConnection[Mazeidx].second;
		break;
	case Direction::up:
		tempConnection.first = ((m_MazeConnection[Mazeidx].first / m_NrCols) * (m_NrCols * 4)) + (temp1 * 2) - m_NrCols * 2;
		tempConnection.second = tempConnection.first + m_NrCols * 2 ;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.first + m_NrCols * 2;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode = m_MazeConnection[Mazeidx].second;
		break;
	case Direction::down:
		tempConnection.first = ((m_MazeConnection[Mazeidx].first / m_NrCols) * (m_NrCols * 4)) + (temp1 * 2) + 1;
		tempConnection.second = tempConnection.first - m_NrCols * 2;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.first - m_NrCols * 2;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode = m_MazeConnection[Mazeidx].second;
		break;
	}
}
void Maze::AddForwardCycleConnections()
{
	std::pair<int, int>tempConnection;
	tempConnection.first = m_CycleConnections.back().second;
	switch (m_direction)
	{
	case Direction::left:
		tempConnection.second = m_CycleConnections.back().second - 1;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second -1;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode -= 1;
		break;
	case Direction::right:
		tempConnection.second = m_CycleConnections.back().second + 1;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second + 1;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode += 1;
		break;
	case Direction::up:
		tempConnection.second = m_CycleConnections.back().second + m_NrCols*2;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second + m_NrCols * 2;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode += m_NrCols;
		break;
	case Direction::down:
		tempConnection.second = m_CycleConnections.back().second - m_NrCols * 2;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second - m_NrCols * 2;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode -= m_NrCols;
		break;
	}
}
void Maze::AddLeftTurnCycleConnections()
{
	std::pair<int, int>tempConnection;

	m_CycleConnections.pop_back();
	tempConnection.first = m_CycleConnections.back().second;
	switch (m_direction)
	{
	case Direction::left:
		
		tempConnection.second = m_CycleConnections.back().second - m_NrCols*2;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second - m_NrCols * 2;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode -= m_NrCols;
		break;
	case Direction::right:
		tempConnection.second = m_CycleConnections.back().second + m_NrCols * 2;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second + m_NrCols * 2;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode += m_NrCols;
		break;
	case Direction::up:
		tempConnection.second = m_CycleConnections.back().second - 1;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second - 1;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode -= 1;
		break;
	case Direction::down:
		tempConnection.second = m_CycleConnections.back().second + 1;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second + 1;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode += 1;
		break;
	}
}
void Maze::AddRightTurnCycleConnections()
{
	std::pair<int, int>tempConnection;

	tempConnection.first = m_CycleConnections.back().second;
	switch (m_direction)
	{
	case Direction::left:

		tempConnection.second = m_CycleConnections.back().second + m_NrCols * 2;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second + m_NrCols * 2;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second + m_NrCols * 2;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode += m_NrCols;
		break;
	case Direction::right:
		tempConnection.second = m_CycleConnections.back().second - m_NrCols * 2;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second - m_NrCols * 2;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second - m_NrCols * 2;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode -= m_NrCols;
		break;
	case Direction::up:
		tempConnection.second = m_CycleConnections.back().second + 1;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second + 1;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second + 1;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode += 1;
		break;
	case Direction::down:
		tempConnection.second = m_CycleConnections.back().second - 1;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second - 1;
		m_CycleConnections.push_back(tempConnection);
		tempConnection.first = tempConnection.second;
		tempConnection.second = tempConnection.second - 1;
		m_CycleConnections.push_back(tempConnection);
		m_CurrentMazeNode -= 1;
		break;
	}
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
