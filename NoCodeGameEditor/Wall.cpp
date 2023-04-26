#include "Wall.h"
#include <iostream>

/// <summary>
/// Default constructor
/// </summary>
Wall::Wall()
{
}

/// <summary>
/// Overloaded constructor
/// </summary>
/// <param name="t_path"></param>
Wall::Wall(std::string t_path)
{
	m_textureManager = new TextureManager();
	m_isCollidable = false;
	m_tag = "Wall";
	m_path = t_path;
	m_boundsHeight = 32;
	m_boundsWidth = 32;
	//m_inspector = new Inspector();
	init();
}

/// <summary>
/// Overloaded constructor
/// </summary>
/// <param name="t_typeTag"></param>
/// <param name="t_path"></param>
/// <param name="t_textureManager"></param>
Wall::Wall(std::string t_typeTag, std::string t_path, TextureManager* t_textureManager)
{
	m_textureManager = t_textureManager;
	m_isCollidable = false;
	m_tag = "Wall";
	m_path = t_path;
	m_boundsHeight = 32;
	m_boundsWidth = 32;
	//m_inspector = new Inspector();
	init();
}

/// <summary>
/// Default constructor
/// </summary>
Wall::~Wall()
{
}

/// <summary>
/// Initialise object
/// </summary>
void Wall::init()
{
	setUpSprite();
	setUpBounds();
}

/// <summary>
/// Sets up the walls sprite
/// </summary>
void Wall::setUpSprite()
{
	setTexture(m_objectTexture);
	m_objectSprite.setOrigin(16, 16);
	m_objectSprite.setColor(sf::Color::White);
	m_objectSprite.setPosition(100, 100);
}

/// <summary>
/// Sets the walls texture
/// </summary>
/// <param name="t_texture"></param>
void Wall::setTexture(sf::Texture& t_texture)
{
	m_objectTexture = m_textureManager->getTexture(m_path + ".png");
	//if (!t_texture.loadFromFile(m_path + ".png"))
	//{
	//	std::cout << "Can't load main menu bgt" << std::endl;
	//}
	m_objectSprite.setTexture(m_objectTexture);
}

/// <summary>
/// Sets the directory path to the texture
/// </summary>
/// <param name="t_path"></param>
void Wall::setPathToTexture(std::string t_path)
{
	m_path = t_path;
}

/// <summary>
/// Sets up the collidable bounds of the wall object
/// </summary>
void Wall::setUpBounds()
{
	m_objectBounds.setSize(sf::Vector2f(m_boundsWidth, m_boundsHeight));
	m_objectBounds.setOrigin(m_boundsWidth / 2, (m_boundsHeight / 2));
	m_objectBounds.setFillColor(sf::Color(sf::Color(0, 0, 0, 0)));
	m_objectBounds.setOutlineColor(sf::Color::Green);
	m_objectBounds.setOutlineThickness(1.0f);
	m_objectBounds.setPosition(m_objectSprite.getPosition());
}

/// <summary>
/// Updates the wall object
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="window"></param>
void Wall::update(sf::Time deltaTime, sf::RenderWindow& window)
{
	m_objectSprite.setPosition(m_objectBounds.getPosition());

}

/// <summary>
/// Renders the wall object
/// </summary>
/// <param name="window"></param>
void Wall::render(sf::RenderWindow& window)
{
	window.draw(m_objectSprite);
	if (m_isSelected)
	{
		//m_inspector->setTextString("Wall");
		//m_inspector->render(&window);
	}
}

/// <summary>
/// Renders the wall objects inspector if it is selected
/// </summary>
/// <param name="window"></param>
void Wall::renderInspector(sf::RenderWindow& window)
{
	if (m_isSelected)
	{
		//m_inspector->setTextString("Enemy");
		m_inspector->render(&window);
	}
}