#include "Fonts.h"

void Fonts::initialize()
{
	//Font Loading
	if (!font.loadFromFile("ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	// Player Score Text
	scoreTextPlayer.setFont(font);
	scoreTextPlayer.setFillColor(sf::Color::White);
	scoreTextPlayer.setPosition({1010, 80});
	scoreTextPlayer.setString("Score: 0");
	// Enemy Score Text
	scoreTextEnemy.setFont(font);
	scoreTextEnemy.setFillColor(sf::Color::White);
	scoreTextEnemy.setPosition({ 1010, 120 });
	scoreTextEnemy.setString("Enemy Score: 0");
	// Turn order text
	currentTurn.setFont(font);
	currentTurn.setFillColor(sf::Color::White);
	currentTurn.setPosition({ 1010, 20 });
	currentTurn.setString("Current Turn: Player");
	// Controls text
	controlText.setFont(font);
	controlText.setFillColor(sf::Color::White);
	controlText.setPosition({ 1010, 800 });
	controlText.setString("Q & E: Cycle Shapes \nR: Rotate \nSpace: Place Shape");
	// Remaining buildings text
	remainingBuildings.setFont(font);
	remainingBuildings.setFillColor(sf::Color::White);
	remainingBuildings.setPosition({ 1010, 200 });
	remainingBuildings.setString("Buildings Left: 11");
}

void Fonts::render(sf::RenderWindow& t_window)
{
	t_window.draw(scoreTextPlayer);
	t_window.draw(scoreTextEnemy);
	t_window.draw(currentTurn);
	t_window.draw(controlText);
	t_window.draw(remainingBuildings);
}

void Fonts::setPlayerScoreText(int t_score)
{
	scoreTextPlayer.setString("Score: " + std::to_string(t_score));
}

void Fonts::setEnemyScoreText(int t_score)
{
	scoreTextEnemy.setString("Score Enemy: " + std::to_string(t_score));
}

void Fonts::setCurrentTurnText(std::string t_turn)
{
	currentTurn.setString("Current Turn: " + t_turn);
}

void Fonts::setRemainingBuildingsText(int t_amount)
{
	remainingBuildings.setString("Buildings Left: " + std::to_string(t_amount));
}
