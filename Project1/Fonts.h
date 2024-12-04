#ifndef FONTS_HPP
#define FONTS_HPP
#include <SFML/Graphics.hpp>
#include <iostream>

class Fonts
{
public:
	void initialize();
	void render(sf::RenderWindow& t_window);
	void setPlayerScoreText(int t_score);
	void setEnemyScoreText(int t_score);
	void setCurrentTurnText(std::string t_turn);
	void setRemainingBuildingsText(int t_amount);

private:
	sf::Font font;
	sf::Text scoreTextPlayer;
	sf::Text scoreTextEnemy;
	sf::Text controlText;
	sf::Text currentTurn;
	sf::Text remainingBuildings;
};

#endif