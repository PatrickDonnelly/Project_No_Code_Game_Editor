#include "DialogueBox.h"
#include <iostream>

/// <summary>
/// Default constructor for the dialogue box
/// </summary>
DialogueBox::DialogueBox()
{
	m_font = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");
	initDialogueBox();
	initText();

}

/// <summary>
/// Overloaded constructor for the dialogue box that takes in a font
/// </summary>
/// <param name="t_font"></param>
/// <returns></returns>
DialogueBox::DialogueBox(sf::Font& t_font)
{
	m_font = t_font;
	initDialogueBox();
	initText();


}

/// <summary>
/// Initialises the text of a dialogue box
/// </summary>
void DialogueBox::initText()
{
	m_textBox.setFont(m_font);
	m_textBox.setCharacterSize(20.0f);
	m_textBox.setFillColor(sf::Color::White);
	m_textBox.setOutlineColor(sf::Color::Black);
	m_textBox.setOutlineThickness(2.0f);
	m_textBox.setPosition(300.0f, 624.0f);
}

/// <summary>
/// Deconstructor for the dialogue box
/// </summary>
DialogueBox::~DialogueBox()
{

}

/// <summary>
/// Gets the dialogue box sprite
/// </summary>
/// <returns></returns>
sf::Sprite DialogueBox::getDialogueBoxSprite()
{
	return sf::Sprite();
}

/// <summary>
/// Gets the dialogue box position
/// </summary>
/// <returns></returns>
sf::Vector2f DialogueBox::getDialogueBoxPosition()
{
	return m_dialogueBoxSprite.getPosition();
}

/// <summary>
/// Initialises the dialogue box
/// </summary>
void DialogueBox::initDialogueBox()
{
	m_dialogueBox.setSize(sf::Vector2f(1376.0f, 200.0f));
	m_dialogueBox.setPosition(272.0f, 608.0f);
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

/// <summary>
/// Sets the dialogue box sprite
/// </summary>
/// <param name="t_dialogueSprite"></param>
void DialogueBox::setDialogueBoxSprite(sf::Sprite t_dialogueSprite)
{
	m_dialogueBoxSprite = t_dialogueSprite;
}

/// <summary>
/// renders the dialogue box
/// </summary>
/// <param name="t_window"></param>
void DialogueBox::render(sf::RenderWindow* t_window)
{
	//t_window->draw(m_dialogueBoxSprite);
	if (isEnabled())
	{
		t_window->draw(m_dialogueBox);
		t_window->draw(m_textBox);
	}
}

/// <summary>
/// Checks if the dialogue box is enabled
/// </summary>
/// <returns></returns>
bool DialogueBox::isEnabled()
{
	return m_enabled;
}

/// <summary>
/// Splits the string into multiple lines for display
/// </summary>
/// <param name="t_dialogueText"></param>
void DialogueBox::splitString(std::string t_dialogueText)
{

	m_dialogue.clear();
	m_textBox.setString("");
	std::string tmp;
	std::stringstream ss(t_dialogueText);

	while (getline(ss, tmp, '\n')) {
		m_dialogue.push_back(tmp+'\n');
	}

	for (int i = 0; i < m_dialogue.size(); i++)
	{
		m_textBox.setString(m_textBox.getString() + m_dialogue.at(i));
	}
}

/// <summary>
/// Loads text from a txt file to be displayed inside the dialogue box
/// </summary>
/// <param name="t_fileName"></param>
void DialogueBox::loadText(std::string t_fileName)
{

	unsigned lines = 0;
	std::string line_content;
	std::string lineContentAppended;


	std::ifstream my_file("Dialogue/" + t_fileName + ".txt");


	while (std::getline(my_file, line_content)) {
		lines++;

		lineContentAppended.append(line_content);
		lineContentAppended.append("\n");

		std::cout << "Line: " << lines << " content: " << line_content << std::endl;
	}


	splitString(lineContentAppended);
	my_file.close();
}
