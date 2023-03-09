#include "DialogueBox.h"
#include <iostream>

DialogueBox::DialogueBox()
{

}

DialogueBox::DialogueBox(sf::Font& t_font)
{
	m_font = t_font;
	initDialogueBox();
	initText();


}

void DialogueBox::initText()
{
	m_textBox.setFont(m_font);
	m_textBox.setCharacterSize(20.0f);
	m_textBox.setFillColor(sf::Color::White);
	m_textBox.setPosition(450.0f, 580.0f);
}

DialogueBox::~DialogueBox()
{

}

sf::Sprite DialogueBox::getDialogueBoxSprite()
{
	return sf::Sprite();
}

sf::Vector2f DialogueBox::getDialogueBoxPosition()
{
	return m_dialogueBoxSprite.getPosition();
}

void DialogueBox::initDialogueBox()
{
	m_dialogueBox.setSize(sf::Vector2f(1000.0f, 200.0f));
	m_dialogueBox.setPosition(440.0f, 600.0f);
	m_dialogueBox.setOutlineThickness(2.0f);
	m_dialogueBox.setOutlineColor(sf::Color::Green);
	m_dialogueBox.setFillColor(sf::Color::Black);

	if (!m_dialogueBoxTexture.loadFromFile("ASSETS\\IMAGES\\buttonGrey.png"))
	{
		std::cout << "error" << std::endl;
	}

	m_dialogueBoxSprite.setTexture(m_dialogueBoxTexture);
	m_dialogueBoxSprite.setOrigin(m_dialogueBoxSprite.getGlobalBounds().width / 2, m_dialogueBoxSprite.getGlobalBounds().height / 2);
}

void DialogueBox::setDialogueBoxSprite(sf::Sprite t_dialogueSprite)
{
	m_dialogueBoxSprite = t_dialogueSprite;
}

void DialogueBox::render(sf::RenderWindow* t_window)
{
	//t_window->draw(m_dialogueBoxSprite);

		t_window->draw(m_dialogueBox);
		t_window->draw(m_textBox);
		std::string temp = m_textBox.getString();
		std::cout << "width : " << m_textBox.getGlobalBounds().width << std::endl;
		std::cout << "height : " << m_textBox.getGlobalBounds().height << std::endl;

		for (int i = 0; i < temp.length(); i++)
		{
			if (m_text.str().at(i) != '\n')
			{
				if (m_textBox.findCharacterPos(i).x > 600)
				{
					//m_text << "\n";
					std::string temp = m_textBox.getString();
					char character = temp.at(i - 1);
					char char2 = temp.at(i);
					temp.pop_back();
					temp.pop_back();
					temp += "\n";
					temp += (character + char2);
					m_text.clear();;
					m_text << temp;
					m_textBox.setString(m_text.str());
				}
			}
			std::cout << "X Position of char : " << m_textBox.findCharacterPos(i).x << std::endl;
			std::cout << "Y Position of char : " << m_textBox.findCharacterPos(i).y << std::endl;

		}


}

bool DialogueBox::isEnabled()
{
	return m_enabled;
}

void DialogueBox::inputTextBox(int t_character)
{
	if (m_text.str().length() % 48 == 0)
	{
		m_text << "\n";
	}
	if(t_character != BACKSPACE_KEY && t_character != ENTER_KEY && t_character != ESCAPE_KEY)
	{
		m_text << static_cast<char>(t_character);
	}
	else if(t_character == BACKSPACE_KEY)
	{
		if (m_text.str().length() > 0)
		{
			deletePreviousCharacter();
		}
	}
	else if (t_character == ENTER_KEY)
	{
		m_text << "\n";
	}

	m_textBox.setString(m_text.str());
}

void DialogueBox::deletePreviousCharacter()
{
	std::string temp = m_text.str();
	std::string empty = "";

	for (int i = 0; i < m_text.str().length() -1; i++)
	{
		empty += temp[i];
	}
	m_text.str("");
	m_text << empty;
	m_textBox.setString(m_text.str());
}

void DialogueBox::typing(sf::Event t_event)
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