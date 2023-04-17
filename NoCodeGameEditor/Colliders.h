#pragma once
#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct ColliderData {
	int m_width = 0;
	int m_height = 0;
	sf::Vector2f m_position{};
	std::string m_tag = "";
	int m_row = 0;
	int m_col = 0;
};

class Colliders
{
public:

		Colliders();
		~Colliders();
		bool m_isVisible;

		ColliderData m_data;
		void init();
		sf::RectangleShape m_colliderBounds;
		void increaseHeight();
		void increaseWidth();
		void decreaseHeight();
		void decreaseWidth();
		void render(sf::RenderWindow* window);
		sf::RectangleShape* getBounds();
		void setRowColumn(int t_row, int t_col) { m_data.m_row = t_row, m_data.m_col = t_col; }
		int getRow() { return m_data.m_row; }
		int getColumn() { return m_data.m_col; }


private:
};
#endif // !COLLIDER_HPP
