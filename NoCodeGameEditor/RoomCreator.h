#pragma once
#ifndef ROOMCREATOR_HPP
#define ROOMCREATOR_HPP

#include <SFML/Graphics.hpp>
#include "Colliders.h"
#include "Obstacle.h"
#include "RoomData.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <list>
#include <queue>
#include "Grid.h"

class RoomCreator
{
public:
	RoomCreator();
	RoomCreator(Grid* t_grid, RoomData* t_roomData, Colliders* t_wallCollider);
	~RoomCreator();

	bool startFound = false;

	sf::Vector2f m_colStartPos{};
	sf::Vector2f m_colEndPos{};
	Colliders* m_wallCollider;
	RoomData* m_roomData;

	// -------
	const int minimumWalls = 15;
	int wallsPlaced = 0;
	bool changed = true;
	int noOfObstacles = 0;
	// -------


	Grid* m_grid;
	int counter = 0;
	sf::Vector2f m_firstTilePosition{};
	bool firstFloorSet = false;
	std::queue<Tile*> m_tileQueue{};
	bool roomValid = false;
	bool roomGenerated = false;
	bool m_playerSet = false;

	void render(sf::RenderWindow* t_window);
	void update(sf::Time t_deltaTime, sf::RenderWindow& m_window);
	void clearRoom();
	void CheckValidityOfWalls(int t_x, int t_y);
	void placeRemove(sf::RenderWindow& m_window);
	void GenerateRoomSprites();
	void checkRoomValidity();
	void setUpWallColliders();


private:


};
#endif // !ROOMCREATOR_HPP

