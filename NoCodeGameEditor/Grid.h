#pragma once
#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <iostream>
#include <vector>
#include <stdio.h>

class Grid
{
private:

public:
	bool changed = true;
	int m_vectGridSize = 4;
	std::vector<std::vector<Tile*>> m_vectGrid;
	sf::Font m_textFont;
	void setUpFont();
	void regenerateGrid(int t_changeInSize);
	sf::Text m_helpText;
	sf::RectangleShape m_background;
	void CheckValidityOfWalls(int t_x, int t_y);
	int counter = 0;
	Grid();
	void render(sf::RenderWindow* t_window);
	void update(sf::Time t_deltaTime, sf::RenderWindow& m_window);
	void placeRemove(sf::RenderWindow& m_window);
};
#endif // !GRID_HPP

