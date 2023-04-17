#include "Colliders.h"

Colliders::Colliders()
{
	m_data = ColliderData();
	m_data.m_height = 32;
	m_data.m_width = 32;
	m_width = 32;
	m_data.m_tag = "Collider";
	m_isVisible = true;
	init();
}

Colliders::~Colliders()
{

}

void Colliders::init()
{
	m_colliderBounds.setSize(sf::Vector2f(m_data.m_width, m_data.m_height));
	m_colliderBounds.setOrigin(sf::Vector2f(m_data.m_width/2, m_data.m_height/2));
	m_colliderBounds.setFillColor(sf::Color(sf::Color(0, 0, 0, 0)));
	m_colliderBounds.setOutlineColor(sf::Color::Green);
	m_colliderBounds.setOutlineThickness(2.0f);
}

void Colliders::setUpSprite()
{
}

void Colliders::setObjectCategory(std::string t_ObjectCategory)
{
}

std::string Colliders::getObjectCategory()
{
	return std::string();
}

void Colliders::setTexture(sf::Texture& t_texture)
{
}

void Colliders::setPathToTexture(std::string t_path)
{
}

void Colliders::setUpBounds()
{
}

void Colliders::update(sf::Time deltaTime, sf::RenderWindow& window)
{
}

void Colliders::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_colliderBounds);
}


void Colliders::increaseHeight()
{

	m_data.m_height += 1.0f;
	m_colliderBounds.setSize(sf::Vector2f(m_data.m_width, m_data.m_height));
	m_colliderBounds.setOrigin(sf::Vector2f(m_data.m_width / 2, m_data.m_height / 2));
}

void Colliders::increaseWidth()
{
	std::cout << "Before : " << m_width << std::endl;
	m_width += m_width;
	std::cout << m_width << std::endl;

	m_data.m_width += 1.0f;
	m_colliderBounds.setSize(sf::Vector2f(m_data.m_width, m_data.m_height));
	m_colliderBounds.setOrigin(sf::Vector2f(m_data.m_width / 2, m_data.m_height / 2));
}

void Colliders::decreaseHeight()
{
	m_data.m_height -= 1.0f;
	m_colliderBounds.setSize(sf::Vector2f(m_data.m_width, m_data.m_height));
	m_colliderBounds.setOrigin(sf::Vector2f(m_data.m_width / 2, m_data.m_height / 2));
}

void Colliders::decreaseWidth()
{
	m_width -= m_width;
	std::cout << m_width << std::endl;
	m_data.m_width -= 1.0f;
	m_colliderBounds.setSize(sf::Vector2f(m_data.m_width, m_data.m_height));
	m_colliderBounds.setOrigin(sf::Vector2f(m_data.m_width / 2, m_data.m_height / 2));
}
