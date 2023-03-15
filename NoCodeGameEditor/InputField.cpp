#include "InputField.h"
#include <iostream>
#include <fstream>

InputField::InputField()
{

}

InputField::InputField(sf::Font& t_font) :
	m_font(t_font)
{
	initText();
	initInputField();
}

void InputField::initText()
{
	m_textBox.setFont(m_font);
	m_textBox.setCharacterSize(20.0f);
	m_textBox.setFillColor(sf::Color::Black);
	m_textBox.setPosition(170.0f, 210.0f);
}

InputField::~InputField()
{

}

void InputField::initInputField()
{
	m_inputField.setSize(sf::Vector2f(1600.0f, 600.0f));
	m_inputField.setPosition(160.0f, 200.0f);
	m_inputField.setOutlineThickness(2.0f);
	m_inputField.setOutlineColor(sf::Color::Black);
	m_inputField.setFillColor(sf::Color::White);
}

void InputField::SetInputFieldSize(sf::Vector2f t_fieldSize, sf::Vector2f t_pos)
{
	m_inputField.setSize(sf::Vector2f(t_fieldSize.x, t_fieldSize.y));
	m_inputField.setPosition(t_pos.x, t_pos.y);
	m_textBox.setPosition(m_inputField.getPosition().x +10, m_inputField.getPosition().y+10);

}


void InputField::render(sf::RenderWindow* t_window)
{
	t_window->draw(m_inputField);
	t_window->draw(m_textBox);
}

bool InputField::isEnabled()
{
	return m_enabled;
}

void InputField::ClearText()
{
	m_text.str("");
	m_textBox.setString(m_text.str());
}

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

void InputField::typing(sf::Event t_event)
{
	int currentCharacter = t_event.text.unicode;
	if (currentCharacter < 128)
	{

		inputTextBox(currentCharacter);
		//if (m_text.str().length() <= m_characterLimit)
		//{
		//	inputTextBox(currentCharacter);
		//}
		//else if (m_text.str().length() > m_characterLimit || currentCharacter == 8)
		//{
		//	deletePreviousCharacter();
		//}
	}
	//else
	//{
	//	inputTextBox(currentCharacter);
	//}
}