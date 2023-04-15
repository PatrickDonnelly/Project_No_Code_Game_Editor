#include "Button.h"
#include <iostream>

Button::Button()
{
	m_hasLabel = false;
	m_selected = false;
	initButton();
}

Button::Button(std::string t_labelText)
{
	m_hasLabel = true;
	m_selected = false;
	m_label = new Label(t_labelText);
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

void Button::resize(float m_xScale, float m_yScale)
{
	m_buttonSprite.setScale(m_xScale, m_yScale);
}

bool Button::getSelected()
{
	return m_selected;
}

void Button::setSelected(bool t_tf)
{
	m_selected = t_tf;
}

bool Button::isEnabled()
{
	return m_enabled;
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

void Button::setColor(sf::Color t_color)
{
	m_buttonSprite.setColor(t_color);
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
	if (m_hasLabel == true)
	{
		m_label->setTextPosition(t_position);
	}
}

void Button::render(sf::RenderWindow* t_window)
{
	t_window->draw(m_buttonSprite);
	if (m_hasLabel == true)
	{
		m_label->render(t_window);
	}
}

bool Button::isButtonClicked(sf::Event& t_event, sf::RenderWindow* t_window)
{
	sf::Vector2f pixelPos = sf::Vector2f(sf::Mouse::getPosition(*t_window).x, sf::Mouse::getPosition(*t_window).y);
	if (m_buttonSprite.getGlobalBounds().contains(pixelPos))
	{
		highlighted();
		if (t_event.type == sf::Event::MouseButtonReleased)
		{
			if (t_event.mouseButton.button == sf::Mouse::Left)
			{
					return true;
			}
		}
	}
	else
	{
		setButtonTexture();
	}
	return false;
}
