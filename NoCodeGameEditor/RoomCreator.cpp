#include "RoomCreator.h"

RoomCreator::RoomCreator()
{
}

RoomCreator::RoomCreator(Grid* t_grid, RoomData* t_roomData, Colliders* t_wallCollider) : 
	m_grid(t_grid), m_roomData(t_roomData), m_wallCollider(t_wallCollider)
{
}

RoomCreator::~RoomCreator()
{
}

void RoomCreator::update(sf::Time t_deltaTime, sf::RenderWindow& m_window)
{
	placeRemove(m_window);
	for (int i = 0; i < m_roomData->m_roomStatues.size(); i++)
	{
		m_roomData->m_roomStatues.at(i)->getSprite()->setPosition(m_roomData->m_roomStatues.at(i)->getBounds()->getPosition());
	}
}

void RoomCreator::render(sf::RenderWindow* t_window)
{
	for (int i = 0; i < m_wallCollider->m_wallColliders.size(); i++)
	{
		m_wallCollider->m_wallColliders.at(i).render(t_window);
	}
	for (int i = 0; i < m_roomData->m_roomStatues.size(); i++)
	{
		t_window->draw(*m_roomData->m_roomStatues.at(i)->getSprite());
		t_window->draw(*m_roomData->m_roomStatues.at(i)->getBounds());
	}
}

void RoomCreator::CheckValidityOfWalls(int t_row, int t_col)
{
	sf::Vector2i up{ t_row, t_col - 1 };
	sf::Vector2i down{ t_row, t_col + 1 };
	sf::Vector2i right{ t_row + 1, t_col };
	sf::Vector2i left{ t_row - 1, t_col };

	counter = 0;
	if (up.y >= 0 && m_grid->m_vectTiles.at(up.x).at(up.y)->cellType == "Wall")
	{
		counter = counter + 1;
	}
	if (down.y < m_grid->m_vectTiles.size() && m_grid->m_vectTiles.at(down.x).at(down.y)->cellType == "Wall")
	{
		counter = counter + 1;
	}
	if (left.x >= 0 && m_grid->m_vectTiles.at(left.x).at(left.y)->cellType == "Wall")
	{
		counter = counter + 1;
	}
	
	if (right.x < m_grid->m_vectTiles.size() && m_grid->m_vectTiles.at(right.x).at(right.y)->cellType == "Wall")
	{
		counter = counter + 1;
	}
	if (counter == 2)
	{
		m_grid->m_vectTiles.at(t_row).at(t_col)->setTileColour(sf::Color::Blue);
		m_grid->m_vectTiles.at(t_row).at(t_col)->validInvalid = "ValidWall";
	}
	else
	{
		m_grid->m_vectTiles.at(t_row).at(t_col)->validInvalid = "NotValid";
		m_grid->m_vectTiles.at(t_row).at(t_col)->setTileColour(sf::Color::Red);
	}
}

void RoomCreator::placeRemove(sf::RenderWindow& m_window)
{

	for (int i = 0; i < m_grid->m_vectTiles.size(); ++i)
	{
		for (int j = 0; j < m_grid->m_vectTiles.size(); ++j)
		{
			if (m_grid->m_vectTiles.at(i).at(j)->getTileBorder().getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
			{
				m_grid->m_vectTiles.at(i).at(j)->setBorderColour(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_grid->m_vectTiles.at(i).at(j)->cellType == "Empty")
				{
					m_grid->m_vectTiles.at(i).at(j)->setTileColour(sf::Color::Color(188, 143, 143));
					m_grid->m_vectTiles.at(i).at(j)->cellType = "Wall";
					wallsPlaced++;
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && m_grid->m_vectTiles.at(i).at(j)->cellType == "Wall")
				{
					m_grid->m_vectTiles.at(i).at(j)->setTileColour(sf::Color::Color(0, 0, 0, 0));
					m_grid->m_vectTiles.at(i).at(j)->cellType = "Empty";
					wallsPlaced--;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_grid->m_vectTiles.at(i).at(j)->cellType == "Floor")
				{
					if (m_roomData->m_roomStatues.size() < 5)
					{
						int temp = m_roomData->m_roomStatues.size();
						m_roomData->m_roomStatues.push_back(new Obstacle);
						m_grid->m_vectTiles.at(i).at(j)->cellType = "FloorObstacle";
						m_roomData->m_roomStatues.at(temp)->getBounds()->setPosition(m_grid->m_vectTiles.at(i).at(j)->getPos());
					}
				}
			}
			else
			{
				m_grid->m_vectTiles.at(i).at(j)->resetBorderColour();
			}
		}
	}
}

void RoomCreator::GenerateRoomSprites()
{
	for (int i = 0; i < m_grid->m_vectTiles.size(); ++i)
	{
		for (int j = 0; j < m_grid->m_vectTiles.size(); ++j)
		{
			sf::Vector2i right{ i + 1, j };
			sf::Vector2i down{ i, j + 1 };
			sf::Vector2i left{ i - 1, j };
			sf::Vector2i up{ i, j - 1 };
			if (m_grid->m_vectTiles.at(i).at(j)->cellType == "Wall")
			{
				m_grid->m_vectTiles.at(i).at(j)->setWallSprite();
				if (right.x < m_grid->m_vectTiles.size())
				{
					if (m_grid->m_vectTiles.at(right.x).at(j)->cellType != "Wall" && firstFloorSet == false)
					{
						m_firstTilePosition = m_grid->m_vectTiles.at(right.x).at(j)->getPos();
						m_grid->m_vectTiles.at(right.x).at(j)->cellType = "Floor";
						m_grid->m_vectTiles.at(right.x).at(j)->setFloorSprite();
						m_grid->m_vectTiles.at(right.x).at(j)->m_checked = true;
						firstFloorSet = true;
						m_tileQueue.push(m_grid->m_vectTiles.at(right.x).at(j));
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
			if (l_row >= 0 && l_row < m_grid->m_vectTiles.size() && l_col >= 0 && l_col < m_grid->m_vectTiles.size() && m_grid->m_vectTiles.at(l_row).at(l_col)->m_checked == false)
			{
				if (m_grid->m_vectTiles.at(l_row).at(l_col)->cellType != "Empty")
				{
					continue; // stops endless loop
				}
				m_grid->m_vectTiles.at(l_row).at(l_col)->m_checked = true;
				m_grid->m_vectTiles.at(l_row).at(l_col)->cellType = "Floor";
				m_grid->m_vectTiles.at(l_row).at(l_col)->setFloorSprite();
				m_tileQueue.push(m_grid->m_vectTiles.at(l_row).at(l_col));
			}
		}
		m_tileQueue.pop();
	}
	setUpWallColliders();
}

void RoomCreator::checkRoomValidity()
{
	roomValid = true;
	for (int i = 0; i < m_grid->m_vectTiles.size(); ++i)
	{
		for (int j = 0; j < m_grid->m_vectTiles.size(); ++j)
		{
			if (m_grid->m_vectTiles.at(i).at(j)->cellType == "Wall")
			{
				CheckValidityOfWalls(i, j);
			}
			if (m_grid->m_vectTiles.at(i).at(j)->validInvalid == "NotValid")
			{
				roomValid = false;
			}
		}
	}
	if (roomValid  && wallsPlaced >= minimumWalls && roomGenerated == false)
	{
		roomGenerated = true;
		GenerateRoomSprites();
	}
	else
	{
		for (int i = 0; i < m_grid->m_vectTiles.size(); ++i)
		{
			for (int j = 0; j < m_grid->m_vectTiles.size(); ++j)
			{
				m_grid->m_vectTiles.at(i).at(j)->m_checked = false;
				m_grid->m_vectTiles.at(i).at(j)->validInvalid = " ";
			}
		}
	}
}

void RoomCreator::clearRoom()
{
	m_wallCollider->noOfWallColliders = 0;
	noOfObstacles = 0;
	wallsPlaced = 0;
	m_playerSet = false;
	firstFloorSet = false;
	roomGenerated = false;
	m_wallCollider->m_wallColliders.clear();
	m_roomData->m_roomStatues.clear();
}

void RoomCreator::setUpWallColliders()
{
	for (int j = 0; j < m_grid->m_vectTiles.size(); j++)
	{
		for (int i = 0; i < m_grid->m_vectTiles.size(); i++)
		{
			if (i < m_grid->m_vectTiles.size() - 1 && m_grid->m_vectTiles.at(i).at(j)->cellType == "Wall" && startFound == false && m_grid->m_vectTiles.at(i + 1).at(j)->cellType == "Wall")
			{
				startFound = true;
				m_colStartPos = m_grid->m_vectTiles.at(i).at(j)->getPos();
			}
			else if (startFound == true && (m_grid->m_vectTiles.at(i).at(j)->cellType == "Empty" || m_grid->m_vectTiles.at(i).at(j)->cellType == "Floor" || i == m_grid->m_vectTiles.size() - 1))
			{
				startFound = false;
				m_colEndPos = m_grid->m_vectTiles.at(i).at(j)->getPos();
				m_wallCollider->setHorizontalWallColliders(m_colStartPos, m_colEndPos);
			}
		}	
	}
	for (int i = 0; i < m_grid->m_vectTiles.size(); i++)
	{
		for (int j = 0; j < m_grid->m_vectTiles.size(); j++)
		{
			if (j < m_grid->m_vectTiles.size() - 1 && m_grid->m_vectTiles.at(i).at(j)->cellType == "Wall" && startFound == false && m_grid->m_vectTiles.at(i).at(j + 1)->cellType == "Wall")
			{
				startFound = true;
				m_colStartPos = m_grid->m_vectTiles.at(i).at(j)->getPos();
			}
			else if (startFound == true && (m_grid->m_vectTiles.at(i).at(j)->cellType == "Empty" || m_grid->m_vectTiles.at(i).at(j)->cellType == "Floor" || j == m_grid->m_vectTiles.size() - 1))
			{
				startFound = false;
				m_colEndPos = m_grid->m_vectTiles.at(i).at(j)->getPos();
				m_wallCollider->setVerticalWallColliders(m_colStartPos, m_colEndPos);
			}
		}
	}
}
