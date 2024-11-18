#ifndef BUILDINGS_H
#define BUILDINGS_H
#include <SFML/Graphics.hpp>
#include <vector>

class Buildings
{
public:
	Buildings();

	void update();
	void render(sf::RenderWindow& t_window);
	void place(sf::Vector2f t_position);
	void placementCollision(Buildings* t_buildings[]);

	
	bool placed{ false };
	
	

	//Getters-Setters
	void setPosition(sf::Vector2f t_position);
	bool getBlocked() { return blocked; }


private:
	std::vector<sf::RectangleShape> shapes;

	bool blocked{ false };	
};
#endif
