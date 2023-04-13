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
#include "DialogueBox.h"
#include "ColourPicker.h"


namespace fs = std::filesystem;

class SaveGame
{
public:

	SaveGame();
	SaveGame(GameState* t_currentGameState);
	~SaveGame();

	void initInputFields();
	void render(sf::RenderWindow* t_window);
	std::vector<Label*> m_labels;
	std::vector<Button*> m_saveAndCancelButtons;
	void processEvents(sf::Event t_event, sf::RenderWindow& t_window);
	void setEnabled(bool t_onOff) { m_enabled = t_onOff; }
	Label* m_titleText;
	Label* m_subTitleText;

	std::string getTitle(bool t_isMainTitle);
	bool getItalics(bool t_isMainTitle);
	bool getUnderlined(bool t_isMainTitle);
	bool getBold(bool t_isMainTitle);
	int getColorRedValue(bool t_isMainTitle);
	int getColorGreenValue(bool t_isMainTitle);
	int getColorBlueValue(bool t_isMainTitle);

	void setMainTitle(std::string t_string) { m_titleText->getText().setString(t_string); }
	void setMainTitleInputField(std::string t_string) { m_mainTitle->SetString(t_string); }
	void setMainItalics(bool t_isItalics) { m_mainTitleOptions.at(0).setEnabled(t_isItalics); }
	void setMainUnderlined(bool t_isUnderlined) { m_mainTitleOptions.at(1).setEnabled(t_isUnderlined); }
	void setMainBold(bool t_isBold) { m_mainTitleOptions.at(2).setEnabled(t_isBold); }
	void setMainRedValue(int t_redValue) {m_mainTitleColor.r = t_redValue; }
	void setMainGreenValue(bool t_greenValue) { m_mainTitleColor.r = t_greenValue; }
	void setMainBlueValue(bool t_blueValue) { m_mainTitleColor.r = t_blueValue; }

	void setSubTitle(std::string t_string) { m_subTitleText->getText().setString(t_string); }
	void setSubTitleInputField(std::string t_string) { m_subTitle->SetString(t_string); }
	void setSubItalics(bool t_isItalics) { m_subTitleOptions.at(0).setEnabled(t_isItalics); }
	void setSubUnderlined(bool t_isUnderlined) { m_subTitleOptions.at(1).setEnabled(t_isUnderlined); }
	void setSubBold(bool t_isBold) { m_subTitleOptions.at(2).setEnabled(t_isBold); }
	void setSubRedValue(int t_redValue) { m_subTitleColor.r = t_redValue; }
	void setSubGreenValue(bool t_greenValue) { m_subTitleColor.r = t_greenValue; }
	void setSubBlueValue(bool t_blueValue) { m_subTitleColor.r = t_blueValue; }

private:
	sf::Color m_mainTitleColor;
	sf::Color m_subTitleColor;
	ColourPicker m_colourPicker;
	bool m_choosingColour = false;
	std::vector<CheckBox> m_subTitleOptions;
	std::vector<CheckBox> m_mainTitleOptions;
	void setUpOptions(std::vector<CheckBox>& t_options, float t_offset);

	InputField* m_mainTitle;
	InputField* m_subTitle;
	FontManager m_fontManager;
	bool saving = false;

	PopUp m_popUpBox;





	std::vector<Button*> m_textEditorButtons;
	std::vector<Label*> m_textEditorLabels;
	GameState* m_gameState;
	bool m_enabled = false;

	sf::RectangleShape m_inputFieldMainBody;
	sf::RectangleShape m_inputFieldTitle;
	sf::RectangleShape m_backGround;


	sf::Text m_textBox;
	sf::Font m_font;

	int m_characterLimit = 24;

};
#endif // !SAVEGAME_HPP

