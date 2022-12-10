#include "Grid.h"

Grid::Grid()
{
	setUpFont();
	m_background.setSize(sf::Vector2f{ 250.0f,1080.0f });
	m_background.setPosition(1670, 0);
	m_background.setFillColor(sf::Color::Color(40,40,40,255));
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

void Grid::clearUnusedCells()
{
	for (int i = 0; i < m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_vectGridSize; ++j)
		{
			if (m_vectTiles.at(i).at(j)->cellType == "Empty")
			{
				m_vectTiles.at(i).at(j)->setBorderColour(sf::Color(sf::Color(0, 0, 0, 0)));
			}
		}
	}

}


void Grid::update(sf::Time t_deltaTime, sf::RenderWindow& m_window)
{

}

void Grid::render(sf::RenderWindow* t_window)
{
	t_window->draw(m_background);
	t_window->draw(m_helpText);
	for (int i = 0; i < m_vectGridSize; i++)
	{
		for (int j = 0; j < m_vectGridSize; j++)
		{
			t_window->draw(m_vectTiles.at(i).at(j)->getTileBorder());
			t_window->draw(m_vectTiles.at(i).at(j)->getTile());
		}
	}
}


void Grid::regenerateGrid()
{
	m_vectTiles.clear();

	for (int i = 0; i < m_vectGridSize; ++i)
	{
		std::vector<Tile*> row;
		for (int j = 0; j < m_vectGridSize; ++j)
		{
			row.push_back(new Tile(m_textFont));
		}
		m_vectTiles.push_back(row);
	}
	for (int i = 0; i < m_vectGridSize; ++i)
	{
		for (int j = 0; j < m_vectGridSize; ++j)
		{
			m_vectTiles.at(i).at(j)->setPosition(m_vectTiles.at(i).at(j)->m_width * i + 960 - (m_vectGridSize * 16), m_vectTiles.at(i).at(j)->m_width * j + 540 - (m_vectGridSize * 16));
			m_vectTiles.at(i).at(j)->rowColumn = sf::Vector2i{ i,j };
			m_vectTiles.at(i).at(j)->setTileColour(sf::Color::Color(200, 200, 220,0));
			m_vectTiles.at(i).at(j)->cellType = "Empty";
			m_vectTiles.at(i).at(j)->m_checked = false;
			m_vectTiles.at(i).at(j)->m_colliderCheck = false;
		}
	}
}
