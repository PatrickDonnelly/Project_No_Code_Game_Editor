#include "ColourPicker.h"
#include <iostream>

/// <summary>
/// Default Constructor
/// </summary>
ColourPicker::ColourPicker()
{
	initColorPicker();
	setUpCloseButton();
}

/// <summary>
/// Deconstructor
/// </summary>
ColourPicker::~ColourPicker()
{

}

/// <summary>
/// Set up the close button used to close the colour picker
/// </summary>
void ColourPicker::setUpCloseButton()
{
	m_closeButton = new Button("Close");
	m_closeButton->setButtonPosition(
			sf::Vector2f{ m_colorPickerBG.getPosition().x + (m_colorPickerBG.getGlobalBounds().width / 2),
							m_colorPickerBG.getPosition().y + m_colorPickerBG.getGlobalBounds().height - 60 });
	m_closeButton->resize(.75f, .75f);
}

/// <summary>
/// Initialise the colour ppicker, the image, texture, position etc.
/// </summary>
void ColourPicker::initColorPicker()
{
	m_colorPickerBG.setSize(sf::Vector2f(380.0f, 460.0f));
	m_colorPickerBG.setPosition(1440.0f, 32.0f);
	m_colorPickerBG.setOutlineThickness(2.0f);
	m_colorPickerBG.setOutlineColor(sf::Color(sf::Color(100, 100, 100)));
	m_colorPickerBG.setFillColor(sf::Color(sf::Color(255, 200, 200)));

	m_textureManager = new TextureManager();
	if (!m_colorPicker.loadFromFile("ASSETS\\IMAGES\\circle.png")) {
		std::cout << "failed to load colour picker" << std::endl;
	}
	m_colorPickerTexture.loadFromImage(m_colorPicker);
	m_colorPickerSprite.setTexture(m_colorPickerTexture);
	m_colorPickerSprite.setPosition(sf::Vector2f(m_colorPickerBG.getPosition().x + 5, m_colorPickerBG.getPosition().y + 5));
	m_selectedColor = sf::Color::White;
}

/// <summary>
/// Processes mouse events
/// </summary>
/// <param name="t_event"></param>
/// <param name="t_window"></param>
/// <returns></returns>
bool ColourPicker::processEvents(sf::Event t_event, sf::RenderWindow& t_window)
{
	if (checkIfCloseClicked(t_event, t_window))
	{
		return true;
	}
	checkIfColorPicked(t_event, t_window);
	return false;
}

/// <summary>
/// Checks if an area inside the colour picker was clicked.
/// If so it sets the selected colour to the colour of the pixel where the click occured
/// </summary>
/// <param name="t_event"></param>
/// <param name="t_window"></param>
void ColourPicker::checkIfColorPicked(sf::Event t_event, sf::RenderWindow& t_window)
{
	sf::Vector2f pixelPos = sf::Vector2f(sf::Mouse::getPosition(t_window).x, sf::Mouse::getPosition(t_window).y);
	m_colorPickerSprite.setTexture(m_colorPickerTexture);

	if (m_colorPickerSprite.getGlobalBounds().contains(pixelPos))
	{
		if (t_event.type == sf::Event::MouseButtonReleased && t_event.mouseButton.button == sf::Mouse::Left)
		{
			int x = t_event.mouseButton.x - m_colorPickerSprite.getPosition().x;
			int y = t_event.mouseButton.y - m_colorPickerSprite.getPosition().y;
			m_selectedColor = m_colorPicker.getPixel(x, y);
		}
	}
}

/// <summary>
/// Checks if the close button on the colour picker was clicked
/// </summary>
/// <param name="t_event"></param>
/// <param name="t_window"></param>
/// <returns></returns>
bool ColourPicker::checkIfCloseClicked(sf::Event t_event, sf::RenderWindow& t_window)
{
	sf::Vector2f pixelPos = sf::Vector2f(sf::Mouse::getPosition(t_window).x, sf::Mouse::getPosition(t_window).y);
	if (m_closeButton->getButtonSprite().getGlobalBounds().contains(pixelPos))
	{
		m_closeButton->highlighted();
		if (t_event.type == sf::Event::MouseButtonReleased 
			&& t_event.mouseButton.button == sf::Mouse::Left)
		{
			setPopUpEnabled(false);
			return true;
		}
	}
	else
	{
		m_closeButton->setButtonTexture();
	}
	return false;
}

/// <summary>
/// renders the colour picker
/// </summary>
/// <param name="t_window"></param>
void ColourPicker::render(sf::RenderWindow* t_window)
{
	if (m_enabled)
	{
		t_window->draw(m_colorPickerBG);
		t_window->draw(m_colorPickerSprite);
		m_closeButton->render(t_window);
	}
}