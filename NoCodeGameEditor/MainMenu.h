#pragma once
#ifndef MAINMENU_HPP
#define MAINMENU_HPP
#include <SFML/Graphics.hpp>
#include "Label.h"
#include "GameState.h"
#include "Button.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class MainMenu
{
private:

public:
	MainMenu();
	MainMenu(GameState* t_gameState);
	~MainMenu();
	
	void initButtons();
	void render(sf::RenderWindow* t_window);
	void processEvents(sf::Event t_event, sf::RenderWindow& t_window);

	std::vector<Button*> m_mainMenuButtons;

	GameState* m_currentGameState;
	void setUpGameButtons();
	std::vector<std::vector<Button*>> m_selectableGameButtons;
	std::vector<std::string> m_gameNames;
	std::string m_pathGames = "Games/";
	int m_rowsGames = 0;

};
#endif  // !MAINMENU_HPP

