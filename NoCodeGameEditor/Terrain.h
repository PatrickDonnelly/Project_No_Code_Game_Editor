#pragma once

#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "Object.h"
#include "TextureManager.h"

class Terrain : public Object
{
private:
	int64_t m_uuid;

public:
	Terrain();
	Terrain(std::string t_typeTag, std::string t_path, TextureManager* t_textureManager);
	~Terrain();
	TextureManager* m_textureManager;
	void init();
	void setUpSprite();
	void setTexture(sf::Texture& t_texture);
	void setPathToTexture(std::string t_path);
	void setUpBounds();
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	int64_t getUUID() override { return m_uuid; }
};
#endif // !TERRAIN_HPP
