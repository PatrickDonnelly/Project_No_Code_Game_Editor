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

class Inspector
{
public:

	Inspector();
	Inspector(sf::Font& t_font);
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

	//void setInspectorText(std::string t_dialogue) { m_textBox.setString(t_dialogue); }

	void splitString(std::string t_dialogueText);
	void setTextString(std::string t_text) { m_text.setString(t_text); }
	

private:

	void addDialogueTab();
	void updateDialogueTab();
	Button* m_addDialogueButton;
	std::vector<std::string> m_dialogueFileNames;
	std::vector<Label> m_labels;
	//Object* m_object;


	int m_noOfOptions;
	void setUpFontAndText();
	void initInspectorOptions();
	std::vector<InspectorOptions*> m_inspectorOptions;
	Label* m_inspectorLabel;
	std::vector<std::string> m_dialogue;
	GameState* m_gameState;
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

