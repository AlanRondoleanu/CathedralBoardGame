#ifndef SCOREMANAGER_HPP
#define SCOREMANAGER_HPP
#include <vector>
#include "Cell.h"

class ScoreManager
{
public:
	void intialize(std::vector<std::vector<Cell>>* t_grid);
	void gatherScore(std::string t_player);
	int getScore() { return score; }
	int getEnemyScore() { return enemyScore; }

	int score{ 0 };
	int enemyScore{ 0 };

private:
	std::vector<std::vector<Cell>>* grid;
};

#endif

