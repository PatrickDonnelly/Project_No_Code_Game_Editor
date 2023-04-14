#include "ObjectPlacement.h"

ObjectPlacement::ObjectPlacement()
{
}

ObjectPlacement::ObjectPlacement(GameState* t_gameState, Grid* t_grid, TextureManager* t_textureManager)
{
	m_currentlySelected = nullptr;
	m_textureManager = t_textureManager;
	m_gameState = t_gameState;
	m_grid = t_grid;
	m_area.setSize(sf::Vector2f(100.0f, 100.0f));
	m_area.setFillColor(sf::Color(255, 0, 0, 125));
	m_area.setOutlineThickness(1.0f);
	m_area.setOutlineColor(sf::Color(255, 0, 0));
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
	if (currentTime - t_doubleClickTime < sf::seconds(0.3)) {
		// This is a double-click
		t_doubleClickTime = sf::Time::Zero;
		return true;
	}
	t_doubleClickTime = currentTime;
	return false;
}

void ObjectPlacement::swapInts(int& t_smallerNumber, int& t_biggerNumber)
{
	if (t_biggerNumber < t_smallerNumber)
	{
		int temp = t_smallerNumber;
		t_smallerNumber = t_biggerNumber;
		t_biggerNumber = temp;
	}
}

void ObjectPlacement::processEvents(sf::Event t_event, sf::RenderWindow& t_window)
{
	placeMultipleObjects(t_event, t_window);
	placeObject(t_event, t_window);
	removeObject(t_event, t_window);
	moveObject(t_event, t_window);
	selectObject(t_event, t_window);
}

void ObjectPlacement::setInitialPress(sf::RenderWindow& m_window)
{
	if (!initialPress)
	{
		initialPress = true;
		m_screenPos = sf::Mouse::getPosition(m_window);
		m_worldPos = m_window.mapPixelToCoords(m_screenPos, m_gameView);
		startRow = m_worldPos.x / 32;
		startCol = m_worldPos.y / 32;
		m_area.setSize(sf::Vector2f(0, 0));
		m_area.setPosition(m_worldPos);
	}
}

void ObjectPlacement::setEndOfPress(sf::RenderWindow& m_window)
{
	initialPress = false;
	m_screenPos = sf::Mouse::getPosition(m_window);
	m_worldPos = m_window.mapPixelToCoords(m_screenPos);
	endRow = m_worldPos.x / 32;
	endCol = m_worldPos.y / 32;
}

void ObjectPlacement::scaleArea(sf::RenderWindow& m_window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
	sf::Vector2f currentMousePosition = m_window.mapPixelToCoords(mousePosition, m_gameView);
	m_area.setSize(sf::Vector2f(currentMousePosition.x - m_worldPos.x, currentMousePosition.y - m_worldPos.y));
}

void ObjectPlacement::placeMultipleObjects(sf::Event t_event, sf::RenderWindow& m_window)
{
	if (t_event.type == sf::Event::MouseButtonPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		setInitialPress(m_window);
	}
	else if (t_event.type == sf::Event::MouseButtonReleased && initialPress == true)
	{
		setEndOfPress(m_window);
		swapInts(startCol, endCol);
		swapInts(startRow, endRow);

		if (startRow >= 0 && startRow < 100 && startCol >= 0 && startCol < 100 
			&& endCol >= 0 && endCol < 100 && endRow >= 0 && endRow < 100)
		{
			for (int row = startRow; row <= endRow; row++){
				for (int col = startCol; col <= endCol; col++){
					createObject(row, col);
				}
			}
		}
	}
	else if (initialPress == true)
	{
		scaleArea(m_window);
	}
}

void ObjectPlacement::moveObject(sf::Event t_event, sf::RenderWindow& m_window)
{
	if (t_event.type == sf::Event::KeyReleased)
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
}

void ObjectPlacement::placeObject(sf::Event t_event, sf::RenderWindow& m_window)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
	sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos);
	int row = worldPos.x / 32;
	int col = worldPos.y / 32;

	if (row >= 0 && row < 100 && col >= 0 && col < 100)
	{
		if (m_grid->m_vectGrid.at(row).at(col).getTileBorder().getGlobalBounds().contains(worldPos))
		{

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && initialPress == false)
			{
				if (m_currentlySelected != nullptr)
				{
					if (m_currentlySelected->m_moving == true && m_grid->m_vectGrid.at(row).at(col).m_hasObject == false)
					{
						m_currentlySelected->getBounds()->setPosition(m_grid->m_vectGrid.at(row).at(col).getPos());
						m_currentlySelected->getSprite()->setPosition(m_currentlySelected->getBounds()->getPosition());
						if (m_grid->m_vectGrid.at(row).at(col).m_hasObject == false)
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
						createObject(row, col);
				}
			}
		}
	}
}

void ObjectPlacement::selectObject(sf::Event t_event, sf::RenderWindow& m_window)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
	sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos);
	int row = worldPos.x / 32;
	int col = worldPos.y / 32;
	if (row >= 0 && row < 100 && col >= 0 && col < 100)
	{
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
					m_originalPosition = sf::Vector2i{ row,col };
					std::cout << "x : " << m_originalPosition.x << " y : " << m_originalPosition.y << std::endl;
				}

			}
		}
	}
}

void ObjectPlacement::removeObject(sf::Event t_event, sf::RenderWindow& m_window)
{
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

void ObjectPlacement::createObject(int row, int col)
{
	if (m_grid->m_vectGrid.at(row).at(col).m_hasObject == false)
	{
		if (m_tempTag.find("Enemies") != std::string::npos)
		{
			m_enemies.push_back(new Enemy(m_tempTag, m_selectedObject, m_textureManager));
			setObject(row, col, "Enemy", m_enemies);
		}
		else if (m_tempTag.find("Item") != std::string::npos)
		{
			m_items.push_back(new Item(m_tempTag, m_selectedObject, m_textureManager));
			setObject(row, col, "Item", m_items);
		}
		else if (m_tempTag.find("Decoration") != std::string::npos)
		{
			m_decorations.push_back(new Decoration(m_tempTag, m_selectedObject, m_textureManager));
			setObject(row, col, "Decoration", m_decorations);
		}
		else if (m_tempTag.find("Wall") != std::string::npos)
		{
			m_walls.push_back(new Wall(m_tempTag, m_selectedObject, m_textureManager));
			setObject(row, col, "Wall", m_walls);
		}
		else if (m_tempTag.find("Terrain") != std::string::npos)
		{
			m_grid->m_vectGrid.at(row).at(col).setFloorSprite(m_selectedObject);
			m_grid->m_vectGrid.at(row).at(col).cellType = "Terrain";
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
			if (m_grid->m_vectGrid.at(i).at(j).cellType == "Floor" || m_grid->m_vectGrid.at(i).at(j).cellType == "Terrain" || m_grid->m_vectGrid.at(i).at(j).cellType == "Empty" )
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
			sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
			sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos);

			m_currentlySelected->getBounds()->setPosition(worldPos);
			m_currentlySelected->getSprite()->setPosition(m_currentlySelected->getBounds()->getPosition());
		}
	}
}

void ObjectPlacement::render(sf::RenderWindow* t_window)
{
	renderPlacedObjects(m_decorations, t_window, m_collidersEnabled);
	renderPlacedObjects(m_items, t_window, m_collidersEnabled);
	renderPlacedObjects(m_enemies, t_window, m_collidersEnabled);
	renderPlacedObjects(m_walls, t_window, m_collidersEnabled);
	if (initialPress)
	{
		t_window->draw(m_area);
	}
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


void ObjectPlacement::setObject(int t_row, int t_col, std::string t_label, std::vector<Object*>& t_objects)
{
	m_grid->m_vectGrid.at(t_row).at(t_col).m_hasObject = true;
	m_grid->m_vectGrid.at(t_row).at(t_col).m_objectType = t_label;
	t_objects.at(t_objects.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(t_row).at(t_col).getPos());
	t_objects.at(t_objects.size() - 1)->getSprite()->setPosition(t_objects.at(t_objects.size() - 1)->getBounds()->getPosition());
	t_objects.at(t_objects.size() - 1)->setRowColumn(t_row, t_col);
}

			
