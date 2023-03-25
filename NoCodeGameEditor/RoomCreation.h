#pragma once
#ifndef ROOMCREATION_HPP
#define ROOMCREATION_HPP

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Colliders.h"
#include "Obstacle.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <list>
#include <queue>
#include "GameState.h"
#include "Enemy.h"
#include "Terrain.h"
#include "Wall.h"
#include "Item.h"
#include "Decoration.h"
#include "Grid.h"

class RoomCreation
{
private:

public:

	GameState* m_gameState;
	sf::Vector2f m_colStartPos{};
	sf::Vector2f m_colEndPos{};
	int noOfWallColliders = 0;
	bool startFound = false;
	std::vector<Colliders*> m_vectColliders;

	sf::Vector2f m_firstTilePosition{};

	const int minimumWalls = 15;
	int wallsPlaced = 0;
	bool firstFloorSet = false;
	bool roomValid = false;
	bool roomGenerated = false;
	void resetValues();


	void CheckValidityOfWalls(int t_x, int t_y);
	int counter = 0;
	std::queue<Tile*> m_tileQueue{};
	RoomCreation();
	RoomCreation(GameState* t_gameState, Grid* t_grid);
	~RoomCreation();
	Grid* m_grid;
	void render(sf::RenderWindow* t_window);

	void update(sf::Time t_deltaTime, sf::RenderWindow& m_window);
	void placeRemove(sf::RenderWindow& m_window);
	void GenerateRoomSprites();
	void checkRoomValidity();
	void clearUnusedCells();
	void setUpWallColliders();




	bool m_collidersEnabled = true;

	//void setGridEnabled() { m_gridEnabled = !m_gridEnabled; }
	//void setCollidersEnabled() { m_collidersEnabled = !m_collidersEnabled; }

};
#endif // !ROOMCREATION_HPP
