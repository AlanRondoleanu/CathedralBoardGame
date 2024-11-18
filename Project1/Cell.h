#ifndef CELL_HPP
#define CELL_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class Cell
{
public:
	Cell();

	void render(sf::RenderWindow& t_window);
	void checkCell();
	void resetCell();


	Cell* neighbours[4];

	// Sets
	void setPosition(sf::Vector2f t_position) {shape.setPosition(t_position);}
	void setID(int t_ID) { cellID = t_ID; }

	// Gets
	sf::RectangleShape getShape() { return shape; }
	Cell* up();
	Cell* down();
	Cell* left();
	Cell* right();


private:
	int cellID{ 0 };
	bool blocked{ false };  
	bool checking{ false };

	sf::RectangleShape shape;
};

#endif