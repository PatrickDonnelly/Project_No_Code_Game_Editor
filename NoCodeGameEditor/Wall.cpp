#include "Wall.h"

#include <iostream>

Wall::Wall()
{
}

Wall::Wall(std::string t_typeTag, std::string t_path, TextureManager* t_textureManager)
{
	m_textureManager = t_textureManager;
	m_isCollidable = false;
	m_tag = t_typeTag;
	m_path = t_path;
	m_boundsHeight = 32;
	m_boundsWidth = 32;
	m_inspector = new Inspector();
	init();
}

Wall::~Wall()
{
}

void Wall::init()
{
	setUpSprite();
	setUpBounds();
}

void Wall::setUpSprite()
{
	setTexture(m_objectTexture);
	m_objectSprite.setOrigin(16, 16);
	m_objectSprite.setColor(sf::Color::White);
	m_objectSprite.setPosition(100, 100);
}

void Wall::setTexture(sf::Texture& t_texture)
{
	m_objectTexture = m_textureManager->getTexture(m_path + ".png");
	//if (!t_texture.loadFromFile(m_path + ".png"))
	//{
	//	std::cout << "Can't load main menu bgt" << std::endl;
	//}
	m_objectSprite.setTexture(m_objectTexture);
}

void Wall::setPathToTexture(std::string t_path)
{
	m_path = t_path;
}

void Wall::setUpBounds()
{
	m_objectBounds.setSize(sf::Vector2f(m_boundsWidth, m_boundsHeight));
	m_objectBounds.setOrigin(m_boundsWidth / 2, (m_boundsHeight / 2));
	m_objectBounds.setFillColor(sf::Color(sf::Color(0, 0, 0, 0)));
	m_objectBounds.setOutlineColor(sf::Color::Green);
	m_objectBounds.setOutlineThickness(1.0f);
	m_objectBounds.setPosition(m_objectSprite.getPosition());
}

void Wall::update(sf::Time deltaTime, sf::RenderWindow& window)
{
	m_objectSprite.setPosition(m_objectBounds.getPosition());

}

void Wall::render(sf::RenderWindow& window)
{
	window.draw(m_objectSprite);
	m_inspector->render(&window);
}