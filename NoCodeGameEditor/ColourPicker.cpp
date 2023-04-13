#include "ColourPicker.h"
#include <iostream>

ColourPicker::ColourPicker()
{
	m_fontManager = FontManager();
	m_font = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");
	initPopUpBox();
	initText();
	setPopUpButton();
	m_textureManager = new TextureManager();
	if (!m_colorPickerTexture.loadFromFile("ASSETS\\IMAGES\\circle.png")) {
		std::cout << "failed to load colour picker" << std::endl;
	}
	//m_colorPickerTexture.loadFromImage(m_colorPicker);
	//sf::Sprite sprite(m_colorPickerTexture);
	//sprite.setTexture(m_colorPickerTexture);
	//sprite.setPosition(800, 400);

	m_colorPickerSprite.setTexture(m_colorPickerTexture);
}

void ColourPicker::initText()
{
	m_text.setFont(m_font);
	m_text.setCharacterSize(20.0f);
	m_text.setFillColor(sf::Color::Black);
	m_text.setPosition(m_popUpBox.getPosition().x, m_popUpBox.getPosition().y);
	m_text.setString(" ");

}

void ColourPicker::setPopUpButton()
{

	m_closeButton = new Button("Close");
	m_closeButton->setButtonPosition(
			sf::Vector2f{ m_popUpBox.getPosition().x + (m_popUpBox.getGlobalBounds().width / 2),
							m_popUpBox.getPosition().y + m_popUpBox.getGlobalBounds().height - 60 });
	m_closeButton->resize(.75f, .75f);


	m_textureManager = new TextureManager();
	if (!m_colorPicker.loadFromFile("ASSETS\\IMAGES\\circle.png")) {
		std::cout << "failed to load colour picker" << std::endl;
	}
	m_colorPickerTexture.loadFromImage(m_colorPicker);
	//sf::Sprite sprite(m_colorPickerTexture);
	//sprite.setTexture(m_colorPickerTexture);
	m_colorPickerSprite.setTexture(m_colorPickerTexture);
	m_colorPickerSprite.setPosition(sf::Vector2f(m_popUpBox.getPosition().x + 5, m_popUpBox.getPosition().y + 5));
	m_selectedColor = sf::Color::White;


	m_shape.setFillColor(sf::Color::White);
	m_shape.setSize(sf::Vector2f(100.0f, 100.0f));
	m_shape.setPosition(sf::Vector2f(5.0f, 380.0f));

}

bool ColourPicker::processEvents(sf::Event t_event, sf::RenderWindow& t_window)
{
	sf::Vector2f pixelPos = sf::Vector2f(sf::Mouse::getPosition(t_window).x, sf::Mouse::getPosition(t_window).y);
	m_colorPickerSprite.setTexture(m_colorPickerTexture);

		if (m_colorPickerSprite.getGlobalBounds().contains(pixelPos))
		{
			if (t_event.type == sf::Event::MouseButtonReleased && t_event.mouseButton.button == sf::Mouse::Left)
			{

			int x = t_event.mouseButton.x - m_colorPickerSprite.getPosition().x;
			int y = t_event.mouseButton.y -m_colorPickerSprite.getPosition().y;
			sf::Vector2f worldPos = t_window.mapPixelToCoords(sf::Vector2i(x,y));

			std::cout << "mouse x : " << x << "mouse y : " << y << std::endl;
			std::cout << "pixel x : " << pixelPos.x << "pixel y : " << pixelPos.y << std::endl;
			m_selectedColor = m_colorPicker.getPixel(x, y);
			m_shape.setFillColor(m_selectedColor);
		}
	}



		if (m_closeButton->getButtonSprite().getGlobalBounds().contains(pixelPos))
		{
			m_closeButton->highlighted();
			if (t_event.type == sf::Event::MouseButtonReleased)
			{
				if (t_event.mouseButton.button == sf::Mouse::Left)
				{
						setPopUpEnabled(false);
						return true;
				}
			}
		}
		else
		{
			m_closeButton->setButtonTexture();
		}
		return false;
}

sf::Color ColourPicker::getColor()
{
	return m_selectedColor;
}

ColourPicker::~ColourPicker()
{

}

void ColourPicker::initPopUpBox()
{
	m_popUpBox.setSize(sf::Vector2f(380.0f, 460.0f));
	m_popUpBox.setPosition(1440.0f, 32.0f);
	m_popUpBox.setOutlineThickness(2.0f);
	m_popUpBox.setOutlineColor(sf::Color(sf::Color(100, 100, 100)));
	m_popUpBox.setFillColor(sf::Color(sf::Color(255, 200, 200)));

	//if (!m_popUpBoxTexture.loadFromFile("ASSETS\\IMAGES\\buttonGrey.png"))
	//{
	//	std::cout << "error" << std::endl;
	//}

	m_popUpBoxSprite.setTexture(m_popUpBoxTexture);
	m_popUpBoxSprite.setOrigin(m_popUpBoxSprite.getGlobalBounds().width / 2, m_popUpBoxSprite.getGlobalBounds().height / 2);
}

void ColourPicker::render(sf::RenderWindow* t_window)
{
	//t_window->draw(m_dialogueBoxSprite);
	if (m_enabled)
	{
		t_window->draw(m_popUpBox);
		//m_fontManager.getNumberOfFonts();
		m_text.setFont(m_font);
		t_window->draw(m_text);
		m_closeButton->render(t_window);
		t_window->draw(m_colorPickerSprite);
		t_window->draw(m_shape);
	}
}

bool ColourPicker::isEnabled()
{
	return m_enabled;
}