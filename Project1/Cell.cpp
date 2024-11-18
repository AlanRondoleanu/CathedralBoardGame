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

	if (blocked == true)
	{
		shape.setFillColor(sf::Color::Red);
	}
	else if (checking == true)
	{
		shape.setFillColor(sf::Color::Green);
	}
	else
	{
		shape.setFillColor(sf::Color::White);
	}
}

void Cell::resetCell()
{
	checking = false;
	if (blocked == false)
	{
		shape.setFillColor(sf::Color::White);
	}
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
