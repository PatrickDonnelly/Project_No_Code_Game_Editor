#include "Player.h"
#include <iostream>

Player::Player()
{
	m_frameSize = 16;
	m_defaultSpeed = 2.0f;
	m_speed = 2.0f;
	m_playerBoundsHeight = 8;
	m_playerBoundsWidth = 16;
	m_spriteSheetName = "MyDude.png";
	loadAssets();
	init();
	setUpPlayerBounds();
	setUpAnimation();
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

void Player::setUpAnimation()
{
	animations[int(AnimationState::IdleDown)] = Animator(0, 0, m_frameSize, m_frameSize, m_spriteSheetName,1);
	animations[int(AnimationState::IdleUp)] = Animator(48, 0, m_frameSize, m_frameSize, m_spriteSheetName, 1);
	animations[int(AnimationState::IdleLeft)] = Animator(16, 0, m_frameSize, m_frameSize, m_spriteSheetName, 1);
	animations[int(AnimationState::IdleRight)] = Animator(32, 0, m_frameSize, m_frameSize, m_spriteSheetName, 1);
	animations[int(AnimationState::WalkingDown)] = Animator(0, 0, m_frameSize, m_frameSize, m_spriteSheetName, 3);
	animations[int(AnimationState::WalkingUp)] = Animator(48, 0, m_frameSize, m_frameSize, m_spriteSheetName, 3);
	animations[int(AnimationState::WalkingLeft)] = Animator(16, 0, m_frameSize, m_frameSize, m_spriteSheetName, 3);
	animations[int(AnimationState::WalkingRight)] = Animator(32, 0, m_frameSize, m_frameSize, m_spriteSheetName, 3);
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

bool Player::movement(sf::Time deltaTime)
{
	moving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_playerBounds.move(0, -m_speed);
		setAnimationState(currentAnimationState, AnimationState::WalkingUp);
		moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_playerBounds.move(0, m_speed);
		setAnimationState(currentAnimationState, AnimationState::WalkingDown);
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
			m_playerBounds.move(-m_speed, 0);
			setAnimationState(currentAnimationState, AnimationState::WalkingLeft);
			moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
			m_playerBounds.move(m_speed, 0);
			setAnimationState(currentAnimationState, AnimationState::WalkingRight);
			moving = true;
	}
	return moving;;
}


void Player::update(sf::Time deltaTime, sf::RenderWindow& window)
{
	if (!movement(deltaTime))
	{
		if (currentAnimationState == AnimationState::WalkingLeft)
		{
			setAnimationState(currentAnimationState, AnimationState::IdleLeft);
		}
		else if (currentAnimationState == AnimationState::WalkingRight)
		{
			setAnimationState(currentAnimationState, AnimationState::IdleRight);
		}
		else if (currentAnimationState == AnimationState::WalkingUp)
		{
			setAnimationState(currentAnimationState, AnimationState::IdleUp);
		}
		else if (currentAnimationState == AnimationState::WalkingDown)
		{
			setAnimationState(currentAnimationState, AnimationState::IdleDown);
		}
	}
	animate(deltaTime);
	m_playerSprite.setPosition(m_playerBounds.getPosition().x, m_playerBounds.getPosition().y - 10);
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

AnimationState Player::getAnimationState()
{
	return currentAnimationState;
}

void Player::setAnimationState(AnimationState& t_current, AnimationState t_new)
{
	if (t_current != t_new)
	{
		t_current = t_new;
	}
}

void Player::animate(sf::Time deltaTime)
{
	animations[int(currentAnimationState)].Update(deltaTime.asSeconds());
	animations[int(currentAnimationState)].ApplyChangesToSprite(m_playerSprite);
}
