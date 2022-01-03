#pragma once
#include "Snake.h"
#include "utils.h"
using namespace utils;
class Apple final
{
public:

	Apple(int nrCols, int nrRows);
	~Apple();

	Apple(const Apple& other) = delete;
	Apple& operator=(const Apple& other) = delete;
	Apple(Apple&& other) = delete;
	Apple& operator=(Apple&& other) = delete;

	int GetApple() { return m_Apple; }
	void AddApple(std::vector<int> Snake);

private:
	int m_Apple;
	int m_NrOfCol;
	int m_NrOfRows;
};