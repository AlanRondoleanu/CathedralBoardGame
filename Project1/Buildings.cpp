#include "Buildings.h"

Buildings::Buildings()
{
	sf::RectangleShape first;
	first.setSize({100,100});
	first.setFillColor(sf::Color::Green);
	shapes.push_back(first);
}

void Buildings::render(sf::RenderWindow& t_window)
{
	for (sf::RectangleShape shape : shapes)
	{
		t_window.draw(shape);
	}
}

void Buildings::placementCollision(Buildings* t_buildings[])
{
	//body.setFillColor(sf::Color::Green);
	//blocked = false;
	/*
	for (int i = 0; i < PLAYER_BUILDING_AMOUNT; i++)
	{
		if (body.getGlobalBounds().intersects(t_buildings[i]->body.getGlobalBounds()))
		{
			body.setFillColor(sf::Color::Red);
			blocked = true;
		}
	}
	*/
}

void Buildings::setPosition(sf::Vector2f t_position)
{
	for (sf::RectangleShape& shape : shapes)
	{
		shape.setPosition(t_position);
	}
}
