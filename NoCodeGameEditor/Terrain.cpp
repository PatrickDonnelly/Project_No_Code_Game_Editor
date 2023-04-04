#include "Terrain.h"
#include <iostream>


Terrain::Terrain()
{
}

Terrain::Terrain(std::string t_typeTag, std::string t_path, TextureManager* t_textureManager)
{
	m_textureManager = t_textureManager;
	m_isCollidable = false;
	m_tag = "Terrain";
	m_path = t_path;
	m_boundsHeight = 32;
	m_boundsWidth = 32;
	//m_inspector = new Inspector();
	init();
}

Terrain::~Terrain()
{
}

void Terrain::init()
{
	setUpSprite();
	setUpBounds();
}

void Terrain::setUpSprite()
{
	setTexture(m_objectTexture);
	m_objectSprite.setOrigin(16, 16);
	m_objectSprite.setColor(sf::Color::White);
	m_objectSprite.setPosition(100, 100);
}

void Terrain::setTexture(sf::Texture& t_texture)
{
	m_objectTexture = m_textureManager->getTexture(m_path + ".png");
	//if (!t_texture.loadFromFile(m_path + ".png"))
	//{
	//	std::cout << "Can't load main menu bgt" << std::endl;
	//}
	m_objectSprite.setTexture(m_objectTexture);
}

void Terrain::setPathToTexture(std::string t_path)
{
	m_path = t_path;
}

void Terrain::setUpBounds()
{
	m_objectBounds.setSize(sf::Vector2f(m_boundsWidth, m_boundsHeight));
	m_objectBounds.setOrigin(m_boundsWidth / 2, (m_boundsHeight / 2));
	m_objectBounds.setFillColor(sf::Color(sf::Color(0, 0, 0, 0)));
	m_objectBounds.setOutlineColor(sf::Color::Green);
	m_objectBounds.setOutlineThickness(1.0f);
	m_objectBounds.setPosition(m_objectSprite.getPosition());
}

void Terrain::update(sf::Time deltaTime, sf::RenderWindow& window)
{
	m_objectSprite.setPosition(m_objectBounds.getPosition());
}

void Terrain::render(sf::RenderWindow& window)
{
	window.draw(m_objectSprite);
	if (m_isSelected)
	{
		//m_inspector->setTextString("Terrain");
		//m_inspector->render(&window);
	}
}