#include "pch.h"
#include "Apple.h"
#include "utils.h"

Apple::Apple(int nrCols, int nrRows)
	:m_NrOfCol{ nrCols },
	m_NrOfRows{ nrRows }
{
}

Apple::~Apple()
{
	
}
void Apple::AddApple(std::vector<int> Snake)
{
	bool temp {true};
	do
	{
		m_Apple = GetIndex(GetRand(0, m_NrOfRows), GetRand(0, m_NrOfCol), m_NrOfCol);
		for (auto snakecell : Snake)
		{
			if (m_Apple != snakecell && m_Apple < 401)
			{
				temp = false;
			}
		}
	}
	while (temp);
	
}