#pragma once

#ifndef WALL_HPP
#define WALL_HPP

#include "Object.h"

class Wall : public Object
{

public:
	Wall();
	Wall(std::string t_typeTag, std::string t_path);
	~Wall();

	void init();
	void setUpSprite();
	void setTexture(sf::Texture& t_texture);
	void setPathToTexture(std::string t_path);
	void setUpBounds();
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
};
#endif // !WALL_HPP


