#include "ObjectPlacement.h"

ObjectPlacement::ObjectPlacement()
{
}

ObjectPlacement::ObjectPlacement(GameState* t_gameState, Grid* t_grid, TextureManager* t_textureManager)
{
	//m_currentlySelected = new Decoration();
	m_currentlySelected = nullptr;
	m_textureManager = t_textureManager;
	m_gameState = t_gameState;
	m_grid = t_grid;
	//for (int i = 0; i < m_grid->m_vectGridSize; ++i)
	//{
	//	for (int j = 0; j < m_grid->m_vectGridSize; ++j)
	//	{
	//		if (m_grid->m_vectGrid.at(i).at(j)->cellType == "Wall")
	//		{
	//			m_walls.push_back(new Wall());
	//		}
	//		else if (m_grid->m_vectGrid.at(i).at(j)->cellType == "Floor")
	//		{

	//		}
	//	}
	//}
}

ObjectPlacement::~ObjectPlacement()
{
}

bool ObjectPlacement::checkValidSelection()
{
	if (!m_selectedObject.empty())
	{
		return true;
	}
	return false;
}

bool ObjectPlacement::checkForDoubleClick(sf::Clock& t_clock, sf::Time& t_doubleClickTime)
{
	std::cout << "Checking for Double Click" << std::endl;
	sf::Time currentTime = t_clock.getElapsedTime();
	if (currentTime - t_doubleClickTime < sf::seconds(0.5)) {
		// This is a double-click
		t_doubleClickTime = sf::Time::Zero;
		return true;
	}
	t_doubleClickTime = currentTime;
	return false;
}

void ObjectPlacement::placeRemove(sf::Event t_event, sf::RenderWindow& m_window)
{
	bool initialPress = false;
	int startRow = 0;
	int endRow = 0;
	int startCol = 0;
	int endCol = 0;
	// get position of initial click, get position of end click
	if (t_event.type == sf::Event::MouseButtonPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		if (!initialPress)
		{
			initialPress = true;
			sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
			sf::Vector2f startPos = m_window.mapPixelToCoords(pixelPos);
			startRow = startPos.x / 32;
			startCol = startPos.y / 32;
		}
	}
	else if (t_event.type == sf::Event::MouseButtonReleased && initialPress == true)
	{
		initialPress = false;
		sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
		sf::Vector2f endPos = m_window.mapPixelToCoords(pixelPos);
		endRow = endPos.x / 32;
		endCol = endPos.y / 32;

		if (endRow < startRow)
		{
			int temp = startRow;
			startRow = endRow;
			endRow = temp;
		}
		if (endCol < startCol)
		{
			int temp = startCol;
			startCol = endCol;
			endCol = temp;
		}
		for (startRow <= endRow; startRow++;)
		{
			for (startCol <= endCol; startCol++;)
			{
				if (m_tempTag.find("Enemies") != std::string::npos)
				{
					m_enemies.push_back(new Enemy(m_tempTag, m_selectedObject, m_textureManager));
					setObject(startRow, startCol, "Enemy", m_enemies);
				}
				else if (m_tempTag.find("Item") != std::string::npos)
				{
					m_items.push_back(new Item(m_tempTag, m_selectedObject, m_textureManager));
					setObject(startRow, startCol, "Item", m_enemies);
				}
				else if (m_tempTag.find("Decoration") != std::string::npos)
				{
					m_decorations.push_back(new Decoration(m_tempTag, m_selectedObject, m_textureManager));
					setObject(startRow, startCol, "Decoration", m_enemies);
				}
				else if (m_tempTag.find("Wall") != std::string::npos)
				{
					m_walls.push_back(new Wall(m_tempTag, m_selectedObject, m_textureManager));
					setObject(startRow, startCol, "Wall", m_enemies);
				}
				else if (m_tempTag.find("Terrain") != std::string::npos)
				{
					m_grid->m_vectGrid.at(startRow).at(startCol).setFloorSprite(m_selectedObject);
					m_grid->m_vectGrid.at(startRow).at(startCol).cellType = "Terrain";
				}
			}
		}
	}
	else if (t_event.type == sf::Event::KeyReleased) 
	{
		if (t_event.key.code == sf::Keyboard::Space)
		{
			if (m_currentlySelected != nullptr)
			{
				m_currentlySelected->setMoving(true);
				m_grid->m_vectGrid.at(m_originalPosition.x).at(m_originalPosition.y).m_objectType = "";
				m_grid->m_vectGrid.at(m_originalPosition.x).at(m_originalPosition.y).m_hasObject = false;
			}
		}
	}

	sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);

	// convert it to world coordinates
	sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos);
	int row = worldPos.x / 32;
	int col = worldPos.y / 32;
	//std::cout << noOfObstacles << std::endl;
	if (row >= 0 && row < 100 && col >= 0 && col < 100)
	{
		if (m_grid->m_vectGrid.at(row).at(col).getTileBorder().getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
		{

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (m_currentlySelected != nullptr)
				{
					if (m_currentlySelected->m_moving == true && m_grid->m_vectGrid.at(row).at(col).m_hasObject == false)
					{
						m_currentlySelected->getBounds()->setPosition(m_grid->m_vectGrid.at(row).at(col).getPos());
						m_currentlySelected->getSprite()->setPosition(m_currentlySelected->getBounds()->getPosition());
						if (m_grid->m_vectGrid.at(row).at(col).cellType == "Floor" && m_grid->m_vectGrid.at(row).at(col).m_hasObject == false)
						{
							m_currentlySelected->setSelected(false);
							m_currentlySelected->setMoving(false);
							m_currentlySelected = nullptr;
							m_grid->m_vectGrid.at(row).at(col).m_hasObject = true;
							m_grid->m_vectGrid.at(row).at(col).m_objectType = m_storedObjectType;


							m_originalPosition = sf::Vector2i{ 0,0 };
						}
					}
					else if (m_currentlySelected->m_moving == false)
					{
						m_currentlySelected->setSelected(false);
						m_currentlySelected = nullptr;
					}

				}
				else if (checkValidSelection())
				{


					if (m_grid->m_vectGrid.at(row).at(col).cellType != "Floor" && m_grid->m_vectGrid.at(row).at(col).m_hasObject == false)
					{
						//addObjectToGrid(m_enemies, Enemy, i, j, m_tempTag, m_selectedObject, m_vectGrid);

						if (m_tempTag.find("Enemies") != std::string::npos)
						{
							std::cout << m_tempTag << std::endl;
							m_enemies.push_back(new Enemy(m_tempTag, m_selectedObject, m_textureManager));
							m_grid->m_vectGrid.at(row).at(col).m_hasObject = true;
							m_grid->m_vectGrid.at(row).at(col).m_objectType = "Enemy";
							m_enemies.at(m_enemies.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(row).at(col).getPos());
							m_enemies.at(m_enemies.size() - 1)->getSprite()->setPosition(m_enemies.at(m_enemies.size() - 1)->getBounds()->getPosition());
							m_enemies.at(m_enemies.size() - 1)->setRowColumn(row, col);
							//m_currentlySelected->setSelected();
							//m_currentlySelected = m_enemies.at(m_enemies.size() - 1);
							//m_currentlySelected->setSelected();

						}
						if (m_tempTag.find("Item") != std::string::npos)
						{
							m_items.push_back(new Item(m_tempTag, m_selectedObject, m_textureManager));
							m_grid->m_vectGrid.at(row).at(col).m_hasObject = true;
							m_grid->m_vectGrid.at(row).at(col).m_objectType = "Item";
							m_items.at(m_items.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(row).at(col).getPos());
							m_items.at(m_items.size() - 1)->getSprite()->setPosition(m_items.at(m_items.size() - 1)->getBounds()->getPosition());
							m_items.at(m_items.size() - 1)->setRowColumn(row, col);

						}
						if (m_tempTag.find("Decoration") != std::string::npos)
						{
							m_decorations.push_back(new Decoration(m_tempTag, m_selectedObject, m_textureManager));
							m_grid->m_vectGrid.at(row).at(col).m_hasObject = true;
							m_grid->m_vectGrid.at(row).at(col).m_objectType = "Decoration";
							m_decorations.at(m_decorations.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(row).at(col).getPos());
							m_decorations.at(m_decorations.size() - 1)->getSprite()->setPosition(m_decorations.at(m_decorations.size() - 1)->getBounds()->getPosition());
							m_decorations.at(m_decorations.size() - 1)->setRowColumn(row, col);
							//m_currentlySelected->setSelected();
							//m_currentlySelected = m_decorations.at(m_decorations.size() - 1);
							//m_currentlySelected->setSelected();
						}
						if (m_tempTag.find("Wall") != std::string::npos)
						{
							m_walls.push_back(new Wall(m_tempTag, m_selectedObject, m_textureManager));
							m_grid->m_vectGrid.at(row).at(col).m_hasObject = true;
							m_grid->m_vectGrid.at(row).at(col).m_objectType = "Wall";
							/*m_grid->m_vectGrid.at(row).at(col).cellType = "Wall";*/
							m_walls.at(m_walls.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(row).at(col).getPos());
							m_walls.at(m_walls.size() - 1)->getSprite()->setPosition(m_walls.at(m_walls.size() - 1)->getBounds()->getPosition());
							m_walls.at(m_walls.size() - 1)->setRowColumn(row, col);

						}

					}
					if (m_grid->m_vectGrid.at(row).at(col).cellType != "Wall")
					{
						if (m_tempTag.find("Terrain") != std::string::npos)
						{
							//m_terrain.push_back(new Terrain(m_tempTag, m_selectedObject, m_textureManager));
							//// check collision for overlapping terrain
							//m_terrain.at(m_terrain.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(i).at(j)->getPos());
							//m_terrain.at(m_terrain.size() - 1)->getSprite()->setPosition(m_terrain.at(m_terrain.size() - 1)->getBounds()->getPosition());

							//m_terrain.at(m_terrain.size() - 1)->setRowColumn(i, j);
							noOfObstacles++;
							std::cout << "no : " << noOfObstacles << std::endl;
							m_grid->m_vectGrid.at(row).at(col).setFloorSprite(m_selectedObject);
							m_grid->m_vectGrid.at(row).at(col).cellType = "Terrain";
						}

					}

				}

			}
			if (t_event.type == sf::Event::MouseButtonPressed && t_event.mouseButton.button == sf::Mouse::Left)
			{
				if (checkForDoubleClick(m_clock, m_doubleClickTime))
				{
					std::cout << "Double Click" << std::endl;

					std::cout << "hasObject : " << m_grid->m_vectGrid.at(row).at(col).m_hasObject << std::endl;
					if (m_grid->m_vectGrid.at(row).at(col).m_hasObject == true)
					{
						std::cout << "hasObject" << std::endl;
						if (m_currentlySelected != nullptr)
						{
							m_currentlySelected->setSelected(false);
							m_currentlySelected = nullptr;
						}




						if (m_grid->m_vectGrid.at(row).at(col).m_objectType == "Enemy")
						{
							m_storedObjectType = "Enemy";
							setSelectedGridObject(m_enemies, m_window);
						}
						else if (m_grid->m_vectGrid.at(row).at(col).m_objectType == "Item")
						{
							m_storedObjectType = "Item";
							setSelectedGridObject(m_items, m_window);
						}
						else if (m_grid->m_vectGrid.at(row).at(col).m_objectType == "Decoration")
						{
							m_storedObjectType = "Decoration";
							setSelectedGridObject(m_decorations, m_window);
						}
						else if (m_grid->m_vectGrid.at(row).at(col).m_objectType == "Wall")
						{
							m_storedObjectType = "Wall";
							setSelectedGridObject(m_walls, m_window);
						}
						//setSelected(m_enemies, &m_window, m_currentlySelected);
						//setSelected(m_items, &m_window, m_currentlySelected);
						//setSelected(m_decorations, &m_window, m_currentlySelected);
						//setSelected(m_walls, &m_window, m_currentlySelected);
						m_originalPosition = sf::Vector2i{ row,col };
						std::cout << "x : " << m_originalPosition.x << " y : " << m_originalPosition.y << std::endl;

						/*m_grid->m_vectGrid.at(i).at(j)->m_hasObject = false;
						m_grid->m_vectGrid.at(i).at(j)->m_objectType = "";*/




						//std::cout << m_currentlySelected->m_isSelected << std::endl;
						//setSelected(m_terrain, &m_window, m_currentlySelected);

					}

				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			{
				deleteObject(m_decorations, m_grid, m_currentlySelected, m_window);
				deleteObject(m_terrain, m_grid, m_currentlySelected, m_window);
				deleteObject(m_walls, m_grid, m_currentlySelected, m_window);
				deleteObject(m_enemies, m_grid, m_currentlySelected, m_window);
				deleteObject(m_items, m_grid, m_currentlySelected, m_window);
				m_currentlySelected = nullptr;
			}
		}
	}
}



void ObjectPlacement::clearObjects()
{
	m_enemies.clear();
	m_terrain.clear();
	m_walls.clear();
	m_items.clear();
	m_decorations.clear();
	noOfObstacles = m_enemies.size();

	for (int i = 0; i < m_grid->m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_grid->m_vectGridSize; ++j)
		{
			if (m_grid->m_vectGrid.at(i).at(j).cellType == "Floor")
			{
				m_grid->m_vectGrid.at(i).at(j).m_hasObject = false;
			}
		}
	}
}

void ObjectPlacement::setSelectedObject(std::string t_path, std::string t_objectName)
{
	m_tempTag = t_path;
	m_selectedObject = t_path + t_objectName;
}


void ObjectPlacement::update(sf::Time t_deltaTime, sf::RenderWindow& m_window)
{
	if (m_currentlySelected != nullptr)
	{
		m_currentlySelected->update(t_deltaTime, m_window);
		if (m_currentlySelected->m_moving == true)
		{
			m_currentlySelected->getBounds()->setPosition(sf::Vector2f(sf::Mouse::getPosition(m_window)));
			m_currentlySelected->getSprite()->setPosition(m_currentlySelected->getBounds()->getPosition());
		}
	}
	//placeRemove(m_window);
}

void ObjectPlacement::render(sf::RenderWindow* t_window)
{
	//renderPlacedObjects(m_terrain, t_window, m_collidersEnabled);
	renderPlacedObjects(m_decorations, t_window, m_collidersEnabled);
	renderPlacedObjects(m_items, t_window, m_collidersEnabled);
	renderPlacedObjects(m_enemies, t_window, m_collidersEnabled);
	renderPlacedObjects(m_walls, t_window, m_collidersEnabled);
}

void ObjectPlacement::setSelectedGridObject(std::vector<Object*>& t_objects, sf::RenderWindow& m_window)
{
	for (int i = 0; i < t_objects.size(); ++i)
	{
		if (t_objects.at(i)->getBounds()->getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
		{
			m_currentlySelected = t_objects.at(i);
			m_currentlySelected->setSelected(true);
		}
	}
}

Object* ObjectPlacement::getSelectedGridObject()
{
	if (m_currentlySelected != nullptr)
	{
		return m_currentlySelected;
	}
	else
	{
		return nullptr;
	}
}


void ObjectPlacement::setObject(int t_row, int t_col, std::string t_label, std::vector<Object*> t_objects)
{
	m_grid->m_vectGrid.at(t_row).at(t_col).m_hasObject = true;
	m_grid->m_vectGrid.at(t_row).at(t_col).m_objectType = t_label;
	t_objects.at(t_objects.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(t_row).at(t_col).getPos());
	t_objects.at(t_objects.size() - 1)->getSprite()->setPosition(t_objects.at(t_objects.size() - 1)->getBounds()->getPosition());
	t_objects.at(t_objects.size() - 1)->setRowColumn(t_row, t_col);
}

			
