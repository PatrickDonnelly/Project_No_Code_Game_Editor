#pragma once
#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Colliders
{
	public:

		Colliders();
		~Colliders();

		void init();
		void setUpHorizontalWallBounds(float m_startPos, float m_endPos);
		void setUpVerticalWallBounds(float m_startPos, float m_endPos);

		void render(sf::RenderWindow* window);
		sf::RectangleShape* getBounds();

		sf::RectangleShape m_wallCentre;
		sf::RectangleShape m_wallColliderBounds;

		std::vector<Colliders> m_wallColliders;
		int noOfWallColliders = 0;
		void setHorizontalWallColliders(sf::Vector2f t_colStartPos, sf::Vector2f t_colEndPos);
		void setVerticalWallColliders(sf::Vector2f t_colStartPos, sf::Vector2f t_colEndPos);

		int m_wallBoundsWidth;
		int m_wallBoundsHeight;
};
#endif // !COLLIDER_HPP
