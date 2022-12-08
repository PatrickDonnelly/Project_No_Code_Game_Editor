#pragma once

#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>

class Obstacle
{
	sf::Texture m_obstacleTexture;
	sf::Sprite m_obstacleSprite;
	sf::RectangleShape m_obstacleBounds;
	int m_boundsWidth;
	int m_boundsHeight;

public:
	Obstacle();
	~Obstacle();


	void init();
	void setUpSprite();
	void setObstacleTexture(sf::Texture& t_texture);
	void setUpBounds();
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	sf::Sprite* getSprite();
	sf::RectangleShape* getBounds();

};
#endif // !OBSTACLE_HPP
