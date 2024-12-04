/// <summary>
/// Author: Alan Rondoleanu
/// Date: 18/11/2024
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Buildings.h"
#include "Cell.h"
#include "CathderalConstruction.h"

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
	void constructCathedral();
	void setNeighbours();
	void resetAllCells();
	void placeBuilding();
	void swapBuilding(int t_i);

	// Grid
	int const CELL_AMOUNT{ 10 };
	std::vector<std::vector<Cell>> Grid;
	Cell* currentHoveredCell;

	// Building Construction
	CathderalConstruction construction;
	std::vector<std::string> instructions;
	bool outOfBounds{ false };
	int currentBuildingChoice{ 0 };

	sf::Vector2f gridPlacement();
		
	sf::Vector2f getMousePosition(sf::RenderWindow& t_window);
	sf::Vector2f mousePosition;
	sf::Vector2f mouseGridPlacement;

	sf::RenderWindow m_window; // main SFML window
	sf::Sprite backgroundSprite; // the sprite for the background
	sf::Texture gameBackground; // The background for the game

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

