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
#include "TextureManager.h"



class Grid
{
private:
	TextureManager* m_textureManager;

public:


	GameState* m_gameState;





	bool m_playerSet = false;



	int m_vectGridSize = 5;
	std::vector<std::vector<Tile*>> m_vectGrid;
	sf::Font m_textFont;
	void setUpFont();
	void regenerateGrid();



	Grid();
	Grid(GameState* t_gameState, TextureManager* t_textureManager);
	void render(sf::RenderWindow* t_window);

	void clearUnusedCells();

	void increaseGridSize();
	void decreaseGridSize();

	bool m_gridEnabled = true;
	bool m_collidersEnabled = true;
	void setGridEnabled() { m_gridEnabled = !m_gridEnabled; }
	void setCollidersEnabled() { m_collidersEnabled = !m_collidersEnabled; }
};
#endif // !GRID_HPP

