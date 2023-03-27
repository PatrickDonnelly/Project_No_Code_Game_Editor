#include "Enemy.h"

#include <iostream>

Enemy::Enemy()
{
}

Enemy::Enemy(std::string t_typeTag, std::string t_path, TextureManager* t_textureManager)
{
	m_textureManager = t_textureManager;
	m_isCollidable = false;
	m_tag = t_typeTag;
	m_path = t_path;
	m_boundsHeight = 32;
	m_boundsWidth = 32;
	m_inspector = new Inspector("Enemy");
	init();
}

Enemy::~Enemy()
{
}

void Enemy::init()
{
	setUpSprite();
	setUpBounds();
}

void Enemy::setUpSprite()
{
	setTexture(m_objectTexture);
	m_objectSprite.setOrigin(16, 16);
	m_objectSprite.setColor(sf::Color::White);
	m_objectSprite.setPosition(100, 100);
}

void Enemy::setTexture(sf::Texture& t_texture)
{
	m_objectTexture = m_textureManager->getTexture(m_path + ".png");
	//if (!t_texture.loadFromFile(m_path + ".png"))
	//{
	//	std::cout << "Can't load main menu bgt" << std::endl;
	//}
	m_objectSprite.setTexture(m_objectTexture);
}

void Enemy::setPathToTexture(std::string t_path)
{
	m_path = t_path;
}

void Enemy::setUpBounds()
{
	m_objectBounds.setSize(sf::Vector2f(m_boundsWidth, m_boundsHeight));
	m_objectBounds.setOrigin(m_boundsWidth / 2, (m_boundsHeight / 2));
	m_objectBounds.setFillColor(sf::Color(sf::Color(0, 0, 0, 0)));
	m_objectBounds.setOutlineColor(sf::Color::Green);
	m_objectBounds.setOutlineThickness(1.0f);
	m_objectBounds.setPosition(m_objectSprite.getPosition());
}

void Enemy::update(sf::Time deltaTime, sf::RenderWindow& window)
{
	m_objectSprite.setPosition(m_objectBounds.getPosition());
	if (m_isSelected)
	{
		//count++;
		//std::string temp = std::to_string(count);
		//m_inspector->setTextString(temp);
	}
}

void Enemy::render(sf::RenderWindow& window)
{
	window.draw(m_objectSprite);
	if(m_isSelected)
	{
		//m_inspector->setTextString("Enemy");
		m_inspector->render(&window);
	}
}