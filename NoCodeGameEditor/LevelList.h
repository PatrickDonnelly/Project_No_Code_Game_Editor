#pragma once
#ifndef LEVELLIST_HPP
#define LEVELLIST_HPP
#include <SFML/Graphics.hpp>
#include "Label.h"
#include "GameState.h"
#include "Button.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class LevelList
{
private:
	void loadLevelList();
public:
	LevelList();
	LevelList(GameState* t_gameState);
	~LevelList();
	void refreshLevelList();
	void initButtons();
	void render(sf::RenderWindow* t_window);
	void processEvents(sf::Event t_event, sf::RenderWindow& t_window);


	GameState* m_currentGameState;
	void setUpGameButtons();
	std::vector<std::vector<Button*>> m_selectableGameButtons;
	std::vector<std::string> m_gameNames;
	std::string m_pathGames = "Games/";
	int m_rowsGames = 0;
	std::string m_gameName;
	std::string getGameToBeLoaded();
};
#endif  // !MAINMENU_HPP

