#pragma once
using namespace utils;
class Grid final
{
public:

	Grid(int nrCols,int nrRows, float cellSize, float windowWidth, float windowHeight);
	~Grid();

	Grid(const Grid& other) = delete;
	Grid& operator=(const Grid& other) = delete;
	Grid(Grid&& other) = delete;
	Grid& operator=(Grid&& other) = delete;

	void ResetGrid();
	void DrawGrid(float windowWidth, float windowHeight);
	std::vector<Tile> GetGrid() { return m_Grid; }
	void SetCellSnake(std::vector<int> idx);
	void SetCellApple(int idx);

	bool CheckGameOver(std::vector<int> snake);

	void ShowMaze(std::vector<int>maze);
	void ShowCycle(std::vector<std::pair<int, int>>cycle);

private:
	Color4f m_GridBackgroundColor{ .4f, .4f, .4f, 1 };
	int m_NrCols{};
	int m_NrRows{};
	float m_CellSize{};
	Rectf m_GridBgRect{};
	std::vector<Tile> m_Grid{};
};
