#include "Label.h"

Label::Label(sf::Font t_font) : m_labelFont(t_font)
{
	initText(t_font);
	m_image = false;
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

void Label::setLabelSprite(std::string t_spriteName)
{
	m_image = true;
	if (!m_labelTexture.loadFromFile("ASSETS\\IMAGES\\" + t_spriteName + ".png"))
	{
		std::cout << "Couldn't load Texture in Label.cpp" << std::endl;
		m_image = false;
	}
	m_labelSprite.setTexture(m_labelTexture);
	m_labelSprite.setOrigin(m_labelSprite.getGlobalBounds().width / 2, m_labelSprite.getGlobalBounds().height / 2);
}

sf::Text Label::getText()
{
	return m_labelText;
}

std::string Label::getTextString()
{
	return m_labelText.getString();
}

void Label::setTextColor(sf::Color t_color)
{
	m_labelText.setFillColor(t_color);
}

void Label::setTextOutlineColor(sf::Color t_color)
{
	m_labelText.setOutlineColor(t_color);
}

void Label::setTextOutlineThickness(float t_thickness)
{
	m_labelText.setOutlineThickness(t_thickness);
}

void Label::setTextSize(float t_size)
{
	m_labelText.setCharacterSize(t_size);
}

void Label::setTextPosition(sf::Vector2f t_pos)
{
	m_labelText.setPosition(t_pos);
}

void Label::setTexturePosition(sf::Vector2f t_pos)
{
	m_labelSprite.setPosition(t_pos);
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
	if (m_image)
	{
		t_window->draw(m_labelSprite);
	}
	t_window->draw(m_labelText);
}