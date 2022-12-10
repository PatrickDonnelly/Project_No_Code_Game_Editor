#pragma once
#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Player.h"
#include "Colliders.h"
#include "Weapon.h"
#include "Obstacle.h"
#include "Roomdata.h"

class Collision
{
public:
	Collision();
	Collision(Player* t_player, RoomData* t_roomData, Weapon* t_weapon, Colliders* t_walls);
	~Collision();

	Player* m_player;
	RoomData* m_roomData;
	Weapon* m_weapon;
	Colliders* m_walls;



	//sf::RectangleShape& m_body;
	void update(sf::Time deltaTime);

	void setColliders(sf::RectangleShape* t_objectOne, std::vector<Colliders> t_objectTwo, int t_size, float t_weight);
	void setColliders(sf::RectangleShape* t_objectOne, std::vector<Obstacle*> t_objectTwo, int t_size, float t_weight);
	void setColliders(std::vector<Obstacle*> t_objectOne, std::vector<Colliders> t_objectTwo, int t_sizeOne, int t_sizeTwo, float t_weight);
	void setColliders(std::vector<Obstacle*> t_objectOne, int t_sizeOne, float t_weight);
	void setColliders();

	bool checkCollision(sf::RectangleShape* t_objectOne, sf::RectangleShape* t_objectTwo, float t_push); // 0 player to wall wont move, 1 push other object crate
	void move(float t_deltaX, float t_deltaY, sf::RectangleShape* t_object);  // do not have to make body public now

}; 
#endif // !COLLISION_HPP

