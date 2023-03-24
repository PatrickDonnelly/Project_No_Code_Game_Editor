#pragma once

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "CheckBox.h"
#include "DialogueBox.h"
#include "Inspector.h"
#include "Attributes.h"



class Enemy
{
	Attributes m_inspectorData;
	sf::Texture m_enemyTexture;
	sf::Sprite m_enemySprite;
	sf::RectangleShape m_enemyBounds;
	int m_boundsWidth;
	int m_boundsHeight;

	int m_row;
	int m_col;

public:
	Enemy();
	Enemy(std::string t_typeTag, std::string t_path);
	~Enemy();

	std::string m_tempPath = "";

	std::string m_tag;
	bool m_isCollidable = false;
	bool isCollidable();
	void init();
	void setUpSprite();
	void setEnemyTexture(sf::Texture& t_texture);
	void setUpEnemyBounds();
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	sf::Sprite* getEnemySprite();
	sf::RectangleShape* getEnemyBounds();

	void setRowColumn(int t_row, int t_col);

	int getRow();

	int getColumn();
	bool m_hasDialogue = false;
	int m_detectionRadius;

	std::vector<std::string> m_dialoguePaths;
	DialogueBox m_dialogue;

	bool m_boundsOn = true;
	void toggleBounds() { m_boundsOn = !m_boundsOn; }

	//CheckBox
};
#endif // !ENEMY_HPP

