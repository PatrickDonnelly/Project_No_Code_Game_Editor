#include "Player.h"
#include <iostream>

Player::Player()
{
	m_frameSize = 16;
	m_speed = 2.0f;
	m_playerBoundsHeight = 28;
	m_playerBoundsWidth = 16;
	m_spriteSheetName = "MyDude.png";
	loadAssets();
	init();
	setUpPlayerBounds();
}

Player::~Player()
{
}

void Player::init()
{
	m_colliding = false;
	setUpSprite();
}
void Player::loadAssets()
{
	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\" + m_spriteSheetName))
	{
		std::cout << "Can't load main menu bgt" << std::endl;
	}
}


void Player::setUpPlayerBounds()
{
	int offset = 0;
	m_playerBounds.setSize(sf::Vector2f(m_playerBoundsWidth, m_playerBoundsHeight));
	m_playerBounds.setOrigin(m_playerBoundsWidth / 2, (m_playerBoundsHeight / 2));
	m_playerBounds.setFillColor(sf::Color(sf::Color(0,0,0,0)));
	m_playerBounds.setOutlineColor(sf::Color::Green);
	m_playerBounds.setOutlineThickness(1.0f);
	m_playerBounds.setPosition(m_playerSprite.getPosition());

	m_playerCentre.setSize(sf::Vector2f(2.0f, 2.0f));
	m_playerCentre.setOrigin(1.0f, 1.0f);
	m_playerCentre.setFillColor(sf::Color::Cyan);
	m_playerCentre.setPosition(m_playerSprite.getPosition());
}

void Player::setUpSprite()
{

	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setTextureRect(m_rectSourceSprite);
	m_playerSprite.setOrigin(m_frameSize / 2, m_frameSize / 2);
	m_playerSprite.setScale(sf::Vector2f(2.0f,2.0f));
	m_playerSprite.setColor(sf::Color::White);
	m_playerSprite.setPosition(100,100);
}

void Player::movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
			m_playerSprite.move(0, -m_speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
			m_playerSprite.move(0, m_speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
			m_playerSprite.move(-m_speed, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
			m_playerSprite.move(m_speed, 0);
	}
	m_playerBounds.setPosition(m_playerSprite.getPosition());
}


void Player::update(sf::Time deltaTime, sf::RenderWindow& window)
{

	movement();
	m_playerCentre.setPosition(m_playerSprite.getPosition());
}

void Player::render(sf::RenderWindow& window)
{
	window.draw(m_playerSprite);
	window.draw(m_playerBounds);
	window.draw(m_playerCentre);
}

sf::Sprite* Player::getSprite()
{
	return &m_playerSprite;
}

sf::RectangleShape* Player::getBounds()
{
	return &m_playerBounds;
}