/// <summary>
/// Author: Alan Rondoleanu
/// Date: 18/11/2024
/// Video: https://1drv.ms/u/s!AjamfDLsDscZh2RWbt4JqtKbcB3H?e=VEuJSb
/// </summary>

#include "Game.h"

/// <summary>
/// default constructor
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1000, 1000, 32U }, "SFML Game" },
	m_exitGame{ false } //when true game will exit

{
	initialize();
}

/// <summary>
/// default destructor 
/// </summary>
Game::~Game()
{
}

/// <summary>
/// main game loop
/// updates 60 times per second
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps

	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handles events and inputs fron the user
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::KeyReleased == newEvent.type)
		{
			processKeyReleases(newEvent);
		}
	}
}


/// <summary>
/// handles the key presses by the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Space == t_event.key.code)
	{
		if (!outOfBounds)
			placeBuilding();
	}
	if (sf::Keyboard::R == t_event.key.code)
	{
		currentHoveredCell = nullptr;
		instructions = construction.rotate(instructions);
	}
	if (sf::Keyboard::E == t_event.key.code)
	{
		currentHoveredCell = nullptr;
		swapBuilding(1);
	}
	if (sf::Keyboard::Q == t_event.key.code)
	{
		currentHoveredCell = nullptr;
		swapBuilding(-1);
	}
}

/// <summary>
/// Processes the keys released on the keyboard
/// </summary>
/// <param name="t_event">the key released</param>
void Game::processKeyReleases(sf::Event t_event)
{
	
}

/// <summary>
/// Update the game
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	mousePosition = getMousePosition(m_window);
	constructCathedral();
}

/// <summary>
/// draws the sprites and displays the window
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	for (auto& row : Grid)
	{
		for (Cell& cell : row)
		{
			cell.render(m_window);
		}
	}

	m_window.display();
}

void Game::initialize()
{
	float x = 0;
	float y = 0;
	int cellNumber = 0;
	Cell cell = Cell();

	Grid.resize(CELL_AMOUNT, std::vector<Cell>(CELL_AMOUNT));

	for (size_t o = 0; o < CELL_AMOUNT; o++)
	{
		for (size_t i = 0; i < CELL_AMOUNT; i++)
		{
			sf::Vector2f newPosition = { x, y };
			cell.setPosition(newPosition);
			cell.setID(cellNumber);

			Grid[o][i] = cell;

			x += 100;
			cellNumber++;
		}
		y += 100;
		x = 0;
	}

	setNeighbours();

	// Construction
	instructions = construction.instructions[0];
}

void Game::constructCathedral()
{
	for (auto& row : Grid)
	{
		for (Cell& cell : row)
		{
			if (&cell != currentHoveredCell &&
				cell.getShape().getGlobalBounds().contains(mousePosition))
			{
				resetAllCells();
				currentHoveredCell = &cell;

				Cell* cellToCheck = currentHoveredCell;
				cellToCheck->checkCell();

				for (std::string direction : instructions)
				{
					if (direction == "up")
					{
						cellToCheck = cellToCheck->up();
						if (cellToCheck != nullptr)
							cellToCheck->checkCell();
						if (cellToCheck == nullptr)
							outOfBounds = true;
					}
					else if (direction == "down")
					{
						cellToCheck = cellToCheck->down();
						if (cellToCheck != nullptr)
							cellToCheck->checkCell();
						if (cellToCheck == nullptr)
							outOfBounds = true;
					}
					else if (direction == "right")
					{
						cellToCheck = cellToCheck->right();
						if (cellToCheck != nullptr)
							cellToCheck->checkCell();
						if (cellToCheck == nullptr)
							outOfBounds = true;
					}
					else if (direction == "left")
					{
						cellToCheck = cellToCheck->left();
						if (cellToCheck != nullptr)
							cellToCheck->checkCell();
						if (cellToCheck == nullptr)
							outOfBounds = true;
					}
					else if (direction == "middle")
					{
						cellToCheck = currentHoveredCell;
					}
				}
			}
		}
	}
}

void Game::setNeighbours()
{
	for (int o = 0; o < CELL_AMOUNT; o++)
	{
		for (int i = 0; i < CELL_AMOUNT; i++)
		{
			Cell* curentCell = &Grid[o][i];


			// Up
			if (o - 1 >= 0)
			{
				curentCell->neighbours[0] = &Grid[o - 1][i];
			}
			else {
				curentCell->neighbours[0] = nullptr;
			}

			// Left
			if (i - 1 >= 0)
			{
				curentCell->neighbours[1] = &Grid[o][i - 1];
			}
			else {
				curentCell->neighbours[1] = nullptr;
			}

			// Right
			if (i + 1 < CELL_AMOUNT)
			{
				curentCell->neighbours[2] = &Grid[o][i + 1];
			}
			else {
				curentCell->neighbours[2] = nullptr;
			}

			// Down
			if (o + 1 < CELL_AMOUNT)
			{
				curentCell->neighbours[3] = &Grid[o + 1][i];
			}
			else {
				curentCell->neighbours[3] = nullptr;
			}
		}
	}
}

void Game::resetAllCells()
{
	outOfBounds = false;
	for (auto& row : Grid)
	{
		for (Cell& cell : row)
		{
			cell.resetCell();
		}
	}
}

void Game::placeBuilding()
{
	// Check if any checked cells are blocked
	bool invalidPlacement = false;
	for (int o = 0; o < CELL_AMOUNT; o++)
	{
		for (int i = 0; i < CELL_AMOUNT; i++)
		{
			Cell* currentCell = &Grid[o][i];

			if (currentCell->isBlocked() == true)
			{
				invalidPlacement = true;
			}
		}
	}
	// If no checked cells are blocked, lock them in
	if (invalidPlacement == false)
	{
		for (int o = 0; o < CELL_AMOUNT; o++)
		{
			for (int i = 0; i < CELL_AMOUNT; i++)
			{
				Cell* currentCell = &Grid[o][i];

				if (currentCell->isChecked() == true && currentCell->isBlocked() == false)
				{
					currentCell->lockInCell();
				}
			}
		}
	}
}

void Game::swapBuilding(int t_i)
{
	const int MAX = construction.instructions.size() - 1;
	const int MIN = 0;

	currentBuildingChoice += t_i; // Increment or decrement based on direction

	if (currentBuildingChoice > MAX)
	{
		currentBuildingChoice = MIN;
	}
	else if (currentBuildingChoice < MIN)
	{
		currentBuildingChoice = MAX;
	}

	instructions = construction.instructions[currentBuildingChoice];
}

sf::Vector2f Game::gridPlacement()
{
	mouseGridPlacement.x = (static_cast<int>(mousePosition.x) / 100) * 100;
	mouseGridPlacement.y = (static_cast<int>(mousePosition.y) / 100) * 100;
	return mouseGridPlacement;
}

sf::Vector2f Game::getMousePosition(sf::RenderWindow& t_window)
{
	sf::Vector2f m_mousePosition;

	m_mousePosition.x = (float)sf::Mouse::getPosition(t_window).x;
	m_mousePosition.y = (float)sf::Mouse::getPosition(t_window).y;

	return m_mousePosition;
}



/// <summary>
/// loads the background for the game
/// </summary>
//void Game::loadTextures()
//{
//	//Robot
//	if (!robotTexture.loadFromFile("robot.png"))
//	{
//		std::cout << "problem loading robot" << std::endl;
//	}
//	robot.setTexture(robotTexture);
//	robot.setTextureRect(sf::IntRect{ 0,0,width,height });
//	robot.setOrigin(width/2, height/2);
//	robot.setScale(0.5f, 0.5f);
//	robot.setPosition(startPos);
//	
//	//Flower
//	if (!flowerTexture.loadFromFile("plant.png"))
//	{
//		std::cout << "problem loading flower" << std::endl;
//	}
//	flower.setTexture(flowerTexture);
//	flower.setTextureRect(sf::IntRect{ 0,0,100,229 });
//	flower.setScale(0.2f, 0.2f);
//	flower.setPosition(startPos.x + 570, startPos.y - 10);
//
//	//Background
//	if (!gameBackground.loadFromFile("background.jpg"))
//	{
//		std::cout << "problem loading background" << std::endl;
//	}
//	backgroundSprite.setTexture(gameBackground);
//	backgroundSprite.setTextureRect(sf::IntRect{ 0,0,819,175 });
//}
//void Game::loadMusic()
//{
//	if (!music.openFromFile("music.wav"))
//	{
//		std::cout << "problem loading music" << std::endl;
//	}
//	music.play();
//	music.setVolume(10.0f);
//}
//
