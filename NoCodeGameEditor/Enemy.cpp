#include "Enemy.h"
#include <iostream>

/// <summary>
/// Default constructor for the enemy
/// </summary>
Enemy::Enemy()
{

}

/// <summary>
/// Overloaded constructor for the enemy
/// </summary>
/// <param name="t_path"></param>
Enemy::Enemy(std::string t_path)
{
	m_textureManager = new TextureManager();
	m_isCollidable = false;
	m_tag = "Enemy";
	m_uuid = UUID();
	m_path = t_path;
	m_boundsHeight = 32;
	m_boundsWidth = 32;
	m_inpectorData.m_allowedDialogue = true;
	m_inspector = new Inspector("Enemy", m_inpectorData);
	m_dialogue = new DialogueBox();
	init();
	m_hasAttributes = true;
}

/// <summary>
/// Overloaded constructor for the enmy class
/// </summary>
/// <param name="t_typeTag"></param>
/// <param name="t_path"></param>
/// <param name="t_textureManager"></param>
Enemy::Enemy(std::string t_typeTag, std::string t_path, TextureManager* t_textureManager)
{
	m_textureManager = t_textureManager;
	m_isCollidable = false;
	m_tag = "Enemy";
	m_uuid = UUID();
	//std::cout << m_uuid << " UUID" << std::endl;
	m_path = t_path;
	m_boundsHeight = 32;
	m_boundsWidth = 32;
	m_inpectorData.m_allowedDialogue = true;
	m_inspector = new Inspector("Enemy", m_inpectorData);
	m_dialogue = new DialogueBox();
	init();
	m_hasAttributes = true;
}

/// <summary>
/// Deconstructor
/// </summary>
Enemy::~Enemy()
{
}

/// <summary>
/// initialises the enemy object
/// </summary>
void Enemy::init()
{
	setUpSprite();
	setUpBounds();
}

/// <summary>
/// Sets up the enemy objects sprite
/// </summary>
void Enemy::setUpSprite()
{
	setTexture(m_objectTexture);
	m_objectSprite.setOrigin(16, 16);
	m_objectSprite.setColor(sf::Color::White);
	m_objectSprite.setPosition(100, 100);
}

/// <summary>
/// Sets the texture of the enemy object
/// </summary>
/// <param name="t_texture"></param>
void Enemy::setTexture(sf::Texture& t_texture)
{
	m_objectTexture = m_textureManager->getTexture(m_path + ".png");
	//if (!t_texture.loadFromFile(m_path + ".png"))
	//{
	//	std::cout << "Can't load main menu bgt" << std::endl;
	//}
	m_objectSprite.setTexture(m_objectTexture);
}

/// <summary>
/// Sets the the path to the directory path of a texture
/// </summary>
/// <param name="t_path"></param>
void Enemy::setPathToTexture(std::string t_path)
{
	m_path = t_path;
}

/// <summary>
/// Sets up the enemy bounds and detection radius
/// </summary>
void Enemy::setUpBounds()
{
	m_objectBounds.setSize(sf::Vector2f(m_boundsWidth, m_boundsHeight));
	m_objectBounds.setOrigin(m_boundsWidth / 2, (m_boundsHeight / 2));
	m_objectBounds.setFillColor(sf::Color(sf::Color(0, 0, 0, 0)));
	m_objectBounds.setOutlineColor(sf::Color::Green);
	m_objectBounds.setOutlineThickness(1.0f);
	m_objectBounds.setPosition(m_objectSprite.getPosition());

	m_detectionRadius.setSize(sf::Vector2f(256.0f,256.0f));
	m_detectionRadius.setOrigin(128, 128);
	m_detectionRadius.setFillColor(sf::Color(sf::Color(0, 255, 0, 100)));
	m_detectionRadius.setOutlineColor(sf::Color::Green);
	m_detectionRadius.setOutlineThickness(1.0f);
	m_detectionRadius.setPosition(m_objectSprite.getPosition());
}

/// <summary>
/// Updates the enemy
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="window"></param>
void Enemy::update(sf::Time deltaTime, sf::RenderWindow& window)
{
	m_objectSprite.setPosition(m_objectBounds.getPosition());
	m_detectionRadius.setPosition(m_objectSprite.getPosition());
	if (m_isSelected)
	{
		//count++;
		//std::string temp = std::to_string(count);
		//m_inspector->setTextString(temp);
	}
}

/// <summary>
/// renders the enmy objects
/// </summary>
/// <param name="window"></param>
void Enemy::render(sf::RenderWindow& window)
{
	if(getSelected())
	{
		window.draw(m_detectionRadius);
	}
	window.draw(m_objectSprite);

	if (m_dialogue->isEnabled())
	{
		m_dialogue->render(&window);
	}
}

/// <summary>
/// Renders the enemy inspector if selected
/// </summary>
/// <param name="window"></param>
void Enemy::renderInspector(sf::RenderWindow& window)
{
	if (m_isSelected)
	{
		//m_inspector->setTextString("Enemy");
		m_inspector->render(&window);
	}
}

/// <summary>
/// loads the enmy objects dialogue iif they have dialogue attached
/// </summary>
/// <param name="t_dialogueType"></param>
void Enemy::loadDialogue(std::string t_dialogueType)
{
	if (m_dialoguePaths.size() != 0)
	{
		//std::cout << m_dialoguePaths.size() << std::endl;
		for (auto iter = m_dialoguePaths.begin(); iter != m_dialoguePaths.end(); iter++)
		{
			//std::cout << iter->first << " : " << iter->second << std::endl;
			if (t_dialogueType == "Interacted")
			{

				if (iter->first == "Interacted")
				{
					m_dialogue->loadText(iter->second);
					break;
				}
			}
			else if (t_dialogueType == "InRange" && !inRangePlayed)
			{
				if (iter->first == "InRange")
				{
					inRangePlayed = true;
					m_dialogue->loadText(iter->second);
					break;
				}
			}
 
		}

	}
}