#pragma once

#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>
#include "CheckBox.h"
#include "DialogueBox.h"

class Obstacle
{
	sf::Texture m_obstacleTexture;
	sf::Sprite m_obstacleSprite;
	sf::RectangleShape m_obstacleBounds;
	int m_boundsWidth;
	int m_boundsHeight;

	int m_row;
	int m_col;
	
public:
	Obstacle();
	Obstacle(std::string t_typeTag, std::string t_path);
	~Obstacle();

	std::string m_tempPath = "";

	std::string m_tag;
	bool m_isCollidable = false;
	bool isCollidable();
	void init();
	void setUpSprite();
	void setObstacleTexture(sf::Texture& t_texture);
	void setUpBounds();
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	sf::Sprite* getSprite();
	sf::RectangleShape* getBounds();

	void setRowColumn(int t_row, int t_col);

	int getRow();

	int getColumn();
	bool m_hasDialogue = false;
	CheckBox m_whenDamaged;
	CheckBox m_whenDead;
	CheckBox m_whenInRadius;
	int m_detectionRadius;
	CheckBox m_whenInteracted;

	std::vector<std::string> m_dialoguePaths;
	DialogueBox m_dialogue;
	//CheckBox
};
#endif // !OBSTACLE_HPP

