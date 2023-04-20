#include "Item.h"

#include <iostream>

Item::Item()
{
}

Item::Item(std::string t_path)
{
	m_uuid = UUID();
	m_textureManager = new TextureManager();
	m_isCollidable = false;
	m_tag = "Item";
	m_path = t_path;
	m_boundsHeight = 32;
	m_boundsWidth = 32;
	//m_inspector = new Inspector();
	init();
}

Item::Item(std::string t_typeTag, std::string t_path, TextureManager* t_textureManager)
{
	m_uuid = UUID();
	m_textureManager = t_textureManager;
	m_isCollidable = false;
	m_tag = "Item";
	m_path = t_path;
	m_boundsHeight = 32;
	m_boundsWidth = 32;
	//m_inspector = new Inspector();
	init();
}

Item::~Item()
{
}

void Item::init()
{
	setUpSprite();
	setUpBounds();
}

void Item::setUpSprite()
{
	setTexture(m_objectTexture);
	m_objectSprite.setOrigin(16, 16);
	m_objectSprite.setColor(sf::Color::White);
	m_objectSprite.setPosition(100, 100);
}

void Item::setTexture(sf::Texture& t_texture)
{
	m_objectTexture = m_textureManager->getTexture(m_path + ".png");
	//if (!t_texture.loadFromFile(m_path + ".png"))
	//{
	//	std::cout << "Can't load main menu bgt" << std::endl;
	//}
	m_objectSprite.setTexture(m_objectTexture);
}

void Item::setPathToTexture(std::string t_path)
{
	m_path = t_path;
}

void Item::setUpBounds()
{
	m_objectBounds.setSize(sf::Vector2f(m_boundsWidth, m_boundsHeight));
	m_objectBounds.setOrigin(m_boundsWidth / 2, (m_boundsHeight / 2));
	m_objectBounds.setFillColor(sf::Color(sf::Color(0, 0, 0, 0)));
	m_objectBounds.setOutlineColor(sf::Color::Green);
	m_objectBounds.setOutlineThickness(1.0f);
	m_objectBounds.setPosition(m_objectSprite.getPosition());
}

void Item::update(sf::Time deltaTime, sf::RenderWindow& window)
{
	m_objectSprite.setPosition(m_objectBounds.getPosition());

}

void Item::render(sf::RenderWindow& window)
{
	window.draw(m_objectSprite);
	if (m_isSelected)
	{
		//m_inspector->setTextString("Item");
		//m_inspector->render(&window);
	}
}

void Item::renderInspector(sf::RenderWindow& window)
{
	if (m_isSelected)
	{
		//m_inspector->setTextString("Enemy");
		m_inspector->render(&window);
	}
}