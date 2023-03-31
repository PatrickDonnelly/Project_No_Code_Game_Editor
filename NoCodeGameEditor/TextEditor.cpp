#include "TextEditor.h"
#include <iostream>
#include <fstream>

TextEditor::TextEditor()
{

}

TextEditor::TextEditor(sf::Font& t_font, GameState* t_currentGameState)
{
	m_dialogueBox = new DialogueBox(t_font);
	m_previewDialogueCheckBox = new CheckBox("Preview Dialogue");
	m_popUpBox = PopUp(&t_font);
	m_mainBody = new InputField(t_font, true, 0);
	m_title = new InputField(t_font, false, 25);
	std::string path = "Dialogue/";

	m_gameState = t_currentGameState;
	m_font = t_font;
	initInputFields();
	initText();
	setUpTextEditorButtons(t_font);
	setPopUpButtons(t_font);
	loadDialogue();
	setUpPlaceableItemsButtons(m_font, m_rowsDialogue, m_selectableDialogueButtons, m_selectableDialogueLabels, m_DialogueOptions, path);
	for (int i = 0; i < 2; ++i)
	{
		m_prevNextbuttons.push_back(new Button());
		m_prevNextbuttons.at(i)->setButtonPosition(sf::Vector2f(60.0f, 175 + (i * 640)));
		m_prevNextbuttons.at(i)->resize(0.1f, 0.4f);
	}
}

void TextEditor::loadDialogue()
{
	std::string path = "Dialogue/";
	for (auto& entry : fs::directory_iterator(path))
	{
		std::string temp = entry.path().filename().string();
		temp.resize(temp.size() - 4);
		m_DialogueOptions.push_back(temp);
	}
}

void TextEditor::refreshDialogue()
{
	std::string path = "Dialogue/";
	loadDialogue();
	setUpPlaceableItemsButtons(m_font, m_rowsDialogue, m_selectableDialogueButtons, m_selectableDialogueLabels, m_DialogueOptions, path);
}

void TextEditor::clearDialogue()
{
	m_DialogueOptions.clear();
	m_selectableDialogueLabels.clear();
	m_selectableDialogueButtons.clear();
}

void TextEditor::setVisibleRow(sf::Event t_event, sf::RenderWindow& t_window, int t_rows, std::vector<std::vector<Button*>>& t_objectButtons)
{
	for (int i = 0; i < m_prevNextbuttons.size(); ++i)
	{
		if (m_prevNextbuttons.at(i)->getButtonSprite().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
		{
			m_prevNextbuttons.at(i)->highlighted();
			if (t_event.type == sf::Event::MouseButtonReleased)
			{
				if (t_event.key.code == sf::Mouse::Left)
				{
					if (i == 0)
					{
						m_currentRowIndex -= 1;
					}
					else
					{
						m_currentRowIndex += 1;
					}
					if (m_currentRowIndex >= t_rows)
					{
						m_currentRowIndex = 0;
					}
					else if (m_currentRowIndex < 0)
					{
						m_currentRowIndex = t_rows - 1;
					}
					//m_currentRowText.setString(std::to_string(m_currentRowIndex + 1) + " / " + std::to_string(t_rows));
					std::vector<std::vector<Button>>::iterator row;
					std::vector<Button>::iterator col;
					int rowIndex = 0;
					int colIndex = 0;

					for (auto& row : t_objectButtons)
					{
						colIndex = 0;
						for (auto& col : row)
						{
							if (m_currentRowIndex == rowIndex)
							{
								t_objectButtons.at(m_currentRowIndex).at(colIndex)->setEnabled(true);
							}
							else
							{
								t_objectButtons.at(rowIndex).at(colIndex)->setEnabled(false);
							}
							colIndex++;
						}
						rowIndex++;
					}
				}
			}
		}
		else
		{
			m_prevNextbuttons.at(i)->setButtonTexture();
		}
	}
	//std::cout << m_currentRowIndex << std::endl;
}

void TextEditor::setUpPlaceableItemsButtons(sf::Font& t_arialFont, int& t_rows, std::vector<std::vector<Button*>>& t_objectButtons, std::vector<std::vector<Label*>>& t_labels, std::vector<std::string> t_objects, std::string t_path)
{
	int buttonsMade = 0;
	int maxButtons = t_objects.size();
	int noOfButtonsPerRow = 20;
	int noOfRows = 0;

	if (t_objects.size() % noOfButtonsPerRow != 0)
	{
		noOfRows = (t_objects.size() / noOfButtonsPerRow) + 1;
		t_rows = noOfRows;
	}
	else
	{
		noOfRows = t_objects.size() / noOfButtonsPerRow;
		t_rows = noOfRows;
	}

	for (int i = 0; i < noOfRows; i++)
	{
		std::vector<Button*> row;
		std::vector<Label*> rowLabels;
		for (int j = 0; j < noOfButtonsPerRow; j++)
		{
			if (buttonsMade < maxButtons)
			{
				buttonsMade++;
				row.push_back(new Button());
				rowLabels.push_back(new Label(t_arialFont));
			}

		}
		t_objectButtons.push_back(row);
		t_labels.push_back(rowLabels);
	}
	std::vector<std::vector<Button>>::iterator row;
	std::vector<Button>::iterator col;
	int rowIndex = 0;
	int colIndex = 0;

	for (auto& row : t_objectButtons)
	{
		colIndex = 0;
		for (auto& col : row)
		{
			if (rowIndex == 0)
			{
				col->setEnabled(true);
			}
			col->setButtonPosition(sf::Vector2f(50.0f, 210.0f + (colIndex * 30)));
			col->resize(0.75f, 0.4f);
			colIndex++;
		}
		rowIndex++;
	}

	std::vector<std::vector<Label>>::iterator rowLabels;
	std::vector<Label>::iterator colLabels;
	colIndex = 0;
	rowIndex = 0;
	int index = 0;
	for (auto& rowLabels : t_labels)
	{
		colIndex = 0;
		for (auto& colLabels : rowLabels)
		{
			colLabels->setTextColor(sf::Color::White);
			colLabels->setTextOutlineColor(sf::Color::Black);
			colLabels->setTextSize(14.0f);
			colLabels->setTextOutlineThickness(2.0f);
			colLabels->setTexturePosition(t_objectButtons.at(rowIndex).at(colIndex)->getButtonPosition());
			colLabels->setTextPosition(sf::Vector2f(t_objectButtons.at(rowIndex).at(colIndex)->getButtonPosition().x + 10, t_objectButtons.at(rowIndex).at(colIndex)->getButtonPosition().y));
			colLabels->setText(t_objects.at(index));
			colIndex++;
			index++;
			//std::cout << colLabels->getTextPosition().x << " : " << colLabels->getTextPosition().y << std::endl;
		}
		rowIndex++;
	}
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

	for (int i = 0; i < 2; ++i)
	{
		m_prevNextbuttons.at(i)->render(t_window);
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

	std::vector<std::vector<Button>>::iterator row;
	std::vector<Button>::iterator col;
	std::vector<std::vector<std::string>>::iterator rowLabel;
	std::vector<std::string>::iterator colLabel;
	int rowIndex = 0;

	for (const auto& row : m_selectableDialogueButtons)
	{
		for (const auto& col : row)
		{
			if (rowIndex == m_currentRowIndex)
			{
				//std::cout << "here" << std::endl;
				//t_window->draw(col->getButtonSprite());
				col->render(t_window);
			}
		}
		rowIndex++;
	}

	rowIndex = 0;
	for (const auto& rowLabel : m_selectableDialogueLabels)
	{
		for (const auto& colLabel : rowLabel)
		{
			if (rowIndex == m_currentRowIndex)
			{
				//t_window->draw(col->getButtonSprite());
				colLabel->render(t_window);
			}
		}
		rowIndex++;
	}

	m_previewDialogueCheckBox->render(t_window);
	m_dialogueBox->render(t_window);
}

void TextEditor::processTextEditorButtons(sf::Event t_event, sf::RenderWindow& t_window)
{
	if (m_gameState->m_currentGameState == State::CREATE_DIALOGUE)
	{
		if (m_previewDialogueCheckBox->getCheckBoxBounds().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
		{
			//col->highlighted();
			if (t_event.type == sf::Event::MouseButtonReleased)
			{
				if (t_event.mouseButton.button == sf::Mouse::Left)
				{
					m_previewDialogueCheckBox->setEnabled();
					m_previewDialogueCheckBox->toggleColor();

					m_dialogueBox->setEnabled();
				}
			}
		}


		setVisibleRow(t_event, t_window, m_rowsDialogue, m_selectableDialogueButtons);


		std::vector<std::vector<Button>>::iterator row;
		std::vector<Button>::iterator col;
		int rowIndex = 0;
		int colIndex = 0;

		for (const auto& row : m_selectableDialogueButtons)
		{

			for (const auto& col : row)
			{

				if (col->getButtonSprite().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
				{
					col->highlighted();
					if (t_event.type == sf::Event::MouseButtonReleased)
					{
						if (t_event.mouseButton.button == sf::Mouse::Left)
						{
							if (col->isEnabled())
							{
								//deselectButtons(t_objectButtons);
								std::vector<std::vector<Button>>::iterator temprow;
								std::vector<Button>::iterator tempcol;
								for (const auto& temprow : m_selectableDialogueButtons)
								{
									for (const auto& tempcol : temprow)
									{
										col->setSelected(false);
										if (!col->getSelected())
										{
											//std::cout << ("White") << std::endl;
											col->setColor(sf::Color::White);
										}
									}
								}
								fileName = m_selectableDialogueLabels.at(rowIndex).at(colIndex)->getText().getString();
								col->setSelected(true);

								if (col->getSelected())
								{
									col->setColor(sf::Color::Blue);
									//std::cout << ("Red") << std::endl;

									// send selected object to grid
									//m_grid->setSelectedObject(t_path, t_labels.at(rowIndex).at(colIndex)->getText().getString());
								}

							}
						}
					}
				}
				else
				{
					col->setButtonTexture();
				}

				colIndex += 1;
			}
			colIndex = 0;
			rowIndex += 1;
		}

		
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
									saving = true;
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
									std::cout << "File does not exist" << std::endl;
									std::ofstream out("Dialogue/" +m_title->GetText() + ".txt");
									out << m_mainBody->GetText();
									out.close();
									clearDialogue();
									refreshDialogue();
								}
							}
							else if (m_textEditorLabels.at(i)->getTextString() == "Delete")
							{
								saving = false;
								//std::cout << "File exists" << std::endl;
								m_popUpBox.setPopUpEnabled();

								unsigned lines = 0;
								std::string line_content;
								std::string lineContentAppended;
								std::ifstream my_file("PopUpMessages/deleteFile.txt");


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
							else if (m_textEditorLabels.at(i)->getTextString() == "Exit")
							{
								m_gameState->setState(State::ROOM_PLACE_OBJECTS);
							}
							else if (m_textEditorLabels.at(i)->getTextString() == "Clear")
							{
								std::cout << "Clear Pressed" << std::endl;
								m_mainBody->ClearText();
								m_title->ClearText();
								m_dialogueBox->splitString(m_mainBody->GetText());
							}
							else if (m_textEditorLabels.at(i)->getTextString() == "Load")
							{

								unsigned lines = 0;
								std::string line_content;
								std::string lineContentAppended;
								
								
								std::ifstream my_file("Dialogue/" + fileName+ ".txt");

								std::cout << "Dialogue/" << m_title->GetText() << ".txt" << std::endl;
								while (std::getline(my_file, line_content)) {
									lines++;

									lineContentAppended.append(line_content);
									lineContentAppended.append("\n");
									m_mainBody->ClearText();

									std::cout << "Line: " << lines << " content: " << line_content << std::endl;
								}
								m_mainBody->SetString(lineContentAppended);
								m_title->SetString(fileName);
								m_dialogueBox->splitString(m_mainBody->GetText());
								my_file.close();
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
							if (m_popUpButtonLabels.at(i)->getTextString() == "Continue")
							{
								if (saving)
								{
									saving = false;
									std::ofstream out("Dialogue/" + m_title->GetText() + ".txt");
									out << m_mainBody->GetText();
									out.close();
									m_popUpBox.setPopUpEnabled();
								}
								else
								{
									std::cout << "Deleting" << std::endl;
									std::string filename = "Dialogue/" + m_title->GetText() + ".txt";
									remove(filename.c_str());
									m_mainBody->ClearText();
									m_title->ClearText();
									m_popUpBox.setPopUpEnabled();
								}
								clearDialogue();
								refreshDialogue();
								
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

void TextEditor::setUpTextEditorButtons(sf::Font& t_arialFont)
{
	for (int i = 0; i < 5; i++)
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
	m_textEditorLabels.at(4)->setText("Delete");

}

void TextEditor::setPopUpButtons(sf::Font& t_arialFont)
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

bool TextEditor::isEnabled()
{
	return m_enabled;
}