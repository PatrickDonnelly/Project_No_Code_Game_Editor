#include "Decoration.h"

#include <iostream>

Decoration::Decoration()
{
}

Decoration::Decoration(std::string t_typeTag, std::string t_path, TextureManager* t_textureManager)
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

Decoration::~Decoration()
{
}

void Decoration::init()
{
	setUpSprite();
	setUpBounds();
}

void Decoration::setUpSprite()
{
	setTexture(m_objectTexture);
	m_objectSprite.setOrigin(16, 16);
	m_objectSprite.setColor(sf::Color::White);
	m_objectSprite.setPosition(100, 100);
}

void Decoration::setTexture(sf::Texture& t_texture)
{
	m_objectTexture = m_textureManager->getTexture(m_path + ".png");
	//if (!t_texture.loadFromFile(m_path + ".png"))
	//{
	//	std::cout << "Can't load main menu bgt" << std::endl;
	//}
	m_objectSprite.setTexture(m_objectTexture);
}

void Decoration::setPathToTexture(std::string t_path)
{
	m_path = t_path;
}

void Decoration::setUpBounds()
{
	m_objectBounds.setSize(sf::Vector2f(m_boundsWidth, m_boundsHeight));
	m_objectBounds.setOrigin(m_boundsWidth / 2, (m_boundsHeight / 2));
	m_objectBounds.setFillColor(sf::Color(sf::Color(0, 0, 0, 0)));
	m_objectBounds.setOutlineColor(sf::Color::Green);
	m_objectBounds.setOutlineThickness(1.0f);
	m_objectBounds.setPosition(m_objectSprite.getPosition());
}

void Decoration::update(sf::Time deltaTime, sf::RenderWindow& window)
{
	m_objectSprite.setPosition(m_objectBounds.getPosition());

}

void Decoration::render(sf::RenderWindow& window)
{
	window.draw(m_objectSprite);
	if (m_isSelected)
	{
		m_inspector->setTextString("Decoration");
		m_inspector->render(&window);
	}
}