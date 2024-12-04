#include "ScoreManager.h"

void ScoreManager::intialize(std::vector<std::vector<Cell>>* t_grid)
{
	grid = t_grid;
}

void ScoreManager::gatherScore(std::string t_player)
{
	sf::Color colorToCheckFor;
	if (t_player == "player")
		colorToCheckFor = sf::Color::Blue;
	else 
		colorToCheckFor = sf::Color::Magenta;

	int currentScore = 0;

	for (auto& row : *grid)
	{
		for (Cell& cell : row)
		{
			if (cell.getShape().getFillColor() == colorToCheckFor ||
				cell.getShape().getFillColor() == sf::Color::Green)
			{
				currentScore++;
			}
		}
	}

	score = currentScore;
}
