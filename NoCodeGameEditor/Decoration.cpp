#include "Decoration.h"
#include <iostream>

/// <summary>
/// Default constructor
/// </summary>
Decoration::Decoration()
{
}

/// <summary>
/// Overloaded constructer
/// </summary>
/// <param name="t_path"></param>
Decoration::Decoration(std::string t_path)
{
	m_tag = "Decoration";
	m_uuid = UUID();
	m_textureManager = new TextureManager();
	m_isCollidable = false;
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
Decoration::Decoration(std::string t_typeTag, std::string t_path, TextureManager* t_textureManager)
{
	m_tag = "Decoration";
	m_uuid = UUID();
	m_textureManager = t_textureManager;
	m_isCollidable = false;
	m_path = t_path;
	m_boundsHeight = 32;
	m_boundsWidth = 32;
	//m_inspector = new Inspector();
	init();
}

/// <summary>
/// deconstructor
/// </summary>
Decoration::~Decoration()
{
}

/// <summary>
/// initialise object
/// </summary>
void Decoration::init()
{
	setUpSprite();
	setUpBounds();
}

/// <summary>
/// Sets up the texture and sprite
/// </summary>
void Decoration::setUpSprite()
{
	setTexture(m_objectTexture);
	m_objectSprite.setOrigin(16, 16);
	m_objectSprite.setColor(sf::Color::White);
	m_objectSprite.setPosition(100, 100);
}

/// <summary>
/// Retrieves the texture and sets the sprites texture to it 
/// </summary>
/// <param name="t_texture"></param>
void Decoration::setTexture(sf::Texture& t_texture)
{
	m_objectTexture = m_textureManager->getTexture(m_path + ".png");
	//if (!t_texture.loadFromFile(m_path + ".png"))
	//{
	//	std::cout << "Can't load main menu bgt" << std::endl;
	//}
	m_objectSprite.setTexture(m_objectTexture);
}

/// <summary>
/// sets the path to the texture in the assets directory
/// </summary>
/// <param name="t_path"></param>
void Decoration::setPathToTexture(std::string t_path)
{
	m_path = t_path;
}
/// <summary>
/// Sets up the bounds of the object
/// </summary>
void Decoration::setUpBounds()
{
	m_objectBounds.setSize(sf::Vector2f(m_boundsWidth, m_boundsHeight));
	m_objectBounds.setOrigin(m_boundsWidth / 2, (m_boundsHeight / 2));
	m_objectBounds.setFillColor(sf::Color(sf::Color(0, 0, 0, 0)));
	m_objectBounds.setOutlineColor(sf::Color::Green);
	m_objectBounds.setOutlineThickness(1.0f);
	m_objectBounds.setPosition(m_objectSprite.getPosition());
}

/// <summary>
/// Updates the object
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="window"></param>
void Decoration::update(sf::Time deltaTime, sf::RenderWindow& window)
{
	m_objectSprite.setPosition(m_objectBounds.getPosition());

}

/// <summary>
/// renders the object
/// </summary>
/// <param name="window"></param>
void Decoration::render(sf::RenderWindow& window)
{
	window.draw(m_objectSprite);
	if (m_isSelected)
	{
		//m_inspector->setTextString("Decoration");
		//m_inspector->render(&window);
	}
}

/// <summary>
/// renders the inspector when the object is selected.
/// </summary>
/// <param name="window"></param>
void Decoration::renderInspector(sf::RenderWindow& window)
{
	if (m_isSelected)
	{
		//m_inspector->setTextString("Enemy");
		m_inspector->render(&window);
	}
}