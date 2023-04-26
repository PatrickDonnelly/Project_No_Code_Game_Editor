#include "Item.h"
#include <iostream>

/// <summary>
/// Default constructor
/// </summary>
Item::Item()
{
}

/// <summary>
/// Overloaded constructor
/// </summary>
/// <param name="t_path"></param>
Item::Item(std::string t_path)
{
	m_uuid = UUID();
	m_textureManager = new TextureManager();
	m_isCollidable = false;
	m_tag = "Item";
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
Item::Item(std::string t_typeTag, std::string t_path, TextureManager* t_textureManager)
{
	m_uuid = UUID();
	m_textureManager = t_textureManager;
	m_isCollidable = false;
	m_tag = "Item";
	m_path = t_path;
	m_boundsHeight = 32;
	m_boundsWidth = 32;
	//m_inspector = new Inspector();
	init();
}

/// <summary>
/// Default constructor
/// </summary>
Item::~Item()
{
}

/// <summary>
/// Initialise the item object
/// </summary>
void Item::init()
{
	setUpSprite();
	setUpBounds();
}

/// <summary>
/// Set up the sprite of the item object
/// </summary>
void Item::setUpSprite()
{
	setTexture(m_objectTexture);
	m_objectSprite.setOrigin(16, 16);
	m_objectSprite.setColor(sf::Color::White);
	m_objectSprite.setPosition(100, 100);
}

/// <summary>
/// Set the texture of the item object
/// </summary>
/// <param name="t_texture"></param>
void Item::setTexture(sf::Texture& t_texture)
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
void Item::setPathToTexture(std::string t_path)
{
	m_path = t_path;
}

/// <summary>
/// Sets up the collidable bounds of the item object
/// </summary>
void Item::setUpBounds()
{
	m_objectBounds.setSize(sf::Vector2f(m_boundsWidth, m_boundsHeight));
	m_objectBounds.setOrigin(m_boundsWidth / 2, (m_boundsHeight / 2));
	m_objectBounds.setFillColor(sf::Color(sf::Color(0, 0, 0, 0)));
	m_objectBounds.setOutlineColor(sf::Color::Green);
	m_objectBounds.setOutlineThickness(1.0f);
	m_objectBounds.setPosition(m_objectSprite.getPosition());
}

/// <summary>
/// Updates the item object
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="window"></param>
void Item::update(sf::Time deltaTime, sf::RenderWindow& window)
{
	m_objectSprite.setPosition(m_objectBounds.getPosition());

}

/// <summary>
/// Renders the item object
/// </summary>
/// <param name="window"></param>
void Item::render(sf::RenderWindow& window)
{
	window.draw(m_objectSprite);
	if (m_isSelected)
	{
		//m_inspector->setTextString("Item");
		//m_inspector->render(&window);
	}
}

/// <summary>
/// Renders the inspector of the item object if it is selected
/// </summary>
/// <param name="window"></param>
void Item::renderInspector(sf::RenderWindow& window)
{
	if (m_isSelected)
	{
		//m_inspector->setTextString("Enemy");
		m_inspector->render(&window);
	}
}