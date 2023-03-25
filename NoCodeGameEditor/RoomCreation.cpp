#include "RoomCreation.h"

RoomCreation::RoomCreation()
{
}

RoomCreation::RoomCreation(GameState* t_gameState, Grid* t_grid)
{
	m_grid = t_grid;
	m_gameState = t_gameState;
}

RoomCreation::~RoomCreation()
{
}

void RoomCreation::placeRemove(sf::RenderWindow& m_window)
{
	//std::cout << noOfObstacles << std::endl;
	for (int i = 0; i < m_grid->m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_grid->m_vectGridSize; ++j)
		{
				
					if (m_grid->m_vectGrid.at(i).at(j)->getTileBorder().getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
					{
						m_grid->m_vectGrid.at(i).at(j)->setBorderColour(sf::Color::Red);
						if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_grid->m_vectGrid.at(i).at(j)->cellType == "Empty")
						{
							m_grid->m_vectGrid.at(i).at(j)->setTileColour(sf::Color::Color(188, 143, 143));
							m_grid->m_vectGrid.at(i).at(j)->cellType = "Wall";
							wallsPlaced++;
						}
						else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && m_grid->m_vectGrid.at(i).at(j)->cellType == "Wall")
						{
							m_grid->m_vectGrid.at(i).at(j)->setTileColour(sf::Color::Color(0, 0, 0, 0));
							m_grid->m_vectGrid.at(i).at(j)->cellType = "Empty";
							wallsPlaced--;
						}
					}
					else
					{
						m_grid->m_vectGrid.at(i).at(j)->resetBorderColour();
					}
				
			
		}
	}
}

void RoomCreation::GenerateRoomSprites()
{
	for (int i = 0; i < m_grid->m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_grid->m_vectGridSize; ++j)
		{
			sf::Vector2i right{ i + 1, j };
			sf::Vector2i down{ i, j + 1 };
			sf::Vector2i left{ i - 1, j };
			sf::Vector2i up{ i, j - 1 };
			if (m_grid->m_vectGrid.at(i).at(j)->cellType == "Wall")
			{
				m_grid->m_vectGrid.at(i).at(j)->setWallSprite();
				if (right.x < m_grid->m_vectGrid.size())
				{
					if (m_grid->m_vectGrid.at(right.x).at(j)->cellType != "Wall" && firstFloorSet == false)
					{
						m_firstTilePosition = m_grid->m_vectGrid.at(right.x).at(j)->getPos();
						m_grid->m_vectGrid.at(right.x).at(j)->cellType = "Floor";
						m_grid->m_vectGrid.at(right.x).at(j)->setFloorSprite();
						m_grid->m_vectGrid.at(right.x).at(j)->m_checked = true;
						firstFloorSet = true;
						m_tileQueue.push(m_grid->m_vectGrid.at(right.x).at(j));
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

			if (l_row >= 0 && l_row < m_grid->m_vectGrid.size() && l_col >= 0 && l_col < m_grid->m_vectGrid.size() && m_grid->m_vectGrid.at(l_row).at(l_col)->m_checked == false)
			{
				if (m_grid->m_vectGrid.at(l_row).at(l_col)->cellType != "Empty")
				{
					continue; // stops endless loop
				}
				m_grid->m_vectGrid.at(l_row).at(l_col)->m_checked = true;
				m_grid->m_vectGrid.at(l_row).at(l_col)->cellType = "Floor";
				m_grid->m_vectGrid.at(l_row).at(l_col)->setFloorSprite();
				m_tileQueue.push(m_grid->m_vectGrid.at(l_row).at(l_col));
			}
		}
		m_tileQueue.pop();
	}
	setUpWallColliders();
	clearUnusedCells();
}

void RoomCreation::setUpWallColliders()
{
	for (int j = 0; j < m_grid->m_vectGridSize; j++)
	{
		for (int i = 0; i < m_grid->m_vectGridSize; i++)
		{

			// and wall found
			if (i < m_grid->m_vectGridSize - 1 && m_grid->m_vectGrid.at(i).at(j)->cellType == "Wall" && startFound == false)
			{
				if (m_grid->m_vectGrid.at(i + 1).at(j)->cellType == "Wall")
				{
					startFound = true;
					m_colStartPos = m_grid->m_vectGrid.at(i).at(j)->getPos();
					std::cout << "here" << std::endl;
				}
				continue;
			}
			else if (startFound == true)
			{
				if (i < m_grid->m_vectGridSize) // goes to end of grid cell 4
				{
					if (m_grid->m_vectGrid.at(i).at(j)->cellType == "Empty" || m_grid->m_vectGrid.at(i).at(j)->cellType == "Floor" || i == m_grid->m_vectGridSize - 1)
					{
						startFound = false;
						m_colEndPos = m_grid->m_vectGrid.at(i).at(j)->getPos();


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
	for (int i = 0; i < m_grid->m_vectGridSize; i++)
	{
		for (int j = 0; j < m_grid->m_vectGridSize; j++)
		{


			// and wall found
			if (j < m_grid->m_vectGridSize - 1 && m_grid->m_vectGrid.at(i).at(j)->cellType == "Wall" && startFound == false)
			{
				if (m_grid->m_vectGrid.at(i).at(j + 1)->cellType == "Wall")
				{
					startFound = true;
					m_colStartPos = m_grid->m_vectGrid.at(i).at(j)->getPos();
					std::cout << "here" << std::endl;
				}
				continue;
			}
			else if (startFound == true)
			{
				if (j < m_grid->m_vectGridSize) // goes to end of grid cell 4
				{
					if (m_grid->m_vectGrid.at(i).at(j)->cellType == "Empty" || m_grid->m_vectGrid.at(i).at(j)->cellType == "Floor" || j == m_grid->m_vectGridSize - 1)
					{
						startFound = false;
						m_colEndPos = m_grid->m_vectGrid.at(i).at(j)->getPos();
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

void RoomCreation::resetValues()
{
	startFound = false;
	roomValid = false;
	firstFloorSet = false;
	wallsPlaced = 0;
	noOfWallColliders = 0;
	roomGenerated = false;
	counter = 0;
	m_vectColliders.clear();
}

void RoomCreation::clearUnusedCells()
{
	for (int i = 0; i < m_grid->m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_grid->m_vectGridSize; ++j)
		{
			if (m_grid->m_vectGrid.at(i).at(j)->cellType == "Empty")
			{
				m_grid->m_vectGrid.at(i).at(j)->setBorderColour(sf::Color(sf::Color(0, 0, 0, 0)));
			}
		}
	}

}

void RoomCreation::checkRoomValidity()
{
	roomValid = true;
	for (int i = 0; i < m_grid->m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_grid->m_vectGridSize; ++j)
		{
			if (m_grid->m_vectGrid.at(i).at(j)->cellType == "Wall")
			{
				CheckValidityOfWalls(i, j);
			}
			if (m_grid->m_vectGrid.at(i).at(j)->validInvalid == "NotValid")
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
		for (int i = 0; i < m_grid->m_vectGridSize; ++i)
		{
			for (int j = 0; j < m_grid->m_vectGridSize; ++j)
			{
				m_grid->m_vectGrid.at(i).at(j)->m_checked = false;
				m_grid->m_vectGrid.at(i).at(j)->validInvalid = " ";
			}
		}
	}
}

void RoomCreation::update(sf::Time t_deltaTime, sf::RenderWindow& m_window)
{
	placeRemove(m_window);
}

void RoomCreation::render(sf::RenderWindow* t_window)
{

		for (int i = 0; i < m_vectColliders.size(); i++)
		{
			t_window->draw(*m_vectColliders.at(i)->getBounds());
		}
	
}

void RoomCreation::CheckValidityOfWalls(int t_row, int t_col)
{
	sf::Vector2i up{ t_row, t_col - 1 };
	sf::Vector2i down{ t_row, t_col + 1 };
	sf::Vector2i right{ t_row + 1, t_col };
	sf::Vector2i left{ t_row - 1, t_col };

	counter = 0;
	if (up.y >= 0)
	{
		if (m_grid->m_vectGrid.at(up.x).at(up.y)->cellType == "Wall")
		{

			counter = counter + 1;
			//std::cout << counter << std::endl;
		}
	}
	if (down.y < m_grid->m_vectGrid.size())
	{
		if (m_grid->m_vectGrid.at(down.x).at(down.y)->cellType == "Wall")
		{
			counter = counter + 1;
			//std::cout << counter << std::endl;
		}
	}
	if (left.x >= 0)
	{
		if (m_grid->m_vectGrid.at(left.x).at(left.y)->cellType == "Wall")
		{
			counter = counter + 1;
			//std::cout << counter << std::endl;
		}
	}
	if (right.x < m_grid->m_vectGrid.size())
	{
		if (m_grid->m_vectGrid.at(right.x).at(right.y)->cellType == "Wall")
		{
			counter = counter + 1;
			//std::cout << counter << std::endl;
		}
	}
	if (counter == 2)
	{
		m_grid->m_vectGrid.at(t_row).at(t_col)->setTileColour(sf::Color::Blue);
		m_grid->m_vectGrid.at(t_row).at(t_col)->validInvalid = "ValidWall";
	}
	else
	{
		m_grid->m_vectGrid.at(t_row).at(t_col)->validInvalid = "NotValid";
		m_grid->m_vectGrid.at(t_row).at(t_col)->setTileColour(sf::Color::Red);
	}
}