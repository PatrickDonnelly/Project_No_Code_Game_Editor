#include "Button.h"
#include <iostream>

Button::Button()
{
	initButton();
}

Button::~Button()
{

}

void Button::initButton()
{
	if (!m_buttonTexture.loadFromFile("ASSETS\\IMAGES\\buttonGrey.png"))
	{
		std::cout << "error" << std::endl;
	}

	if (!m_buttonHighlightTexture.loadFromFile("ASSETS\\IMAGES\\button.png"))
	{
		std::cout << "error" << std::endl;
	}

	m_buttonSprite.setTexture(m_buttonTexture);
	m_buttonSprite.setOrigin(m_buttonSprite.getGlobalBounds().width / 2, m_buttonSprite.getGlobalBounds().height / 2);
}

void Button::setButtonSprite(sf::Sprite t_buttonSprite)
{
	m_buttonSprite = t_buttonSprite;
}

void Button::setButtonTexture()
{
	m_buttonSprite.setTexture(m_buttonTexture);
}

void Button::highlighted()
{
	m_buttonSprite.setTexture(m_buttonHighlightTexture);
}

sf::Sprite Button::getButtonSprite()
{
	return m_buttonSprite;
}

sf::Vector2f Button::getButtonPosition()
{
	return m_buttonSprite.getPosition();
}

void Button::setButtonPosition(sf::Vector2f t_position)
{
	m_buttonSprite.setPosition(t_position);
}
