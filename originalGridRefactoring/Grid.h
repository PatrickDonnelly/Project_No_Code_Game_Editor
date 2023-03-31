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
#include "Enemy.h"
#include "Terrain.h"
#include "Wall.h"
#include "Item.h"
#include "Decoration.h"

//template <typename T, typename Type>
//void addObjectToGrid(std::vector<T*> t_vectorOfObjects, int t_i, int t_j, std::string t_tag, std::string t_selectedObject, std::vector<std::vector<Tile*>> t_grid)
//{
//	t_vectorOfObjects.push_back(new Type(t_tag, t_selectedObject));
//	t_vectorOfObjects.at(t_vectorOfObjects.size() - 1)->getEnemyBounds()->setPosition(m_vectGrid.at(t_i).at(t_j)->getPos());
//	t_vectorOfObjects.at(t_vectorOfObjects.size() - 1)->setRowColumn(t_i, t_j);
//}

template <typename T>
void renderPlacedObjects(std::vector<T*>& t_objects, sf::RenderWindow* t_window, bool t_collidersEnabled)
{
	for (int i = 0; i < t_objects.size(); i++)
	{
		t_objects.at(i)->render(*t_window);
		if (t_collidersEnabled)
		{
			t_window->draw(*t_objects.at(i)->getBounds());
		}
	}
}

template <typename T>
void setSpriteAndBounds(std::vector<T*>& t_objects)
{
	for (int i = 0; i < t_objects.size(); i++)
	{
		t_objects.at(i)->getSprite()->setPosition(t_objects.at(i)->getBounds()->getPosition());
	}
}

class Grid
{
private:

public:
	std::vector <Object*> m_enemies;
	std::vector <Object*> m_terrain;
	std::vector <Object*> m_walls;
	std::vector <Object*> m_items;
	std::vector <Object*> m_decorations;

	GameState* m_gameState;
	RoomCreation m_roomCreation(m_gr)
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


	//void addObjectToGrid(std::vector<T*> t_vectorOfObjects)
};
#endif // !GRID_HPP

