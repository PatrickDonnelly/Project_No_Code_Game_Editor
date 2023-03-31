#pragma once

#ifndef WALL_HPP
#define WALL_HPP

#include "Object.h"
#include "TextureManager.h"

class Wall : public Object
{

public:
	Wall();
	Wall(std::string t_typeTag, std::string t_path, TextureManager* t_textureManager);
	~Wall();
	TextureManager* m_textureManager;

	void init();
	void setUpSprite();
	void setTexture(sf::Texture& t_texture);
	void setPathToTexture(std::string t_path);
	void setUpBounds();
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);

	void setObjectCategory(std::string t_objectCategory) { m_objectCategory = "Wall"; }
	std::string getObjectCategory() { return m_objectCategory; }

};
#endif // !WALL_HPP


