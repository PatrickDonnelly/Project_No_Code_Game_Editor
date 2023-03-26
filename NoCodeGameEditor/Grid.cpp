#include "Grid.h"

Grid::Grid()
{
}

Grid::Grid(GameState* t_gameState, TextureManager* t_textureManager)
{
	m_textureManager = t_textureManager;
	m_gameState = t_gameState;
	setUpFont();
	regenerateGrid();
}

void Grid::setUpFont()
{
	if (!m_textFont.loadFromFile("ASSETS\\FONTS\\Arial.ttf"))
	{

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

void Grid::render(sf::RenderWindow* t_window)
{
	for (int i = 0; i < m_vectGridSize; i++)
	{
		for (int j = 0; j < m_vectGridSize; j++)
		{
			if (m_gridEnabled)
			{
				t_window->draw(m_vectGrid.at(i).at(j)->getTileBorder());
			}
			t_window->draw(m_vectGrid.at(i).at(j)->getTile());
		}
	}
}




void Grid::regenerateGrid()
{

	m_vectGrid.clear();
	
	m_playerSet = false;

	for (int i = 0; i < m_vectGridSize; ++i)
	{
		std::vector<Tile*> row;
		for (int j = 0; j < m_vectGridSize; ++j)
		{
			row.push_back(new Tile(m_textFont, m_textureManager));
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
