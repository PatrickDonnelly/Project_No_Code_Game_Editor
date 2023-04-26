#include "Tile.h"

/// <summary>
/// Sets up text object
/// </summary>
/// <param name="t_font"></param>
void Tile::setUpText(sf::Font& t_font)
{
	m_text.setFont(t_font);
	m_text.setString("0");
	m_text.setPosition(m_width / 2, m_width / 2);
	m_text.setCharacterSize(10U);
	m_text.setFillColor(sf::Color::White);
}

/// <summary>
/// Deconstructor
/// </summary>
Tile::~Tile()
{
}

/// <summary>
/// Overloaded constructor
/// </summary>
/// <param name="t_font"></param>
/// <param name="t_textureManager"></param>
Tile::Tile(sf::Font& t_font, TextureManager* t_textureManager)
{
	m_path = "ASSETS\\IMAGES\\dirt_0";
	m_textureManager = t_textureManager;
	//setUpSprites();
	m_tile.setSize(sf::Vector2f(m_width, m_width));
	m_tile.setOrigin(sf::Vector2f(m_width/2.0f, m_width/2.0f));
	m_tile.setFillColor(sf::Color(sf::Color(0,0,0,0)));
	m_tile.setOutlineThickness(1.0f);
	m_tile.setOutlineColor(sf::Color(sf::Color(0, 255, 0, 150)));
	m_cellSprite.setOrigin(16.0f, 16.0f);
}

/// <summary>
/// Default constructor
/// </summary>
Tile::Tile()
{
}

/// <summary>
/// Sets the position of the tile object
/// </summary>
/// <param name="t_x"></param>
/// <param name="t_y"></param>
void Tile::setPosition(float t_x, float t_y)
{
	m_tile.setPosition(t_x, t_y);
	m_cellSprite.setPosition(t_x, t_y);
}

/// <summary>
/// Removes the tile objects texture (sets it to black,
/// to appear empty)
/// </summary>
void Tile::removeTexture()
{
	m_cellSprite.setColor(sf::Color(0,0,0,0));
}

/// <summary>
/// Sets the texture of the tile
/// </summary>
/// <param name="t_path"></param>
void Tile::setFloorSprite(std::string t_path)
{
	m_path = t_path;
	m_floorTexture = m_textureManager->getTexture(t_path + ".png");
	//if (!t_texture.loadFromFile(m_path + ".png"))
	//{
	//	std::cout << "Can't load main menu bgt" << std::endl;
	//}
	m_cellSprite.setColor(sf::Color::White);
	m_cellSprite.setTexture(m_floorTexture);
}

/// <summary>
/// Gets the position of the tile
/// </summary>
/// <returns></returns>
sf::Vector2f Tile::getPos()
{
	return m_tile.getPosition();
}

/// <summary>
/// Sets the colour of the tile
/// </summary>
/// <param name="t_color"></param>
void Tile::setTileColour(sf::Color t_color)
{
	m_tile.setFillColor(t_color);
	defaultColour = t_color;
}

/// <summary>
/// Sets the outline colour of the tile, used to form a grid
/// </summary>
/// <param name="t_color"></param>
void Tile::setBorderColour(sf::Color t_color)
{
	m_tile.setOutlineColor(t_color);
	m_tile.setFillColor(t_color);
}

/// <summary>
/// Resets the colour of the tile to its default colour
/// </summary>
void Tile::resetBorderColour()
{
	m_tile.setOutlineColor(sf::Color(sf::Color(0, 255, 0, 150)));
	m_tile.setFillColor(defaultColour);

}