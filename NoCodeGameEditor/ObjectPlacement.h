#pragma once
#ifndef OBJECTPLACEMENT_HPP
#define OBJECTPLACEMENT_HPP

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
#include "TextureManager.h"

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

template <typename T>
void deleteObject(std::vector<T*>& t_objects, Grid* t_grid, int& t_noOfObstacles, sf::RenderWindow& m_window)
{
	if (t_objects.size() > 0)
	{
		for (typename std::vector<T*>::iterator iter = t_objects.begin(); iter != t_objects.end();)
		{
			//(*iter)->getBounds()->getGlobalBounds();
			if ((*iter)->getBounds()->getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
			{
				// resets the right tile even if the object was moved
				t_grid->m_vectGrid.at((*iter)->getRow()).at((*iter)->getColumn())->m_hasObject = false;
				iter = t_objects.erase(iter);
				t_noOfObstacles--;
			}
			else
			{
				iter++;
			}
		}
	}
}



class ObjectPlacement
{
private:

public:
	std::vector <Object*> m_enemies;
	std::vector <Object*> m_terrain;
	std::vector <Object*> m_walls;
	std::vector <Object*> m_items;
	std::vector <Object*> m_decorations;

	GameState* m_gameState;

	ObjectPlacement();
	ObjectPlacement(GameState* t_gameState, Grid* t_grid, TextureManager* t_texturemanager);
	~ObjectPlacement();
	Grid* m_grid;
	TextureManager* m_textureManager;
	int noOfObstacles = 0;
	int maxObstacles = 190;


	void clearObjects();


	void render(sf::RenderWindow* t_window);
	void update(sf::Time t_deltaTime, sf::RenderWindow& m_window);
	void placeRemove(sf::RenderWindow& m_window);


	bool checkValidSelection();
	std::string m_selectedObject;
	std::vector<std::string> m_selectableObjects;
	void setSelectedObject(std::string t_path, std::string t_objectName);

	bool m_collidersEnabled = true;
	std::string m_tempTag = "";
	void setCollidersEnabled() { m_collidersEnabled = !m_collidersEnabled; }
	//void setGridEnabled() { m_gridEnabled = !m_gridEnabled; }
	//void setCollidersEnabled() { m_collidersEnabled = !m_collidersEnabled; }

};
#endif // !OBJECTPLACEMENT_HPP
