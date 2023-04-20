#pragma once
#ifndef INSPECTOR_HPP
#define INSPECTOR_HPP
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include "Button.h"
#include "Label.h"
#include "GameState.h"
#include "InspectorOptions.h"
#include "FontManager.h"
//#include "Object.h"
//#include "Enemy.h"
#include "Attributes.h"
//#include "ObjectPlacement.h"
//#include "TextEditor.h"
#include "DropDownMenu.h"
#include "Globals.h"




class Inspector
{
public:

	Inspector();
	//Inspector(ObjectPlacement* t_objects);
	Inspector(sf::Font& t_font);
	Inspector(std::string t_title, Attributes& t_object);
	Inspector(std::string t_title);
	~Inspector();
	FontManager m_fontManager;

	sf::Sprite getInspectorSprite();
	sf::Vector2f getInspectorPosition();

	void initInspector();

	void setInspectorSprite(sf::Sprite t_dialogueSprite);
	void render(sf::RenderWindow* t_window);
	bool isEnabled();
	void setEnabled() { m_enabled = !m_enabled; }
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void processEvents(sf::Event t_event, sf::RenderWindow& t_window, GameState* t_gameState, std::string t_fileName, std::map<std::string, std::string>& t_dialoguePaths);

	//void setInspectorText(std::string t_dialogue) { m_textBox.setString(t_dialogue); }

	void splitString(std::string t_dialogueText);
	void setTextString(std::string t_text) { m_text.setString(t_text); }
	Label* m_currentLabel;

private:
	bool isNull();
	void addDialogueTab();
	void updateDialogueTab();
	Button* m_addDialogueButton;
	Button* m_applyButton;
	Label* m_addDialogueLabel;
	Label* m_addCategoryLabel;
	void repositionDropDown(std::vector<Button*>::iterator t_iter1, std::vector<Button*>::iterator t_iter2, std::vector<Label*>::iterator t_iter3, std::vector<DropDownMenu*>::iterator t_iter4, int t_offset);

	void repositionDialogueButtons();
	//TextEditor m_textEditor;
	GameState* m_gameState;

	void saveChanges(std::map<std::string, std::string>& t_dialoguePaths);


	std::vector<std::string> m_dialogueFileNames;
	std::vector<Label> m_labels;
	Attributes m_objectData;
	//ObjectPlacement* m_objects;
	std::vector<Button*> m_deleteButtons;
	std::vector<Button*> m_dialogueButtons;
	std::vector<Label*> m_dialogueLabels;
	std::vector<DropDownMenu*> m_dialogueDropDownMenu;



	int m_noOfOptions;
	void setUpFontAndText();
	void initInspectorOptions();
	std::vector<InspectorOptions*> m_inspectorOptions;
	Label* m_inspectorLabel;
	std::vector<std::string> m_dialogue;
	bool m_enabled = false;
	sf::Sprite m_inspectorSprite;
	sf::Texture m_inspectorTexture;
	sf::RectangleShape m_inspectorBGShape;
	std::string m_title;
	//std::string m_text;
	sf::Text m_text;
	sf::Font m_font;
	void initText();
};
#endif  // !INSPECTOR_HPP

