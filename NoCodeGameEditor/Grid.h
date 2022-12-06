#pragma once
#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <list>
#include <queue>


class Grid
{
private:

public:
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
	sf::Text m_helpText;
	sf::RectangleShape m_background;
	void CheckValidityOfWalls(int t_x, int t_y);
	int counter = 0;
	std::queue<Tile*> m_tileQueue{};
	Grid();
	void render(sf::RenderWindow* t_window);
	void update(sf::Time t_deltaTime, sf::RenderWindow& m_window);
	void placeRemove(sf::RenderWindow& m_window);
	void GenerateRoomSprites();
	void checkRoomValidity();
	void clearUnusedCells();
};
#endif // !GRID_HPP

