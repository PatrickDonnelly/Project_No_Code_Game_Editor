#include "CheckBox.h"
#include <iostream>

CheckBox::CheckBox()
{

}

CheckBox::CheckBox(std::string t_tag)
{
	m_font = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");
	m_checkBoxLabel = new Label(m_font);
	
	m_tag = t_tag;
	m_checkBoxLabel->setText(m_tag);
	initCheckBox();
}

CheckBox::~CheckBox()
{
}

void CheckBox::setCheckBoxPosition(sf::Vector2f t_pos)
{
	m_checkBox.setPosition(t_pos);
	m_checkBoxLabel->setTextPosition(sf::Vector2f(m_checkBox.getPosition().x + (m_checkBoxLabel->getText().getGlobalBounds().width / 2) + m_checkBox.getGlobalBounds().width, m_checkBox.getPosition().y + (m_checkBoxLabel->getText().getGlobalBounds().height / 2)));
}

void CheckBox::toggleColor()
{
	if (m_enabled)
	{
		m_checkBox.setFillColor(sf::Color(0, 125, 0));
	}
	else if (!m_enabled)
	{
		m_checkBox.setFillColor(sf::Color::Black);
	}
}

void CheckBox::update(sf::Time deltaTime, sf::RenderWindow& window)
{

}

void CheckBox::initCheckBox()
{
	m_checkBox.setSize(sf::Vector2f(32.0f, 32.0f));
	m_checkBox.setPosition(1000.0f, 80.0f);
	m_checkBox.setOutlineThickness(2.0f);
	m_checkBox.setOutlineColor(sf::Color::Green);
	m_checkBox.setFillColor(sf::Color::Black);
}

void CheckBox::render(sf::RenderWindow* t_window)
{
	//t_window->draw(m_checkBoxSprite);
	t_window->draw(m_checkBox);
	m_checkBoxLabel->render(t_window);
}

bool CheckBox::isCheckBoxClicked(sf::Event& t_event, sf::RenderWindow* t_window)
{
	sf::Vector2f pixelPos = sf::Vector2f(sf::Mouse::getPosition(*t_window).x, sf::Mouse::getPosition(*t_window).y);

	if (m_checkBox.getGlobalBounds().contains(pixelPos))
	{
		if (t_event.type == sf::Event::MouseButtonReleased)
		{
			if (t_event.mouseButton.button == sf::Mouse::Left)
			{
				setEnabled();
				return true;
			}
		}
	}
	return false;
}
