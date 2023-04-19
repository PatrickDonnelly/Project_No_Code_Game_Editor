#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"

class Tile
{
private:

	sf::RectangleShape m_tile;
	TextureManager* m_textureManager;

public:
	bool m_top = false;
	bool m_bottom = false;
	bool m_left = false;
	bool m_right = false;
	bool m_checked = false;
	bool m_colliderCheck = false;
	bool m_hasObject = false;
	std::string m_objectType = "";

	sf::Sprite m_cellSprite;
	sf::Texture m_floorTexture;
	sf::Texture m_wallTexture;

	void setWallSprite();
	void setFloorSprite();
	void setUpSprites();
	void removeTexture();

	std::string cellType = "Empty";
	std::string cornerwall = "CornerWall";
	std::string sidewall = "SideWall";
	std::string validInvalid = " ";

	sf::Text m_text;
	sf::Vector2i rowColumn{};
	sf::Vector2f m_vector{};
	sf::Vector2f getPos();
	std::string m_path = "";

	void setUpText(sf::Font& t_font);
	Tile(sf::Font& t_font, TextureManager* t_textureManager);
	Tile();
	~Tile();
	void setFloorSprite(std::string t_path);
	float m_width = 32.0f;
	void setPosition(float m_x, float m_y);
	void setTileColour(sf::Color t_color);
	void setBorderColour(sf::Color t_color);
	void resetBorderColour();
	sf::Color defaultColour;
	sf::RectangleShape getTileBorder() { return m_tile; }
	sf::Sprite getTile() { return m_cellSprite; }
	std::string getPath() { return m_path; }
};
#endif // !TILE_HPP
