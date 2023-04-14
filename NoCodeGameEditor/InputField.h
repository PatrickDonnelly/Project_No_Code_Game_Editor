#ifndef INPUTFIELD_HPP
#define INPUTFIELD_HPP
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>


#define ENTER_KEY 13
#define ESCAPE_KEY 27
#define BACKSPACE_KEY 8

class InputField
{
public:

	InputField();
	InputField(sf::Font& t_font, bool t_multiline, int t_chatacterLimit);
	~InputField();


	void initInputField();

	void render(sf::RenderWindow* t_window);
	bool isEnabled();
	void setEnabled(bool t_onOff) { m_enabled = t_onOff; }
	void typing(sf::Event t_event);
	//void SetInputFieldBackGroundSize(float t_extraHeight, float t_extraWidth);
	void SetInputFieldSize(sf::Vector2f t_fieldSize, sf::Vector2f t_pos);
	bool GetSelected() { return isSelected; };
	void SetSelected(bool t_toggle) { isSelected = t_toggle; };
	sf::RectangleShape GetInputField() { return m_inputField; }
	void ClearText();
	std::string GetText() { return m_textBox.getString(); }
	void SetString(std::string t_text) { m_text.str(t_text); m_textBox.setString(m_text.str()); }
private:
	bool isSelected = false;
	bool m_enabled = false;
	sf::Sprite m_dialogueBoxSprite;
	sf::Texture m_dialogueBoxTexture;
	sf::RectangleShape m_inputField;
	//sf::RectangleShape m_backGround;
	//bool m_hasBackGround = false;

	void inputTextBox(int t_character);
	void deletePreviousCharacter();
	std::ostringstream m_text;
	sf::Text m_textBox;
	sf::Font m_font;
	void initText();
	int m_characterLimit = 500;
	bool m_multiline;
};
#endif  // !INPUTFIELD_HPP

