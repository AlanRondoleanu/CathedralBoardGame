#include "Cell.h"

Cell::Cell()
{
	shape.setSize({100,100});
	shape.setFillColor(sf::Color::White);
	shape.setOutlineColor(sf::Color::Blue);
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

void Cell::resetCell()
{
	checking = false;
	blocked = false;
	if (blocked == false && lockedIn == false)
	{
		shape.setFillColor(sf::Color::White);
	}
	if (lockedIn == true)
	{
		shape.setFillColor(sf::Color::Blue);
	}
}

void Cell::lockInCell()
{
	shape.setFillColor(sf::Color::Blue);
	lockedIn = true;
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
