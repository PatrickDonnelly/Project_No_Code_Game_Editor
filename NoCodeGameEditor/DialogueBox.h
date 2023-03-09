#ifndef DIALOGUEBOX_HPP
#define DIALOGUEBOX_HPP
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include "Button.h"
#include "Label.h"
#include "GameState.h"

#define ENTER_KEY 13
#define ESCAPE_KEY 27
#define BACKSPACE_KEY 8
class DialogueBox
{
public:

	DialogueBox();
	DialogueBox(sf::Font& t_font);
	~DialogueBox();

	sf::Sprite getDialogueBoxSprite();
	sf::Vector2f getDialogueBoxPosition();

	void initDialogueBox();

	void setDialogueBoxSprite(sf::Sprite t_dialogueSprite);
	void render(sf::RenderWindow* t_window);
	bool isEnabled();
	void setEnabled(bool t_onOff) { m_enabled = t_onOff; }
	void typing(sf::Event t_event);

private:

	GameState* m_gameState;
	bool m_enabled = false;
	sf::Sprite m_dialogueBoxSprite;
	sf::Texture m_dialogueBoxTexture;
	sf::RectangleShape m_dialogueBox;

	void inputTextBox(int t_character);
	void deletePreviousCharacter();
	std::ostringstream m_text;
	sf::Text m_textBox;
	sf::Font m_font;
	void initText();
	int m_characterLimit = 500;
};
#endif  // !DIALOGUEBOX_HPP