#include "SaveGame.h"

SaveGame::SaveGame()
{

}

SaveGame::SaveGame(GameState* t_currentGameState)
{
	m_fontManager = FontManager();
	m_font = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");
	m_mainTitle = new InputField(m_font, false, 20);
	m_subTitle = new InputField(m_font, false, 24);
	m_saveAndCancelButtons.push_back(new Button("Cancel"));
	m_saveAndCancelButtons.push_back(new Button("Save"));
	m_labels.push_back(new Label("Enter Your Game Title Here"));
	m_labels.push_back(new Label("Enter A Subtitle (Optional)"));
	m_titleText = new Label();
	m_subTitleText = new Label();

	std::string path = "Games/";
	m_popUpBox = PopUp(2);
	m_gameState = t_currentGameState;

	initInputFields();
	setUpOptions(m_mainTitleOptions, 0, 100, 40.0f, m_titleText, m_mainTitleColor);
	setUpOptions(m_subTitleOptions, 150.0f, 200, 30.0f, m_subTitleText, m_subTitleColor);
}

SaveGame::~SaveGame()
{

}

void SaveGame::initInputFields()
{
	m_mainTitle->SetInputFieldSize(sf::Vector2f(800.0f, 50.0f), sf::Vector2f(560.0f, 600.0f));
	m_subTitle->SetInputFieldSize(sf::Vector2f(800.0f, 50.0f), sf::Vector2f(560.0f, 750.0f));

	m_backGround.setSize(sf::Vector2f(840.0f, 800.0f));
	m_backGround.setPosition(540.0f, 200.0f);
	m_backGround.setOutlineThickness(4.0f);
	m_backGround.setOutlineColor(sf::Color(sf::Color(140, 140, 140)));
	m_backGround.setFillColor(sf::Color(sf::Color(204, 204, 204)));
	sf::Vector2f pos = m_mainTitle->GetInputField().getPosition();

	m_labels.at(0)->setTextPosition(sf::Vector2f(m_mainTitle->GetInputField().getPosition().x + 180,
		m_mainTitle->GetInputField().getPosition().y - 30));
	m_labels.at(1)->setTextPosition(sf::Vector2f(m_subTitle->GetInputField().getPosition().x + 180,
		m_subTitle->GetInputField().getPosition().y - 30));
	m_saveAndCancelButtons.at(0)->setButtonPosition(sf::Vector2f(740.0f, 900.0f));
	m_saveAndCancelButtons.at(1)->setButtonPosition(sf::Vector2f(1180.0f, 900.0f));
}

void SaveGame::processEvents(sf::Event t_event, sf::RenderWindow& t_window)
{
	if (!m_mainTitleOptions.at(3).isEnabled() && !m_subTitleOptions.at(3).isEnabled())
	{
		m_colourPicker.setPopUpEnabled(false);
	}
	if (!m_popUpBox.isEnabled())
	{
		for (int i = 0; i < m_mainTitleOptions.size(); ++i)
		{
			m_mainTitleOptions.at(i).isCheckBoxClicked(t_event, &t_window);
			m_subTitleOptions.at(i).isCheckBoxClicked(t_event, &t_window);
			setTextStyle(m_mainTitleOptions, m_titleText, i, m_mainTitleColor, t_event, t_window);
			setTextStyle(m_subTitleOptions, m_subTitleText, i, m_subTitleColor, t_event, t_window);
		}
		processButtons(t_event, t_window);
		setSelectedInputField(t_event, t_window);
		typing(t_event);

	}
	else
	{
		if (m_popUpBox.processEvents(t_event, t_window))
		{
			m_gameState->setState(State::SAVING);
			setUpPopUpBox("saveSuccessful", 1);
		}
	}
}

void SaveGame::processButtons(sf::Event t_event, sf::RenderWindow& t_window)
{
	sf::Vector2f pixelPos = sf::Vector2f(sf::Mouse::getPosition(t_window).x, sf::Mouse::getPosition(t_window).y);
	for (int i = 0; i < m_saveAndCancelButtons.size(); i++)
	{
		if (m_saveAndCancelButtons.at(i)->getButtonSprite().getGlobalBounds().contains(pixelPos))
		{
			m_saveAndCancelButtons.at(i)->highlighted();
			if (t_event.type == sf::Event::MouseButtonReleased
				&& t_event.mouseButton.button == sf::Mouse::Left
				&& m_saveAndCancelButtons.at(i)->getButtonLabel()->getTextString() == "Save")
			{
				std::string temp = m_mainTitle->GetText();
				temp.erase(std::remove_if(temp.begin(), temp.end(), [](char c) { return std::isspace(c); }), temp.end());
				if (temp == "")
				{
					setUpPopUpBox("emptyInput", 1);
				}
				else
				{
					std::string projectDirectory = fs::current_path().string() + "\\Games";
					std::cout << projectDirectory << std::endl;
					std::string folderName = m_mainTitle->GetText();
					m_folderPath = " ";
					m_folderPath = projectDirectory + "\\" + folderName;

					if (!fs::exists(m_folderPath))
					{
						fs::create_directory(m_folderPath);
						setUpPopUpBox("saveSuccessful", 1);
						m_gameState->setState(State::SAVING);
					}
					else
					{
						setUpPopUpBox("fileExists", 2);
					}
				}
			}
			else if (t_event.type == sf::Event::MouseButtonReleased
				&& t_event.mouseButton.button == sf::Mouse::Left
				&& m_saveAndCancelButtons.at(i)->getButtonLabel()->getTextString() == "Cancel")
			{
				m_enabled = false;
				m_gameState->setState(State::ROOM_TEST);
			}
		}
		else
		{
			m_saveAndCancelButtons.at(i)->setButtonTexture();
		}
	}
}

void SaveGame::setTextStyle(std::vector<CheckBox>& t_textOptions, Label* t_text , int t_index, sf::Color& t_textColor, sf::Event t_event, sf::RenderWindow& t_window)
{
	if (t_textOptions.at(t_index).getTag() == "Colour")
	{
		if (t_textOptions.at(t_index).isEnabled())
		{
			m_colourPicker.setPopUpEnabled(true);
			if (m_colourPicker.processEvents(t_event, t_window))
			{
				t_textOptions.at(t_index).setEnabled(false);
			}
			t_textColor = m_colourPicker.getColor();
			t_text->setTextColor(t_textColor);
		}
	}
	else if (t_textOptions.at(t_index).getTag() == "Italics")
	{
		if (t_textOptions.at(t_index).isEnabled())
		{
			t_text->setItalics(true);
		}
		else
		{
			t_text->setItalics(false);
		}
	}
	else if (t_textOptions.at(t_index).getTag() == "Underline")
	{
		if (t_textOptions.at(t_index).isEnabled())
		{
			t_text->setUnderline(true);
		}
		else
		{
			t_text->setUnderline(false);
		}
	}
	else if (t_textOptions.at(t_index).getTag() == "Bold")
	{
		if (t_textOptions.at(t_index).isEnabled())
		{
			t_text->setBold(true);
		}
		else
		{
			t_text->setBold(false);
		}
	}
	t_text->setTextStyle();
}

void SaveGame::typing(sf::Event t_event)
{
	if (sf::Event::TextEntered == t_event.type)
	{
		if (m_subTitle->GetSelected())
		{
			m_subTitle->typing(t_event);
			m_subTitleText->setText(m_subTitle->GetText());
		}
		else if (m_mainTitle->GetSelected())
		{
			m_mainTitle->typing(t_event);
			m_titleText->setText(m_mainTitle->GetText());
		}
	}

}

void SaveGame::setSelectedInputField(sf::Event t_event, sf::RenderWindow& t_window)
{
	sf::Vector2f pixelPos = sf::Vector2f(sf::Mouse::getPosition(t_window).x, sf::Mouse::getPosition(t_window).y);

	if (t_event.type == sf::Event::MouseButtonReleased
		&& t_event.mouseButton.button == sf::Mouse::Left)
	{
		if (m_mainTitle->GetInputField().getGlobalBounds().contains(pixelPos))
		{
			m_mainTitle->SetSelected(true);
			m_subTitle->SetSelected(false);
		}
		else if (m_subTitle->GetInputField().getGlobalBounds().contains(pixelPos))
		{
			m_subTitle->SetSelected(true);
			m_mainTitle->SetSelected(false);
		}
	}
}

void SaveGame::setUpOptions(std::vector<CheckBox>& t_options, int t_yOffsetOne, int t_yOffsetTwo, float t_fontSize, Label* t_text, sf::Color& t_textColor)
{
	for (int i = 0; i < 4; ++i)
	{
		if(i == 0)
			t_options.push_back(CheckBox("Italics"));
		if (i == 1)
			t_options.push_back(CheckBox("Underline"));
		if (i == 2)
			t_options.push_back(CheckBox("Bold"));
		if (i == 3)
			t_options.push_back(CheckBox("Colour"));
		t_options.at(i).setCheckBoxPosition(sf::Vector2f(600.0f + (i * 200.0f), 660.0f + t_yOffsetOne));
	}

	t_text->setTextPosition(sf::Vector2f(m_backGround.getPosition().x + (m_backGround.getGlobalBounds().width / 2),
		m_backGround.getPosition().y + t_yOffsetTwo));

	t_text->setTextSize(t_fontSize);
	t_text->setText(" ");
	t_textColor = sf::Color::White;
}

void SaveGame::setUpPopUpBox(std::string t_fileName, int t_noOfButtons)
{
	m_popUpBox.setPopUpEnabled();
	m_popUpBox.readInFile(t_fileName);
	m_popUpBox.setPopUpButtons(t_noOfButtons);
}

void SaveGame::render(sf::RenderWindow* t_window)
{
	if (m_enabled)
	{
		t_window->draw(m_backGround);
		m_mainTitle->render(t_window);
		m_subTitle->render(t_window);
		m_titleText->render(t_window);
		m_subTitleText->render(t_window);

		for (int i = 0; i < m_saveAndCancelButtons.size(); ++i)
		{
			m_saveAndCancelButtons.at(i)->render(t_window);
			m_labels.at(i)->render(t_window);
		}
		for (int i = 0; i < m_subTitleOptions.size(); ++i)
		{
			m_mainTitleOptions.at(i).render(t_window);
			m_subTitleOptions.at(i).render(t_window);
		}
	}
	if (m_popUpBox.isEnabled())
	{
		m_popUpBox.render(t_window);
	}
	if (m_colourPicker.isEnabled())
	{
		m_colourPicker.render(t_window);
	}
}

std::string SaveGame::getTitle(bool t_isMainTitle)
{
	if (t_isMainTitle)
	{
		return m_titleText->getTextString();
	}
	return m_subTitleText->getTextString();
}

bool SaveGame::getItalics(bool t_isMainTitle)
{
	if (t_isMainTitle)
	{
		if (m_mainTitleOptions.at(0).isEnabled() == true)
		{
			return true;
		}
		return false;
	}
	if (m_subTitleOptions.at(0).isEnabled() == true)
	{
		return true;
	}
	return false;
}

bool SaveGame::getUnderlined(bool t_isMainTitle)
{
	if (t_isMainTitle)
	{
		if (m_mainTitleOptions.at(1).isEnabled() == true)
		{
			return true;
		}
		return false;
	}
	if (m_subTitleOptions.at(1).isEnabled() == true)
	{
		return true;
	}
	return false;
}

bool SaveGame::getBold(bool t_isMainTitle)
{
	if (t_isMainTitle)
	{
		if (m_mainTitleOptions.at(2).isEnabled() == true)
		{
			return true;
		}
		return false;
	}
	if (m_subTitleOptions.at(2).isEnabled() == true)
	{
		return true;
	}
	return false;
}

int SaveGame::getColorRedValue(bool t_isMainTitle)
{
	if (t_isMainTitle)
	{
		return m_mainTitleColor.r;
	}
	return m_subTitleColor.r;
}

int SaveGame::getColorGreenValue(bool t_isMainTitle)
{
	if (t_isMainTitle)
	{
		return m_mainTitleColor.g;
	}
	return m_subTitleColor.g;
}

int SaveGame::getColorBlueValue(bool t_isMainTitle)
{
	if (t_isMainTitle)
	{
		return m_mainTitleColor.b;
	}
	return m_subTitleColor.b;
}