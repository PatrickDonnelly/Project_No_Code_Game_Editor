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
	//Attributes* m_enemyAttributes;
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

	
	void setObjectCategory(std::string t_objectCategory) { m_objectCategory = "Enemy"; }
	std::string getObjectCategory() { return m_objectCategory; }

	DialogueBox* getDialogueBox() { return m_dialogue; }
	void loadDialogue();
};
#endif // !ENEMY_HPP

