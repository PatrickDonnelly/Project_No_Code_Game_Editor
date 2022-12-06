#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Tile
{
private:

	sf::RectangleShape m_tile;

public:
	bool m_top = false;
	bool m_bottom = false;
	bool m_left = false;
	bool m_right = false;
	bool checked = false;

	std::string cellType = " ";
	std::string cornerwall = "CornerWall";
	std::string sidewall = "SideWall";
	std::string validInvalid = " ";

	sf::Text m_text;
	sf::Vector2i rowColumn{};
	sf::Vector2f m_vector{};
	sf::Vector2f getPos();


	void setUpText(sf::Font& t_font);
	Tile(sf::Font& t_font);
	float m_width = 32.0f;
	void setPosition(float m_x, float m_y);
	void setColour(sf::Color t_color);
	void setBorderColour(sf::Color t_color);
	void resetBorderColour();
	sf::Color defaultColour;
	sf::RectangleShape getTile() { return m_tile; }
};
#endif // !TILE_HPP
