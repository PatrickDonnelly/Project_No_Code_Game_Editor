#ifndef TEXTEDITOR_HPP
#define TEXTEDITOR_HPP
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include "Button.h"
#include "Label.h"
#include "GameState.h"
#include "PopUp.h"
#include "InputField.h"

#define ENTER_KEY 13
#define ESCAPE_KEY 27
#define BACKSPACE_KEY 8

class TextEditor
{
public:

	TextEditor();
	TextEditor(sf::Font& t_font, GameState* t_currentGameState);
	~TextEditor();


	void initInputFields();


	void render(sf::RenderWindow* t_window);
	bool isEnabled();
	void setEnabled(bool t_onOff) { m_enabled = t_onOff; }
	void processTextEditorButtons(sf::Event t_event, sf::RenderWindow& t_window);
	InputField* GetTitle() { return m_title; }
	InputField* GetMainBody() { return m_mainBody; }


private:

	InputField* m_mainBody;
	InputField* m_title;


	PopUp m_popUpBox;
	std::vector<Button*> m_popUpButtons;
	std::vector<Label*> m_popUpButtonLabels;

	void setUpTextEditorButtons(sf::Font t_arialFont);
	void setPopUpButtons(sf::Font t_arialFont);

	std::vector<Button*> m_textEditorButtons;
	std::vector<Label*> m_textEditorLabels;
	GameState* m_gameState;
	bool m_enabled = false;

	sf::RectangleShape m_inputFieldMainBody;
	sf::RectangleShape m_inputFieldTitle;
	sf::RectangleShape m_backGround;


	void inputTextBox(int t_character);
	void deletePreviousCharacter();
	std::ostringstream m_text;
	sf::Text m_textBox;
	sf::Font m_font;
	void initText();
	int m_characterLimit = 500;
};
#endif  // !TEXTEDITOR_HPP

