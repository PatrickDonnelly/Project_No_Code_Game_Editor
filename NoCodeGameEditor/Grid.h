#pragma once
#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Colliders.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <list>
#include <queue>
#include "GameState.h"
#include "TextureManager.h"



class Grid
{
private:
	TextureManager* m_textureManager;
	void processEvents(sf::Event t_event, sf::RenderWindow& t_window);
public:


	GameState* m_gameState;

	void clear();
	void newGrid();
	void setGridSize(int t_gridSize) { m_vectGridSize = t_gridSize; }


	bool m_playerSet = false;

	//int rows = 160;
	//int cols = 160;
	//std::vector<Tile> m_tiles = std::vector<Tile>(10);
	//std::vector<std::vector<Tile>> m_vectGrid = std::vector<std::vector<Tile>>(10, std::vector<Tile>(10));
	//160
	int m_vectGridSize = 100;
	std::vector<std::vector<Tile>> m_vectGrid;
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

