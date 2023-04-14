#ifndef POPUP_HPP
#define POPUP_HPP
#include <SFML/Graphics.hpp>
#include "FontManager.h"

#include "Button.h"
#include "Label.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>



class PopUp
{
public:

	PopUp();
	PopUp(int t_noOfbuttons);
	~PopUp();

	sf::Sprite getPopUpBoxSprite();
	sf::Vector2f getPopUpBoxPosition();

	void initPopUpBox();

	void setPopUpBoxSprite(sf::Sprite t_dialogueSprite);
	void render(sf::RenderWindow* t_window);
	bool isEnabled();
	//void setEnabled(bool t_onOff) { m_enabled = t_onOff; }
	void setPopUpBoxText(std::string t_text);
	void setPopUpEnabled() { m_enabled = !m_enabled; }
	sf::Vector2f getPopUpBoxBounds();
	void readInFile(std::string t_fileName);
	void setPopUpButtons(int t_noOfbuttons);
	std::vector<Button*> getButtons() { return m_popUpButtons; }
	bool processEvents(sf::Event t_event, sf::RenderWindow& t_window);
private:
	FontManager m_fontManager;
	std::string fileName = "";
	std::vector<Button*> m_popUpButtons;
	std::vector<Label*> m_popUpButtonLabels;



	bool m_enabled = false;
	sf::Sprite m_popUpBoxSprite;
	sf::Texture m_popUpBoxTexture;
	sf::RectangleShape m_popUpBox;

	sf::Text m_text;
	sf::Font m_font;
	void initText();
};
#endif  // !POPUP_HPP
