#include "MiniMax.h"

int MiniMax::minimax(CathderalConstruction* t_instructions)
{
    int minEval = 0;
	Board bestBoard;

    for (auto& board : getPossibleMoves(t_instructions))
    {
		if (board.score > minEval)
		{
			minEval = board.score;
			bestBoard = board;
		}
    }
	applyMove(bestBoard.changedCells);
	return bestBoard.pieceUsed;
}

void MiniMax::applyMove(std::vector<Cell> changedCells)
{
	for (auto& row : *Grid)
	{
		for (Cell& cell : row)
		{
			for (Cell changedCell : changedCells)
			{
				if (changedCell.getID() == cell.getID())
				{
					cell.lockInCell("enemy");
				}
			}
		}
	}
}

std::vector<Cell*> MiniMax::fillTool(Cell* t_cell)
{
	Cell* startingCell = t_cell;
	std::queue<Cell*> q;
	std::unordered_set<Cell*> visited; // Track visited cells
	std::vector<Cell*> temporarilyChanged; // Track white cells changed

	if (t_cell->getOwner() != "none") // Only start from unowned cells
		return {};

	q.push(startingCell);
	temporarilyChanged.push_back(startingCell);

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

			if (owner == currentPlayer) {
				continue; // Don't expand further from current cells
			}
			else if (owner == "none") {
				temporarilyChanged.push_back(neighbor);
				q.push(neighbor);
			}
			else if (owner == currentEnemy) {
				isEnclosed = false; // Enemy cells break the loop
			}
		}
	}

	if (isEnclosed)
	{ 
		return temporarilyChanged;
	}
	else {
		return {};
	}
}

void MiniMax::changeTurns()
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
}

void MiniMax::initalize(std::vector<std::vector<Cell>>* t_grid)
{
	Grid = t_grid;
}

std::vector<Board> MiniMax::getPossibleMoves(CathderalConstruction* t_instructions)
{
	std::vector<Board> boards;
	int pieces_enemy = 0;
	int pieces_player = 0;

	// The current board
	Board board = {};
	board.grid = *Grid;
	std::vector<std::vector<std::string>> instructions = t_instructions->instructions;
	
    for (auto& row : board.grid)
    {
        for (Cell& cell : row)
        {
			// For loop to check every possible building available
			for (size_t i = 0; i < instructions.size(); i++)
			{
				for (size_t i = 0; i < 4; i++)
				{
					// Sets new board copy
					board.grid = *Grid;

					// Sets the main cells to check
					Cell* firstCell = &cell;
					Cell* cellToCheck = &cell;
					std::vector<Cell*> placementCells; // Hold the current placement cells colored green

					bool outOfBounds = false; // out of bounds bool

					// Check first cell
					cellToCheck->checkCell();
					if (cellToCheck->isBlocked()) // Break to next loop if first cell is blocked
						continue;

					placementCells.push_back(cellToCheck);

					// Constructing the shapes with instructions
					for (auto direction : instructions[i])
					{
						if (direction == "up")
						{
							// Out of Bounds
							if (cellToCheck == nullptr || cellToCheck->up() == nullptr)
							{
								outOfBounds = true;
								break;
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
								break;
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
								break;
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
								break;
							}
							else {
								cellToCheck = cellToCheck->left();
								cellToCheck->checkCell();
								placementCells.push_back(cellToCheck);
							}
						}
						else if (direction == "middle")
						{
							cellToCheck = firstCell;
						}
					}

					// Check for blocked cells
					for (auto& cell : placementCells)
					{
						if (cell->isBlocked() == true)
						{
							outOfBounds = true;
						}
						cell->uncheckCell();
					}
					// Add valid cells to vector
					if (outOfBounds == false)
					{
						for (auto& cell : placementCells)
						{
							cell->lockInCell(currentPlayer);
							board.changedCells.push_back(*cell);
						}

						bool pass = false;
						// Fill tool add
						for (auto& cell : placementCells)
						{
							for (auto& neighbour : cell->neighbours)
							{
								if (neighbour != nullptr &&
									cell->getShape().getFillColor() != sf::Color::Green)
								{
									std::vector<Cell*> filledCells = fillTool(neighbour);

									if (filledCells.size() > 1 && pass == false)
									{
										pass = true;

										for (auto& filledCell : filledCells)
										{
											board.changedCells.push_back(*filledCell);
										}
									}
								}
							}
						}

						// Add board if valid
						board.pieceUsed = i;
						board.score = gatherScore(board.grid, board.changedCells.size());
						boards.push_back(board);

						for (auto& cell : placementCells)
						{
							cell->unlockCell();
						}
					}
					// Clear vectors
					board.changedCells.clear();
					placementCells.clear();

					// Rotate shape
					CathderalConstruction constructor;
					instructions[i] = constructor.rotate(instructions[i]);
				}
			}
        }
    }

	return boards;
}

int MiniMax::gatherScore(std::vector<std::vector<Cell>> t_grid, int t_increase)
{
	int currentScore = 0;

	for (auto& row : t_grid)
	{
		for (Cell& cell : row)
		{
			if (cell.getOwner() == "enemy")
			{
				currentScore++;
			}
		}
	}
	currentScore += t_increase;
	return currentScore;
}


