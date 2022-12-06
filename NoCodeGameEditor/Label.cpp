#include "Label.h"

Label::Label(sf::Font t_font) : m_labelFont(t_font)
{
	initText(t_font);
}

Label::Label()
{

}

Label::~Label()
{

}

void Label::initText(sf::Font t_font)
{
	m_labelText.setString(" ");
	m_labelFont = t_font;
	m_labelText.setFont(m_labelFont);
	m_labelText.setCharacterSize(24U);
	m_labelText.setFillColor(sf::Color::Black);
	//m_labelText.setOutlineThickness(1.0f);
	//m_labelText.setOutlineColor(sf::Color::Red);
}

void Label::setText(std::string t_text)
{
	m_labelText.setString(t_text);
	m_labelText.setOrigin(m_labelText.getGlobalBounds().width / 2,m_labelText.getGlobalBounds().height/2);
}

sf::Text Label::getText()
{
	return m_labelText;
}

std::string Label::getTextString()
{
	return m_labelText.getString();
}

void Label::setTextPosition(sf::Vector2f t_pos)
{
	m_labelText.setPosition(t_pos);
}

sf::Vector2f Label::getTextPosition()
{
	return m_labelText.getPosition();
}

void Label::clear()
{
	m_labelText.setString("");
}

void Label::render(sf::RenderWindow* t_window)
{
	t_window->draw(m_labelText);
}