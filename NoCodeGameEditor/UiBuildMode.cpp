#include "UiBuildMode.h"

void UiBuildMode::setUpPlaceableItemsButtons(sf::Font t_arialFont, std::vector<std::vector<Button*>>& t_objectButtons, std::vector<std::vector<Label*>>& t_labels, std::vector<std::string> t_objects)
{
	int buttonsMade = 0;
	int maxButtons = t_objects.size();
	int noOfButtonsPerRow = 6;
	int noOfRows = 0;

	if (t_objects.size() % noOfButtonsPerRow != 0)
	{
		noOfRows = (t_objects.size() / noOfButtonsPerRow) +1;
	}
	else
	{
		noOfRows = t_objects.size() / noOfButtonsPerRow;
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

	for ( auto& row : m_selectableFloorButtons)
	{

		colIndex = 0;
		for (auto& col : row)
		{
	


			//if (buttonsMade < maxButtons)
			//{
				//buttonsMade++;
				//t_objectButtons.at(i).at(j).push_back(new Button());
			col->setButtonPosition(sf::Vector2f(768.0f + (colIndex * 64), 200.0f + (rowIndex * 80)));
			col->resize(0.25, 1.0f);

			colIndex++;


		}
		rowIndex++;
	}

	std::vector<std::vector<Label>>::iterator rowLabels;
	std::vector<Label>::iterator colLabels;
	colIndex = 0;
	rowIndex = 0;
	int index = 0;
	for (auto& rowLabels : m_selectableFloorLabels)
	{
		colIndex = 0;
		for (auto& colLabels : rowLabels)
		{


			colLabels->setTextColor(sf::Color::White);
			colLabels->setTextOutlineColor(sf::Color::Black);
			colLabels->setTextSize(11.0f);
			colLabels->setTextOutlineThickness(2.0f);
			colLabels->setTexturePosition(t_objectButtons.at(rowIndex).at(colIndex)->getButtonPosition());
			colLabels->setTextPosition(sf::Vector2f(t_objectButtons.at(rowIndex).at(colIndex)->getButtonPosition().x + 2, t_objectButtons.at(rowIndex).at(colIndex)->getButtonPosition().y + 24));
			colLabels->setText(t_objects.at(index));
			colLabels->setLabelSprite(t_objects.at(index));
			colIndex++;
			index++;
			std::cout << colLabels->getTextPosition().x << " : " << colLabels->getTextPosition().y << std::endl;
		}
		rowIndex++;
	}
}

//void UiBuildMode::setUpLabels(std::vector<Button>::iterator t_col, std::vector<Label*>& t_labels, std::vector<std::vector<Button*>>& t_objectButtons, ststd::vector<std::string> t_objects)
//{
//	int i = t_row;
//	int j = t_col;
//	if (i == 1)
//	{
//		j = t_col + 6;
//	}
//	else if (i == 2)
//	{
//		j = t_col + 12;
//	}
//
//
//	t_labels.at(11)->setTextColor(sf::Color::White);
//	t_labels.at(11)->setTextOutlineColor(sf::Color::Black);
//	t_labels.at(11)->setTextSize(11.0f);
//	t_labels.at(11)->setTextOutlineThickness(2.0f);
//	t_labels.at(11)->setTexturePosition(t_col->getButtonPosition());
//	t_labels.at(11)->setTextPosition(sf::Vector2f(t_col->getButtonPosition().x + 2, t_col->getButtonPosition().y + 24));
//	t_labels.at(11)->setText(t_objects.at(0));
//	t_labels.at(11)->setLabelSprite(t_objects.at(0));
//	std::cout << t_labels.at(j)->getTextPosition().x << " : " << t_labels.at(j)->getTextPosition().y << std::endl;
//}

void UiBuildMode::setUpGridFunctionButtons(sf::Font t_arialFont)
{
	for (int i = 0; i < 4; i++)
	{
		if (i == 2)
		{
			m_buildButtons.push_back(Button());
			m_buildButtons.at(i).setButtonPosition(sf::Vector2f{820.0f, 1000.0f});
		}
		else if (i == 3)
		{
			m_buildButtons.push_back(Button());
			m_buildButtons.at(i).setButtonPosition(sf::Vector2f{820.0f + 280.0f, 1000.0f});
		}
		else 
		{
			m_buildButtons.push_back(Button());
			m_buildButtons.at(i).setButtonPosition(sf::Vector2f{ 820.0f + (i * 280), 900.0f });
		}
		m_buildButtonLabels.push_back(new Label(t_arialFont));
		m_buildButtonLabels.at(i)->setTextPosition(m_buildButtons.at(i).getButtonPosition());
	}
	m_buildButtonLabels.at(0)->setText("Clear Grid");
	m_buildButtonLabels.at(1)->setText("Generate Room");
	m_buildButtonLabels.at(2)->setText("-");
	m_buildButtonLabels.at(3)->setText("+");
}

void UiBuildMode::setUpTestBuildButtons(sf::Font t_arialFont)
{
	for (int i = 0; i < 3; i++)
	{
		m_testingButtons.push_back(Button());
		m_testingButtons.at(i).setButtonPosition(sf::Vector2f{820.0f + (i * 280), 900.0f});
		if (i == 2)
		{
			m_testingButtons.at(i) = Button();
			m_testingButtons.at(i).setButtonPosition(sf::Vector2f{820.0f, 1000.0f});
		}
		m_testingButtonLabels.push_back(new Label(t_arialFont));
		m_testingButtonLabels.at(i)->setTextPosition(m_buildButtons.at(i).getButtonPosition());
	}
	m_testingButtonLabels.at(0)->setText("Place Objects");
	m_testingButtonLabels.at(1)->setText("Save Room");
	m_testingButtonLabels.at(2)->setText("Start Over");
}

void UiBuildMode::setUpPlacementModeButtons(sf::Font t_arialFont)
{
	for (int i = 0; i < 3; i++)
	{
		m_placementOptions.push_back(Button());
		m_placementOptions.at(i).setButtonPosition(sf::Vector2f{ 820.0f + (i * 280), 900.0f });
		if (i == 2)
		{
			m_placementOptions.at(i) = Button();
			m_placementOptions.at(i).setButtonPosition(sf::Vector2f{ 820.0f, 1000.0f });
		}
		m_placementOptionsLabels.push_back(new Label(t_arialFont));
		m_placementOptionsLabels.at(i)->setTextPosition(m_placementOptions.at(i).getButtonPosition());
	}
	m_placementOptionsLabels.at(0)->setText("Rebuild Room");
	m_placementOptionsLabels.at(1)->setText("Test Room");
	m_placementOptionsLabels.at(2)->setText("Clear Room");
}

void UiBuildMode::setUpCategoryButtons(sf::Font t_arialFont)
{
	for (int i = 0; i < 5; i++)
	{
		m_objectCategoryButtons.push_back(new Button());
		m_objectCategoryButtons.at(i)->setButtonPosition(sf::Vector2f{ 490.0f + (i * m_objectCategoryButtons.at(i)->getButtonSprite().getGlobalBounds().width), 100.0f});
		m_objectCategoryButtons.at(i)->resize(1.0f, 0.5f);

		m_objectCategoryLabels.push_back(new Label(t_arialFont));
		m_objectCategoryLabels.at(i)->setTextColor(sf::Color::White);
		m_objectCategoryLabels.at(i)->setTextOutlineColor(sf::Color::Black);
		//m_objectCategoryLabels.at(i)->setTextSize(11.0f);
		m_objectCategoryLabels.at(i)->setTextOutlineThickness(2.0f);
		m_objectCategoryLabels.at(i)->setTextPosition(m_objectCategoryButtons.at(i)->getButtonPosition());
	}
	m_objectCategoryLabels.at(0)->setText("Walls");
	m_objectCategoryLabels.at(1)->setText("Terrain");
	m_objectCategoryLabels.at(2)->setText("Enemies");
	m_objectCategoryLabels.at(3)->setText("Items");
	m_objectCategoryLabels.at(4)->setText("Decorations");

}

void UiBuildMode::setUpTextureRoomButtons(sf::Font t_arialFont)
{
	for (int i = 0; i < 6; i++)
	{
		m_textureRoomButtons.push_back(Button());
		m_textureRoomButtons.at(i).setButtonPosition(sf::Vector2f{ 768.0f + (i * 64), 200.0f });
		m_textureRoomButtons.at(i).resize(0.25, 1.0f);

		m_textureRoomLabels.push_back(new Label(t_arialFont));
		m_textureRoomLabels.at(i)->setTextColor(sf::Color::White);
		m_textureRoomLabels.at(i)->setTextOutlineColor(sf::Color::Black);
		m_textureRoomLabels.at(i)->setTextSize(11.0f);
		m_textureRoomLabels.at(i)->setTextOutlineThickness(2.0f);
		m_textureRoomLabels.at(i)->setTexturePosition(m_selectableObjects.at(i).getButtonPosition());
		m_textureRoomLabels.at(i)->setTextPosition(sf::Vector2f(m_selectableObjects.at(i).getButtonPosition().x + 2, m_selectableObjects.at(i).getButtonPosition().y + 24));
	}
	m_textureRoomLabels.at(0)->setText("Grass");
	m_textureRoomLabels.at(0)->setLabelSprite(m_texturedLabels.at(0)->getText().getString());
	m_textureRoomLabels.at(1)->setText("Dirt");
	m_textureRoomLabels.at(1)->setLabelSprite(m_texturedLabels.at(1)->getText().getString());
	m_textureRoomLabels.at(2)->setText("Concrete");
	m_textureRoomLabels.at(2)->setLabelSprite(m_texturedLabels.at(2)->getText().getString());
	m_textureRoomLabels.at(3)->setText("Brick");
	m_textureRoomLabels.at(3)->setLabelSprite(m_texturedLabels.at(3)->getText().getString());
	m_textureRoomLabels.at(4)->setText("Stone");
	m_textureRoomLabels.at(4)->setLabelSprite(m_texturedLabels.at(4)->getText().getString());
	m_textureRoomLabels.at(5)->setText("Wood");
	m_textureRoomLabels.at(5)->setLabelSprite(m_texturedLabels.at(5)->getText().getString());
}

UiBuildMode::UiBuildMode(sf::Font t_arialFont, Grid* t_grid, GameState* t_currentGameState)
{
	m_gameState = t_currentGameState;
	m_grid = t_grid;
	m_arialFont = t_arialFont;

	std::string path = "ASSETS/IMAGES/Terrain/Grass/";
	for (auto& entry : fs::directory_iterator(path))
	{
		std::string temp = entry.path().filename().string();
		temp.resize(temp.size() - 4);
		m_floors.push_back(temp);
	}






	setUpPlaceableItemsButtons(m_arialFont, m_selectableFloorButtons, m_selectableFloorLabels, m_floors);
	setUpPlacementModeButtons(m_arialFont);
	setUpCategoryButtons(m_arialFont);
	setUpGridFunctionButtons(m_arialFont);
	setUpTestBuildButtons(m_arialFont);
	//setUpTextureRoomButtons(m_arialFont);
}

UiBuildMode::UiBuildMode()
{
}

UiBuildMode::~UiBuildMode()
{
}

void UiBuildMode::processBuildRoomButtonInput(sf::Event t_event, sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_buildButtons.size(); i++)
	{
		if (m_buildButtons.at(i).getButtonSprite().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
		{
			m_buildButtons.at(i).highlighted();
			if (t_event.type == sf::Event::MouseButtonReleased)
			{
				if (t_event.mouseButton.button == sf::Mouse::Left)
				{
					if (m_buildButtonLabels.at(i)->getTextString() == "Clear Grid")
					{
						m_grid->regenerateGrid();
					}
					else if (m_buildButtonLabels.at(i)->getTextString() == "Generate Room")
					{
						m_grid->checkRoomValidity();
					}
					else if (m_buildButtonLabels.at(i)->getTextString() == "-")
					{
						m_grid->decreaseGridSize();
					}
					else if (m_buildButtonLabels.at(i)->getTextString() == "+")
					{
						m_grid->increaseGridSize();
					}
				}
			}
		}
		else
		{
			m_buildButtons.at(i).setButtonTexture();
		}
	}
}

void UiBuildMode::processPlaceObjectsButtonInput(sf::Event t_event, sf::RenderWindow& t_window)
{



	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (m_selectableFloorButtons.at(i).at(j)->getButtonSprite().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
			{
				if (t_event.type == sf::Event::MouseButtonReleased)
				{
					if (t_event.mouseButton.button == sf::Mouse::Left)
					{
						for (int k = 0; k < 2; k++)
						{
							for (int l = 0; l < 6; l++)
							{
								m_selectableFloorButtons.at(k).at(l)->setSelected(false);
							}
						}
						m_selectableFloorButtons.at(i).at(j)->setSelected(true);

						if (m_selectableFloorButtons.at(i).at(j)->getSelected())
						{
							m_selectableFloorButtons.at(i).at(j)->setColor(sf::Color::Red);
							// send selected object to grid
							m_grid->setSelectedObject(m_selectableFloorLabels.at(i).at(j)->getText().getString());
						}
					}
				}
			}
			if (!m_selectableFloorButtons.at(i).at(j)->getSelected())
			{
				m_selectableFloorButtons.at(i).at(j)->setColor(sf::Color::White);
			}
		}
	}













	for (int i = 0; i < m_placementOptions.size(); i++)
	{
		if (m_placementOptions.at(i).getButtonSprite().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
		{
			m_placementOptions.at(i).highlighted();
			if (t_event.type == sf::Event::MouseButtonReleased)
			{
				if (t_event.mouseButton.button == sf::Mouse::Left)
				{
					if (m_placementOptionsLabels.at(i)->getTextString() == "Rebuild Room")
					{
						m_grid->regenerateGrid();
						m_gameState->m_currentGameState = State::ROOM_BUILD;
					}
					else if (m_placementOptionsLabels.at(i)->getTextString() == "Test Room")
					{
						m_gameState->m_currentGameState = State::ROOM_TEST;
						for (int j = 0; j < m_grid->m_placedObjects.size(); ++j)
						{
							m_storePositions.push_back(m_grid->m_placedObjects.at(j)->getSprite()->getPosition());
						}
						// need to move player into scene here
					}
					else if (m_placementOptionsLabels.at(i)->getTextString() == "Clear Room")
					{
						m_grid->clearObjects();
					}
				}
			}
		}
		else
		{
			m_placementOptions.at(i).setButtonTexture();
		}
	}
}

void UiBuildMode::processTestRoomButtonInput(sf::Event t_event, sf::RenderWindow & t_window)
{
	for (int i = 0; i < m_testingButtons.size(); i++)
	{
		if (m_testingButtons.at(i).getButtonSprite().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
		{
			m_testingButtons.at(i).highlighted();
			if (t_event.type == sf::Event::MouseButtonReleased)
			{
				if (t_event.mouseButton.button == sf::Mouse::Left)
				{
					if (m_testingButtonLabels.at(i)->getTextString() == "Place Objects")
					{
						// Go back to placing objects
						// reset the objects position
						//cahnge state
						for (int j = 0; j < m_grid->m_placedObjects.size(); ++j)
						{
							m_grid->m_placedObjects.at(j)->getBounds()->setPosition(m_storePositions.at(j));
						}
						m_storePositions.clear();
						m_grid->m_playerSet = false;
						m_gameState->m_currentGameState = State::ROOM_PLACE_OBJECTS;

					}
					else if (m_testingButtonLabels.at(i)->getTextString() == "Save Room")
					{
						// save room here;
					}
					else if (m_testingButtonLabels.at(i)->getTextString() == "Start Over")
					{
						m_grid->regenerateGrid();
						m_gameState->m_currentGameState = State::ROOM_BUILD;
					}
				}
			}
		}
		else
		{
			m_testingButtons.at(i).setButtonTexture();
		}
	}
}

void UiBuildMode::processEvents(sf::Event t_event, sf::RenderWindow& t_window)
{
	sf::Event newEvent = t_event;
	if (m_gameState->m_currentGameState == State::ROOM_BUILD)
	{
		processBuildRoomButtonInput(t_event,t_window);
	}
	else if (m_gameState->m_currentGameState == State::ROOM_PLACE_OBJECTS)
	{
		processPlaceObjectsButtonInput(t_event,t_window);
	}
	else if (m_gameState->m_currentGameState == State::ROOM_TEST)
	{
		processTestRoomButtonInput(t_event, t_window);
	}	
}

void UiBuildMode::render(sf::RenderWindow* t_window)
{
	if (m_gameState->m_currentGameState == State::ROOM_BUILD)
	{
		for (int i = 0; i < m_buildButtons.size(); i++)
		{
			m_buildButtons.at(i).render(t_window);
			m_buildButtonLabels.at(i)->render(t_window);
		}
	}
	if (m_gameState->m_currentGameState == State::ROOM_TEXTURE)
	{
		for (int i = 0; i < m_textureRoomButtons.size(); i++)
		{
			m_textureRoomButtons.at(i).render(t_window);
			m_textureRoomLabels.at(i)->render(t_window);
		}
	}
	if (m_gameState->m_currentGameState == State::ROOM_PLACE_OBJECTS)
	{
		for (int i = 0; i < m_objectCategoryButtons.size(); i++)
		{
			m_objectCategoryButtons.at(i)->render(t_window);
			m_objectCategoryLabels.at(i)->render(t_window);
		}
		for (int i = 0; i < m_selectableObjects.size(); i++)
		{
			m_selectableObjects.at(i).render(t_window);
			m_texturedLabels.at(i)->render(t_window);
		}
		for (int i = 0; i < m_placementOptions.size(); i++)
		{
			m_placementOptions.at(i).render(t_window);
			m_placementOptionsLabels.at(i)->render(t_window);
		}

		std::vector<std::vector<Button>>::iterator row;
		std::vector<Button>::iterator col;


		for (const auto& row:m_selectableFloorButtons)
		{
			for (const auto& col:row)
			{
				//t_window->draw(col->getButtonSprite());
				col->render(t_window);
			}
		}

		std::vector<std::vector<std::string>>::iterator rowLabel;
		std::vector<std::string>::iterator colLabel;

		for (const auto& rowLabel : m_selectableFloorLabels)
		{
			for (const auto& colLabel : rowLabel)
			{
				//t_window->draw(col->getButtonSprite());
				colLabel->render(t_window);
			}
		}
	}
	if (m_gameState->m_currentGameState == State::ROOM_TEST)
	{
		for (int i = 0; i < m_testingButtons.size(); i++)
		{
			m_testingButtons.at(i).render(t_window);
			m_testingButtonLabels.at(i)->render(t_window);
		}
	}
}
