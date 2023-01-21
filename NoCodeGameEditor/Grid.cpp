#include "Grid.h"

Grid::Grid()
{
}

Grid::Grid(GameState* t_gameState)
{
	m_gameState = t_gameState;
	setUpFont();
	m_background.setSize(sf::Vector2f{ 250.0f,1080.0f });
	m_background.setPosition(1670, 0);
	m_background.setFillColor(sf::Color::Color(40,40,40,255));
	m_selectableObjects.push_back("Statue");
	m_selectableObjects.push_back("Grass");
	m_selectableObjects.push_back("Potion");
	m_selectableObjects.push_back("Enemy");
	m_selectableObjects.push_back("Water");

	regenerateGrid();
}

void Grid::setUpFont()
{
	if (!m_textFont.loadFromFile("ASSETS\\FONTS\\Arial.ttf"))
	{

	}
	m_helpText.setFont(m_textFont);
	m_helpText.setString("Right Click Mouse to \nplace floor tiles. \n\n\n\nLeft Click Mouse to \nplace walls tiles. \n\n\n\nPress Up To \nincrease Grid Size \n\n\n\nPress Down to \nDecrease grid Size.");
	m_helpText.setPosition(1700, 200);
	m_helpText.setCharacterSize(18U);
	m_helpText.setFillColor(sf::Color::White);
}
bool Grid::checkValidSelection()
{
	if (!m_selectedObject.empty())
	{
		return true;
	}
	return false;
}
void Grid::placeRemove(sf::RenderWindow& m_window)
{
	//std::cout << noOfObstacles << std::endl;
	for (int i = 0; i < m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_vectGridSize; ++j)
		{
			if (m_gameState->getState() == State::ROOM_BUILD)
			{
				if (!roomGenerated)
				{
					if (m_vectGrid.at(i).at(j)->getTileBorder().getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
					{
						m_vectGrid.at(i).at(j)->setBorderColour(sf::Color::Red);
						if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_vectGrid.at(i).at(j)->cellType == "Empty")
						{
							m_vectGrid.at(i).at(j)->setTileColour(sf::Color::Color(188, 143, 143));
							m_vectGrid.at(i).at(j)->cellType = "Wall";
							wallsPlaced++;
						}
						else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && m_vectGrid.at(i).at(j)->cellType == "Wall")
						{
							m_vectGrid.at(i).at(j)->setTileColour(sf::Color::Color(0, 0, 0, 0));
							m_vectGrid.at(i).at(j)->cellType = "Empty";
							wallsPlaced--;
						}
					}
					else
					{
						m_vectGrid.at(i).at(j)->resetBorderColour();
					}
				}
			}
			else if(m_gameState->getState() == State::ROOM_PLACE_OBJECTS)
			{
				if (m_vectGrid.at(i).at(j)->getTileBorder().getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						if (checkValidSelection())
						{
							if (m_placedObjects.size() < maxObstacles)
							{
								if (m_vectGrid.at(i).at(j)->cellType == "Floor" && m_vectGrid.at(i).at(j)->m_hasObject == false)
								{
									m_placedObjects.push_back(new Obstacle(m_selectedObject));
									m_vectGrid.at(i).at(j)->m_hasObject = true;
									m_placedObjects.at(noOfObstacles)->getBounds()->setPosition(m_vectGrid.at(i).at(j)->getPos());
									m_placedObjects.at(noOfObstacles)->setRowColumn(i,j);
									noOfObstacles++;
								}
							}
						}
					}
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
					{

						if (m_placedObjects.size() > 0)
						{

								std::vector<Obstacle*>::iterator it;
								for (it = m_placedObjects.begin(); it != m_placedObjects.end();)
								{
									Obstacle* l_obstacle = *it;
									if (l_obstacle->getBounds()->getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
									{
										// resets the right tile even if the object was moved
										m_vectGrid.at(l_obstacle->getRow()).at(l_obstacle->getColumn())->m_hasObject = false;
										it = m_placedObjects.erase(it);
										noOfObstacles--;
									}
									else
									{
										it++;
									}
								}
							
						}
					}
				}
			}
		}
	}
}

void Grid::clearObjects()
{
	m_placedObjects.clear();
	noOfObstacles = m_placedObjects.size();
	for (int i = 0; i < m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_vectGridSize; ++j)
		{
			if (m_vectGrid.at(i).at(j)->cellType == "Floor")
			{
				m_vectGrid.at(i).at(j)->m_hasObject = false;
			}
		}
	}
}


void Grid::GenerateRoomSprites()
{
	for (int i = 0; i < m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_vectGridSize; ++j)
		{
			sf::Vector2i right{ i + 1, j };
			sf::Vector2i down{ i, j + 1 };
			sf::Vector2i left{ i - 1, j };
			sf::Vector2i up{ i, j - 1 };
			if (m_vectGrid.at(i).at(j)->cellType == "Wall")
			{
				m_vectGrid.at(i).at(j)->setWallSprite();
				if (right.x < m_vectGrid.size())
				{
					if (m_vectGrid.at(right.x).at(j)->cellType != "Wall" && firstFloorSet == false)
					{
						m_firstTilePosition = m_vectGrid.at(right.x).at(j)->getPos();
						m_vectGrid.at(right.x).at(j)->cellType = "Floor";
						m_vectGrid.at(right.x).at(j)->setFloorSprite();
						m_vectGrid.at(right.x).at(j)->m_checked = true;
						firstFloorSet = true;
						m_tileQueue.push(m_vectGrid.at(right.x).at(j));
					}
				}
			}
		}
	}

	while (!m_tileQueue.empty())
	{

		for (int direction = 0; direction < 9; direction++)
		{
			if (direction == 4)
			{
				continue; // stops starting point being assigned a cost
			}

			int l_row = m_tileQueue.front()->rowColumn.x + (direction / 3) - 1;
			int l_col = m_tileQueue.front()->rowColumn.y + (direction % 3) - 1;

			if (l_row >= 0 && l_row < m_vectGrid.size() && l_col >= 0 && l_col < m_vectGrid.size() && m_vectGrid.at(l_row).at(l_col)->m_checked == false)
			{
				if (m_vectGrid.at(l_row).at(l_col)->cellType != "Empty")
				{
					continue; // stops endless loop
				}
				m_vectGrid.at(l_row).at(l_col)->m_checked = true;
				m_vectGrid.at(l_row).at(l_col)->cellType = "Floor";
				m_vectGrid.at(l_row).at(l_col)->setFloorSprite();
				m_tileQueue.push(m_vectGrid.at(l_row).at(l_col));
			}
		}
		m_tileQueue.pop();
	}
	setUpWallColliders();
	clearUnusedCells();
}

void Grid::setUpWallColliders()
{
	for (int j = 0; j < m_vectGridSize; j++)
	{
		for (int i = 0; i < m_vectGridSize; i++)
		{

			// and wall found
			if (i < m_vectGridSize -1 && m_vectGrid.at(i).at(j)->cellType == "Wall" && startFound == false)
			{
				if (m_vectGrid.at(i + 1).at(j)->cellType == "Wall")
				{
					startFound = true;
					m_colStartPos = m_vectGrid.at(i).at(j)->getPos();
					std::cout << "here" << std::endl;
				}
				continue;
			}
			else if (startFound == true)
			{
				if (i < m_vectGridSize) // goes to end of grid cell 4
				{
					if (m_vectGrid.at(i).at(j)->cellType == "Empty" || m_vectGrid.at(i).at(j)->cellType == "Floor" || i == m_vectGridSize - 1)
					{
						startFound = false;
						m_colEndPos = m_vectGrid.at(i).at(j)->getPos();


						m_vectColliders.push_back(new Colliders());
						m_vectColliders.at(noOfWallColliders)->m_wallColliderBounds.setPosition(m_colStartPos);
						m_vectColliders.at(noOfWallColliders)->setUpHorizontalWallBounds(m_colStartPos.x, m_colEndPos.x);

						noOfWallColliders++;

						std::cout << noOfWallColliders << std::endl;
						continue;
					}
				}
			}
		}
	}
	for (int i = 0; i < m_vectGridSize; i++)
	{
		for (int j = 0; j < m_vectGridSize; j++)
		{


			// and wall found
			if (j < m_vectGridSize - 1 && m_vectGrid.at(i).at(j)->cellType == "Wall" && startFound == false)
			{
				if (m_vectGrid.at(i).at(j+1)->cellType == "Wall")
				{
					startFound = true;
					m_colStartPos = m_vectGrid.at(i).at(j)->getPos();
					std::cout << "here" << std::endl;
				}
				continue;
			}
			else if (startFound == true)
			{
				if (j < m_vectGridSize) // goes to end of grid cell 4
				{
					if (m_vectGrid.at(i).at(j)->cellType == "Empty" || m_vectGrid.at(i).at(j)->cellType == "Floor" || j == m_vectGridSize - 1)
					{
						startFound = false;
						m_colEndPos = m_vectGrid.at(i).at(j)->getPos();
						int loc = m_colEndPos.y - m_colStartPos.y;

							m_vectColliders.push_back(new Colliders());
							m_vectColliders.at(noOfWallColliders)->m_wallColliderBounds.setPosition(m_colStartPos);
							m_vectColliders.at(noOfWallColliders)->setUpVerticalWallBounds(m_colStartPos.y, m_colEndPos.y);
							
							noOfWallColliders++;
						
						std::cout << noOfWallColliders << std::endl;

						continue;
					}
				}
			}
		}
	}
}

void Grid::clearUnusedCells()
{
	for (int i = 0; i < m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_vectGridSize; ++j)
		{
			if (m_vectGrid.at(i).at(j)->cellType == "Empty")
			{
				m_vectGrid.at(i).at(j)->setBorderColour(sf::Color(sf::Color(0, 0, 0, 0)));
			}
		}
	}

}

void Grid::checkRoomValidity()
{
	roomValid = true;
	for (int i = 0; i < m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_vectGridSize; ++j)
		{
			if (m_vectGrid.at(i).at(j)->cellType == "Wall")
			{
				CheckValidityOfWalls(i, j);
			}
			if (m_vectGrid.at(i).at(j)->validInvalid == "NotValid")
			{
				roomValid = false;
				//std::cout << "This room is not valid" << std::endl;
			}
		}
	}
	if (roomValid && wallsPlaced >= minimumWalls && roomGenerated == false)
	{
		roomGenerated = true;
		//std::cout << "This room is valid" << std::endl;
		GenerateRoomSprites();
		m_gameState->setState(State::ROOM_PLACE_OBJECTS);
	}
	else
	{
		//std::cout << "This room is invalid" << std::endl;
		for (int i = 0; i < m_vectGridSize; ++i)
		{
			for (int j = 0; j < m_vectGridSize; ++j)
			{
				m_vectGrid.at(i).at(j)->m_checked = false;
				m_vectGrid.at(i).at(j)->validInvalid = " ";
			}
		}
	}
}

void Grid::CheckValidityOfWalls(int t_row, int t_col)
{
	sf::Vector2i up{ t_row, t_col - 1 };
	sf::Vector2i down{ t_row, t_col + 1 };
	sf::Vector2i right{ t_row + 1, t_col };
	sf::Vector2i left{ t_row - 1, t_col };

	counter = 0;
	if (up.y >= 0)
	{
		if (m_vectGrid.at(up.x).at(up.y)->cellType == "Wall")
		{
			
			counter = counter + 1;
			//std::cout << counter << std::endl;
		}
	}
	if (down.y <m_vectGrid.size())
	{
		if (m_vectGrid.at(down.x).at(down.y)->cellType == "Wall")
		{
			counter = counter + 1;
			//std::cout << counter << std::endl;
		}
	}
	if (left.x >= 0)
	{
		if (m_vectGrid.at(left.x).at(left.y)->cellType == "Wall")
		{
			counter = counter + 1;
			//std::cout << counter << std::endl;
		}
	}
	if (right.x < m_vectGrid.size())
	{
		if (m_vectGrid.at(right.x).at(right.y)->cellType == "Wall")
		{
			counter = counter + 1;
			//std::cout << counter << std::endl;
		}
	}
	if (counter == 2)
	{
		m_vectGrid.at(t_row).at(t_col)->setTileColour(sf::Color::Blue);
		m_vectGrid.at(t_row).at(t_col)->validInvalid = "ValidWall";
	}
	else
	{
		m_vectGrid.at(t_row).at(t_col)->validInvalid = "NotValid";
		m_vectGrid.at(t_row).at(t_col)->setTileColour(sf::Color::Red);
	}
}

void Grid::increaseGridSize()
{
	if (m_vectGridSize < 16)
	{
		m_vectGridSize = m_vectGridSize + 1;
		regenerateGrid();
	}
}

void Grid::decreaseGridSize()
{
	if (m_vectGridSize > 5)
	{
		m_vectGridSize = m_vectGridSize - 1;
		regenerateGrid();
	}
}

void Grid::setSelectedObject(std::string t_path, std::string t_objectName)
{
	m_selectedObject = t_path + t_objectName;
}


void Grid::update(sf::Time t_deltaTime, sf::RenderWindow& m_window)
{
	placeRemove( m_window);
	for (int i = 0; i < m_placedObjects.size(); i++)
	{
		m_placedObjects.at(i)->getSprite()->setPosition(m_placedObjects.at(i)->getBounds()->getPosition());
	}
}

void Grid::render(sf::RenderWindow* t_window)
{
	t_window->draw(m_background);
	t_window->draw(m_helpText);
	for (int i = 0; i < m_vectGridSize; i++)
	{
		for (int j = 0; j < m_vectGridSize; j++)
		{
			t_window->draw(m_vectGrid.at(i).at(j)->getTileBorder());
			t_window->draw(m_vectGrid.at(i).at(j)->getTile());
		}
	}
	for (int i = 0; i < m_vectColliders.size(); i++)
	{
		m_vectColliders.at(i)->render(t_window);
	}
	for (int i = 0; i < m_placedObjects.size(); i++)
	{
		t_window->draw(*m_placedObjects.at(i)->getSprite());
		t_window->draw(*m_placedObjects.at(i)->getBounds());
	}
}


void Grid::regenerateGrid()
{
	noOfWallColliders = 0;
	noOfObstacles = 0;
	m_vectGrid.clear();
	m_vectColliders.clear();
	m_placedObjects.clear();
	wallsPlaced = 0;
	m_playerSet = false;
	firstFloorSet = false;
	roomGenerated = false;
	for (int i = 0; i < m_vectGridSize; ++i)
	{
		std::vector<Tile*> row;
		for (int j = 0; j < m_vectGridSize; ++j)
		{
			row.push_back(new Tile(m_textFont));
		}
		m_vectGrid.push_back(row);
	}
	for (int i = 0; i < m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_vectGridSize; ++j)
		{
			m_vectGrid.at(i).at(j)->setPosition(m_vectGrid.at(i).at(j)->m_width * i + 960 - (m_vectGridSize * 16), m_vectGrid.at(i).at(j)->m_width * j + 540 - (m_vectGridSize * 16));
			m_vectGrid.at(i).at(j)->rowColumn = sf::Vector2i{ i,j };
			m_vectGrid.at(i).at(j)->setTileColour(sf::Color::Color(200, 200, 220,0));
			m_vectGrid.at(i).at(j)->cellType = "Empty";
			m_vectGrid.at(i).at(j)->m_checked = false;
			m_vectGrid.at(i).at(j)->m_colliderCheck = false;
		}
	}
}
