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
	void lockInCell(std::string t_player);
	void unlockCell();

	Cell* neighbours[4];

	// Sets
	void setPosition(sf::Vector2f t_position) {shape.setPosition(t_position);}
	void setID(int t_ID) { cellID = t_ID; }
	void setColor(sf::Color t_color) { shape.setFillColor(t_color); }
	void setOwner(std::string t_player) { owner = t_player; }

	// Gets
	sf::RectangleShape getShape() { return shape; }
	bool isChecked() { return checking; }
	bool isBlocked() { return blocked; }
	bool isLocked() { return lockedIn; }
	std::string getOwner() { return owner; }

	Cell* up();
	Cell* down();
	Cell* left();
	Cell* right();


private:
	int cellID{ 0 };
	bool blocked{ false };  
	bool checking{ false };
	bool lockedIn{ false };
	std::string owner{"none"};

	sf::RectangleShape shape;
};

#endif