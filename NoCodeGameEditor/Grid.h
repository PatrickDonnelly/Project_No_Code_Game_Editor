#pragma once
#ifndef GRID_HPP
#define GRID_HPP

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



class Grid
{
private:

public:

	GameState* m_gameState;
	int noOfObstacles = 0;
	int maxObstacles = 196;
	std::vector <Obstacle*> m_placedObjects;
	sf::Vector2f m_colStartPos{};
	sf::Vector2f m_colEndPos{};
	int noOfWallColliders = 0;
	bool startFound = false;
	bool roomGenerated = false;
	void clearObjects();
	std::vector<Colliders*> m_vectColliders;
	sf::Vector2f m_firstTilePosition{};
	bool m_playerSet = false;
	const int minimumWalls = 15;
	int wallsPlaced = 0;
	bool firstFloorSet = false;
	bool roomValid = false;
	bool changed = true;
	int m_vectGridSize = 5;
	std::vector<std::vector<Tile*>> m_vectGrid;
	sf::Font m_textFont;
	void setUpFont();
	void regenerateGrid();
	void CheckValidityOfWalls(int t_x, int t_y);
	int counter = 0;
	std::queue<Tile*> m_tileQueue{};
	Grid();
	Grid(GameState* t_gameState);
	void render(sf::RenderWindow* t_window);
	void update(sf::Time t_deltaTime, sf::RenderWindow& m_window);
	void placeRemove(sf::RenderWindow& m_window);
	void GenerateRoomSprites();
	void checkRoomValidity();
	void clearUnusedCells();
	void setUpWallColliders();
	void increaseGridSize();
	void decreaseGridSize();

	bool checkValidSelection();
	std::string m_selectedObject;
	std::vector<std::string> m_selectableObjects;
	void setSelectedObject(std::string t_path, std::string t_objectName);
	bool m_gridEnabled = true;
	bool m_collidersEnabled = true;
	std::string m_tempTag = "";
	void setGridEnabled() { m_gridEnabled = !m_gridEnabled; }
	void setCollidersEnabled() { m_collidersEnabled = !m_collidersEnabled; }

};
#endif // !GRID_HPP

