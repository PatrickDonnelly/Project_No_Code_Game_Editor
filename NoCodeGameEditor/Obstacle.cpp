#include "Obstacle.h"
#include <iostream>

Obstacle::Obstacle()
{
	m_boundsHeight = 32;
	m_boundsWidth = 32;
	setUpSprite();
	setUpBounds();

}

Obstacle::~Obstacle()
{
}

void Obstacle::init()
{
}

void Obstacle::setUpSprite()
{
	setObstacleTexture(m_obstacleTexture);
	m_obstacleSprite.setOrigin(16, 16);
	m_obstacleSprite.setColor(sf::Color::White);
	m_obstacleSprite.setPosition(100, 100);
}

void Obstacle::setObstacleTexture(sf::Texture& t_texture)
{
	if (!t_texture.loadFromFile("ASSETS\\IMAGES\\statue.png"))
	{
		std::cout << "Can't load main menu bgt" << std::endl;
	}
	m_obstacleSprite.setTexture(t_texture);
}

void Obstacle::setUpBounds()
{
	m_obstacleBounds.setSize(sf::Vector2f(m_boundsWidth, m_boundsHeight));
	m_obstacleBounds.setOrigin(m_boundsWidth / 2, (m_boundsHeight / 2));
	m_obstacleBounds.setFillColor(sf::Color(sf::Color(0, 0, 0, 0)));
	m_obstacleBounds.setOutlineColor(sf::Color::Green);
	m_obstacleBounds.setOutlineThickness(1.0f);
	m_obstacleBounds.setPosition(m_obstacleSprite.getPosition());
}

void Obstacle::update(sf::Time deltaTime, sf::RenderWindow& window)
{
	m_obstacleSprite.setPosition(m_obstacleBounds.getPosition());

}

void Obstacle::render(sf::RenderWindow& window)
{
	window.draw(m_obstacleSprite);
	window.draw(m_obstacleBounds);
}

sf::Sprite* Obstacle::getSprite()
{
    return &m_obstacleSprite;
}

sf::RectangleShape* Obstacle::getBounds()
{
    return &m_obstacleBounds;
}
