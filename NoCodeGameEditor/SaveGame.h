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
#include <filesystem>
#include "CheckBox.h"
#include "DialogueBox.h"


namespace fs = std::filesystem;

class SaveGame
{
public:

	SaveGame();
	SaveGame(GameState* t_currentGameState);
	~SaveGame();

	/*void setUpPlaceableItemsButtons(sf::Font& t_arialFont, int& t_rows, std::vector<std::vector<Button*>>& t_objectButtons, std::vector<std::vector<Label*>>& t_labels, std::vector<std::string> t_objects, std::string t_path);
	std::vector<std::vector<Button*>> m_selectableDialogueButtons;
	std::vector<std::vector<Label*>> m_selectableDialogueLabels;
	std::vector<std::string> m_DialogueOptions;
	std::string m_pathDialogue = "DialogueBoxes/";
	int m_rowsDialogue = 0;
	int m_currentRowIndex = 0;
	std::vector<Button*> m_prevNextbuttons;
	std::string fileName = "";

	void setVisibleRow(sf::Event t_event, sf::RenderWindow& t_window, int t_rows, std::vector<std::vector<Button*>>& t_objectButtons);


	bool isEnabled();

	void processTextEditorButtons(sf::Event t_event, sf::RenderWindow& t_window, Label* t_label);
*/
	void initInputFields();
	void render(sf::RenderWindow* t_window);
	std::vector<Label*> m_labels;
	std::vector<Button*> m_saveAndCancelButtons;
	void processEvents(sf::Event t_event, sf::RenderWindow& t_window);
	void setEnabled(bool t_onOff) { m_enabled = t_onOff; }
	Label* m_titleText;
	Label* m_subTitleText;

private:

	InputField* m_mainTitle;
	InputField* m_subTitle;
	FontManager m_fontManager;
	bool saving = false;
	void loadDialogue();
	void refreshDialogue();
	void clearDialogue();

	PopUp m_popUpBox;
	std::vector<Button*> m_popUpButtons;
	std::vector<Label*> m_popUpButtonLabels;

	void setUpTextEditorButtons(sf::Font& t_arialFont);
	void setPopUpButtons(sf::Font& t_arialFont);

	std::vector<Button*> m_textEditorButtons;
	std::vector<Label*> m_textEditorLabels;
	GameState* m_gameState;
	bool m_enabled = false;

	sf::RectangleShape m_inputFieldMainBody;
	sf::RectangleShape m_inputFieldTitle;
	sf::RectangleShape m_backGround;


	void inputTextBox(int t_character);
	void deletePreviousCharacter();
	//std::ostringstream m_text;
	sf::Text m_textBox;
	sf::Font m_font;
	void initText();
	int m_characterLimit = 500;

};
#endif // !SAVEGAME_HPP

