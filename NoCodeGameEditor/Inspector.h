#ifndef INSPECTOR_HPP
#define INSPECTOR_HPP
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include "Button.h"
#include "Label.h"
#include "GameState.h"
#include "InspectorOptions.h"

class Inspector
{
public:

	Inspector();
	Inspector(sf::Font& t_font);
	~Inspector();

	sf::Sprite getInspectorSprite();
	sf::Vector2f getInspectorPosition();

	void initInspector();

	void setInspectorSprite(sf::Sprite t_dialogueSprite);
	void render(sf::RenderWindow* t_window);
	bool isEnabled();
	void setEnabled() { m_enabled = !m_enabled; }

	//void setInspectorText(std::string t_dialogue) { m_textBox.setString(t_dialogue); }

	void splitString(std::string t_dialogueText);
	

private:
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

	//std::string m_text;
	sf::Text m_text;
	sf::Font m_font;
	void initText();
};
#endif  // !INSPECTOR_HPP

