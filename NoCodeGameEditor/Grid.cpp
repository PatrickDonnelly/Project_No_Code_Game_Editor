#include "Grid.h"

/// <summary>
/// Default constructor Grid
/// </summary>
Grid::Grid()
{
}

/// <summary>
/// Overloaded constructor for the Grid
/// </summary>
/// <param name="t_gameState"></param>
/// <param name="t_textureManager"></param>
Grid::Grid(GameState* t_gameState, TextureManager* t_textureManager)
{
	m_textureManager = t_textureManager;
	m_gameState = t_gameState;
	setUpFont();
	regenerateGrid();
}

/// <summary>
/// Loads in a font
/// </summary>
void Grid::setUpFont()
{
	if (!m_textFont.loadFromFile("ASSETS\\FONTS\\Arial.ttf"))
	{

	}
}

/// <summary>
/// Visually clears unoccupied cells in the grid by changing the outline colour to black
/// </summary>
void Grid::clearUnusedCells()
{
	for (int i = 0; i < m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_vectGridSize; ++j)
		{
			if (m_vectGrid.at(i).at(j).cellType == "Empty")
			{
				m_vectGrid.at(i).at(j).setBorderColour(sf::Color(sf::Color(0, 0, 0, 0)));
			}
		}
	}
}

/// <summary>
/// Increases the size of the grid
/// </summary>
void Grid::increaseGridSize()
{
	if (m_vectGridSize < 16)
	{
		m_vectGridSize = m_vectGridSize + 1;
		regenerateGrid();
	}
}

/// <summary>
/// Decreases the size of the grid
/// </summary>
void Grid::decreaseGridSize()
{
	if (m_vectGridSize > 5)
	{
		m_vectGridSize = m_vectGridSize - 1;
		regenerateGrid();
	}
}

/// <summary>
/// Renders the grid to the window
/// </summary>
/// <param name="t_window"></param>
void Grid::render(sf::RenderWindow* t_window)
{
	for (int i = 0; i < m_vectGridSize; i++)
	{
		for (int j = 0; j < m_vectGridSize; j++)
		{
			if (m_gridEnabled)
			{
				t_window->draw(m_vectGrid.at(i).at(j).getTileBorder());
			}
			t_window->draw(m_vectGrid.at(i).at(j).getTile());
		}
	}
}

/// <summary>
/// Clears the grid
/// </summary>
void Grid::clear()
{
	m_vectGrid.clear();
}

/// <summary>
/// Creates a new grid
/// </summary>
void Grid::newGrid()
{
	for (int i = 0; i < m_vectGridSize; ++i)
	{
		std::vector<Tile> row;
		for (int j = 0; j < m_vectGridSize; ++j)
		{
			row.push_back(Tile(m_textFont, m_textureManager));
		}
		m_vectGrid.push_back(row);
	}
}

/// <summary>
/// Regenerates the current grid to make a new one
/// </summary>
void Grid::regenerateGrid()
{

	m_vectGrid.clear();
	
	m_playerSet = false;

	newGrid();

	for (int i = 0; i < m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_vectGridSize; ++j)
		{
			m_vectGrid.at(i).at(j).setPosition(m_vectGrid.at(i).at(j).m_width * i +16, m_vectGrid.at(i).at(j).m_width * j +16);
			m_vectGrid.at(i).at(j).rowColumn = sf::Vector2i{ i,j };
			m_vectGrid.at(i).at(j).setTileColour(sf::Color::Color(200, 200, 220,0));
			m_vectGrid.at(i).at(j).cellType = "Empty";
			m_vectGrid.at(i).at(j).m_checked = false;
			m_vectGrid.at(i).at(j).m_colliderCheck = false;
		}
	}
}
