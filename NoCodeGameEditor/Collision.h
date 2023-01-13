#pragma once
#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Player.h"
#include "Colliders.h"


class Collision
{
public:
	Collision();
	~Collision();

	//sf::RectangleShape& m_body;
	bool checkCollision(sf::RectangleShape* t_objectOne, sf::RectangleShape* t_objectTwo, float t_push); // 0 player to wall wont move, 1 push other object crate
	bool checkCollision(sf::RectangleShape* t_objectOne, sf::RectangleShape* t_objectTwo); // 0 player to wall wont move, 1 push other object crate
	void move(float t_deltaX, float t_deltaY, sf::RectangleShape* t_object);  // do not have to make body public now

}; 
#endif // !COLLISION_HPP

