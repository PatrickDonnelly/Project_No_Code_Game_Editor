#pragma once
#ifndef DROPDOWNMENU_HPP
#define DROPDOWNMENU_HPP

#include "Button.h"
#include "CheckBox.h"
#include <SFML/Graphics.hpp>

class DropDownMenu
{
public:

	DropDownMenu();
	DropDownMenu(std::string t_type);
	~DropDownMenu();

	Button* m_dropDownMenuButton;
	std::vector<CheckBox> m_dropDownMenuOptions;
	std::string m_type;
	void processEvents(sf::Event t_event, sf::RenderWindow& t_window);

	void setUpDropDownMenu();

	sf::Sprite getDropDownButtonSprite();
	sf::Vector2f getDropDownButtonPosition();
	int	m_buttonIndex;

	void initButton();
	void setDropDownMenuPosition(sf::Vector2f t_position, float t_width);
	void setDropDownButtonSprite(sf::Sprite t_buttonSprite);
	void highlighted();
	void setColor(sf::Color t_color);
	void setButtonTexture();
	void render(sf::RenderWindow* t_window);
	void resize(float m_xScale, float m_yScale);
	bool getSelected();
	void setSelected(bool t_tf);
	bool isEnabled() { return m_enabled; };
	bool isOpened() { return m_opened; };

	void setEnabled(bool t_onOff) { m_enabled = t_onOff; }
	void setOpened(bool t_onOff) { m_opened = t_onOff; }
	void setOpened() { m_opened = !m_opened; }
	void setEnabled() { m_enabled = !m_enabled; }

	bool isButtonClicked(sf::Event& t_event, sf::RenderWindow* t_window);
	void checkEnabledOptions(std::map<std::string, std::string>& t_dialoguePaths, std::string t_fileName);
private:
	bool m_opened = false;
	bool m_selected;
	bool m_enabled = false;
	bool m_checkBoxClicked = false;
	std::string m_currentlyEnabledDialogueOption;
	sf::Sprite m_buttonSprite;
	sf::Texture m_buttonTexture;
	sf::Texture m_buttonHighlightTexture;


};
#endif  // !DROPDOWNMENU_HPP
