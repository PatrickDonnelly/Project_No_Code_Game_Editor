#include "Weapon.h"
#include <iostream>

/// <summary>
/// Overloaded cinstructor
/// </summary>
/// <param name="t_player"></param>
Weapon::Weapon(Player* t_player) : m_player(t_player)
{
	m_frameSize = 16;
	m_weaponBoundsHeight = 32;
	m_weaponBoundsWidth = 10;
	loadAssets();
	init();
	setUpWeaponBounds(m_weaponBoundsWidth, m_weaponBoundsHeight, 0.0f, 0.0f);
	setUpBoundsColour();
}

/// <summary>
/// Deafult constructor
/// </summary>
Weapon::Weapon()
{
}

/// <summary>
/// Deconstructor
/// </summary>
Weapon::~Weapon()
{
}

/// <summary>
/// Initialise the weapon
/// </summary>
void Weapon::init()
{
	m_colliding = false;
	setUpSprite();
}

/// <summary>
/// Loads the texture for the weapon
/// </summary>
void Weapon::loadAssets()
{
	if (!m_weaponTexture.loadFromFile("ASSETS\\IMAGES\\spear_2.png"))
	{
		std::cout << "Can't load main menu bgt" << std::endl;
	}
}

/// <summary>
/// Sets up sprite
/// </summary>
void Weapon::setUpSprite()
{
	m_weaponSprite.setTexture(m_weaponTexture);
	m_weaponSprite.setOrigin(6, 16);
	m_weaponSprite.setScale(1.5f, 1.0f);
}

/// <summary>
/// Sets up the collidable bounds of the weapon
/// </summary>
/// <param name="t_width"></param>
/// <param name="t_height"></param>
/// <param name="t_offsetX"></param>
/// <param name="t_offsetY"></param>
void Weapon::setUpWeaponBounds(float t_width, float t_height, float t_offsetX, float t_offsetY)
{
	m_weaponBounds.setSize(sf::Vector2f(t_width, t_height));
	m_weaponBounds.setOrigin(t_width / 2.0f, (t_height / 2.0f));
	m_weaponBounds.setPosition(m_player->m_playerSprite.getPosition().x + t_offsetX,
								m_player->m_playerSprite.getPosition().y + t_offsetY);
}

/// <summary>
/// sets the colour of the bounding box
/// </summary>
void Weapon::setUpBoundsColour()
{
	m_weaponBounds.setFillColor(sf::Color(sf::Color(255, 0, 0, 50)));
	m_weaponBounds.setOutlineColor(sf::Color::Green);
	m_weaponBounds.setOutlineThickness(1.0f);
}


/// <summary>
/// Processes key presses
/// </summary>
/// <param name="t_event"></param>
void Weapon::processEvents(sf::Event t_event)
{
	if (sf::Event::KeyPressed == t_event.type)
	{
		if (sf::Keyboard::Q == t_event.key.code && m_weaponCanUse == true)
		{
			m_weaponUsed = true;
			m_weaponCanUse = false;
			std::cout << "T" << std::endl;
		}
	}
	if (sf::Event::KeyReleased == t_event.type)
	{
		if (sf::Keyboard::Q == t_event.key.code)
		{
			m_weaponCanUse = true;
			std::cout << "T" << std::endl;
		}
	}
}

/// <summary>
/// Updates weapon
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="window"></param>
void Weapon::update(sf::Time deltaTime, sf::RenderWindow& window)
{
	if (m_weaponUsed)
	{
		weaponCoolDown = m_timer.getElapsedTime().asSeconds();
	}
	if (weaponCoolDown > 0.40f)
	{
		m_weaponUsed = false;
		m_timer.restart();
	}
	if (m_player->moving == true)
	{
		if (m_player->getAnimationState() == AnimationState::WalkingUp
			|| m_player->getAnimationState() == AnimationState::IdleUp)
		{
			m_weaponSprite.setRotation(0);
			setUpWeaponBounds(m_weaponBoundsWidth, m_weaponBoundsHeight, 0.0f, -m_player->m_playerBoundsHeight);
		}
		else if (m_player->getAnimationState() == AnimationState::WalkingDown
			|| m_player->getAnimationState() == AnimationState::IdleDown)
		{
			m_weaponSprite.setRotation(180);
			setUpWeaponBounds(m_weaponBoundsWidth, m_weaponBoundsHeight, 0.0f, m_player->m_playerBoundsHeight);
		}
		else if (m_player->getAnimationState() == AnimationState::WalkingLeft
			|| m_player->getAnimationState() == AnimationState::IdleLeft)
		{
			m_weaponSprite.setRotation(270);
			setUpWeaponBounds(m_weaponBoundsHeight, m_weaponBoundsWidth, -m_player->m_playerBoundsWidth, 0.0f);
		}
		else if (m_player->getAnimationState() == AnimationState::WalkingRight
			|| m_player->getAnimationState() == AnimationState::IdleRight)
		{
			m_weaponSprite.setRotation(90);
			setUpWeaponBounds(m_weaponBoundsHeight, m_weaponBoundsWidth, m_player->m_playerBoundsWidth, 0.0f);
		}
	}
	m_weaponSprite.setPosition(m_weaponBounds.getPosition());
}

/// <summary>
/// renders weapon
/// </summary>
/// <param name="window"></param>
void Weapon::render(sf::RenderWindow& window)
{
	if (m_weaponUsed && weaponCoolDown < 0.30)
	{
		window.draw(m_weaponSprite);
		window.draw(m_weaponBounds);
	}
}

/// <summary>
/// Gets the weapon sprite
/// </summary>
/// <returns></returns>
sf::Sprite* Weapon::getSprite()
{
	return &m_weaponSprite;
}

/// <summary>
/// Get the weapons bounds
/// </summary>
/// <returns></returns>
sf::RectangleShape* Weapon::getWeaponBounds()
{
	return &m_weaponBounds;
}
