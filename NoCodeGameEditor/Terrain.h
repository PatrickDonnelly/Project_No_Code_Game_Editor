#pragma once

#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "Object.h"

class Terrain : public Object
{

public:
	Terrain();
	Terrain(std::string t_typeTag, std::string t_path);
	~Terrain();

	void init();
	void setUpSprite();
	void setTexture(sf::Texture& t_texture);
	void setPathToTexture(std::string t_path);
	void setUpBounds();
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
};
#endif // !TERRAIN_HPP
