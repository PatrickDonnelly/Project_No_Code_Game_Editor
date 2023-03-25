#include "ObjectPlacement.h"

ObjectPlacement::ObjectPlacement()
{
}

ObjectPlacement::ObjectPlacement(GameState* t_gameState, Grid* t_grid)
{
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
void ObjectPlacement::placeRemove(sf::RenderWindow& m_window)
{
	//std::cout << noOfObstacles << std::endl;
	for (int i = 0; i < m_grid->m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_grid->m_vectGridSize; ++j)
		{
			if (m_grid->m_vectGrid.at(i).at(j)->getTileBorder().getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					if (checkValidSelection())
					{

						if (m_grid->m_vectGrid.at(i).at(j)->cellType == "Floor" && m_grid->m_vectGrid.at(i).at(j)->m_hasObject == false)
						{
							//addObjectToGrid(m_enemies, Enemy, i, j, m_tempTag, m_selectedObject, m_vectGrid);

							if (m_tempTag.find("Enemies") != std::string::npos)
							{
								m_enemies.push_back(new Enemy(m_tempTag, m_selectedObject));
								m_grid->m_vectGrid.at(i).at(j)->m_hasObject = true;
								m_enemies.at(m_enemies.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(i).at(j)->getPos());
								m_enemies.at(m_enemies.size() - 1)->getSprite()->setPosition(m_enemies.at(m_enemies.size() - 1)->getBounds()->getPosition());
								m_enemies.at(m_enemies.size() - 1)->setRowColumn(i, j);
							}
							if (m_tempTag.find("Item") != std::string::npos)
							{
								m_items.push_back(new Enemy(m_tempTag, m_selectedObject));
								m_grid->m_vectGrid.at(i).at(j)->m_hasObject = true;
								m_items.at(m_items.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(i).at(j)->getPos());
								m_items.at(m_items.size() - 1)->getSprite()->setPosition(m_items.at(m_items.size() - 1)->getBounds()->getPosition());
								m_items.at(m_items.size() - 1)->setRowColumn(i, j);
							}
							if (m_tempTag.find("Decoration") != std::string::npos)
							{
								m_decorations.push_back(new Enemy(m_tempTag, m_selectedObject));
								m_grid->m_vectGrid.at(i).at(j)->m_hasObject = true;
								m_decorations.at(m_decorations.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(i).at(j)->getPos());
								m_decorations.at(m_decorations.size() - 1)->getSprite()->setPosition(m_decorations.at(m_decorations.size() - 1)->getBounds()->getPosition());
								m_decorations.at(m_decorations.size() - 1)->setRowColumn(i, j);
							}
							if (m_tempTag.find("Wall") != std::string::npos)
							{
								m_walls.push_back(new Enemy(m_tempTag, m_selectedObject));
								m_grid->m_vectGrid.at(i).at(j)->m_hasObject = true;
								m_walls.at(m_walls.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(i).at(j)->getPos());
								m_walls.at(m_walls.size() - 1)->getSprite()->setPosition(m_walls.at(m_walls.size() - 1)->getBounds()->getPosition());
								m_walls.at(m_walls.size() - 1)->setRowColumn(i, j);
							}
							noOfObstacles++;
						}
						if (m_grid->m_vectGrid.at(i).at(j)->cellType == "Floor")
						{
							if (m_tempTag.find("Terrain") != std::string::npos)
							{
								m_terrain.push_back(new Terrain(m_tempTag, m_selectedObject));
								// check collision for overlapping terrain
								m_terrain.at(m_terrain.size() - 1)->getBounds()->setPosition(m_grid->m_vectGrid.at(i).at(j)->getPos());
								m_terrain.at(m_terrain.size() - 1)->getSprite()->setPosition(m_terrain.at(m_terrain.size() - 1)->getBounds()->getPosition());

								m_terrain.at(m_terrain.size() - 1)->setRowColumn(i, j);
							}
						}

					}
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			{
				deleteObject(m_decorations, m_grid, noOfObstacles, m_window);
				deleteObject(m_terrain, m_grid, noOfObstacles, m_window);
				deleteObject(m_walls, m_grid, noOfObstacles, m_window);
				deleteObject(m_enemies, m_grid, noOfObstacles, m_window);
				deleteObject(m_items, m_grid, noOfObstacles, m_window);
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
	placeRemove(m_window);
}

void ObjectPlacement::render(sf::RenderWindow* t_window)
{
	renderPlacedObjects(m_terrain, t_window, m_collidersEnabled);
	renderPlacedObjects(m_decorations, t_window, m_collidersEnabled);
	renderPlacedObjects(m_items, t_window, m_collidersEnabled);
	renderPlacedObjects(m_enemies, t_window, m_collidersEnabled);
	renderPlacedObjects(m_walls, t_window, m_collidersEnabled);
}
