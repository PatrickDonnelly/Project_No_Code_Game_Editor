#include "ObjectPlacement.h"

/// <summary>
/// Default constructor for object placement
/// </summary>
ObjectPlacement::ObjectPlacement()
{
}

/// <summary>
/// Overloaded constructor for object placement that takes
/// in a pointer to the game state, grid and to the texture manager
/// </summary>
/// <param name="t_gameState"></param>
/// <param name="t_grid"></param>
/// <param name="t_textureManager"></param>
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

/// <summary>
/// Deconstructor
/// </summary>
ObjectPlacement::~ObjectPlacement()
{
}

/// <summary>
/// Check if a valid object was selected was made
/// </summary>
/// <returns></returns>
bool ObjectPlacement::checkValidSelection()
{
	if (!m_selectedObject.empty())
	{
		return true;
	}
	return false;
}

/// <summary>
/// Check for a double click on the mouse
/// </summary>
/// <param name="t_clock"></param>
/// <param name="t_doubleClickTime"></param>
/// <returns></returns>
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

/// <summary>
/// swaps two values
/// </summary>
/// <param name="t_smallerNumber"></param>
/// <param name="t_biggerNumber"></param>
void ObjectPlacement::swapInts(int& t_smallerNumber, int& t_biggerNumber)
{
	if (t_biggerNumber < t_smallerNumber)
	{
		int temp = t_smallerNumber;
		t_smallerNumber = t_biggerNumber;
		t_biggerNumber = temp;
	}
}

/// <summary>
/// processes mouse events
/// </summary>
/// <param name="t_event"></param>
/// <param name="t_window"></param>
void ObjectPlacement::processEvents(sf::Event t_event, sf::RenderWindow& t_window)
{
	placeMultipleObjects(t_event, t_window);
	placeObject(t_event, t_window);
	removeObject(t_event, t_window);
	moveObject(t_event, t_window);
	selectObject(t_event, t_window);
	sf::Vector2i pixelPos = sf::Mouse::getPosition(t_window);

	sf::Vector2f worldPos = t_window.mapPixelToCoords(pixelPos);
	int row = worldPos.x / 32;
	int col = worldPos.y / 32;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::C) && initialPress == false)
	{
		if (m_currentlySelected != nullptr)
		{

			m_currentlySelected->setSelected(false);

		}
		m_tempTag = "";
		m_currentlySelected = nullptr;
		m_selectedObject = "";
		if (m_grid->m_vectGrid.at(row).at(col).m_hasObject == false)
		{
			m_colliders.push_back(Colliders());
			m_grid->m_vectGrid.at(row).at(col).m_hasObject = true;
			m_grid->m_vectGrid.at(row).at(col).m_objectType = "Collider";
			m_colliders.at(m_colliders.size() - 1).getBounds()->setPosition(m_grid->m_vectGrid.at(row).at(col).getPos());
			m_colliders.at(m_colliders.size() - 1).setRowColumn(row, col);
		}
	}
}

/// <summary>
/// Sets the initial position of where a mouse clicked occured
/// </summary>
/// <param name="m_window"></param>
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

/// <summary>
/// set the end of a mouse press
/// </summary>
/// <param name="m_window"></param>
void ObjectPlacement::setEndOfPress(sf::RenderWindow& m_window)
{
	initialPress = false;
	m_screenPos = sf::Mouse::getPosition(m_window);
	m_worldPos = m_window.mapPixelToCoords(m_screenPos);
	endRow = m_worldPos.x / 32;
	endCol = m_worldPos.y / 32;
}

/// <summary>
/// Set the area of where multiple objects are going to be placed.
/// </summary>
/// <param name="m_window"></param>
void ObjectPlacement::scaleArea(sf::RenderWindow& m_window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
	sf::Vector2f currentMousePosition = m_window.mapPixelToCoords(mousePosition, m_gameView);
	m_area.setSize(sf::Vector2f(currentMousePosition.x - m_worldPos.x, currentMousePosition.y - m_worldPos.y));
}

/// <summary>
/// Allows you place multiple objects
///  as well as deleting them
/// </summary>
/// <param name="t_event"></param>
/// <param name="m_window"></param>
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
		if (t_event.mouseButton.button == sf::Mouse::Left && sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			if (startRow >= 0 && startRow < 100 && startCol >= 0 && startCol < 100
				&& endCol >= 0 && endCol < 100 && endRow >= 0 && endRow < 100)
			{
				for (int row = startRow; row <= endRow; row++) {
					for (int col = startCol; col <= endCol; col++) {
						m_currentlySelected = nullptr;
						m_colliders.push_back(Colliders());
						m_grid->m_vectGrid.at(row).at(col).m_hasObject = true;
						m_grid->m_vectGrid.at(row).at(col).m_objectType = "Collider";
						m_colliders.at(m_colliders.size() - 1).getBounds()->setPosition(m_grid->m_vectGrid.at(row).at(col).getPos());
						m_colliders.at(m_colliders.size() - 1).setRowColumn(row, col);
					}
				}
			}
		}
		else if (t_event.mouseButton.button == sf::Mouse::Left)
		{
			if (startRow >= 0 && startRow < 100 && startCol >= 0 && startCol < 100
				&& endCol >= 0 && endCol < 100 && endRow >= 0 && endRow < 100)
			{
				for (int row = startRow; row <= endRow; row++) {
					for (int col = startCol; col <= endCol; col++) {
						createObject(row, col);
					}
				}
			}
		}
		else if (t_event.mouseButton.button == sf::Mouse::Right)
		{
			if (startRow >= 0 && startRow < 100 && startCol >= 0 && startCol < 100
				&& endCol >= 0 && endCol < 100 && endRow >= 0 && endRow < 100)
			{
				for (int row = startRow; row <= endRow; row++) {
					for (int col = startCol; col <= endCol; col++) {
						m_grid->m_vectGrid.at(row).at(col).removeTexture();
						m_grid->m_vectGrid.at(row).at(col).m_hasObject = false;
						m_grid->m_vectGrid.at(row).at(col).cellType = "Empty";
						deleteMultipleObjects(m_walls, row, col);
						deleteMultipleObjects(m_items, row, col);
						deleteMultipleObjects(m_decorations, row, col);
						deleteMultipleObjects(m_enemies, row, col);

						for (std::vector<Colliders>::iterator iter = m_colliders.begin(); iter != m_colliders.end();)
						{
							if ((iter)->getRow() == row
								&& (iter)->getColumn() == col)
							{
								iter = m_colliders.erase(iter);
								m_grid->m_vectGrid.at(row).at(col).m_hasObject = false;
								m_grid->m_vectGrid.at(row).at(col).cellType = "Empty";

							}
							else
							{
								iter++;
							}

						}
					}
				}
			}
		}
	}
	else if (initialPress == true)
	{
		scaleArea(m_window);
	}
}

/// <summary>
/// iterate through a vector of objects and delete any that fall
/// within the highlighted area
/// </summary>
/// <param name="t_objects"></param>
/// <param name="t_row"></param>
/// <param name="t_col"></param>
void ObjectPlacement::deleteMultipleObjects(std::vector<Object*>& t_objects, int t_row, int t_col)
{
	for (std::vector<Object*>::iterator iter = t_objects.begin(); iter != t_objects.end();)
	{
		if ((*iter)->getRow() == t_row
			&& (*iter)->getColumn() == t_col)
		{
			iter = t_objects.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

/// <summary>
/// Move a selected object to a new location on the grid
/// </summary>
/// <param name="t_event"></param>
/// <param name="m_window"></param>
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

/// <summary>
/// Place a selected object on the grid
/// </summary>
/// <param name="t_event"></param>
/// <param name="m_window"></param>
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
			if (m_squareBounds.contains(sf::Vector2f(pixelPos)))
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
}

/// <summary>
/// Select an object already on the grid
/// </summary>
/// <param name="t_event"></param>
/// <param name="m_window"></param>
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
			if (m_squareBounds.contains(sf::Vector2f(pixelPos)))
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
						else if (m_grid->m_vectGrid.at(row).at(col).m_objectType == "Collider")
						{
							m_storedObjectType = "Collider";
							for (int i = 0; i < m_colliders.size(); ++i)
							{
								if (m_colliders.at(i).getBounds()->getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
								{
									m_currentlySelected = &m_colliders.at(i);
									m_currentlySelected->setSelected(true);
								}
							}
						}
						m_originalPosition = sf::Vector2i{ row,col };
						std::cout << "x : " << m_originalPosition.x << " y : " << m_originalPosition.y << std::endl;
					}

				}
			}
		}
	}
}

/// <summary>
/// Delete an object
/// </summary>
/// <param name="t_event"></param>
/// <param name="m_window"></param>
void ObjectPlacement::removeObject(sf::Event t_event, sf::RenderWindow& m_window)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
	sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos);
	int row = worldPos.x / 32;
	int col = worldPos.y / 32;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && initialPress == false)
	{
		deleteObject(m_decorations, m_grid, m_window);
		deleteObject(m_terrain, m_grid, m_window);
		deleteObject(m_walls, m_grid, m_window);
		deleteObject(m_enemies, m_grid, m_window);
		deleteObject(m_items, m_grid, m_window);
		if (m_grid->m_vectGrid.at(row).at(col).getTileBorder().getGlobalBounds().contains(worldPos))
		{
			if (m_squareBounds.contains(sf::Vector2f(pixelPos)))
			{
				for (std::vector<Colliders>::iterator iter = m_colliders.begin(); iter != m_colliders.end();)
				{
					if ((iter)->getRow() == row
						&& (iter)->getColumn() == col)
					{
						iter = m_colliders.erase(iter);
						m_grid->m_vectGrid.at(row).at(col).m_hasObject = false;
						m_grid->m_vectGrid.at(row).at(col).cellType = "Empty";

					}
					else
					{
						iter++;
					}
				}
			}
		}
		m_currentlySelected = nullptr;
	}

	if (row >= 0 && row < 100 && col >= 0 && col < 100)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (m_grid->m_vectGrid.at(row).at(col).getTileBorder().getGlobalBounds().contains(worldPos))
			{
				if (m_squareBounds.contains(sf::Vector2f(pixelPos)))
				{
					m_grid->m_vectGrid.at(row).at(col).removeTexture();
				}
			}
			
		}
	}
}

/// <summary>
/// create an object and set ithe type of object to be placed on the grid.
/// </summary>
/// <param name="row"></param>
/// <param name="col"></param>
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
	}
	if (m_tempTag.find("Terrain") != std::string::npos)
	{
			m_grid->m_vectGrid.at(row).at(col).setFloorSprite(m_selectedObject);
			m_grid->m_vectGrid.at(row).at(col).cellType = "Terrain";
	}
}

/// <summary>
/// Clear the grid and reset its tiles values to have no object
/// </summary>
void ObjectPlacement::clearObjects()
{
	m_enemies.clear();
	m_terrain.clear();
	m_walls.clear();
	m_items.clear();
	m_decorations.clear();
	m_colliders.clear();
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

/// <summary>
/// Update collider sizes and the currently selected object
/// </summary>
/// <param name="t_deltaTime"></param>
/// <param name="m_window"></param>
void ObjectPlacement::update(sf::Time t_deltaTime, sf::RenderWindow& m_window)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		for (int i = 0; i < m_colliders.size(); i++)
		{
			m_colliders.at(i).increaseWidth();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		for (int i = 0; i < m_colliders.size(); i++)
		{
			m_colliders.at(i).decreaseWidth();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		for (int i = 0; i < m_colliders.size(); i++)
		{
			m_colliders.at(i).increaseHeight();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		for (int i = 0; i < m_colliders.size(); i++)
		{
			m_colliders.at(i).decreaseHeight();
		}
	}

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

/// <summary>
/// Renders placed objects, independent colliders and the highlighted areas
/// </summary>
/// <param name="t_window"></param>
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
	if (m_collidersEnabled)
	{
		for (auto collider : m_colliders)
		{
			collider.render(*t_window);
		}
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

			
