#pragma once

#ifndef ITEM_HPP
#define ITEM_HPP

#include "Object.h"
#include "TextureManager.h"

class Item : public Object
{
private:
	int64_t m_uuid;
public:
	Item();
	Item(std::string t_path);
	Item(std::string t_typeTag, std::string t_path, TextureManager* t_textureManager);
	~Item();
	TextureManager* m_textureManager;

	void init();
	void setUpSprite();
	void setTexture(sf::Texture& t_texture);
	void setPathToTexture(std::string t_path);
	void setUpBounds();
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void renderInspector(sf::RenderWindow& window);

	void setObjectCategory(std::string t_objectCategory) { m_objectCategory = "Item"; }
	std::string getObjectCategory() { return m_objectCategory; }
	int64_t getUUID() override { return m_uuid; }
};
#endif // !ITEM_HPP


