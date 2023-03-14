#include "TextEditor.h"
#include <iostream>

TextEditor::TextEditor()
{

}

TextEditor::TextEditor(sf::Font& t_font, GameState* t_currentGameState)
{
	m_gameState = t_currentGameState;
	m_font = t_font;
	initDialogueBox();
	initText();
	setUpTextEditorButtons(t_font);
}

void TextEditor::initText()
{
	m_textBox.setFont(m_font);
	m_textBox.setCharacterSize(20.0f);
	m_textBox.setFillColor(sf::Color::Black);
	m_textBox.setPosition(450.0f, 100.0f);
}

TextEditor::~TextEditor()
{

}

sf::Sprite TextEditor::getDialogueBoxSprite()
{
	return sf::Sprite();
}

sf::Vector2f TextEditor::getDialogueBoxPosition()
{
	return m_dialogueBoxSprite.getPosition();
}

void TextEditor::initDialogueBox()
{
	m_inputFieldMainBody.setSize(sf::Vector2f(1600.0f, 600.0f));
	m_inputFieldMainBody.setPosition(160.0f, 200.0f);
	m_inputFieldMainBody.setOutlineThickness(2.0f);
	m_inputFieldMainBody.setOutlineColor(sf::Color::Black);
	m_inputFieldMainBody.setFillColor(sf::Color::White);

	m_inputFieldTitle.setSize(sf::Vector2f(600.0f, 50.0f));
	m_inputFieldTitle.setPosition(160.0f, 75.0f);
	m_inputFieldTitle.setOutlineThickness(2.0f);
	m_inputFieldTitle.setOutlineColor(sf::Color::Black);
	m_inputFieldTitle.setFillColor(sf::Color::White);

	m_backGround.setSize(sf::Vector2f(1640.0f, 800.0f));
	m_backGround.setPosition(140.0f, 20.0f);
	m_backGround.setOutlineThickness(4.0f);
	m_backGround.setOutlineColor(sf::Color(sf::Color(140, 140, 140)));
	m_backGround.setFillColor(sf::Color(sf::Color(204,204,204)));

	if (!m_dialogueBoxTexture.loadFromFile("ASSETS\\IMAGES\\buttonGrey.png"))
	{
		std::cout << "error" << std::endl;
	}

	m_dialogueBoxSprite.setTexture(m_dialogueBoxTexture);
	m_dialogueBoxSprite.setPosition(0.0f, 0.0f);
	m_dialogueBoxSprite.setOrigin(m_dialogueBoxSprite.getGlobalBounds().width / 2, m_dialogueBoxSprite.getGlobalBounds().height / 2);
}

void TextEditor::setDialogueBoxSprite(sf::Sprite t_dialogueSprite)
{
	m_dialogueBoxSprite = t_dialogueSprite;
}

void TextEditor::render(sf::RenderWindow* t_window)
{
	//t_window->draw(m_dialogueBoxSprite);
	t_window->draw(m_backGround);

	t_window->draw(m_inputFieldMainBody);
	t_window->draw(m_inputFieldTitle);
	t_window->draw(m_textBox);
	for (int i = 0; i < m_textEditorButtons.size(); ++i)
	{
		m_textEditorButtons.at(i)->render(t_window);
		m_textEditorLabels.at(i)->render(t_window);
	}
}

void TextEditor::processTextEditorButtons(sf::Event t_event, sf::RenderWindow& t_window)
{
	if (m_gameState->m_currentGameState == State::CREATE_DIALOGUE)
	{
		for (int i = 0; i < m_textEditorButtons.size(); i++)
		{
			if (m_textEditorButtons.at(i)->getButtonSprite().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
			{
				m_textEditorButtons.at(i)->highlighted();
				if (t_event.type == sf::Event::MouseButtonReleased)
				{
					if (t_event.mouseButton.button == sf::Mouse::Left)
					{
						if (m_textEditorLabels.at(i)->getTextString() == "Save")
						{
							// Save dialogue here
						}
						else if (m_textEditorLabels.at(i)->getTextString() == "Exit")
						{
							m_gameState->setState(State::ROOM_PLACE_OBJECTS);
						}
						else if (m_textEditorLabels.at(i)->getTextString() == "Clear")
						{
							m_text.str("");
							m_textBox.setString("");
						}
						else if (m_textEditorLabels.at(i)->getTextString() == "Load")
						{
							// Load dialogue here
						}
					}
				}
			}
			else
			{
				m_textEditorButtons.at(i)->setButtonTexture();
			}
		}
	}
}

void TextEditor::setUpTextEditorButtons(sf::Font t_arialFont)
{
	for (int i = 0; i < 4; i++)
	{
		m_textEditorButtons.push_back(new Button());
		m_textEditorButtons.at(i)->setButtonPosition(sf::Vector2f{ 215.0f + (i * 162.0f), 50.0f });
		m_textEditorButtons.at(i)->resize(.5f, 0.5f);

		m_textEditorLabels.push_back(new Label(t_arialFont));
		m_textEditorLabels.at(i)->setTextColor(sf::Color::White);
		m_textEditorLabels.at(i)->setTextOutlineColor(sf::Color::Black);
		//m_labels.at(i)->setTextSize(11.0f);
		m_textEditorLabels.at(i)->setTextOutlineThickness(2.0f);
		m_textEditorLabels.at(i)->setTextPosition(m_textEditorButtons.at(i)->getButtonPosition());
	}
	m_textEditorLabels.at(0)->setText("Save");
	m_textEditorLabels.at(1)->setText("Load");
	m_textEditorLabels.at(2)->setText("Clear");
	m_textEditorLabels.at(3)->setText("Exit");
}

bool TextEditor::isEnabled()
{
	return m_enabled;
}

void TextEditor::inputTextBox(int t_character)
{
	if (m_text.str().length() % 48 == 0)
	{
		//m_text << '\n';
	}
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
	for (int i = 0; i < temp.length(); i++)
	{

		if (m_text.str().at(i) != '\n')
		{
			if (m_textBox.findCharacterPos(i).x > 600)
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

				if (m_textBox.findCharacterPos(m_text.str().length() - 1).x > 600)
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
				break;
			}
		}
		//std::cout << "X Position of char : " << m_textBox.findCharacterPos(i).x << std::endl;
		//std::cout << "Y Position of char : " << m_textBox.findCharacterPos(i).y << std::endl;
	}
}

void TextEditor::deletePreviousCharacter()
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

void TextEditor::typing(sf::Event t_event)
{
	int currentCharacter = t_event.text.unicode;

	if (currentCharacter < 128)
	{
		if (m_text.str().length() <= m_characterLimit)
		{
			inputTextBox(currentCharacter);
		}
		else if (m_text.str().length() > m_characterLimit || currentCharacter == 8)
		{
			deletePreviousCharacter();
		}
	}
	//else
	//{
	//	inputTextBox(currentCharacter);
	//}
}