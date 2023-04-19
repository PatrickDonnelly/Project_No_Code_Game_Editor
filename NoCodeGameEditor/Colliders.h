#pragma once
#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Object.h"

struct ColliderData {
	int m_width = 0;
	int m_height = 0;
	sf::Vector2f m_position{};
	std::string m_tag = "";
	int m_row = 0;
	int m_col = 0;
};

class Colliders : public Object
{
public:

	void init();
	void setUpSprite();
	void setObjectCategory(std::string t_ObjectCategory);
	std::string getObjectCategory();
	void setTexture(sf::Texture& t_texture);
	void setPathToTexture(std::string t_path);
	void setUpBounds();
	void update(sf::Time deltaTime, sf::RenderWindow& window);



	int m_width = 32;
		Colliders();
		~Colliders();
		bool m_isVisible;

		ColliderData m_data;

		sf::RectangleShape m_colliderBounds;
		void increaseHeight();
		void increaseWidth();
		void decreaseHeight();
		void decreaseWidth();
		void render(sf::RenderWindow& window);
		sf::RectangleShape* getBounds() override { return&m_colliderBounds; }
		void setRowColumn(int t_row, int t_col) { m_data.m_row = t_row, m_data.m_col = t_col; }
		int getRow() { return m_data.m_row; }
		int getColumn() { return m_data.m_col; }


private:
	int64_t m_uuid;




};
#endif // !COLLIDER_HPP
