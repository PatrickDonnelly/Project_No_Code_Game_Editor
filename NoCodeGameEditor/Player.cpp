#include "Player.h"
#include <iostream>

/// <summary>
/// Default constructor for the player object
/// </summary>
Player::Player()
{
	m_frameSize = 16;
	m_defaultSpeed = 2.0f;
	m_speed = 2.0f;
	m_playerBoundsHeight = 8;
	m_playerBoundsWidth = 16;
	m_spriteSheetName = "MyDude.png";
	m_defaultPos = sf::Vector2f(352.0f, 960.0f);
	loadAssets();
	init();
	setUpPlayerBounds();
	setUpAnimation();
}

/// <summary>
/// Deconstructor for the player object
/// </summary>
Player::~Player()
{
}

/// <summary>
/// Initialise the player object
/// </summary>
void Player::init()
{
	m_colliding = false;
	setUpSprite();
}

/// <summary>
/// load the player objects texture
/// </summary>
void Player::loadAssets()
{
	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\" + m_spriteSheetName))
	{
		std::cout << "Can't load main menu bgt" << std::endl;
	}
}

/// <summary>
/// Set up the colliding bounds
/// interaction bounds
/// and centre point of the player
/// </summary>
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

	m_playerInteractionRadius.setSize(sf::Vector2f(16.0f, 16.0f));
	m_playerInteractionRadius.setOrigin(8.0f, 8.0f);
	m_playerInteractionRadius.setFillColor(sf::Color(sf::Color(0, 255, 0, 125)));
	m_playerInteractionRadius.setOutlineColor(sf::Color::Green);
	m_playerInteractionRadius.setOutlineThickness(1.0f);
	m_playerInteractionRadius.setPosition(m_playerSprite.getPosition().x - 16.0f, m_playerSprite.getPosition().y);
}

/// <summary>
/// Set up the players animation
/// </summary>
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

/// <summary>
/// Set up the players sprite
/// </summary>
void Player::setUpSprite()
{
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setTextureRect(m_rectSourceSprite);
	m_playerSprite.setOrigin(m_frameSize / 2, m_frameSize / 2);
	m_playerSprite.setScale(sf::Vector2f(2.0f,2.0f));
	m_playerSprite.setColor(sf::Color::White);
	m_playerSprite.setPosition(m_defaultPos);
}

/// <summary>
/// Process player movement
/// </summary>
/// <param name="deltaTime"></param>
/// <returns></returns>
bool Player::movement(sf::Time deltaTime)
{
	moving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_playerBounds.move(0, -m_speed);
		setAnimationState(currentAnimationState, AnimationState::WalkingUp);
		m_playerInteractionRadius.setPosition(m_playerSprite.getPosition().x, m_playerSprite.getPosition().y -16);
		moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_playerBounds.move(0, m_speed);
		setAnimationState(currentAnimationState, AnimationState::WalkingDown);
		m_playerInteractionRadius.setPosition(m_playerSprite.getPosition().x, m_playerSprite.getPosition().y +16);

		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
			m_playerBounds.move(-m_speed, 0);
			setAnimationState(currentAnimationState, AnimationState::WalkingLeft);
			m_playerInteractionRadius.setPosition(m_playerSprite.getPosition().x - 16.0f, m_playerSprite.getPosition().y);
			moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
			m_playerBounds.move(m_speed, 0);
			setAnimationState(currentAnimationState, AnimationState::WalkingRight);
			m_playerInteractionRadius.setPosition(m_playerSprite.getPosition().x + 16.0f, m_playerSprite.getPosition().y);
			moving = true;
	}
	return moving;;
}


/// <summary>
/// Update player
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="window"></param>
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

/// <summary>
/// render player and bounds if enabled
/// </summary>
/// <param name="window"></param>
void Player::render(sf::RenderWindow& window)
{
	window.draw(m_playerSprite);
	if (m_collidersEnabled)
	{
		window.draw(m_playerBounds);
		window.draw(m_playerCentre);
		window.draw(m_playerInteractionRadius);
	}
}

/// <summary>
/// gets the player sprite
/// </summary>
/// <returns></returns>
sf::Sprite* Player::getSprite()
{
	return &m_playerSprite;
}

/// <summary>
/// Gets the player bounds
/// </summary>
/// <returns></returns>
sf::RectangleShape* Player::getBounds()
{
	return &m_playerBounds;
}

/// <summary>
/// Gets the animation state of the player
/// </summary>
/// <returns></returns>
AnimationState Player::getAnimationState()
{
	return currentAnimationState;
}

/// <summary>
/// Sets the animation state of the player
/// </summary>
/// <param name="t_current"></param>
/// <param name="t_new"></param>
void Player::setAnimationState(AnimationState& t_current, AnimationState t_new)
{
	if (t_current != t_new)
	{
		t_current = t_new;
	}
}

/// <summary>
/// Animates the player
/// </summary>
/// <param name="deltaTime"></param>
void Player::animate(sf::Time deltaTime)
{
	animations[int(currentAnimationState)].Update(deltaTime.asSeconds());
	animations[int(currentAnimationState)].ApplyChangesToSprite(m_playerSprite);
}

/// <summary>
/// Checks if the player is interacting with an object or not
/// </summary>
/// <param name="t_event"></param>
/// <returns></returns>
bool Player::isInteracting(sf::Event t_event)
{

	if (t_event.type == sf::Event::KeyReleased)
	{
		if (t_event.key.code == sf::Keyboard::Space)
		{
 			return true;
		}
	}
	
	return false;
}

/// <summary>
/// Returns the players interaction bounds
/// </summary>
/// <returns></returns>
sf::RectangleShape* Player::getInteractionBounds()
{
	return &m_playerInteractionRadius;
}
