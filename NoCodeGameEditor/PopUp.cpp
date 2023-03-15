#include "PopUp.h"
#include <iostream>

PopUp::PopUp()
{

}

PopUp::PopUp(sf::Font* t_font)
{
	m_font = t_font;
	initPopUpBox();
	initText();
}

void PopUp::initText()
{
	m_text.setFont(*m_font);
	m_text.setCharacterSize(20.0f);
	m_text.setFillColor(sf::Color::Black);
	m_text.setPosition(m_popUpBox.getPosition().x, m_popUpBox.getPosition().y);
	m_text.setString(" ");
}

void PopUp::setPopUpBoxText(std::string t_text) 
{ 
	m_text.setString(t_text); 
	m_text.setPosition(m_popUpBox.getPosition().x + (m_popUpBox.getGlobalBounds().width / 2) - (m_text.getLocalBounds().width / 2), m_popUpBox.getPosition().y);
}

sf::Vector2f PopUp::getPopUpBoxBounds()
{
	return sf::Vector2f(m_popUpBox.getGlobalBounds().width, m_popUpBox.getGlobalBounds().height);
}

PopUp::~PopUp()
{

}

sf::Sprite PopUp::getPopUpBoxSprite()
{
	return sf::Sprite();
}



sf::Vector2f PopUp::getPopUpBoxPosition()
{
	return m_popUpBox.getPosition();
}

void PopUp::initPopUpBox()
{
	m_popUpBox.setSize(sf::Vector2f(800.0f, 400.0f));
	m_popUpBox.setPosition(560.0f, 340.0f);
	m_popUpBox.setOutlineThickness(2.0f);
	m_popUpBox.setOutlineColor(sf::Color(sf::Color(100,100,100)));
	m_popUpBox.setFillColor(sf::Color(sf::Color(255, 200, 200)));

	//if (!m_popUpBoxTexture.loadFromFile("ASSETS\\IMAGES\\buttonGrey.png"))
	//{
	//	std::cout << "error" << std::endl;
	//}

	m_popUpBoxSprite.setTexture(m_popUpBoxTexture);
	m_popUpBoxSprite.setOrigin(m_popUpBoxSprite.getGlobalBounds().width / 2, m_popUpBoxSprite.getGlobalBounds().height / 2);
}

void PopUp::setPopUpBoxSprite(sf::Sprite t_dialogueSprite)
{
	m_popUpBoxSprite = t_dialogueSprite;
}



void PopUp::render(sf::RenderWindow* t_window)
{
	//t_window->draw(m_dialogueBoxSprite);
	if(m_enabled)
	{
		t_window->draw(m_popUpBox);
		t_window->draw(m_text);
	}
}

bool PopUp::isEnabled()
{
	return m_enabled;
}