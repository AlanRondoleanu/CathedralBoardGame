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
	m_window{ sf::VideoMode{ 1400, 1000, 32U }, "SFML Game" },
	m_exitGame{ false } //when true game will exit

{
	initialize();
	scoreManager.intialize(&Grid);
	fonts.initialize();
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
		{
			placeBuilding();
			changeTurns();
		}
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

	if (sf::Keyboard::Z == t_event.key.code)
	{
		//fillTool();
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
	outlineBuilding();
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

	fonts.render(m_window);

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

void Game::outlineBuilding()
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

				std::vector<Cell*> placementCells; // Hold the current placement cells colored green
				placementCells.push_back(cellToCheck);

				for (std::string direction : instructions)
				{
					if (direction == "up")
					{
						// Out of Bounds
						if (cellToCheck == nullptr || cellToCheck->up() == nullptr) 
						{
							outOfBounds = true;
						}
						else {
							cellToCheck = cellToCheck->up();
							cellToCheck->checkCell();
							placementCells.push_back(cellToCheck);
						}

					}
					else if (direction == "down")
					{
						// Out of Bounds
						if (cellToCheck == nullptr || cellToCheck->down() == nullptr)
						{
							outOfBounds = true;
						}
						else {
							cellToCheck = cellToCheck->down();
							cellToCheck->checkCell();
							placementCells.push_back(cellToCheck);
						}
					}
					else if (direction == "right")
					{		
						// Out of Bounds
						if (cellToCheck == nullptr || cellToCheck->right() == nullptr)
						{
							outOfBounds = true;
						}
						else {
							cellToCheck = cellToCheck->right();
							cellToCheck->checkCell();
							placementCells.push_back(cellToCheck);
						}
					}
					else if (direction == "left")
					{
						// Out of Bounds
						if (cellToCheck == nullptr || cellToCheck->left() == nullptr)
						{
							outOfBounds = true;
						}
						else {
							cellToCheck = cellToCheck->left();
							cellToCheck->checkCell();
							placementCells.push_back(cellToCheck);
						}
					}
					else if (direction == "middle")
					{
						cellToCheck = currentHoveredCell;
					}
				}
				// Check for filled space
				for (auto& cell : placementCells)
				{		
					for (auto& cell : cell->neighbours)
					{
						if (turns >= 2 && 
							cell != nullptr &&
							cell->getShape().getFillColor() != sf::Color::Green)
						{
							fillTool(cell);
						}
					}						
				}
				// Get Score for current layout
				scoreManager.gatherScore(currentPlayer);

				if (currentPlayer == "player")
					fonts.setPlayerScoreText(scoreManager.getScore());
				if (currentPlayer == "enemy")
					fonts.setEnemyScoreText(scoreManager.getScore());
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
					currentCell->lockInCell(currentPlayer);
				}

				if (currentCell->getShape().getFillColor() == currentPlayerColor)
				{
					currentCell->lockInCell(currentPlayer);
				}
			}
		}
	}
	// Remove building from play
	if (currentPlayer == "player")
		construction.instructions.erase(construction.instructions.begin() + currentBuildingChoice);
	else
		enemyConstruction.instructions.erase(enemyConstruction.instructions.begin() + currentBuildingChoice);
	fonts.setRemainingBuildingsText(construction.instructions.size());
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

	if (currentPlayer == "player")
		instructions = construction.instructions[currentBuildingChoice];
	else
		instructions = enemyConstruction.instructions[currentBuildingChoice];
}

void Game::changeTurns()
{
	if (currentPlayer == "player")
	{
		currentPlayer = "enemy";
		currentEnemy = "player";
		currentPlayerColor = sf::Color::Magenta;
	}
	else if (currentPlayer == "enemy")
	{
		currentPlayer = "player";
		currentEnemy = "enemy";
		currentPlayerColor = sf::Color::Blue;
	}
	fonts.setCurrentTurnText(currentPlayer);
	turns++;

	// Setting the correct constructions or the correct player 
	currentBuildingChoice = 0;
	if (currentPlayer == "player")
		instructions = construction.instructions[currentBuildingChoice];
	else
		instructions = enemyConstruction.instructions[currentBuildingChoice];
}

void Game::fillTool(Cell* t_cell)
{
	Cell* startingCell = t_cell;
	std::queue<Cell*> q;
	std::unordered_set<Cell*> visited; // Track visited cells
	std::vector<Cell*> temporarilyChanged; // Track white cells changed to blue
	
	if (t_cell->getOwner() != "none") // Only start from unowned cells
		return; 

	q.push(startingCell);
	temporarilyChanged.push_back(startingCell);
	startingCell->setColor(currentPlayerColor);

	bool isEnclosed = true;

	while (!q.empty()) {
		Cell* currentCellToCheck = q.front();
		q.pop();

		if (visited.find(currentCellToCheck) != visited.end())
			continue; // Skip already visited cells

		visited.insert(currentCellToCheck);

		for (auto* neighbor : currentCellToCheck->neighbours) {
			if (!neighbor || visited.find(neighbor) != visited.end())
				continue;

			std::string owner = neighbor->getOwner();

			if (owner == currentPlayer || neighbor->isChecked() == true) {
				continue; // Don't expand further from current cells
			}
			else if (owner == "none") {
				neighbor->setColor(currentPlayerColor);
				temporarilyChanged.push_back(neighbor);
				q.push(neighbor);
			}
			else if (owner == currentEnemy) {
				isEnclosed = false; // Enemy cells break the loop
			}
		}
	}

	if (!isEnclosed) {
		// Revert all temporarily changed cells to white
		for (auto* cell : temporarilyChanged) {
			cell->setColor(sf::Color::White);
		}
	}
}

sf::Vector2f Game::getMousePosition(sf::RenderWindow& t_window)
{
	sf::Vector2f m_mousePosition;

	m_mousePosition.x = (float)sf::Mouse::getPosition(t_window).x;
	m_mousePosition.y = (float)sf::Mouse::getPosition(t_window).y;

	return m_mousePosition;
}