#include "Button.h"
#include <iostream>

/// <summary>
/// Constructor
/// </summary>
Button::Button()
{
	m_hasLabel = false;
	m_selected = false;
	initButton();
}

/// <summary>
/// Overloaded constructor. button with label
/// </summary>
/// <param name="t_labelText"></param>
Button::Button(std::string t_labelText)
{
	m_hasLabel = true;
	m_selected = false;
	m_label = new Label(t_labelText);
	initButton();
}

/// <summary>
/// Deconstructor
/// </summary>
Button::~Button()
{

}

/// <summary>
/// Sets up button texture and origin
/// </summary>
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

/// <summary>
/// Resizes the button based on a given scale parametres
/// </summary>
/// <param name="m_xScale"></param>
/// <param name="m_yScale"></param>
void Button::resize(float m_xScale, float m_yScale)
{
	m_buttonSprite.setScale(m_xScale, m_yScale);
}

/// <summary>
/// Checks if a button is selected
/// </summary>
/// <returns></returns>
bool Button::getSelected()
{
	return m_selected;
}

/// <summary>
/// toggle selected between true or false
/// </summary>
/// <param name="t_tf"></param>
void Button::setSelected(bool t_tf)
{
	m_selected = t_tf;
}

/// <summary>
/// returns true if button is enabled
/// </summary>
/// <returns></returns>
bool Button::isEnabled()
{
	return m_enabled;
}

/// <summary>
/// Sets the sprite of the button
/// </summary>
/// <param name="t_buttonSprite"></param>
void Button::setButtonSprite(sf::Sprite t_buttonSprite)
{
	m_buttonSprite = t_buttonSprite;
}

/// <summary>
/// Sets the button texture
/// </summary>
void Button::setButtonTexture()
{
	m_buttonSprite.setTexture(m_buttonTexture);
}

/// <summary>
/// Changes the texture of the button if it is highlighted
/// </summary>
void Button::highlighted()
{
	m_buttonSprite.setTexture(m_buttonHighlightTexture);
}

/// <summary>
/// Sets the colour of a button
/// </summary>
/// <param name="t_color"></param>
void Button::setColor(sf::Color t_color)
{
	m_buttonSprite.setColor(t_color);
}

/// <summary>
/// Returns the button sprite
/// </summary>
/// <returns></returns>
sf::Sprite Button::getButtonSprite()
{
	return m_buttonSprite;
}

/// <summary>
/// Returns the Button Position
/// </summary>
/// <returns></returns>
sf::Vector2f Button::getButtonPosition()
{
	return m_buttonSprite.getPosition();
}

/// <summary>
/// Sets the Button Position
/// </summary>
/// <param name="t_position"></param>
void Button::setButtonPosition(sf::Vector2f t_position)
{
	m_buttonSprite.setPosition(t_position);
	if (m_hasLabel == true)
	{
		m_label->setTextPosition(t_position);
	}
}

/// <summary>
/// Renders the button and a label if it has one
/// </summary>
/// <param name="t_window"></param>
void Button::render(sf::RenderWindow* t_window)
{
	t_window->draw(m_buttonSprite);
	if (m_hasLabel == true)
	{
		m_label->render(t_window);
	}
}

/// <summary>
/// Checks if a button has been clicked
/// </summary>
/// <param name="t_event"></param>
/// <param name="t_window"></param>
/// <returns></returns>
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
