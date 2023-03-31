#pragma once

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SFML/Graphics.hpp>
#include "CheckBox.h"
#include "DialogueBox.h"
#include "Inspector.h"
#include "Attributes.h"

class Object
{
protected:

	Inspector* m_inspector;
	sf::Texture m_objectTexture;
	sf::Sprite m_objectSprite;
	sf::RectangleShape m_objectBounds;
	int m_boundsWidth;
	int m_boundsHeight;
	bool m_boundsOn = true;
	int m_row;
	int m_col;
	std::string m_path = "";
	std::string m_tag;
	bool m_isCollidable = false;
	std::string m_objectCategory;


public:
	Object();
	~Object();
	Attributes m_inpectorData;
	DialogueBox* m_dialogue;
	bool m_isSelected = false;
	bool m_moving = false;
	bool m_hasBeenSelected = false;

	virtual void init() = 0;
	virtual void setUpSprite() = 0;
	virtual void setObjectCategory(std::string t_ObjectCategory) = 0;
	virtual std::string getObjectCategory() = 0;
	virtual void setTexture(sf::Texture& t_texture) = 0;
	virtual void setPathToTexture(std::string t_path) = 0;
	virtual void setUpBounds() = 0;
	virtual void update(sf::Time deltaTime, sf::RenderWindow& window) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

	void setRowColumn(int t_row, int t_col) { m_row = t_row; m_col = t_col; }
	sf::RectangleShape* getBounds() { return &m_objectBounds; }
	sf::Sprite* getSprite() { return &m_objectSprite; }
	void toggleBounds() { m_boundsOn = !m_boundsOn; }
	bool isCollidable() { return m_isCollidable; }
	int getRow() { return m_row; }
	int getColumn() { return m_col; }
	void setCollidable(bool t_state) { m_isCollidable = t_state; }
	void setSelected(bool t_state) { m_isSelected = t_state; if(m_isSelected)m_objectSprite.setColor(sf::Color::Red); if (!m_isSelected)m_objectSprite.setColor(sf::Color::White); }
	void setMoving(bool t_state) { m_moving = t_state; }
	void setTag(std::string t_tag) { m_tag = t_tag; }
	Inspector* getInspector() { return m_inspector; }
	std::string getTag() { return m_tag; }
	std::string getPath() { return m_path; }
	DialogueBox* getDialogueBox() { return m_dialogue; }
	std::map<std::string, std::string> m_dialoguePaths;
	std::map<std::string, std::string> getDialoguePaths() { return m_dialoguePaths; }
	virtual void loadDialogue() = 0;
	//std::map<std::string, std::string> getDialoguePaths() { return m_dialoguePaths; }
};
#endif // !OBJECT_HPP

