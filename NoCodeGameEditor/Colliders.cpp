#include "Colliders.h"

Colliders::Colliders()
{
	init();
}

Colliders::~Colliders()
{

}

void Colliders::init()
{
	m_wallColliderBounds.setSize(sf::Vector2f(32.0f,32.0f));
	m_wallColliderBounds.setFillColor(sf::Color(sf::Color(255, 0, 0, 50)));
	m_wallColliderBounds.setOutlineColor(sf::Color::Red);
	m_wallColliderBounds.setOutlineThickness(2.0f);
	m_wallColliderBounds.setPosition(704,285);
	m_wallCentre.setSize(sf::Vector2f(2.0f, 2.0f));
	m_wallCentre.setFillColor(sf::Color::Cyan);
	m_wallCentre.setOrigin(1.0f,1.0f);
	m_wallCentre.setPosition(400.0f,200.0f);
	m_wallBoundsWidth = 32;
	m_wallBoundsHeight = 32;

}

void Colliders::setUpHorizontalWallBounds(float m_startPos, float m_endPos)
{
	// horizontal
	float l_size = m_endPos - m_startPos;
	m_wallColliderBounds.setSize(sf::Vector2f(l_size, 32.0f));
}

void Colliders::setUpVerticalWallBounds(float m_startPos, float m_endPos)
{
	// horizontal
	float l_size = m_endPos - m_startPos;
	m_wallColliderBounds.setSize(sf::Vector2f(32.0f, l_size));
}

void Colliders::render(sf::RenderWindow* t_window)
{
	t_window->draw(m_wallColliderBounds);
	t_window->draw(m_wallCentre);
}

sf::RectangleShape* Colliders::getBounds()
{
	return nullptr;
}
