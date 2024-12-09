#ifndef MINIMAX_HPP
#define MINIMAX_HPP
#include "Cell.h"
#include "CathderalConstruction.h"
#include <queue>
#include <unordered_set>

struct Board {
	std::vector<std::vector<Cell>> grid;
	std::vector<Cell> changedCells;
	int score = 0;
	int pieceUsed = 0;
};

class MiniMax
{
public:
	void initalize(std::vector<std::vector<Cell>>* t_grid);
	int minimax(CathderalConstruction* t_instructions);
	std::vector<Board> getPossibleMoves(CathderalConstruction* t_instructions);
	int gatherScore(std::vector<std::vector<Cell>> t_grid, int t_increase);
	void applyMove(std::vector<Cell> changedCells);
	std::vector<Cell*> fillTool(Cell* t_cell);
	void changeTurns();
private:
	std::vector<std::vector<Cell>>* Grid;
	std::string currentPlayer{ "player" };
	std::string currentEnemy{ "enemy" };
	sf::Color currentPlayerColor{ sf::Color::Blue };
};

#endif
