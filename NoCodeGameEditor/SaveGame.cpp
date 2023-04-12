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
	std::string path = "Games/";
	m_popUpBox = PopUp(&m_font);
	m_gameState = t_currentGameState;
	//m_font = t_font;

	m_saveAndCancelButtons.push_back(new Button("Cancel"));
	m_saveAndCancelButtons.push_back(new Button("Save"));
	m_labels.push_back(new Label("Enter Your Game Title Here"));
	m_labels.push_back(new Label("Enter A Subtitle (Optional)"));
	m_titleText = new Label();
	m_subTitleText = new Label();
	initInputFields();
	m_titleText->setTextPosition(sf::Vector2f(m_backGround.getPosition().x + (m_backGround.getGlobalBounds().width/2),
		m_backGround.getPosition().y+100));
	m_subTitleText->setTextPosition(sf::Vector2f(m_backGround.getPosition().x+(m_backGround.getGlobalBounds().width/2), 
		m_backGround.getPosition().y + 200));
	m_titleText->setTextSize(40.0f);
	m_subTitleText->setTextSize(30.0f);
	m_titleText->setText(" ");
	m_subTitleText->setText(" ");

	setPopUpButtons(m_font);

	//initText();
	//setUpTextEditorButtons(t_font);
	//setPopUpButtons(t_font);
	//loadDialogue();
	//setUpPlaceableItemsButtons(m_font, m_rowsDialogue, m_selectableDialogueButtons, m_selectableDialogueLabels, m_DialogueOptions, path);
	//for (int i = 0; i < 2; ++i)
	//{

	//}
}

//void SaveGame::loadDialogue()
//{
//	std::string path = "Dialogue/";
//	for (auto& entry : fs::directory_iterator(path))
//	{
//		std::string temp = entry.path().filename().string();
//		temp.resize(temp.size() - 4);
//		m_DialogueOptions.push_back(temp);
//	}
//}

//void SaveGame::refreshDialogue()
//{
//	std::string path = "Dialogue/";
//	loadDialogue();
//	setUpPlaceableItemsButtons(m_font, m_rowsDialogue, m_selectableDialogueButtons, m_selectableDialogueLabels, m_DialogueOptions, path);
//}

//void SaveGame::clearDialogue()
//{
//	m_DialogueOptions.clear();
//	m_selectableDialogueLabels.clear();
//	m_selectableDialogueButtons.clear();
//}

//void SaveGame::initText()
//{
//	m_textBox.setFont(m_font);
//	m_textBox.setCharacterSize(20.0f);
//	m_textBox.setFillColor(sf::Color::Black);
//	m_textBox.setPosition(450.0f, 100.0f);
//}

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
	sf::Vector2f pixelPos = sf::Vector2f(sf::Mouse::getPosition(t_window).x, sf::Mouse::getPosition(t_window).y);
	for (int i = 0; i < m_saveAndCancelButtons.size(); i++)
	{
		if (m_saveAndCancelButtons.at(i)->getButtonSprite().getGlobalBounds().contains(pixelPos))
		{
			m_saveAndCancelButtons.at(i)->highlighted();
			if (t_event.type == sf::Event::MouseButtonReleased)
			{
				if (t_event.mouseButton.button == sf::Mouse::Left)
				{
					if (m_saveAndCancelButtons.at(i)->getButtonLabel()->getTextString() == "Save")
					{
						//m_gameState->setState(State::SAVING);
						//if (saving)
						//{

							//saving = false;

							std::string projectDirectory = fs::current_path().string() + "\\Games";
							std::cout << projectDirectory << std::endl;
							std::string folderName = m_mainTitle->GetText();
							std::string folderPath = projectDirectory + "\\" + folderName;

							if (!fs::exists(folderPath))
							{
								fs::create_directory(folderPath);
								// save file name here
								//saving = false;
								std::ofstream out((folderPath +"/") + "mainTitle.txt");
								out << m_mainTitle->GetText();
								out.close();
								std::ofstream out2((folderPath + "/") + "subTitle.txt");
								out2 << m_subTitle->GetText();
								out2.close();
								//m_popUpBox.setPopUpEnabled();
							}
							else
							{
								m_popUpBox.setPopUpEnabled();
								unsigned lines = 0;
								std::string line_content;
								std::string lineContentAppended;
								std::ifstream my_file("PopUpMessages/fileExists.txt");

								while (std::getline(my_file, line_content)) {
									lines++;


									lineContentAppended.append(line_content);
									lineContentAppended.append("\n");


									//std::cout << "Line: " << lines << " content: " << line_content << std::endl;
								}

								my_file.close();

								//m_popUpBox.setPopUpBoxText(lineContentAppended);

								for (int i = 0; i < 2; i++)
								{

									m_popUpButtons.at(i)->setButtonPosition(
										sf::Vector2f{ m_popUpBox.getPopUpBoxPosition().x + (m_popUpBox.getPopUpBoxBounds().x / 2) + (i * 200) - 100,
														m_popUpBox.getPopUpBoxPosition().y + (m_popUpBox.getPopUpBoxBounds().y) - (m_popUpButtons.at(i)->getButtonSprite().getGlobalBounds().height) });
									m_popUpButtonLabels.at(i)->setTextPosition(m_popUpButtons.at(i)->getButtonPosition());
								}
							}

							//std::ofstream out("Games/" + m_mainTitle->GetText() + ".txt");
							//out << m_subTitle->GetText();
							//out.close();
							//m_popUpBox.setPopUpEnabled();
						//}
						//clearDialogue();
						//refreshDialogue();
					}
					else if (m_saveAndCancelButtons.at(i)->getButtonLabel()->getTextString() == "Cancel")
					{
						m_enabled = false;
						m_gameState->setState(State::ROOM_TEST);
					}
				}
			}
		}
		else
		{
			m_saveAndCancelButtons.at(i)->setButtonTexture();
		}
	}


	if (m_mainTitle->GetInputField().getGlobalBounds().contains(pixelPos))
	{
		if (t_event.type == sf::Event::MouseButtonReleased)
		{
			if (t_event.mouseButton.button == sf::Mouse::Left)
			{
				m_mainTitle->SetSelected(true);
				m_subTitle->SetSelected(false);
			}
		}
	}
	if (m_subTitle->GetInputField().getGlobalBounds().contains(pixelPos))
	{
		if (t_event.type == sf::Event::MouseButtonReleased)
		{
			if (t_event.mouseButton.button == sf::Mouse::Left)
			{
				m_subTitle->SetSelected(true);
				m_mainTitle->SetSelected(false);
			}
		}
	}


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

void SaveGame::setPopUpButtons(sf::Font& t_arialFont)
{
	for (int i = 0; i < 2; i++)
	{
		m_popUpButtons.push_back(new Button());
		m_popUpButtons.at(i)->setButtonPosition(
			sf::Vector2f{ m_popUpBox.getPopUpBoxPosition().x + (m_popUpBox.getPopUpBoxBounds().x / 2),
							m_popUpBox.getPopUpBoxPosition().y });
		m_popUpButtons.at(i)->resize(.5f, 0.5f);

		m_popUpButtonLabels.push_back(new Label(t_arialFont));
		m_popUpButtonLabels.at(i)->setTextColor(sf::Color::White);
		m_popUpButtonLabels.at(i)->setTextOutlineColor(sf::Color::Black);
		//m_labels.at(i)->setTextSize(11.0f);
		m_popUpButtonLabels.at(i)->setTextOutlineThickness(2.0f);
		m_popUpButtonLabels.at(i)->setTextPosition(m_popUpButtons.at(i)->getButtonPosition());
	}
	m_popUpButtonLabels.at(0)->setText("Cancel");
	m_popUpButtonLabels.at(1)->setText("Continue");
}

void SaveGame::render(sf::RenderWindow* t_window)
{
	if (m_enabled)
	{
		t_window->draw(m_backGround);

		m_mainTitle->render(t_window);
		m_subTitle->render(t_window);
		for (int i = 0; i < m_saveAndCancelButtons.size(); ++i)
		{
			m_saveAndCancelButtons.at(i)->render(t_window);
			m_labels.at(i)->render(t_window);
		}
		m_titleText->render(t_window);
		m_subTitleText->render(t_window);
	}

	if (m_popUpBox.isEnabled())
	{
		m_popUpBox.render(t_window);
		for (int i = 0; i < m_popUpButtons.size(); ++i)
		{
			m_popUpButtons.at(i)->render(t_window);
			m_popUpButtonLabels.at(i)->render(t_window);
		}
	}
	
}