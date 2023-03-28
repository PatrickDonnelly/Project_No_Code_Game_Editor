#pragma once

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Object.h"
#include "TextureManager.h"
#include "Attributes.h"

class Enemy : public Object
{

public:
	Enemy();
	Enemy(std::string t_typeTag, std::string t_path, TextureManager* t_textureManager);
	~Enemy();
	TextureManager* m_textureManager;
	Attributes* m_enemyAttributes;
	void init();
	void setUpSprite();
	void setTexture(sf::Texture& t_texture);
	void setPathToTexture(std::string t_path);
	void setUpBounds();
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	int count = 0;

	bool m_hasDialogue = false;
	int m_detectionRadius;
	std::vector<std::string> m_dialoguePaths;
	DialogueBox m_dialogue;

};
#endif // !ENEMY_HPP

