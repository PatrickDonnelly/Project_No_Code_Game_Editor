#include "CheckBox.h"
#include <iostream>

CheckBox::CheckBox()
{

}

CheckBox::CheckBox(sf::Font& t_font)
{
	m_font = t_font;
	m_checkBoxLabel = new Label(t_font);

	initCheckBox();
	initText();


}

void CheckBox::initText()
{
	m_text.setFont(m_font);
	m_text.setCharacterSize(20.0f);
	m_text.setFillColor(sf::Color::Black);
	m_text.setOutlineColor(sf::Color::White);
	m_text.setOutlineThickness(2.0f);
	m_text.setPosition(10.0f, 10.0f);
	m_checkBoxLabel->setText("Preview Dialogue");
	m_checkBoxLabel->setTextPosition(sf::Vector2f(m_checkBox.getPosition().x + (m_checkBoxLabel->getText().getGlobalBounds().width /2) + m_checkBox.getGlobalBounds().width, m_checkBox.getPosition().y + (m_checkBoxLabel->getText().getGlobalBounds().height / 2)));
}

CheckBox::~CheckBox()
{

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

	//if (!m_checkBoxTexture.loadFromFile("ASSETS\\IMAGES\\buttonGrey.png"))
	//{
	//	std::cout << "error" << std::endl;
	//}

	//m_checkBoxSprite.setTexture(m_checkBoxTexture);
	//m_checkBoxSprite.setOrigin(m_checkBoxSprite.getGlobalBounds().width / 2, m_checkBoxSprite.getGlobalBounds().height / 2);
}

void CheckBox::render(sf::RenderWindow* t_window)
{
	//t_window->draw(m_checkBoxSprite);

	t_window->draw(m_checkBox);
	t_window->draw(m_text);
	m_checkBoxLabel->render(t_window);
}
