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
	m_tile.setSize(sf::Vector2f(m_width, m_width));
	m_tile.setFillColor(sf::Color::Blue);
	m_tile.setOutlineThickness(1.0f);
	m_tile.setOutlineColor(sf::Color(sf::Color(0, 255, 0, 150)));
}

void Tile::setPosition(float t_x, float t_y)
{
	m_tile.setPosition(t_x, t_y);
}

sf::Vector2f Tile::getPos()
{
	return m_tile.getPosition();
}

void Tile::setColour(sf::Color t_color)
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