#pragma once

#ifndef ITEM_HPP
#define ITEM_HPP

#include "Object.h"

class Item : public Object
{

public:
	Item();
	Item(std::string t_typeTag, std::string t_path);
	~Item();

	void init();
	void setUpSprite();
	void setTexture(sf::Texture& t_texture);
	void setPathToTexture(std::string t_path);
	void setUpBounds();
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
};
#endif // !ITEM_HPP


