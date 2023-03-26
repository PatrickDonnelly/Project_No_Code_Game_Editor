#pragma once

#ifndef DECORATION_HPP
#define DECORATION_HPP

#include "Object.h"
#include "TextureManager.h"

class Decoration : public Object
{

public:
	Decoration();
	Decoration(std::string t_typeTag, std::string t_path, TextureManager* t_textureManager);
	~Decoration();

	TextureManager* m_textureManager;

	void init();
	void setUpSprite();
	void setTexture(sf::Texture& t_texture);
	void setPathToTexture(std::string t_path);
	void setUpBounds();
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
};
#endif // !DECORATION_HPP

