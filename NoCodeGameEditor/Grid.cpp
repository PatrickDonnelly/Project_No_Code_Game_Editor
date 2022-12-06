#include "Grid.h"

Grid::Grid()
{
	setUpFont();
	m_background.setSize(sf::Vector2f{ 250.0f,1080.0f });
	m_background.setPosition(1670, 0);
	m_background.setFillColor(sf::Color::Color(40,40,40,255));
	regenerateGrid(0);
}

void Grid::setUpFont()
{
	if (!m_textFont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{

	}
	m_helpText.setFont(m_textFont);
	m_helpText.setString("Right Click Mouse to \nplace floor tiles. \n\n\n\nLeft Click Mouse to \nplace walls tiles. \n\n\n\nPress Up To \nincrease Grid Size \n\n\n\nPress Down to \nDecrease grid Size.");
	m_helpText.setPosition(1700, 200);
	m_helpText.setCharacterSize(18U);
	m_helpText.setFillColor(sf::Color::White);
}

void Grid::placeRemove(sf::RenderWindow& m_window)
{
	for (int i = 0; i < m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_vectGridSize; ++j)
		{
			if (m_vectGrid.at(i).at(j)->getTileBorder().getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
			{
				m_vectGrid.at(i).at(j)->setBorderColour(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_vectGrid.at(i).at(j)->cellType == "Floor")
				{
					m_vectGrid.at(i).at(j)->setColour(sf::Color::Color(188, 143, 143));
					m_vectGrid.at(i).at(j)->cellType = "Wall";
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
				{
					m_vectGrid.at(i).at(j)->setColour(sf::Color::Color(200, 200, 220));
					m_vectGrid.at(i).at(j)->cellType = "Floor";

				}
			}
			else
			{
				m_vectGrid.at(i).at(j)->resetBorderColour();
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
			std::cout << counter << std::endl;
		}
	}
	if (down.y <m_vectGrid.size())
	{
		if (m_vectGrid.at(down.x).at(down.y)->cellType == "Wall")
		{
			counter = counter + 1;
			std::cout << counter << std::endl;
		}
	}
	if (left.x >= 0)
	{
		if (m_vectGrid.at(left.x).at(left.y)->cellType == "Wall")
		{
			counter = counter + 1;
			std::cout << counter << std::endl;
		}
	}
	if (right.x < m_vectGrid.size())
	{
		if (m_vectGrid.at(right.x).at(right.y)->cellType == "Wall")
		{
			counter = counter + 1;
			std::cout << counter << std::endl;
		}
	}
	if (counter == 2)
	{
		m_vectGrid.at(t_row).at(t_col)->setColour(sf::Color::Blue);
		m_vectGrid.at(t_row).at(t_col)->validInvalid = "ValidWall";
	}
	else
	{
		m_vectGrid.at(t_row).at(t_col)->validInvalid = "NotValid";
		m_vectGrid.at(t_row).at(t_col)->setColour(sf::Color::Red);
	}
}

void Grid::update(sf::Time t_deltaTime, sf::RenderWindow& m_window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_vectGridSize < 16)
		{
			int plusCells = 1;
			regenerateGrid(plusCells);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_vectGridSize > 4)
		{
			int minusCells = -1;
			regenerateGrid(minusCells);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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
					std::cout << "This room is not valid" << std::endl;
				}
			}
		}
		if (roomValid)
		{
			std::cout << "This room is valid" << std::endl;
			for (int i = 0; i < m_vectGridSize; ++i)
			{
				for (int j = 0; j < m_vectGridSize; ++j)
				{
					if (m_vectGrid.at(i).at(j)->cellType == "Wall")
					{
						m_vectGrid.at(i).at(j)->setWallSprite();
					}
					else if (m_vectGrid.at(i).at(j)->cellType == "Floor")
					{
						m_vectGrid.at(i).at(j)->setFloorSprite();
					}
				}
			}
		}
		else
		{
			std::cout << "This room is invalid" << std::endl;

		}
	}
	placeRemove( m_window);
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
}


void Grid::regenerateGrid(int t_changeInSize)
{
	m_vectGrid.clear();
	m_vectGridSize = m_vectGridSize + (t_changeInSize);
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
			m_vectGrid.at(i).at(j)->setColour(sf::Color::Color(200, 200, 220,0));
			m_vectGrid.at(i).at(j)->cellType = "Floor";
		}
	}
}
