#include "Enemy.h"

#include <iostream>

Enemy::Enemy()
{
}

Enemy::Enemy(std::string t_typeTag, std::string t_path)
{
	m_isCollidable = false;
	m_tag = t_typeTag;
	m_tempPath = t_path;
	m_boundsHeight = 32;
	m_boundsWidth = 32;
	setUpSprite();
	setUpEnemyBounds();
	//m_inspector = new Inspector();

}

Enemy::~Enemy()
{
}

bool Enemy::isCollidable()
{
	return m_isCollidable;
}

void Enemy::init()
{
}

void Enemy::setUpSprite()
{
	setEnemyTexture(m_enemyTexture);
	m_enemySprite.setOrigin(16, 16);
	m_enemySprite.setColor(sf::Color::White);
	m_enemySprite.setPosition(100, 100);
}

void Enemy::setEnemyTexture(sf::Texture& t_texture)
{
	if (!t_texture.loadFromFile(m_tempPath + ".png"))
	{
		std::cout << "Can't load main menu bgt" << std::endl;
	}
	m_enemySprite.setTexture(t_texture);
}

void Enemy::setUpEnemyBounds()
{
	m_enemyBounds.setSize(sf::Vector2f(m_boundsWidth, m_boundsHeight));
	m_enemyBounds.setOrigin(m_boundsWidth / 2, (m_boundsHeight / 2));
	m_enemyBounds.setFillColor(sf::Color(sf::Color(0, 0, 0, 0)));
	m_enemyBounds.setOutlineColor(sf::Color::Green);
	m_enemyBounds.setOutlineThickness(1.0f);
	m_enemyBounds.setPosition(m_enemySprite.getPosition());
}

void Enemy::update(sf::Time deltaTime, sf::RenderWindow& window)
{
	m_enemySprite.setPosition(m_enemyBounds.getPosition());

}

void Enemy::render(sf::RenderWindow& window)
{
	window.draw(m_enemySprite);
	if (m_boundsOn)
	{
		window.draw(m_enemyBounds);
	}

	//m_inspector->render(&window);
}

sf::Sprite* Enemy::getEnemySprite()
{
	return &m_enemySprite;
}

sf::RectangleShape* Enemy::getEnemyBounds()
{
	return &m_enemyBounds;
}

void Enemy::setRowColumn(int t_row, int t_col)
{
	m_row = t_row;
	m_col = t_col;
}

int Enemy::getRow()
{
	return m_row;
}

int Enemy::getColumn()
{
	return m_col;
}