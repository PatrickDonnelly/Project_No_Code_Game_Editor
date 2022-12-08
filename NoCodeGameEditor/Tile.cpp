#include "Tile.h"

void Tile::setUpText(sf::Font& t_font)
{
	m_text.setFont(t_font);
	m_text.setString("0");
	m_text.setPosition(m_width / 2, m_width / 2);
	m_text.setCharacterSize(10U);
	m_text.setFillColor(sf::Color::White);
}

Tile::Tile(sf::Font& t_font)
{
	setUpText(t_font);
	setUpSprites();
	m_tile.setSize(sf::Vector2f(m_width, m_width));
	m_tile.setOrigin(sf::Vector2f(m_width/2.0f, m_width/2.0f));
	m_tile.setFillColor(sf::Color(sf::Color(0,0,0,0)));
	m_tile.setOutlineThickness(1.0f);
	m_tile.setOutlineColor(sf::Color(sf::Color(0, 255, 0, 150)));
	m_cellSprite.setOrigin(16.0f, 16.0f);
}

void Tile::setPosition(float t_x, float t_y)
{
	m_tile.setPosition(t_x, t_y);
	m_cellSprite.setPosition(t_x, t_y);
}

void Tile::setWallSprite()
{
	m_cellSprite.setTexture(m_wallTexture);
}

void Tile::setFloorSprite()
{
	m_cellSprite.setTexture(m_floorTexture);
}

void Tile::setUpSprites()
{
	if (!m_floorTexture.loadFromFile("ASSETS\\IMAGES\\dirt_0.png"))
	{
		// error...
	}
	if (!m_wallTexture.loadFromFile("ASSETS\\IMAGES\\rock_0.png"))
	{
		// error...
	}
}

sf::Vector2f Tile::getPos()
{
	return m_tile.getPosition();
}

void Tile::setTileColour(sf::Color t_color)
{
	m_tile.setFillColor(t_color);
	defaultColour = t_color;
}
void Tile::setBorderColour(sf::Color t_color)
{
	m_tile.setOutlineColor(t_color);
	m_tile.setFillColor(t_color);
}
void Tile::resetBorderColour()
{
	m_tile.setOutlineColor(sf::Color(sf::Color(0, 255, 0, 150)));
	m_tile.setFillColor(defaultColour);

}