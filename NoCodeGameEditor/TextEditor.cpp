#include "TextEditor.h"
#include <iostream>
#include <fstream>

TextEditor::TextEditor()
{

}

TextEditor::TextEditor(sf::Font& t_font, GameState* t_currentGameState)
{
	m_popUpBox = PopUp(&t_font);
	m_mainBody = new InputField(t_font);
	m_title = new InputField(t_font);

	m_gameState = t_currentGameState;
	m_font = t_font;
	initInputFields();
	initText();
	setUpTextEditorButtons(t_font);
	setPopUpButtons(t_font);
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

void TextEditor::initInputFields()
{
	m_mainBody->SetInputFieldSize(sf::Vector2f(1600.0f, 600.0f), sf::Vector2f(160.0f, 200.0f));
	m_title->SetInputFieldSize(sf::Vector2f(600.0f, 50.0f), sf::Vector2f(160.0f, 75.0f));

	m_backGround.setSize(sf::Vector2f(1640.0f, 800.0f));
	m_backGround.setPosition(140.0f, 20.0f);
	m_backGround.setOutlineThickness(4.0f);
	m_backGround.setOutlineColor(sf::Color(sf::Color(140, 140, 140)));
	m_backGround.setFillColor(sf::Color(sf::Color(204, 204, 204)));
}

void TextEditor::render(sf::RenderWindow* t_window)
{
	//t_window->draw(m_dialogueBoxSprite);
	t_window->draw(m_backGround);

	m_mainBody->render(t_window);
	m_title->render(t_window);

	t_window->draw(m_textBox);
	for (int i = 0; i < m_textEditorButtons.size(); ++i)
	{
		m_textEditorButtons.at(i)->render(t_window);
		m_textEditorLabels.at(i)->render(t_window);
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

void TextEditor::processTextEditorButtons(sf::Event t_event, sf::RenderWindow& t_window)
{
	if (m_gameState->m_currentGameState == State::CREATE_DIALOGUE)
	{
		if (!m_popUpBox.isEnabled())
		{
			if (m_mainBody->GetInputField().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
			{
				if (t_event.type == sf::Event::MouseButtonReleased)
				{
					if (t_event.mouseButton.button == sf::Mouse::Left)
					{
						m_mainBody->SetSelected(true);
						m_title->SetSelected(false);
					}
				}
			}
			if (m_title->GetInputField().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
			{
				if (t_event.type == sf::Event::MouseButtonReleased)
				{
					if (t_event.mouseButton.button == sf::Mouse::Left)
					{
						m_title->SetSelected(true);
						m_mainBody->SetSelected(false);
					}
				}
			}





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
								// creating an ifstream object named file
								std::ifstream file;

								// opening the file
								file.open("Dialogue/" + m_title->GetText() + ".txt");
								if (file)
								{

									//std::cout << "File exists" << std::endl;
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

									m_popUpBox.setPopUpBoxText(lineContentAppended);

									for (int i = 0; i < 2; i++)
									{

										m_popUpButtons.at(i)->setButtonPosition(
											sf::Vector2f{ m_popUpBox.getPopUpBoxPosition().x + (m_popUpBox.getPopUpBoxBounds().x / 2) + (i * 200) - 100,
															m_popUpBox.getPopUpBoxPosition().y + (m_popUpBox.getPopUpBoxBounds().y) - (m_popUpButtons.at(i)->getButtonSprite().getGlobalBounds().height) });
										m_popUpButtonLabels.at(i)->setTextPosition(m_popUpButtons.at(i)->getButtonPosition());
									}
								}
								else
								{
									// printing the error message
									std::cout << "File does not exists" << std::endl;
									std::ofstream out("Dialogue/" +m_title->GetText() + ".txt");
									out << m_mainBody->GetText();
									out.close();
								}
							}
							else if (m_textEditorLabels.at(i)->getTextString() == "Exit")
							{
								m_gameState->setState(State::ROOM_PLACE_OBJECTS);
							}
							else if (m_textEditorLabels.at(i)->getTextString() == "Clear")
							{
								std::cout << "Clear Pressed" << std::endl;
								if (m_mainBody->GetSelected())
								{
									std::cout << "Clearing main body" << std::endl;

									m_mainBody->ClearText();
								}
								else if (m_title->GetSelected())
								{
									std::cout << "Clearing title" << std::endl;

									m_title->ClearText();
								}

							}
							else if (m_textEditorLabels.at(i)->getTextString() == "Load")
							{

								unsigned lines = 0;
								std::string line_content;
								std::string lineContentAppended;
								
								std::ifstream my_file("Dialogue/" + m_title->GetText()+ ".txt");

								std::cout << "Dialogue/" << m_title->GetText() << ".txt" << std::endl;
								while (std::getline(my_file, line_content)) {
									lines++;

									lineContentAppended.append(line_content);
									lineContentAppended.append("\n");
									m_mainBody->ClearText();

									std::cout << "Line: " << lines << " content: " << line_content << std::endl;
								}
								m_mainBody->SetString(lineContentAppended);
								//m_text.str(lineContentAppended);
								//m_textBox.setString(lineContentAppended);
								my_file.close();


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
		else
		{
			for (int i = 0; i < m_popUpButtons.size(); i++)
			{
				if (m_popUpButtons.at(i)->getButtonSprite().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
				{
					m_popUpButtons.at(i)->highlighted();
					if (t_event.type == sf::Event::MouseButtonReleased)
					{
						if (t_event.mouseButton.button == sf::Mouse::Left)
						{
							if (m_popUpButtonLabels.at(i)->getTextString() == "Save")
							{
								
								std::ofstream out("Dialogue/" + m_title->GetText() + ".txt");
								out << m_mainBody->GetText();
								out.close();
								m_popUpBox.setPopUpEnabled();

								
							}
							else if (m_popUpButtonLabels.at(i)->getTextString() == "Cancel")
							{
								m_popUpBox.setPopUpEnabled();
							}
						}
					}
				}
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

void TextEditor::setPopUpButtons(sf::Font t_arialFont)
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
	m_popUpButtonLabels.at(1)->setText("Save");
}

bool TextEditor::isEnabled()
{
	return m_enabled;
}