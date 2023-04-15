#include "UiBuildMode.h"

void UiBuildMode::setUpPlaceableItemsButtons(sf::Font& t_arialFont, int& t_rows, std::vector<std::vector<Button*>>& t_objectButtons, std::vector<std::vector<Label*>>& t_labels, std::vector<std::string> t_objects, std::string t_path)
{
	int buttonsMade = 0;
	int maxButtons = t_objects.size();
	int noOfButtonsPerRow = 16;
	int noOfRows = 0;

	if (t_objects.size() % noOfButtonsPerRow != 0)
	{
		noOfRows = (t_objects.size() / noOfButtonsPerRow) +1;
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

	for ( auto& row : t_objectButtons)
	{
		colIndex = 0;
		for (auto& col : row)
		{
			if (rowIndex == 0)
			{
				col->setEnabled(true);
			}
			col->setButtonPosition(sf::Vector2f(490.0f + (colIndex * 64), 960.0f));
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
	for (auto& rowLabels : t_labels)
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
			colLabels->setLabelSprite(t_objects.at(index), t_path);
			colIndex++;
			index++;
			//std::cout << colLabels->getTextPosition().x << " : " << colLabels->getTextPosition().y << std::endl;
		}
		rowIndex++;
	}
}

void UiBuildMode::setUpGridFunctionButtons(sf::Font& t_arialFont)
{
	for (int i = 0; i < 2; i++)
	{
		//if (i == 2)
		//{
		//	m_buildButtons.push_back(Button());
		//	m_buildButtons.at(i).setButtonPosition(sf::Vector2f{820.0f, 1000.0f});
		//}
		//else if (i == 3)
		//{
		//	m_buildButtons.push_back(Button());
		//	m_buildButtons.at(i).setButtonPosition(sf::Vector2f{820.0f + 280.0f, 1000.0f});
		//}
		//else 
		//{
			m_buildButtons.push_back(Button());
			m_buildButtons.at(i).setButtonPosition(sf::Vector2f{ 820.0f + (i * 280), 900.0f });
		//}
		m_buildButtonLabels.push_back(new Label(t_arialFont));
		m_buildButtonLabels.at(i)->setTextPosition(m_buildButtons.at(i).getButtonPosition());
	}
	m_buildButtonLabels.at(0)->setText("Clear Grid");
	m_buildButtonLabels.at(1)->setText("Generate Room");
	//m_buildButtonLabels.at(2)->setText("-");
	//m_buildButtonLabels.at(3)->setText("+");
}

void UiBuildMode::setUpTestBuildButtons(sf::Font& t_arialFont)
{
	for (int i = 0; i < 2; i++)
	{
		m_testingButtons.push_back(Button());
		m_testingButtons.at(i).setButtonPosition(sf::Vector2f{ 16 + m_placementOptions.at(i).getButtonSprite().getGlobalBounds().width / 2,
			304.0f + (i * 216) + (m_placementOptions.at(i).getButtonSprite().getGlobalBounds().height / 2) });
		m_testingButtonLabels.push_back(new Label(t_arialFont));
		m_testingButtonLabels.at(i)->setTextPosition(m_testingButtons.at(i).getButtonPosition());
	}
	m_testingButtonLabels.at(0)->setText("Stop Test");
	m_testingButtonLabels.at(1)->setText("Save Room");
}

void UiBuildMode::setUpPlacementModeButtons(sf::Font& t_arialFont)
{
	for (int i = 0; i < 4; i++)
	{
		m_placementOptions.push_back(Button());
		m_placementOptions.at(i).setButtonPosition(sf::Vector2f{ 16 + m_placementOptions.at(i).getButtonSprite().getGlobalBounds().width / 2, 
			216.0f + (i * 216) + (m_placementOptions.at(i).getButtonSprite().getGlobalBounds().height / 2)});
		m_placementOptionsLabels.push_back(new Label(t_arialFont));
		m_placementOptionsLabels.at(i)->setTextPosition(m_placementOptions.at(i).getButtonPosition());
	}
	m_placementOptionsLabels.at(0)->setText("Load Game");
	m_placementOptionsLabels.at(1)->setText("Test Room");
	m_placementOptionsLabels.at(2)->setText("Clear Room");
	m_placementOptionsLabels.at(3)->setText("Main Menu");
}

void UiBuildMode::setUpCategoryButtons(sf::Font& t_arialFont)
{
	for (int i = 0; i < 5; i++)
	{
		m_objectCategoryButtons.push_back(new Button());
		m_objectCategoryButtons.at(i)->resize(1.0f, 0.5f);
		m_objectCategoryButtons.at(i)->setButtonPosition(sf::Vector2f{ 512.0f + (i * m_objectCategoryButtons.at(i)->getButtonSprite().getGlobalBounds().width), 832.0f + (m_objectCategoryButtons.at(i)->getButtonSprite().getGlobalBounds().height /2) });
		

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

void UiBuildMode::setUpTextureRoomButtons(sf::Font& t_arialFont)
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
	//m_textureRoomLabels.at(0)->setText("Grass");
	//m_textureRoomLabels.at(0)->setLabelSprite(m_texturedLabels.at(0)->getText().getString());
	//m_textureRoomLabels.at(1)->setText("Dirt");
	//m_textureRoomLabels.at(1)->setLabelSprite(m_texturedLabels.at(1)->getText().getString());
	//m_textureRoomLabels.at(2)->setText("Concrete");
	//m_textureRoomLabels.at(2)->setLabelSprite(m_texturedLabels.at(2)->getText().getString());
	//m_textureRoomLabels.at(3)->setText("Brick");
	//m_textureRoomLabels.at(3)->setLabelSprite(m_texturedLabels.at(3)->getText().getString());
	//m_textureRoomLabels.at(4)->setText("Stone");
	//m_textureRoomLabels.at(4)->setLabelSprite(m_texturedLabels.at(4)->getText().getString());
	//m_textureRoomLabels.at(5)->setText("Wood");
	//m_textureRoomLabels.at(5)->setLabelSprite(m_texturedLabels.at(5)->getText().getString());
}

UiBuildMode::UiBuildMode(sf::Font& t_arialFont, Grid* t_grid, GameState* t_currentGameState, RoomCreation* t_roomCreation, ObjectPlacement* t_objectPlacement)
{
	m_gameState = t_currentGameState;
	m_grid = t_grid;
	m_objectPlacement = t_objectPlacement;
	m_roomCreation = t_roomCreation;
	m_arialFont = t_arialFont;
	m_inspector = new Inspector(m_arialFont);
	m_currentTab = TabState::TAB_DECORATIONS;

	m_currentRowText.setString("1 / 3");
	m_currentRowText.setFont(t_arialFont);
	m_currentRowText.setFillColor(sf::Color::Black);
	m_currentRowText.setOutlineColor(sf::Color::White);
	m_currentRowText.setCharacterSize(16.0f);
	m_currentRowText.setOutlineThickness(1.0f);
	m_currentRowText.setPosition(1440.0f,1008.0f);

	m_gridOnOffText.setString("Grid On");
	m_gridOnOffText.setFont(t_arialFont);
	m_gridOnOffText.setFillColor(sf::Color::White);
	m_gridOnOffText.setOutlineColor(sf::Color::Black);
	m_gridOnOffText.setCharacterSize(24.0f);
	m_gridOnOffText.setOutlineThickness(1.0f);
	m_gridOnOffText.setPosition(48.0f, 64.0f);

	m_collidersOnOffText.setString("Colliders On");
	m_collidersOnOffText.setFont(t_arialFont);
	m_collidersOnOffText.setFillColor(sf::Color::White);
	m_collidersOnOffText.setOutlineColor(sf::Color::Black);
	m_collidersOnOffText.setCharacterSize(24.0f);
	m_collidersOnOffText.setOutlineThickness(1.0f);
	m_collidersOnOffText.setPosition(48.0f, 128.0f);

	std::string path = "ASSETS/IMAGES/Terrain/Grass/";
	for (auto& entry : fs::directory_iterator(path))
	{
		std::string temp = entry.path().filename().string();
		temp.resize(temp.size() - 4);
		m_floors.push_back(temp);
	}
	setUpPlaceableItemsButtons(m_arialFont, m_rowsFloors, m_selectableFloorButtons, m_selectableFloorLabels, m_floors, path);
	path = "ASSETS/IMAGES/Enemies/";
	
	for (auto& entry : fs::directory_iterator(path))
	{
		std::string temp = entry.path().filename().string();
		temp.resize(temp.size() - 4);
		m_enemies.push_back(temp);
	}
	setUpPlaceableItemsButtons(m_arialFont, m_rowsEnemies, m_selectableEnemiesButtons, m_selectableEnemiesLabels, m_enemies, path);

	path = "ASSETS/IMAGES/Decorations/";

	for (auto& entry : fs::directory_iterator(path))
	{
		std::string temp = entry.path().filename().string();
		temp.resize(temp.size() - 4);
		m_decorations.push_back(temp);
	}
	setUpPlaceableItemsButtons(m_arialFont, m_rowsDecorations, m_selectableDecorationButtons, m_selectableDecorationLabels, m_decorations, path);

	path = "ASSETS/IMAGES/Items/";

	for (auto& entry : fs::directory_iterator(path))
	{
		std::string temp = entry.path().filename().string();
		temp.resize(temp.size() - 4);
		m_items.push_back(temp);
	}
	setUpPlaceableItemsButtons(m_arialFont, m_rowsItems, m_selectableItemButtons, m_selectableItemLabels, m_items, path);

	path = "ASSETS/IMAGES/Walls/";

	for (auto& entry : fs::directory_iterator(path))
	{
		std::string temp = entry.path().filename().string();
		temp.resize(temp.size() - 4);
		m_walls.push_back(temp);
	}
	setUpPlaceableItemsButtons(m_arialFont, m_rowsWalls, m_selectableWallButtons, m_selectableWallLabels, m_walls, path);


	for (int i = 0 ; i < 2; ++i)
	{
		m_prevNextbuttons.push_back(new Button());
		m_prevNextbuttons.at(i)->setButtonPosition(sf::Vector2f(432.0f + (i * 1072), 960.0f ));
		m_prevNextbuttons.at(i)->resize(0.1f, 0.4f);
	}

	for (int i = 0; i < 2; ++i)
	{
		m_toggleGridButtons.push_back(new Button());
		m_toggleGridButtons.at(i)->setButtonPosition(sf::Vector2f(32.0f, 80.0f + (i * 64)));
		m_toggleGridButtons.at(i)->resize(0.1f, 0.4f);
	}


	setUpPlacementModeButtons(m_arialFont);
	setUpCategoryButtons(m_arialFont);
	setUpGridFunctionButtons(m_arialFont);
	setUpTestBuildButtons(m_arialFont);

	m_bgRight.setSize(sf::Vector2f(256.0f, 2160.0f));
	m_bgRight.setPosition(1664.0f, 0.0f);
	m_bgRight.setOutlineThickness(1.0f);
	m_bgRight.setOutlineColor(sf::Color(sf::Color(140, 140, 140)));
	m_bgRight.setFillColor(G_COLOR_UI_GREY);

	m_bgLeft.setSize(sf::Vector2f(256.0f, 2160.0f));
	m_bgLeft.setPosition(0.0f, 0.0f);
	m_bgLeft.setOutlineThickness(1.0f);
	m_bgLeft.setOutlineColor(sf::Color(sf::Color(140, 140, 140)));
	m_bgLeft.setFillColor(G_COLOR_UI_GREY);

	m_bgBottom.setSize(sf::Vector2f(1920.0f, 256.0f));
	m_bgBottom.setPosition(0.0f, 824.0f);
	m_bgBottom.setOutlineThickness(1.0f);
	m_bgBottom.setOutlineColor(sf::Color(sf::Color(140, 140, 140)));
	m_bgBottom.setFillColor(G_COLOR_UI_GREY);



	//setUpTextureRoomButtons(m_arialFont);
}

UiBuildMode::UiBuildMode()
{
}

UiBuildMode::~UiBuildMode()
{
}

void UiBuildMode::processDialogueButtons(sf::Event t_event, sf::RenderWindow& t_window)
{
	//for (int i = 0; i < m_dialogueButtons.size(); i++)
	//{
	//	if (m_dialogueButtons.at(i).getButtonSprite().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
	//	{
	//		m_dialogueButtons.at(i).highlighted();
	//		if (t_event.type == sf::Event::MouseButtonReleased)
	//		{
	//			if (t_event.mouseButton.button == sf::Mouse::Left)
	//			{
	//				if (m_buildButtonLabels.at(i)->getTextString() == "Save")
	//				{
	//					 Save dialogue here
	//				}
	//				else if (m_buildButtonLabels.at(i)->getTextString() == "Exit")
	//				{
	//					 Toggle dialogue box off
	//				}
	//			}
	//		}
	//	}
	//	else
	//	{
	//		m_dialogueButtons.at(i).setButtonTexture();
	//	}
	//}
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
						m_roomCreation->checkRoomValidity();
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

void UiBuildMode::deselectButtons(std::vector<std::vector<Button*>>& t_objectButtons)
{
	std::vector<std::vector<Button>>::iterator row;
	std::vector<Button>::iterator col;
	for (const auto& row : t_objectButtons)
	{
		for (const auto& col : row)
		{
			col->setSelected(false);
		}
	}
}

void UiBuildMode::processPlaceObjectsButtonInput(sf::Event t_event, sf::RenderWindow& t_window, std::string& t_path, std::vector<std::vector<Label*>>& t_labels, std::vector<std::vector<Button*>>& t_objectButtons)
{
	std::vector<std::vector<Button>>::iterator row;
	std::vector<Button>::iterator col;
	int rowIndex = 0;
	int colIndex = 0;
	sf::Vector2f pixelPos = sf::Vector2f(sf::Mouse::getPosition(t_window).x, sf::Mouse::getPosition(t_window).y);

	// convert it to world coordinates
	//sf::Vector2f worldPos = t_window.mapPixelToCoords(pixelPos);
	for (const auto& row : t_objectButtons)
	{
		
		for (const auto& col : row)
		{
			
			if (col->getButtonSprite().getGlobalBounds().contains(pixelPos))
			{
				col->highlighted();
				if (t_event.type == sf::Event::MouseButtonReleased)
				{
					if (t_event.mouseButton.button == sf::Mouse::Left)
					{
						if(col->isEnabled())
						{
							deselectButtons(t_objectButtons);

							col->setSelected(true);
							if (col->getSelected())
							{
								col->setColor(sf::Color::Red);
								// send selected object to grid
								m_objectPlacement->setSelectedObject(t_path, t_labels.at(rowIndex).at(colIndex)->getText()->getString());
							}
						}
					}
				}
			}
			else 
			{
				col->setButtonTexture();
			}
			if (!col->getSelected())
			{
				col->setColor(sf::Color::White);
			}
				
			colIndex += 1;
		}
		colIndex = 0;
		rowIndex += 1;
	}
	for (int i = 0; i < m_toggleGridButtons.size(); i++)
	{
		if (m_toggleGridButtons.at(i)->getButtonSprite().getGlobalBounds().contains(pixelPos))
		{
			m_toggleGridButtons.at(i)->highlighted();
			if (t_event.type == sf::Event::MouseButtonReleased)
			{
				if (t_event.mouseButton.button == sf::Mouse::Left)
				{
					if (i == 0)
					{
						m_grid->setGridEnabled();
						std::cout << "grid on off" << std::endl;
					}
					else
					{
						m_grid->setCollidersEnabled();
						m_roomCreation->setCollidersEnabled();
						m_objectPlacement->setCollidersEnabled();
					}
				}
			}
		}
		else
		{
			m_toggleGridButtons.at(i)->setButtonTexture();
		}
	}

	for (int i = 0; i < m_objectCategoryButtons.size(); i++)
	{
		if (m_objectCategoryButtons.at(i)->getButtonSprite().getGlobalBounds().contains(pixelPos))
		{
			m_objectCategoryButtons.at(i)->highlighted();
			if (t_event.type == sf::Event::MouseButtonReleased)
			{
				if (t_event.mouseButton.button == sf::Mouse::Left)
				{
					if (m_objectCategoryLabels.at(i)->getTextString() == "Walls")
					{
						m_currentTab = TabState::TAB_WALLS;
						m_currentRowIndex = 0;
						m_currentRowText.setString(std::to_string(m_currentRowIndex+1) + " / " + std::to_string(m_rowsWalls));
					}
					else if (m_objectCategoryLabels.at(i)->getTextString() == "Terrain")
					{
						m_currentTab = TabState::TAB_TERRAIN;
						m_currentRowIndex = 0;
						m_currentRowText.setString(std::to_string(m_currentRowIndex+1) + " / " + std::to_string(m_rowsFloors));

					}
					else if (m_objectCategoryLabels.at(i)->getTextString() == "Enemies")
					{
						m_currentTab = TabState::TAB_ENEMIES;
						m_currentRowIndex = 0;
						m_currentRowText.setString(std::to_string(m_currentRowIndex+1) + " / " + std::to_string(m_rowsEnemies));

					}
					else if (m_objectCategoryLabels.at(i)->getTextString() == "Items")
					{
						m_currentTab = TabState::TAB_ITEMS;
						m_currentRowIndex = 0;
						m_currentRowText.setString(std::to_string(m_currentRowIndex +1) + " / " + std::to_string(m_rowsItems));

					}
					else if (m_objectCategoryLabels.at(i)->getTextString() == "Decorations")
					{
						m_currentTab = TabState::TAB_DECORATIONS;
						m_currentRowIndex = 0;
						m_currentRowText.setString(std::to_string(m_currentRowIndex +1) + " / " + std::to_string(m_rowsDecorations));
					}
				}
			}
		}
		else
		{
			m_objectCategoryButtons.at(i)->setButtonTexture();
		}






	}



		for (int i = 0; i < m_placementOptions.size(); i++)
		{
			if (m_placementOptions.at(i).getButtonSprite().getGlobalBounds().contains(pixelPos))
			{
				m_placementOptions.at(i).highlighted();
				if (t_event.type == sf::Event::MouseButtonReleased)
				{
					if (t_event.mouseButton.button == sf::Mouse::Left)
					{
						if (m_placementOptionsLabels.at(i)->getTextString() == "Load Game")
						{
							m_roomCreation->resetValues();
							m_grid->regenerateGrid();
							m_objectPlacement->clearObjects();
							m_gameState->m_currentGameState = State::LEVEL_LIST;
						}
						else if (m_placementOptionsLabels.at(i)->getTextString() == "Test Room")
						{
							m_gameState->m_currentGameState = State::ROOM_TEST;
							//for (int j = 0; j < m_objectPlacement->m_placedObjects.size(); ++j)
							//{
							//	m_storePositions.push_back(m_objectPlacement->m_placedObjects.at(j)->getSprite()->getPosition());
							//}
							// need to move player into scene here
						}
						else if (m_placementOptionsLabels.at(i)->getTextString() == "Clear Room")
						{
							m_objectPlacement->clearObjects();
						}
						else if (m_placementOptionsLabels.at(i)->getTextString() == "Main Menu")
						{
							m_gameState->m_currentGameState = State::MENU;
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
	int rowIndex = 0;
	int colIndex = 0;
	sf::Vector2f pixelPos = sf::Vector2f(sf::Mouse::getPosition(t_window).x, sf::Mouse::getPosition(t_window).y);

	for (int i = 0; i < m_testingButtons.size(); i++)
	{
		if (m_testingButtons.at(i).getButtonSprite().getGlobalBounds().contains(pixelPos))
		{
			m_testingButtons.at(i).highlighted();
			if (t_event.type == sf::Event::MouseButtonReleased)
			{
				if (t_event.mouseButton.button == sf::Mouse::Left)
				{
					if (m_testingButtonLabels.at(i)->getTextString() == "Stop Test")
					{
						// Go back to placing objects
						// reset the objects position
						//cahnge state
						//for (int j = 0; j < m_objectPlacement->m_placedObjects.size(); ++j)
						//{
						//	m_objectPlacement->m_placedObjects.at(j)->getBounds()->setPosition(m_storePositions.at(j));
						//}
						m_storePositions.clear();
						m_grid->m_playerSet = false;
						m_gameState->m_currentGameState = State::ROOM_PLACE_OBJECTS;

					}
					else if (m_testingButtonLabels.at(i)->getTextString() == "Save Room")
					{
						// save room here;
						m_gameState->setState(State::SAVING_SCREEN);
					}
					else if (m_testingButtonLabels.at(i)->getTextString() == "Start Over")
					{
						m_objectPlacement->clearObjects();
						m_grid->regenerateGrid();
						m_gameState->m_currentGameState = State::ROOM_PLACE_OBJECTS;
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



void UiBuildMode::setVisibleRow(sf::Event t_event, sf::RenderWindow& t_window, int t_rows, std::vector<std::vector<Button*>>& t_objectButtons)
{
	int rowIndex = 0;
	int colIndex = 0;
	sf::Vector2f pixelPos = sf::Vector2f(sf::Mouse::getPosition(t_window).x, sf::Mouse::getPosition(t_window).y);

	for (int i = 0; i < m_prevNextbuttons.size(); ++i)
	{
		if (m_prevNextbuttons.at(i)->getButtonSprite().getGlobalBounds().contains(pixelPos))
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
						m_currentRowIndex = t_rows -1;
					}
					m_currentRowText.setString(std::to_string(m_currentRowIndex +1) + " / " + std::to_string(t_rows));
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
}

void UiBuildMode::zoomViewAtPoint(sf::Vector2i pixel, sf::RenderWindow& window, float zoom, bool t_zoomIn)
{
	const sf::Vector2f beforeZoom{ window.mapPixelToCoords(pixel) };


	std::cout << "view size x : " << m_gameView.getSize().x << " view size y : " << m_gameView.getSize().y << std::endl;
	if (m_gameView.getSize().x > 576 && t_zoomIn)
	{
		m_gameView.zoom(zoom);
		window.setView(m_gameView);
		const sf::Vector2f afterZoom{ window.mapPixelToCoords(pixel) };
		const sf::Vector2f offset{ beforeZoom - afterZoom };
		m_gameView.move(offset);
		window.setView(m_gameView);
	}
	else if(m_gameView.getSize().x < 576 && t_zoomIn)
	{
		m_gameView.setSize(576, 324);
		window.setView(m_gameView);
		const sf::Vector2f afterZoom{ window.mapPixelToCoords(pixel) };
		const sf::Vector2f offset{ beforeZoom - afterZoom };
		m_gameView.move(offset);
		window.setView(m_gameView);
		std::cout << "zoom zoom";
	}
	else if (m_gameView.getSize().x < 2880 && !t_zoomIn)
	{
		m_gameView.zoom(zoom);
		window.setView(m_gameView);
		const sf::Vector2f afterZoom{ window.mapPixelToCoords(pixel) };
		const sf::Vector2f offset{ beforeZoom - afterZoom };
		m_gameView.move(offset);
		window.setView(m_gameView);
	}
	else if (m_gameView.getSize().x > 2880 && !t_zoomIn)
	{
		m_gameView.setSize(2880, 1620);
		window.setView(m_gameView);
		const sf::Vector2f afterZoom{ window.mapPixelToCoords(pixel) };
		const sf::Vector2f offset{ beforeZoom - afterZoom };
		m_gameView.move(offset);
		window.setView(m_gameView);
		std::cout << "zoom zoom";
	}
}

void UiBuildMode::processEvents(sf::Event t_event, sf::RenderWindow& t_window)
{
	sf::Event newEvent = t_event;

	if (m_gameState->m_currentGameState == State::ROOM_BUILD)
	{
		processBuildRoomButtonInput(t_event, t_window);
	}
	else if (m_gameState->m_currentGameState == State::ROOM_PLACE_OBJECTS)
	{
		if (t_event.type == sf::Event::MouseWheelScrolled)
		{
			if (t_event.mouseWheelScroll.delta > 0)
			{
				zoomViewAtPoint({ t_event.mouseWheelScroll.x, t_event.mouseWheelScroll.y }, t_window, (1.f / m_zoomRate), true);
			}
			else if (t_event.mouseWheelScroll.delta < 0)
			{
				zoomViewAtPoint({ t_event.mouseWheelScroll.x, t_event.mouseWheelScroll.y }, t_window, m_zoomRate, false);
			}
		}
		processDialogueButtons(t_event, t_window);
		if (m_currentTab == TabState::TAB_TERRAIN)
		{
			setVisibleRow(t_event, t_window, m_rowsFloors, m_selectableFloorButtons);
			processPlaceObjectsButtonInput(t_event, t_window, m_pathFloors, m_selectableFloorLabels, m_selectableFloorButtons);
		}
		else if (m_currentTab == TabState::TAB_WALLS)
		{
			setVisibleRow(t_event, t_window, m_rowsWalls, m_selectableWallButtons);
			processPlaceObjectsButtonInput(t_event, t_window, m_pathWalls, m_selectableWallLabels, m_selectableWallButtons);
		}
		else if (m_currentTab == TabState::TAB_DECORATIONS)
		{
			setVisibleRow(t_event, t_window, m_rowsDecorations, m_selectableDecorationButtons);
			processPlaceObjectsButtonInput(t_event, t_window, m_pathDecorations, m_selectableDecorationLabels, m_selectableDecorationButtons);
		}
		else if (m_currentTab == TabState::TAB_ENEMIES)
		{
			setVisibleRow(t_event, t_window, m_rowsEnemies, m_selectableEnemiesButtons);
			processPlaceObjectsButtonInput(t_event, t_window, m_pathEnemies, m_selectableEnemiesLabels, m_selectableEnemiesButtons);
		}
		else if (m_currentTab == TabState::TAB_ITEMS)
		{
			setVisibleRow(t_event, t_window, m_rowsItems, m_selectableItemButtons);
			processPlaceObjectsButtonInput(t_event, t_window, m_pathItems, m_selectableItemLabels, m_selectableItemButtons);
		}
	}
	else if (m_gameState->m_currentGameState == State::ROOM_TEST)
	{
		processTestRoomButtonInput(t_event, t_window);
	}	
}

void UiBuildMode::render(sf::RenderWindow* t_window)
{
	t_window->draw(m_bgBottom);
	t_window->draw(m_bgLeft);
	t_window->draw(m_bgRight);

	if (m_gameState->m_currentGameState == State::ROOM_TEXTURE || m_gameState->m_currentGameState == State::LEVEL_LIST)
	{
		for (int i = 0; i < m_textureRoomButtons.size(); i++)
		{
			m_textureRoomButtons.at(i).render(t_window);
			m_textureRoomLabels.at(i)->render(t_window);
		}
	}
	if (m_gameState->m_currentGameState == State::ROOM_PLACE_OBJECTS || m_gameState->m_currentGameState == State::LEVEL_LIST)
	{

		t_window->draw(m_currentRowText);
		t_window->draw(m_gridOnOffText);
		t_window->draw(m_collidersOnOffText);

		for (int i = 0; i < 2; ++i)
		{
			m_prevNextbuttons.at(i)->render(t_window);
		}
		for (int i = 0; i < 2; ++i)
		{
			m_toggleGridButtons.at(i)->render(t_window);
		}
		for (int i = 0; i < m_objectCategoryButtons.size(); i++)
		{
			m_objectCategoryButtons.at(i)->render(t_window);
			m_objectCategoryLabels.at(i)->render(t_window);
		}
		//for (int i = 0; i < m_selectableObjects.size(); i++)
		//{
		//	m_selectableObjects.at(i).render(t_window);
		//	m_texturedLabels.at(i)->render(t_window);
		//}
		for (int i = 0; i < m_placementOptions.size(); i++)
		{
			m_placementOptions.at(i).render(t_window);
			m_placementOptionsLabels.at(i)->render(t_window);
		}
		std::vector<std::vector<Button>>::iterator row;
		std::vector<Button>::iterator col;
		std::vector<std::vector<std::string>>::iterator rowLabel;
		std::vector<std::string>::iterator colLabel;
		if (m_currentTab == TabState::TAB_TERRAIN)
		{
			int rowIndex = 0;

			for (const auto& row : m_selectableFloorButtons)
			{
				for (const auto& col : row)
				{
					if (rowIndex == m_currentRowIndex)
					{
						//t_window->draw(col->getButtonSprite());
						col->render(t_window);
					}
				}
				rowIndex++;
			}
			rowIndex = 0;
			for (const auto& rowLabel : m_selectableFloorLabels)
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
		}
		else if (m_currentTab == TabState::TAB_ENEMIES)
		{
			int rowIndex = 0;

			for (const auto& row : m_selectableEnemiesButtons)
			{
				for (const auto& col : row)
				{
					if (rowIndex == m_currentRowIndex)
					{
						//t_window->draw(col->getButtonSprite());
						col->render(t_window);
					}
				}
				rowIndex++;
			}
			rowIndex = 0;
			for (const auto& rowLabel : m_selectableEnemiesLabels)
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
		}
		else if (m_currentTab == TabState::TAB_DECORATIONS)
		{
			int rowIndex = 0;

			for (const auto& row : m_selectableDecorationButtons)
			{
				for (const auto& col : row)
				{
					if (rowIndex == m_currentRowIndex)
					{
						//t_window->draw(col->getButtonSprite());
						col->render(t_window);
					}
				}
				rowIndex++;
			}
			rowIndex = 0;
			for (const auto& rowLabel : m_selectableDecorationLabels)
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
		}
		else if (m_currentTab == TabState::TAB_ITEMS)
		{
		int rowIndex = 0;

		for (const auto& row : m_selectableItemButtons)
		{
			for (const auto& col : row)
			{
				if (rowIndex == m_currentRowIndex)
				{
					//t_window->draw(col->getButtonSprite());
					col->render(t_window);
				}
			}
			rowIndex++;
		}
		rowIndex = 0;
		for (const auto& rowLabel : m_selectableItemLabels)
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
		}
		else if (m_currentTab == TabState::TAB_WALLS)
		{
			int rowIndex = 0;

			for (const auto& row : m_selectableWallButtons)
			{
				for (const auto& col : row)
				{
					if (rowIndex == m_currentRowIndex)
					{
						//t_window->draw(col->getButtonSprite());
						col->render(t_window);
					}
				}
				rowIndex++;
			}
			rowIndex = 0;
			for (const auto& rowLabel : m_selectableWallLabels)
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
		}


		// temp remove later



		// -----------------------------------------------




	}
	if (m_gameState->m_currentGameState == State::ROOM_TEST)
	{
		for (int i = 0; i < m_testingButtons.size(); i++)
		{
			m_testingButtons.at(i).render(t_window);
			m_testingButtonLabels.at(i)->render(t_window);
		}
	}
	//m_inspector->render(t_window);

}
