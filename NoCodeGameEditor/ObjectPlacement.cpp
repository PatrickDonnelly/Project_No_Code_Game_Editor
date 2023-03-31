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
	if (t_event.type == sf::Event::KeyReleased) 
	{

		if (t_event.key.code == sf::Keyboard::Space)
		{
			if (m_currentlySelected != nullptr)
			{
				m_currentlySelected->setMoving(true);
				m_grid->m_vectGrid.at(m_originalPosition.x).at(m_originalPosition.y)->m_objectType = "";
				m_grid->m_vectGrid.at(m_originalPosition.x).at(m_originalPosition.y)->m_hasObject = false;
			}
		}
	}


	//std::cout << noOfObstacles << std::endl;
	for (int i = 0; i < m_grid->m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_grid->m_vectGridSize; ++j)
		{
			if (m_grid->m_vectGrid.at(i).at(j)->getTileBorder().getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
			{

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (m_currentlySelected != nullptr)
					{	
						if (m_currentlySelected->m_moving == true && m_grid->m_vectGrid.at(i).at(j)->m_hasObject == false)
						{
							m_currentlySelected->getBounds()->setPosition(m_grid->m_vectGrid.at(i).at(j)->getPos());
							m_currentlySelected->getSprite()->setPosition(m_currentlySelected->getBounds()->getPosition());
							if (m_grid->m_vectGrid.at(i).at(j)->cellType == "Floor" && m_grid->m_vectGrid.at(i).at(j)->m_hasObject == false)
							{
								m_currentlySelected->setSelected(false);
								m_currentlySelected->setMoving(false);
								m_currentlySelected = nullptr;
								m_grid->m_vectGrid.at(i).at(j)->m_hasObject = true;
								m_grid->m_vectGrid.at(i).at(j)->m_objectType = m_storedObjectType;


								m_originalPosition = sf::Vector2i{ 0,0 };
							}
						}
						else if(m_currentlySelected->m_moving == false)
						{
							m_currentlySelected->setSelected(false);
							m_currentlySelected = nullptr;
						}

					}
					else if (checkValidSelection())
					{

						if (m_grid->m_vectGrid.at(i).at(j)->cellType == "Floor" && m_grid->m_vectGrid.at(i).at(j)->m_hasObject == false)
						{
							//addObjectToGrid(m_enemies, Enemy, i, j, m_tempTag, m_selectedObject, m_vectGrid);

							if (m_tempTag.find("Enemies") != std::string::npos)
							{
								std::cout << m_tempTag << std::endl;
								m_enemies.push_back(new Enemy(m_tempTag, m_selectedObject, m_textureManager));
								m_grid->m_vectGrid.at(i).at(j)->m_hasObject = true;
								m_grid->m_vectGrid.at(i).at(j)->m_objectType = "Enemy";
								m_enemies.at(m_enemies.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(i).at(j)->getPos());
								m_enemies.at(m_enemies.size() - 1)->getSprite()->setPosition(m_enemies.at(m_enemies.size() - 1)->getBounds()->getPosition());
								m_enemies.at(m_enemies.size() - 1)->setRowColumn(i, j);
								//m_currentlySelected->setSelected();
								//m_currentlySelected = m_enemies.at(m_enemies.size() - 1);
								//m_currentlySelected->setSelected();

							}
							if (m_tempTag.find("Item") != std::string::npos)
							{
								m_items.push_back(new Item(m_tempTag, m_selectedObject, m_textureManager));
								m_grid->m_vectGrid.at(i).at(j)->m_hasObject = true;
								m_grid->m_vectGrid.at(i).at(j)->m_objectType = "Item";
								m_items.at(m_items.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(i).at(j)->getPos());
								m_items.at(m_items.size() - 1)->getSprite()->setPosition(m_items.at(m_items.size() - 1)->getBounds()->getPosition());
								m_items.at(m_items.size() - 1)->setRowColumn(i, j);

							}
							if (m_tempTag.find("Decoration") != std::string::npos)
							{
								m_decorations.push_back(new Decoration(m_tempTag, m_selectedObject, m_textureManager));
								m_grid->m_vectGrid.at(i).at(j)->m_hasObject = true;
								m_grid->m_vectGrid.at(i).at(j)->m_objectType = "Decoration";
								m_decorations.at(m_decorations.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(i).at(j)->getPos());
								m_decorations.at(m_decorations.size() - 1)->getSprite()->setPosition(m_decorations.at(m_decorations.size() - 1)->getBounds()->getPosition());
								m_decorations.at(m_decorations.size() - 1)->setRowColumn(i, j);
								//m_currentlySelected->setSelected();
								//m_currentlySelected = m_decorations.at(m_decorations.size() - 1);
								//m_currentlySelected->setSelected();
							}
							if (m_tempTag.find("Wall") != std::string::npos)
							{
								m_walls.push_back(new Wall(m_tempTag, m_selectedObject, m_textureManager));
								m_grid->m_vectGrid.at(i).at(j)->m_hasObject = true;
								m_grid->m_vectGrid.at(i).at(j)->m_objectType = "Wall";
								m_walls.at(m_walls.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(i).at(j)->getPos());
								m_walls.at(m_walls.size() - 1)->getSprite()->setPosition(m_walls.at(m_walls.size() - 1)->getBounds()->getPosition());
								m_walls.at(m_walls.size() - 1)->setRowColumn(i, j);

							}

						}
						if (m_grid->m_vectGrid.at(i).at(j)->cellType == "Floor")
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
								m_grid->m_vectGrid.at(i).at(j)->setFloorSprite(m_selectedObject);
							}

						}

					}

				}
				if (t_event.type == sf::Event::MouseButtonPressed && t_event.mouseButton.button == sf::Mouse::Left)
				{
					if (checkForDoubleClick(m_clock, m_doubleClickTime))
					{
						std::cout << "Double Click" << std::endl;

						std::cout << "hasObject : " << m_grid->m_vectGrid.at(i).at(j)->m_hasObject << std::endl;
						if (m_grid->m_vectGrid.at(i).at(j)->m_hasObject == true)
						{
							std::cout << "hasObject" << std::endl;
							if (m_currentlySelected != nullptr)
							{
								m_currentlySelected->setSelected(false);
								m_currentlySelected = nullptr;
							}




								if (m_grid->m_vectGrid.at(i).at(j)->m_objectType == "Enemy")
								{
									m_storedObjectType = "Enemy";
									setSelectedGridObject(m_enemies, m_window);
								}
								else if (m_grid->m_vectGrid.at(i).at(j)->m_objectType == "Item")
								{
									m_storedObjectType = "Item";
									setSelectedGridObject(m_items, m_window);
								}
								else if (m_grid->m_vectGrid.at(i).at(j)->m_objectType == "Decoration")
								{
									m_storedObjectType = "Decoration";
									setSelectedGridObject(m_decorations, m_window);
								}
								else if (m_grid->m_vectGrid.at(i).at(j)->m_objectType == "Wall")
								{
									m_storedObjectType = "Wall";
									setSelectedGridObject(m_walls, m_window);
								}
								//setSelected(m_enemies, &m_window, m_currentlySelected);
								//setSelected(m_items, &m_window, m_currentlySelected);
								//setSelected(m_decorations, &m_window, m_currentlySelected);
								//setSelected(m_walls, &m_window, m_currentlySelected);
								m_originalPosition = sf::Vector2i{ i,j };
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
			if (m_grid->m_vectGrid.at(i).at(j)->cellType == "Floor")
			{
				m_grid->m_vectGrid.at(i).at(j)->m_hasObject = false;
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

