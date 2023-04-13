#include "Label.h"

Label::Label(sf::Font& t_font)
{
	m_fontManager = FontManager();
	m_labelFont = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");

	initText();
	m_image = false;
}

Label::Label(std::string t_labelText)
{
	m_fontManager = FontManager();
	m_labelFont = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");

	initText();
	setText(t_labelText);
	m_image = false;
}

Label::Label(sf::Font& t_font, bool t_isOn)
{
	m_fontManager = FontManager();
	m_labelFont = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");
	m_hasBG = t_isOn;

	initText();
	m_image = false;
	setUpBG();
}

Label::Label()
{
	m_fontManager = FontManager();
	m_labelFont = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");
	initText();
	m_image = false;
}

Label::~Label()
{

}

void Label::setUpBG()
{
	if (m_hasBG)
	{
		m_labelBG.setSize(sf::Vector2f(m_labelText.getGlobalBounds().width + 5, m_labelText.getGlobalBounds().height + 5));
		m_labelBG.setOrigin(m_labelBG.getGlobalBounds().width / 2, m_labelBG.getGlobalBounds().height / 2);
		m_labelBG.setPosition(m_labelText.getPosition());
		m_labelBG.setFillColor(sf::Color::White);
		m_labelBG.setOutlineThickness(-1.0f);
		m_labelBG.setOutlineColor(sf::Color::Black);
	}
}

void Label::updateLabelBG()
{
	m_labelBG.setSize(sf::Vector2f(m_labelText.getGlobalBounds().width + 5, m_labelText.getGlobalBounds().height + 5));
	m_labelBG.setOrigin(m_labelBG.getGlobalBounds().width / 2, m_labelBG.getGlobalBounds().height / 2);
	m_labelBG.setPosition(m_labelText.getPosition());
}

void Label::initText()
{
	m_labelText.setString(" dumnnnnnnn");
	//if (!m_labelFont.loadFromFile("ASSETS\\FONTS\\Arial.ttf"))
	//{
	//	std::cout << "problem loading arial black font" << std::endl;
	//}
	//m_text.setFont(m_labelFont);
	m_labelText.setFont(m_labelFont);
	m_labelText.setCharacterSize(24U);
	m_labelText.setFillColor(sf::Color::White);
	m_labelText.setOutlineThickness(2.0f);
	m_labelText.setOutlineColor(sf::Color::Black);
}

void Label::setText(std::string t_text)
{
	m_labelText.setString(t_text);
	m_labelText.setOrigin(m_labelText.getGlobalBounds().width / 2,m_labelText.getGlobalBounds().height/2);
}

void Label::setLabelSprite(std::string t_spriteName, std::string t_path)
{
	m_image = true;
	if (!m_labelTexture.loadFromFile(t_path + t_spriteName + ".png"))
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

void Label::setTextStyle()
{
	if(m_italics && m_underlined && m_bold)
		m_labelText.setStyle(sf::Text::Italic | sf::Text::Underlined | sf::Text::Bold);
	else if (m_italics && m_underlined)
		m_labelText.setStyle(sf::Text::Italic | sf::Text::Underlined);
	else if (m_italics && m_bold)
		m_labelText.setStyle(sf::Text::Italic | sf::Text::Bold);
	else if (m_underlined && m_bold)
		m_labelText.setStyle( sf::Text::Underlined | sf::Text::Bold);
	else if(m_italics)
		m_labelText.setStyle(sf::Text::Italic);
	else if (m_bold)
		m_labelText.setStyle(sf::Text::Bold);
	else if (m_underlined)
		m_labelText.setStyle(sf::Text::Underlined);
	else
		m_labelText.setStyle(sf::Text::Regular);
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
	else
	{
		t_window->draw(m_labelText);
	}
}