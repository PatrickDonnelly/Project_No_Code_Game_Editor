#ifndef COLOURPICKER_HPP
#define COLOURPICKER_HPP
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Button.h"

class ColourPicker
{
public:

	ColourPicker();
	~ColourPicker();

	void render(sf::RenderWindow* t_window);
	void setPopUpEnabled(bool t_onOff) { m_enabled = t_onOff; }

	bool isEnabled() { return m_enabled; }
	bool processEvents(sf::Event t_event, sf::RenderWindow& t_window);
	
	Button* getButtons() { return m_closeButton; }
	sf::Color getColor() { return m_selectedColor; }

private:

	void initColorPicker();
	void setUpCloseButton();
	
	bool checkIfCloseClicked(sf::Event t_event, sf::RenderWindow& t_window);
	void checkIfColorPicked(sf::Event t_event, sf::RenderWindow& t_window);

	TextureManager* m_textureManager;
	sf::Texture m_colorPickerTexture;
	sf::Image m_colorPicker;
	sf::Sprite m_colorPickerSprite;
	sf::Color m_selectedColor;
	Button* m_closeButton;

	bool m_enabled = false;
	sf::RectangleShape m_colorPickerBG;
};
#endif  // !COLOURPICKER_HPP

