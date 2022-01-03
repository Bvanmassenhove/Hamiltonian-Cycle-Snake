#pragma once
#include "utils.h"
#include "Apple.h"
using namespace utils;
class Snake final
{
public:

	Snake(int nrCols, int nrRows,float cellSize);
	~Snake();

	Snake(const Snake& other) = delete;
	Snake& operator=(const Snake& other) = delete;
	Snake(Snake&& other) = delete;
	Snake& operator=(Snake&& other) = delete;

	void Update(float elapsedSec);
	std::vector<int> GetSnake() { return m_Snake; }
	void SetDirection(Direction direction) { m_Direction = direction; }
	bool AppleOverlap(int idx);
	int GetSnakeSize() { return m_SnakeSize; };

private:
	std::vector<int> m_Snake;
	int m_SnakeSize{};
	int m_NrOfCol;
	float m_CellSize{};
	Direction m_Direction{};
	float m_elapsedSec{};

	void ExtendSnake(int idx) { m_Snake.push_back(idx); m_SnakeSize++; }
};