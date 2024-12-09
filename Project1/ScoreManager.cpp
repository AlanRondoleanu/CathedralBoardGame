#include "ScoreManager.h"

void ScoreManager::intialize(std::vector<std::vector<Cell>>* t_grid)
{
	grid = t_grid;
}

void ScoreManager::gatherScore(std::string t_player)
{
	int currentScore = 0;
	for (auto& row : *grid)
	{
		for (Cell& cell : row)
		{
			if (t_player == "player" && (cell.getShape().getFillColor() == sf::Color::Blue ||
				cell.getShape().getFillColor() == sf::Color::Green))
			{
				currentScore++;
			}
			else if (t_player == "enemy" && cell.getOwner() == "enemy")
			{
				currentScore++;
			}
		}
	}
	
	if (t_player == "player")
	{
		score = currentScore;
	}
	else
	{
		enemyScore = currentScore++;
	}
}
