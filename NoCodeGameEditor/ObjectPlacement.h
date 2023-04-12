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
#include "Globals.h"

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
void deleteObject(std::vector<T*>& t_objects, Grid* t_grid, Object* t_currentlySelected, sf::RenderWindow& m_window)
{
	if (t_objects.size() > 0)
	{
		for (typename std::vector<T*>::iterator iter = t_objects.begin(); iter != t_objects.end();)
		{
			(*iter)->setSelected(false);
			//(*iter)->getBounds()->getGlobalBounds();
			if ((*iter)->getBounds()->getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
			{
				// resets the right tile even if the object was moved
				t_grid->m_vectGrid.at((*iter)->getRow()).at((*iter)->getColumn()).m_hasObject = false;
				t_grid->m_vectGrid.at((*iter)->getRow()).at((*iter)->getColumn()).m_objectType = "";
				iter = t_objects.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
}

template <typename T>
void setSelected(std::vector<T*>& t_objects, sf::RenderWindow* t_window, Object* t_currentlySelected)
{
	for (int i = 0; i < t_objects.size(); ++i)
	{
		if (t_objects.at(i)->getBounds()->getGlobalBounds().contains(t_window->mapPixelToCoords(sf::Mouse::getPosition(*t_window))))
		{

			t_currentlySelected = t_objects.at(i);
			t_currentlySelected->setSelected(true);
		}
	}
}

//template <typename T>
//void setSelectedGridObjectt(std::vector<T*>& t_objects, sf::RenderWindow* t_window, Object* t_currentlySelected)
//{
//	for (int i = 0; i < t_objects.size(); ++i)
//	{
//		if (t_objects.at(i)->getBounds()->getGlobalBounds().contains(t_window->mapPixelToCoords(sf::Mouse::getPosition(*t_window))))
//		{
//
//			t_currentlySelected = t_objects.at(i);
//			t_currentlySelected->setSelected(true);
//			break;
//		}
//	}
//}

class ObjectPlacement
{
private:

	void setSelectedGridObject(std::vector<Object*>& t_enemies, sf::RenderWindow& m_window);
	sf::Vector2i m_originalPosition{ 0,0 };
	std::string m_storedObjectType = "";
	void setObject(int t_row, int t_col, std::string t_label, std::vector<Object*>& t_objects);
	bool initialPress = false;
	bool m_placingMultiple = false;
	int startRow = 0;
	int endRow = 0;
	int startCol = 0;
	int endCol = 0;
	sf::RectangleShape m_area;
	sf::Vector2i m_screenPos;
	sf::Vector2f m_worldPos;
	void createObject(int row, int col);
	void swapInts(int& t_smallerNumber, int& t_biggerNumber);
	void removeObject(sf::Event t_event, sf::RenderWindow& m_window);
	void placeObject(sf::Event t_event, sf::RenderWindow& m_window);
	void moveObject(sf::Event t_event, sf::RenderWindow& m_window);
	void selectObject(sf::Event t_event, sf::RenderWindow& m_window);

	void placeMultipleObjects(sf::Event t_event, sf::RenderWindow& m_window);
	void setInitialPress(sf::RenderWindow& m_window);
	void setEndOfPress(sf::RenderWindow& m_window);
	void scaleArea(sf::RenderWindow& m_window);

public:
	Object* getSelectedGridObject();
	void processEvents(sf::Event t_event, sf::RenderWindow& t_window);
	sf::Clock m_clock;
	sf::Time m_doubleClickTime = sf::Time::Zero;
	bool checkForDoubleClick(sf::Clock& t_clock, sf::Time& t_doubleClickTime);
	std::vector <Object*> m_enemies;
	std::vector <Object*> m_terrain;
	std::vector <Object*> m_walls;
	std::vector <Object*> m_items;
	std::vector <Object*> m_decorations;

	Object* m_currentlySelected{nullptr};
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



	bool checkValidSelection();
	std::string m_selectedObject;
	std::vector<std::string> m_selectableObjects;
	void setSelectedObject(std::string t_path, std::string t_objectName);

	bool m_collidersEnabled = true;
	std::string m_tempTag = "";
	void setCollidersEnabled() { m_collidersEnabled = !m_collidersEnabled; }
};
#endif // !OBJECTPLACEMENT_HPP
