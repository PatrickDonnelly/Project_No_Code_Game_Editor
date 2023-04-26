#include "InputField.h"
#include <iostream>
#include <fstream>

/// <summary>
/// Default constructor for the input field
/// </summary>
InputField::InputField()
{

}

/// <summary>
/// Overloaded constructor for the input field.
/// Sets a character limit
/// and whether or not the input field is multiline or not
/// </summary>
/// <param name="t_font"></param>
/// <param name="t_multiline"></param>
/// <param name="t_characterLimit"></param>
InputField::InputField(sf::Font& t_font, bool t_multiline, int t_characterLimit) :
	m_font(t_font), m_multiline(t_multiline), m_characterLimit(t_characterLimit)
{
	initText();
	initInputField();
}

/// <summary>
/// Initialise the input fields text object
/// </summary>
void InputField::initText()
{
	m_textBox.setFont(m_font);
	m_textBox.setCharacterSize(20.0f);
	m_textBox.setFillColor(sf::Color::Black);
	m_textBox.setPosition(170.0f, 210.0f);

}

/// <summary>
/// Deconstructor for the input field
/// </summary>
InputField::~InputField()
{

}

/// <summary>
/// Initialises the input field
/// </summary>
void InputField::initInputField()
{
	m_inputField.setSize(sf::Vector2f(1600.0f, 600.0f));
	m_inputField.setPosition(160.0f, 200.0f);
	m_inputField.setOutlineThickness(2.0f);
	m_inputField.setOutlineColor(sf::Color::Black);
	m_inputField.setFillColor(sf::Color::White);
}

/// <summary>
/// Sets the size of the input field
/// </summary>
/// <param name="t_fieldSize"></param>
/// <param name="t_pos"></param>
void InputField::SetInputFieldSize(sf::Vector2f t_fieldSize, sf::Vector2f t_pos)
{
	m_inputField.setSize(sf::Vector2f(t_fieldSize.x, t_fieldSize.y));
	m_inputField.setPosition(t_pos.x, t_pos.y);
	m_textBox.setPosition(m_inputField.getPosition().x +10, m_inputField.getPosition().y+10);

}

/// <summary>
/// Renders the input fields
/// </summary>
/// <param name="t_window"></param>
void InputField::render(sf::RenderWindow* t_window)
{
	t_window->draw(m_inputField);
	t_window->draw(m_textBox);
}

/// <summary>
/// Checks if the input field is enabled
/// </summary>
/// <returns></returns>
bool InputField::isEnabled()
{
	return m_enabled;
}

/// <summary>
/// Clears all text from the input field
/// </summary>
void InputField::ClearText()
{
	m_text.str("");
	m_textBox.setString(m_text.str());
}

/// <summary>
/// Checks what key is pressed and acts accordingly.
/// If back space or delete it calls for the previous character to be deleted from the string
/// If enter is pressed a new line is inserted
/// If a character or number is pressed it is added to the text objects string field
/// </summary>
/// <param name="t_character"></param>
void InputField::inputTextBox(int t_character)
{
	if (t_character != BACKSPACE_KEY && t_character != ENTER_KEY && t_character != ESCAPE_KEY)
	{
		m_text << static_cast<char>(t_character);
	}
	else if (t_character == BACKSPACE_KEY)
	{
		if (m_text.str().length() > 0)
		{
			deletePreviousCharacter();
		}
	}
	else if (t_character == ENTER_KEY)
	{
		m_text << '\n';
	}

	m_textBox.setString(m_text.str());
	std::string temp = m_textBox.getString();
	//std::cout << "width : " << m_textBox.getGlobalBounds().width << std::endl;
	//std::cout << "height : " << m_textBox.getGlobalBounds().height << std::endl;
	std::string word;
	if (m_text.str().length() > 0)
	{
		if (m_text.str().at(temp.length() - 1) != '\n')
		{
			if (m_textBox.findCharacterPos(temp.length() - 1).x > m_inputField.getSize().x +140)
			{
				word = "";
				for (int i = temp.length() - 1; i >= 0; i--)
				{
					if (temp.at(i) == ' ' || temp.at(i) == '\n')
					{
						if (temp.at(i) == ' ')
						{
							temp.pop_back();
						}
						break;
					}
					else
					{
						word += temp.at(i);
						temp.pop_back();
						std::cout << "\n" << word;
					}
				}
				//m_text << "\n";
				std::string temp1 = temp;
				temp1 += '\n';
				std::reverse(word.begin(), word.end());

				temp1 += word;

				m_text.str(" ");
				m_text << temp1;

				m_textBox.setString(m_text.str());

				if (m_textBox.findCharacterPos(m_text.str().length() - 1).x > m_inputField.getSize().x+140)
				{
					temp1.insert(temp1.length() - 1, 1, '\n');
					//temp1 += word;

					if (temp1.at(0) == '\n')
					{
						temp1.erase(0, 1);
					}
					m_text.str(" ");
					m_text << temp1;

					//std::cout << "Here" << word;
					m_textBox.setString(m_text.str());
				}
				else
				{

				}
				//std::cout << "breaking";

			}
		}
		//std::cout << "X Position of char : " << m_textBox.findCharacterPos(i).x << std::endl;
		//std::cout << "Y Position of char : " << m_textBox.findCharacterPos(i).y << std::endl;
	}
}

/// <summary>
/// Deletes the previous character of the text objects string
/// </summary>
void InputField::deletePreviousCharacter()
{
	std::string temp = m_text.str();
	std::string empty = "";

	for (int i = 0; i < m_text.str().length() - 1; i++)
	{
		empty += temp[i];
	}
	m_text.str("");
	m_text << empty;
	m_textBox.setString(m_text.str());
}

/// <summary>
/// Checks if a letter key or number key was pressed
/// Deletes the input character if the string is at its character limit
/// If not it calls for the input character to be added to the string
/// </summary>
/// <param name="t_event"></param>
void InputField::typing(sf::Event t_event)
{
	int currentCharacter = t_event.text.unicode;
	if (currentCharacter < 128)
	{
		if (m_characterLimit == 0)
		{
			inputTextBox(currentCharacter);
			if (!m_multiline && currentCharacter == ENTER_KEY)
			{
				deletePreviousCharacter();
			}
		}
		else if (m_text.str().length() < m_characterLimit)
		{

			inputTextBox(currentCharacter);
			if (!m_multiline && currentCharacter == ENTER_KEY)
			{
				deletePreviousCharacter();
			}
		}
		else if (m_text.str().length() > m_characterLimit || currentCharacter == BACKSPACE_KEY)
		{
			deletePreviousCharacter();
		}
	}
	//else
	//{
	//	inputTextBox(currentCharacter);
	//}
}