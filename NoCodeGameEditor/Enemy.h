#pragma once

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Object.h"
#include "TextureManager.h"
#include "Attributes.h"
#include <SFML/Graphics.hpp>


class Enemy : public Object
{
private:
	sf::RectangleShape m_detectionRadius;
	int64_t m_uuid;
public:
	Enemy();
	Enemy(std::string t_path);
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
	void renderInspector(sf::RenderWindow& window);

	int count = 0;

	bool m_hasDialogue = false;
	bool getHasDialogue() override { return m_hasDialogue; }

	
	void setObjectCategory(std::string t_objectCategory) { m_objectCategory = "Enemy"; }
	std::string getObjectCategory() { return m_objectCategory; }

	DialogueBox* getDialogueBox() { return m_dialogue; }

	void loadDialogue(std::string t_dialogueType) override;
	bool inRangePlayed = false;
	bool getInRange() override{ return inRangePlayed; }
	std::map<std::string, std::string>* getDialoguePaths() override { return &m_dialoguePaths; }
	sf::RectangleShape* getDetectionRadius() override { return& m_detectionRadius; }
	void setDetectionRadius(int t_noOfCells) { m_detectionRadius.setSize(sf::Vector2f(32.0f * t_noOfCells, 32.0f * t_noOfCells)); }
	int64_t getUUID() override { return m_uuid; }
};
#endif // !ENEMY_HPP

