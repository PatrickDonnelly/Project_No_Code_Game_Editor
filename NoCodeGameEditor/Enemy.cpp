#include "Enemy.h"

#include <iostream>

Enemy::Enemy()
{
}

Enemy::Enemy(std::string t_typeTag, std::string t_path, TextureManager* t_textureManager)
{
	m_textureManager = t_textureManager;
	m_isCollidable = false;
	m_tag = t_typeTag;
	m_path = t_path;
	m_boundsHeight = 32;
	m_boundsWidth = 32;
	m_inpectorData.m_allowedDialogue = true;
	m_inspector = new Inspector("Enemy", m_inpectorData);
	m_dialogue = new DialogueBox();
	init();
}

Enemy::~Enemy()
{
}

void Enemy::init()
{
	setUpSprite();
	setUpBounds();
}

void Enemy::setUpSprite()
{
	setTexture(m_objectTexture);
	m_objectSprite.setOrigin(16, 16);
	m_objectSprite.setColor(sf::Color::White);
	m_objectSprite.setPosition(100, 100);
}

void Enemy::setTexture(sf::Texture& t_texture)
{
	m_objectTexture = m_textureManager->getTexture(m_path + ".png");
	//if (!t_texture.loadFromFile(m_path + ".png"))
	//{
	//	std::cout << "Can't load main menu bgt" << std::endl;
	//}
	m_objectSprite.setTexture(m_objectTexture);
}

void Enemy::setPathToTexture(std::string t_path)
{
	m_path = t_path;
}

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

void Enemy::render(sf::RenderWindow& window)
{
	if(getSelected())
	{
		window.draw(m_detectionRadius);
	}
	window.draw(m_objectSprite);
	if(m_isSelected)
	{
		//m_inspector->setTextString("Enemy");
		m_inspector->render(&window);
	}
	if (m_dialogue->isEnabled())
	{
		m_dialogue->render(&window);
	}
}

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