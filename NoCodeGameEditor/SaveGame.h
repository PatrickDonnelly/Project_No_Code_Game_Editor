#pragma once
#ifndef SAVEGAME_HPP
#define SAVEGAME_HPP
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Button.h"
#include "Label.h"
#include "GameState.h"
#include "PopUp.h"
#include "InputField.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <filesystem>
#include "CheckBox.h"
#include "ColourPicker.h"
#include "Globals.h"


namespace fs = std::filesystem;

class SaveGame
{
public:

	SaveGame();
	SaveGame(GameState* t_currentGameState);
	~SaveGame();

	void render(sf::RenderWindow* t_window);
	void processEvents(sf::Event t_event, sf::RenderWindow& t_window);
	void setEnabled(bool t_onOff) { m_enabled = t_onOff; }

	std::string getTitle(bool t_isMainTitle);
	bool getItalics(bool t_isMainTitle);
	bool getUnderlined(bool t_isMainTitle);
	bool getBold(bool t_isMainTitle);
	int getColorRedValue(bool t_isMainTitle);
	int getColorGreenValue(bool t_isMainTitle);
	int getColorBlueValue(bool t_isMainTitle);
	std::string getFolderPath() { return m_folderPath; }

	void setMainTitle(std::string t_string) { m_titleText->getText()->setString(t_string); }
	void setMainTitleInputField(std::string t_string) { m_mainTitle->SetString(t_string); }
	void setMainItalics(bool t_isItalics) { m_mainTitleOptions.at(0).setEnabled(t_isItalics); }
	void setMainUnderlined(bool t_isUnderlined) { m_mainTitleOptions.at(1).setEnabled(t_isUnderlined); }
	void setMainBold(bool t_isBold) { m_mainTitleOptions.at(2).setEnabled(t_isBold); }
	void setMainRedValue(int t_redValue) {m_mainTitleColor.r = t_redValue; m_titleText->setTextColor(m_mainTitleColor);}
	void setMainGreenValue(int t_greenValue) { m_mainTitleColor.g = t_greenValue; m_titleText->setTextColor(m_mainTitleColor);}
	void setMainBlueValue(int t_blueValue) { m_mainTitleColor.b = t_blueValue; m_titleText->setTextColor(m_mainTitleColor);}
	void setMainColor(int t_red, int t_green, int t_blue) { m_titleText->setTextColor(sf::Color(t_red, t_green, t_blue)); m_mainTitleColor = (sf::Color(t_red, t_green, t_blue));}


	void setSubTitle(std::string t_string) { m_subTitleText->getText()->setString(t_string); }
	void setSubTitleInputField(std::string t_string) { m_subTitle->SetString(t_string); }
	void setSubItalics(bool t_isItalics) { m_subTitleOptions.at(0).setEnabled(t_isItalics); }
	void setSubUnderlined(bool t_isUnderlined) { m_subTitleOptions.at(1).setEnabled(t_isUnderlined); }
	void setSubBold(bool t_isBold) { m_subTitleOptions.at(2).setEnabled(t_isBold); }
	void setSubRedValue(int t_redValue) { m_subTitleColor.r = t_redValue; m_subTitleText->setTextColor(m_subTitleColor); }
	void setSubGreenValue(int t_greenValue) { m_subTitleColor.g = t_greenValue; m_subTitleText->setTextColor(m_subTitleColor);}
	void setSubBlueValue(int t_blueValue) { m_subTitleColor.b = t_blueValue; m_subTitleText->setTextColor(m_subTitleColor);}
	void setSubColor(int t_red, int t_green, int t_blue) { m_subTitleText->setTextColor(sf::Color(t_red, t_green, t_blue)); m_subTitleColor = (sf::Color(t_red, t_green, t_blue)); }

private:
	sf::Color m_mainTitleColor;
	sf::Color m_subTitleColor;
	ColourPicker m_colourPicker;
	bool m_choosingColour = false;
	std::vector<CheckBox> m_subTitleOptions;
	std::vector<CheckBox> m_mainTitleOptions;

	std::string m_folderPath;

	InputField* m_mainTitle;
	InputField* m_subTitle;
	FontManager m_fontManager;
	bool saving = false;

	PopUp m_popUpBox;
	Label* m_titleText;
	Label* m_subTitleText;
	std::vector<Label*> m_labels;
	std::vector<Button*> m_saveAndCancelButtons;

	void initInputFields();
	void setSelectedInputField(sf::Event t_event, sf::RenderWindow& t_window);
	void typing(sf::Event t_event);
	void setTextStyle(std::vector<CheckBox>& t_textOptions, Label* t_text, int t_index, sf::Color& t_textColor, sf::Event t_event, sf::RenderWindow& t_window);
	void processButtons(sf::Event t_event, sf::RenderWindow& t_window);
	void setUpOptions(std::vector<CheckBox>& t_options, int t_yOffsetOne, int t_yOffsetTwo, float t_fontSize, Label* t_text, sf::Color& t_textColor);
	void setUpPopUpBox(std::string t_fileName, int t_noOfButtons);

	GameState* m_gameState;
	bool m_enabled = false;

	sf::RectangleShape m_inputFieldMainBody;
	sf::RectangleShape m_inputFieldTitle;
	sf::RectangleShape m_backGround;

	sf::Font m_font;
};
#endif // !SAVEGAME_HPP

