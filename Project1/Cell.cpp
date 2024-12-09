#include "Cell.h"

Cell::Cell()
{
	shape.setSize({100,100});
	shape.setFillColor(sf::Color::White);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(1);
}

void Cell::render(sf::RenderWindow& t_window)
{
	t_window.draw(shape);
}

void Cell::checkCell()
{
	checking = true;

	if (lockedIn == true)
	{
		shape.setFillColor(sf::Color::Red);
		blocked = true;
	}
	else if (checking == true && blocked == false)
	{
		shape.setFillColor(sf::Color::Green);
	}
}

void Cell::uncheckCell()
{
	if (owner == "none")
	{
		checking = false;
		shape.setFillColor(sf::Color::White);
	}
}

void Cell::resetCell()
{
	checking = false;
	blocked = false;
	if (blocked == false && lockedIn == false)
	{
		shape.setFillColor(sf::Color::White);
	}
	if (lockedIn == true && owner == "player")
	{
		shape.setFillColor(sf::Color::Blue);
	}
	if (lockedIn == true && owner == "enemy")
	{
		shape.setFillColor(sf::Color::Magenta);
	}
}

void Cell::lockInCell(std::string t_player)
{
	if (t_player == "player")
		shape.setFillColor(sf::Color::Blue);
	if (t_player == "enemy")
		shape.setFillColor(sf::Color::Magenta);

	owner = t_player;
	lockedIn = true;
}

void Cell::unlockCell()
{
	if (shape.getFillColor() != sf::Color::Green)
		shape.setFillColor(sf::Color::White);
	if (checking == true)
		shape.setFillColor(sf::Color::Green);

	owner = "none";
	lockedIn = false;
}

void Cell::setDebug()
{
	debug = true;
}

Cell* Cell::up()
{
	if (neighbours[0] != nullptr)
	{
		return neighbours[0];
	}
	else {
		return nullptr;
	}
}

Cell* Cell::down()
{
	if (neighbours[3] != nullptr)
	{
		return neighbours[3];
	}
	else {
		return nullptr;
	}
}

Cell* Cell::left()
{
	if (neighbours[1] != nullptr)
	{
		return neighbours[1];
	}
	else {
		return nullptr;
	}
}

Cell* Cell::right()
{
	if (neighbours[2] != nullptr)
	{
		return neighbours[2];
	}
	else {
		return nullptr;
	}
}
