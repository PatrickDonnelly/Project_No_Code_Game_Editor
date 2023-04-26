#include "Label.h"

/// <summary>
/// Overloaded constructor for the label class that takes in a font
/// </summary>
/// <param name="t_font"></param>
Label::Label(sf::Font& t_font)
{
	m_fontManager = FontManager();
	m_labelFont = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");

	initText();
	m_image = false;
}

/// <summary>
/// Overloaded constructor for the label class that takes in a string
/// </summary>
/// <param name="t_labelText"></param>
Label::Label(std::string t_labelText)
{
	m_fontManager = FontManager();
	m_labelFont = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");

	initText();
	setText(t_labelText);
	m_image = false;
}

/// <summary>
/// Overloaded constructor for the label class that takes in a font and a bool to check if the label
/// has a background or not
/// </summary>
/// <param name="t_font"></param>
/// <param name="t_isOn"></param>
Label::Label(sf::Font& t_font, bool t_isOn)
{
	m_fontManager = FontManager();
	m_labelFont = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");
	m_hasBG = t_isOn;

	initText();
	m_image = false;
	setUpBG();
}

/// <summary>
/// Default constructor for the label class
/// </summary>
Label::Label()
{
	m_fontManager = FontManager();
	m_labelFont = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");
	initText();
	m_image = false;
}

/// <summary>
/// Deconstructor for the label class
/// </summary>
Label::~Label()
{

}

/// <summary>
/// Sets up the BG of the label
/// </summary>
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

/// <summary>
/// Update label backgrounds
/// </summary>
void Label::updateLabelBG()
{
	m_labelBG.setSize(sf::Vector2f(m_labelText.getGlobalBounds().width + 5, m_labelText.getGlobalBounds().height + 5));
	m_labelBG.setOrigin(m_labelBG.getGlobalBounds().width / 2, m_labelBG.getGlobalBounds().height / 2);
	m_labelBG.setPosition(m_labelText.getPosition());
}

/// <summary>
/// Initialise Text string
/// </summary>
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

/// <summary>
/// Set Text
/// </summary>
/// <param name="t_text"></param>
void Label::setText(std::string t_text)
{
	m_labelText.setString(t_text);
	m_labelText.setOrigin(m_labelText.getGlobalBounds().width / 2,m_labelText.getGlobalBounds().height/2);
}

/// <summary>
/// Set Label Sprite
/// </summary>
/// <param name="t_spriteName"></param>
/// <param name="t_path"></param>
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

/// <summary>
/// Get the label text
/// </summary>
/// <returns></returns>
sf::Text* Label::getText()
{
	return& m_labelText;
}

/// <summary>
/// Format text styles
/// </summary>
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

/// <summary>
/// Get the text string 
/// </summary>
/// <returns></returns>
std::string Label::getTextString()
{
	return m_labelText.getString();
}

/// <summary>
/// Set the colour of the label
/// </summary>
/// <param name="t_color"></param>
void Label::setTextColor(sf::Color t_color)
{
	m_labelText.setFillColor(t_color);
}

/// <summary>
///  set the outline colour of a label
/// </summary>
/// <param name="t_color"></param>
void Label::setTextOutlineColor(sf::Color t_color)
{
	m_labelText.setOutlineColor(t_color);
}

/// <summary>
/// Set the outline thickness of the label text
/// </summary>
/// <param name="t_thickness"></param>
void Label::setTextOutlineThickness(float t_thickness)
{
	m_labelText.setOutlineThickness(t_thickness);
}

/// <summary>
/// Set the character size of the label text
/// </summary>
/// <param name="t_size"></param>
void Label::setTextSize(float t_size)
{
	m_labelText.setCharacterSize(t_size);
}

/// <summary>
/// set the position of the label text
/// </summary>
/// <param name="t_pos"></param>
void Label::setTextPosition(sf::Vector2f t_pos)
{
	m_labelText.setPosition(t_pos);
}

/// <summary>
/// Set the labels background sprites position
/// </summary>
/// <param name="t_pos"></param>
void Label::setTexturePosition(sf::Vector2f t_pos)
{
	m_labelSprite.setPosition(t_pos);
}

/// <summary>
/// get the position of the label text
/// </summary>
/// <returns></returns>
sf::Vector2f Label::getTextPosition()
{
	return m_labelText.getPosition();
}

/// <summary>
/// clears the label string
/// </summary>
void Label::clear()
{
	m_labelText.setString("");
}

/// <summary>
/// Renders the label
/// </summary>
/// <param name="t_window"></param>
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