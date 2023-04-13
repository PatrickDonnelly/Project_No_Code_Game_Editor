#ifndef COLOURPICKER_HPP
#define COLOURPICKER_HPP
#include <SFML/Graphics.hpp>
#include "FontManager.h"
#include "TextureManager.h"
#include "Button.h"
#include "Label.h"
#include "Globals.h"

class ColourPicker
{
public:

	ColourPicker();
	~ColourPicker();

	void initPopUpBox();


	void render(sf::RenderWindow* t_window);
	bool isEnabled();
	//void setEnabled(bool t_onOff) { m_enabled = t_onOff; }

	void setPopUpEnabled(bool t_onOff) { m_enabled = t_onOff; }


	void setPopUpButton();
	Button* getButtons() { return m_closeButton; }
	bool processEvents(sf::Event t_event, sf::RenderWindow& t_window);
	sf::Color getColor();

private:
	FontManager m_fontManager;
	TextureManager* m_textureManager;
	sf::Texture m_colorPickerTexture;
	sf::Image m_colorPicker;
	sf::Sprite m_colorPickerSprite;
	sf::Color m_selectedColor;
	Button* m_closeButton;
	sf::RectangleShape m_shape;



	bool m_enabled = false;
	sf::Sprite m_popUpBoxSprite;
	sf::Texture m_popUpBoxTexture;
	sf::RectangleShape m_popUpBox;

	sf::Text m_text;
	sf::Font m_font;
	void initText();
};
#endif  // !COLOURPICKER_HPP

