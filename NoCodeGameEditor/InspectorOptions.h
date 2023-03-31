#ifndef INSPECTOROPTIONS_HPP
#define INSPECTOROPTIONS_HPP
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include "Button.h"
#include "Label.h"
#include "GameState.h"
#include "CheckBox.h"



class InspectorOptions
{
public:

	InspectorOptions();
	InspectorOptions(sf::Font& t_font, int noOfOptions, std::string t_tag);
	~InspectorOptions();


	sf::Sprite getInspectorOptionsSprite();
	sf::Vector2f getInspectorOptionsPosition();

	void initInspectorOptions();

	void setInspectorOptionsPosition(sf::Vector2f t_pos);
	void update(sf::Time deltaTime, sf::RenderWindow& window);

	void render(sf::RenderWindow* t_window);
	bool isEnabled();
	void setEnabled() { m_enabled = !m_enabled; }

	void setInspectorOptionsText(std::string t_dialogue) { m_text.setString(t_dialogue); }

	void splitString(std::string t_dialogueText);

	void initOptions();
private:

	std::string m_tag;
	std::vector<CheckBox*> m_options;
	int m_noOfOptions;
	Label* m_inspectorOptionsLabel;
	std::vector<std::string> m_dialogue;
	GameState* m_gameState;
	bool m_enabled = false;
	sf::Sprite m_inspectorOptionsSprite;
	sf::Texture m_inspectorOptionsTexture;
	sf::RectangleShape m_inspectorOptionsBGShape;

	//std::ostringstream m_text;
	sf::Text m_text;
	sf::Font m_font;
	void initText();
};
#endif  // !INSPECTOROPTIONS_HPP

