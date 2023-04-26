#include "PopUp.h"
#include <iostream>

/// <summary>
/// Default constructor for the pop up class
/// </summary>
PopUp::PopUp()
{
	m_fontManager = FontManager();
	m_font = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");
	initPopUpBox();
	initText();
}

/// <summary>
/// Overloaded constructor for the pop up class that takes in a number of buttons
/// to display on the pop up
/// </summary>
/// <param name="t_noOfbuttons"></param>
PopUp::PopUp(int t_noOfbuttons)
{
	m_fontManager = FontManager();
	m_font = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");
	initPopUpBox();
	initText();
	setPopUpButtons(t_noOfbuttons);
}

/// <summary>
/// Initialises the pop up classes text object
/// </summary>
void PopUp::initText()
{
	m_text.setFont(m_font);
	m_text.setCharacterSize(20.0f);
	m_text.setFillColor(sf::Color::Black);
	m_text.setPosition(m_popUpBox.getPosition().x, m_popUpBox.getPosition().y);
	m_text.setString(" ");

}

/// <summary>
/// Sets the pop up box text to a string thats passed in
/// </summary>
/// <param name="t_text"></param>
void PopUp::setPopUpBoxText(std::string t_text) 
{ 
	m_text.setString(t_text); 
	m_text.setPosition(m_popUpBox.getPosition().x + (m_popUpBox.getGlobalBounds().width / 2) - (m_text.getLocalBounds().width / 2), m_popUpBox.getPosition().y);
}

/// <summary>
/// Sets up the buttons to be displayed on the pop up.
/// Close and / or continue
/// </summary>
/// <param name="t_noOfbuttons"></param>
void PopUp::setPopUpButtons(int t_noOfbuttons)
{
	m_popUpButtons.clear();
	m_popUpButtonLabels.clear();
	for (int i = 0; i < t_noOfbuttons; i++)
	{
		m_popUpButtons.push_back(new Button());
		m_popUpButtons.at(i)->setButtonPosition(
			sf::Vector2f{ m_popUpBox.getPosition().x + (m_popUpBox.getGlobalBounds().width / 2 - 200) + (i * 400),
							m_popUpBox.getPosition().y + m_popUpBox.getGlobalBounds().height - 60});
		m_popUpButtons.at(i)->resize(.75f, .75f);

		m_popUpButtonLabels.push_back(new Label(m_font));
		m_popUpButtonLabels.at(i)->setTextColor(sf::Color::White);
		m_popUpButtonLabels.at(i)->setTextOutlineColor(sf::Color::Black);
		//m_labels.at(i)->setTextSize(11.0f);
		m_popUpButtonLabels.at(i)->setTextOutlineThickness(2.0f);
		m_popUpButtonLabels.at(i)->setTextPosition(m_popUpButtons.at(i)->getButtonPosition());
	}
	if(t_noOfbuttons == 1)
	m_popUpButtonLabels.at(0)->setText("Close");
	else if (t_noOfbuttons == 2)
	{
		m_popUpButtonLabels.at(0)->setText("Close");
		m_popUpButtonLabels.at(1)->setText("Continue");
	}
}

/// <summary>
/// Processes whether or not a button was clicked on a button.
/// Disables the pop up if a button was clicked
/// returns true if continue was cliked
/// otherwise false is returned
/// </summary>
/// <param name="t_event"></param>
/// <param name="t_window"></param>
/// <returns></returns>
bool PopUp::processEvents(sf::Event t_event, sf::RenderWindow& t_window)
{
	sf::Vector2f pixelPos = sf::Vector2f(sf::Mouse::getPosition(t_window).x, sf::Mouse::getPosition(t_window).y);
	for (int i = 0; i < m_popUpButtons.size(); i++)
	{
		if (m_popUpButtons.at(i)->getButtonSprite().getGlobalBounds().contains(pixelPos))
		{
			m_popUpButtons.at(i)->highlighted();
			if (t_event.type == sf::Event::MouseButtonReleased)
			{
				if (t_event.mouseButton.button == sf::Mouse::Left)
				{
					if (m_popUpButtonLabels.at(i)->getTextString() == "Continue")
					{
						setPopUpEnabled();
						return true;
					}
					else if (m_popUpButtonLabels.at(i)->getTextString() == "Close")
					{
						setPopUpEnabled();
					}
				}
			}
		}
		else
		{
			m_popUpButtons.at(i)->setButtonTexture();
		}
	}
	return false;
}

/// <summary>
/// Reads in a text file to display a message in the pop up box window
/// </summary>
/// <param name="t_fileName"></param>
void PopUp::readInFile(std::string t_fileName)
{
	m_text.setFont(m_font);
	unsigned lines = 0;
	std::string line_content;
	std::string lineContentAppended;


	std::ifstream my_file("PopUpMessages/" + t_fileName + ".txt");

	std::cout << t_fileName << std::endl;
	while (std::getline(my_file, line_content)) {
		lines++;

		lineContentAppended.append(line_content);
		lineContentAppended.append("\n");

		std::cout << "Line: " << lines << " content: " << line_content << std::endl;
	}
	my_file.close();

	m_text.setString(lineContentAppended);
	//m_text.setPosition(m_popUpBox.getPosition().x + (m_popUpBox.getGlobalBounds().width / 2) - (m_text.getLocalBounds().width / 2), m_popUpBox.getPosition().y);
}

/// <summary>
/// gets the bounds of the pop up box
/// </summary>
/// <returns></returns>
sf::Vector2f PopUp::getPopUpBoxBounds()
{
	return sf::Vector2f(m_popUpBox.getGlobalBounds().width, m_popUpBox.getGlobalBounds().height);
}

/// <summary>
/// Deconstructor for the pop up class
/// </summary>
PopUp::~PopUp()
{

}

/// <summary>
/// gets the sprite of the pop up box
/// </summary>
/// <returns></returns>
sf::Sprite PopUp::getPopUpBoxSprite()
{
	return sf::Sprite();
}

/// <summary>
/// Gets the position of the pop up box
/// </summary>
/// <returns></returns>
sf::Vector2f PopUp::getPopUpBoxPosition()
{
	return m_popUpBox.getPosition();
}

/// <summary>
/// Initialises the pop up box
/// </summary>
void PopUp::initPopUpBox()
{
	m_popUpBox.setSize(sf::Vector2f(800.0f, 400.0f));
	m_popUpBox.setPosition(560.0f, 340.0f);
	m_popUpBox.setOutlineThickness(2.0f);
	m_popUpBox.setOutlineColor(sf::Color(sf::Color(100,100,100)));
	m_popUpBox.setFillColor(sf::Color(sf::Color(255, 200, 200)));

	//if (!m_popUpBoxTexture.loadFromFile("ASSETS\\IMAGES\\buttonGrey.png"))
	//{
	//	std::cout << "error" << std::endl;
	//}

	m_popUpBoxSprite.setTexture(m_popUpBoxTexture);
	m_popUpBoxSprite.setOrigin(m_popUpBoxSprite.getGlobalBounds().width / 2, m_popUpBoxSprite.getGlobalBounds().height / 2);
}

/// <summary>
/// sets the pop up box sprite
/// </summary>
/// <param name="t_dialogueSprite"></param>
void PopUp::setPopUpBoxSprite(sf::Sprite t_dialogueSprite)
{
	m_popUpBoxSprite = t_dialogueSprite;
}


/// <summary>
/// Renders the pop up box and its buttons / labels
/// </summary>
/// <param name="t_window"></param>
void PopUp::render(sf::RenderWindow* t_window)
{
	//t_window->draw(m_dialogueBoxSprite);
	if(m_enabled)
	{
		t_window->draw(m_popUpBox);
		//m_fontManager.getNumberOfFonts();
		t_window->draw(m_text);
		for (int i = 0; i < m_popUpButtons.size(); ++i)
		{
			m_popUpButtons.at(i)->render(t_window);
			m_popUpButtonLabels.at(i)->render(t_window);
		}
	}
}

/// <summary>
/// Checks if the pop up box is enabled
/// </summary>
/// <returns></returns>
bool PopUp::isEnabled()
{
	return m_enabled;
}