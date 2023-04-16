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
#include "PopUp.h"
#include "Globals.h"
#include "FontManager.h"

namespace fs = std::filesystem;

class LevelList
{
private:
	void loadLevelList();
	void setVisibleRow(sf::Event t_event, sf::RenderWindow& t_window);
	std::vector<Button*> m_prevNextbuttons;
	int m_currentRowIndex = 0;
	sf::RectangleShape m_bg;
	Button* m_closeButton;
	void initText();
	sf::Font m_font;
	FontManager m_fontManager;
	sf::Text m_text;
public:
	LevelList();
	LevelList(GameState* t_gameState);
	~LevelList();

	void refreshLevelList();
	void render(sf::RenderWindow* t_window);
	void processEvents(sf::Event t_event, sf::RenderWindow& t_window);


	GameState* m_currentGameState;
	void setUpGameButtons();
	std::vector<std::vector<Button*>> m_selectableGameButtons;
	std::vector<std::string> m_gameNames;
	std::string m_pathGames = "Games/";
	int m_noOfGamesFound = 0;
	int m_rowsGames = 0;
	std::string m_gameName;
	std::string getGameToBeLoaded();
};
#endif  // !MAINMENU_HPP

