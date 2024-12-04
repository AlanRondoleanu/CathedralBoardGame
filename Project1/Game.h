/// <summary>
/// Author: Alan Rondoleanu
/// Date: 18/11/2024
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <queue>
#include <unordered_set>
#include "Cell.h"
#include "CathderalConstruction.h"
#include "ScoreManager.h"
#include "Fonts.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processKeyReleases(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void initialize();
	void outlineBuilding();
	void setNeighbours();
	void resetAllCells();
	void placeBuilding();
	void swapBuilding(int t_i);
	void changeTurns();
	void fillTool(Cell* t_cell);

	// Grid
	int const CELL_AMOUNT{ 10 };
	std::vector<std::vector<Cell>> Grid;
	Cell* currentHoveredCell;

	// Score Manager
	ScoreManager scoreManager;

	// Building Construction
	CathderalConstruction construction;
	CathderalConstruction enemyConstruction;
	std::vector<std::string> instructions;
	bool outOfBounds{ false };
	int currentBuildingChoice{ 0 };

	// Fonts
	Fonts fonts;

	// Mouse stuff
	sf::Vector2f getMousePosition(sf::RenderWindow& t_window);
	sf::Vector2f mousePosition;
	sf::Vector2f mouseGridPlacement;

	// Turns
	std::string currentPlayer{ "player" };
	std::string currentEnemy{ "enemy" };
	int turns{ 0 };
	sf::Color currentPlayerColor{ sf::Color::Blue };


	sf::RenderWindow m_window; // main SFML window
	sf::Sprite backgroundSprite; // the sprite for the background
	sf::Texture gameBackground; // The background for the game

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

