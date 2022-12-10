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



class Grid
{
private:

public:
	Grid();

	std::vector<std::vector<Tile*>> m_vectTiles;
	int m_vectGridSize = 5;


	// ---------------------------


	//bool startFound = false;
	//std::vector<Colliders*> m_vectColliders;
	//sf::Vector2f m_colStartPos{};
	//sf::Vector2f m_colEndPos{};
	//int noOfWallColliders = 0;
	void setUpWallColliders();
	












	// -------------------------------


	sf::Font m_textFont;
	void setUpFont();
	void regenerateGrid();
	sf::Text m_helpText;
	sf::RectangleShape m_background;



	void render(sf::RenderWindow* t_window);
	void update(sf::Time t_deltaTime, sf::RenderWindow& m_window);

	void clearUnusedCells();

};
#endif // !GRID_HPP

