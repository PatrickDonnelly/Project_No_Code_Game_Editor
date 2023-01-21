#ifndef UIBUILDMODE_HPP
#define UIBUILDMODE_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "Button.h"
#include "Label.h"
#include "Grid.h"
#include "GameState.h"
#include <fstream>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

enum class TabState {
	TAB_WALLS = 0,
	TAB_TERRAIN = 1,
	TAB_ENEMIES = 2,
	TAB_ITEMS = 3,
	TAB_DECORATIONS = 4
};

class UiBuildMode
{
private:

	TabState m_currentTab;
	void setUpPlaceableItemsButtons(sf::Font t_arialFont, std::vector<std::vector<Button*>>& t_objectButtons, std::vector<std::vector<Label*>>& t_labels, std::vector<std::string> t_objects, std::string t_path);
	void setUpGridFunctionButtons(sf::Font t_arialFont);
	void setUpTestBuildButtons(sf::Font t_arialFont);
	void setUpTextureRoomButtons(sf::Font t_arialFont);
	void setUpPlacementModeButtons(sf::Font t_arialFont);
	void setUpCategoryButtons(sf::Font t_arialFont);
	void setUpLabels(std::vector<Button>::iterator t_col, std::vector<Label*>& t_labels, std::vector<std::vector<Button*>>& t_objectButtons, std::vector<std::string>t_objects);

	void processBuildRoomButtonInput(sf::Event t_event, sf::RenderWindow& t_window);
	void processPlaceObjectsButtonInput(sf::Event t_event, sf::RenderWindow& t_window, std::string& t_path, std::vector<std::vector<Label*>>& t_labels, std::vector<std::vector<Button*>>& t_objectButtons);
	void processTestRoomButtonInput(sf::Event t_event, sf::RenderWindow& t_window);

	sf::Font m_arialFont;
public:

	UiBuildMode(sf::Font t_arialFont, Grid* t_grid, GameState* t_currentGameState);
	UiBuildMode();
	~UiBuildMode();
	GameState* m_gameState;
	void render(sf::RenderWindow* t_window);
	void processEvents(sf::Event t_event, sf::RenderWindow& t_window);

	// buttons for building the room
	// -. + , clear, generate
	std::vector<Button> m_buildButtons;
	std::vector<Label*> m_buildButtonLabels;

	// buttons for texturing the room
	// save, rebuild room, texture buttons floor, texture buttons walls
	std::vector<Button> m_textureRoomButtons;
	std::vector<Label*> m_textureRoomLabels;


	// buttons for placing objects
	// object buttons, test, rebuild room, clear objects
	std::vector<Button*> m_objectCategoryButtons;
	std::vector<Label*> m_objectCategoryLabels;

	std::vector<Button> m_selectableObjects;
	std::vector<Label*> m_texturedLabels;

	std::vector<Button> m_placementOptions;
	std::vector<Label*> m_placementOptionsLabels;

	std::vector<std::vector<Button*>> m_selectableWallButtons;
	std::vector<std::vector<Label*>> m_selectableWallLabels;
	std::vector<std::string> m_walls;
	std::string m_pathWalls = "ASSETS/IMAGES/Walls/";

	std::vector<std::vector<Button*>> m_selectableFloorButtons;
	std::vector<std::vector<Label*>> m_selectableFloorLabels;
	std::vector<std::string> m_floors;
	std::string m_pathFloors = "ASSETS/IMAGES/Terrain/Grass/";


	std::vector<std::vector<Button*>> m_selectableDecorationButtons;
	std::vector<std::vector<Label*>> m_selectableDecorationLabels;
	std::vector<std::string> m_decorations;
	std::string m_pathDecorations = "ASSETS/IMAGES/Decorations/";


	std::vector<std::vector<Button*>> m_selectableItemButtons;
	std::vector<std::vector<Label*>> m_selectableItemLabels;
	std::vector<std::string> m_items;
	std::string m_pathItems = "ASSETS/IMAGES/Items/";


	std::vector<std::vector<Button*>> m_selectableEnemiesButtons;
	std::vector<std::vector<Label*>> m_selectableEnemiesLabels;
	std::vector<std::string> m_enemies;
	std::string m_pathEnemies = "ASSETS/IMAGES/Enemies/";


	void deselectButtons(std::vector<std::vector<Button*>>& t_objectButtons);

	// buttons for testing
	// save room, place more objects, start over
	std::vector<Button> m_testingButtons;
	std::vector<Label*> m_testingButtonLabels;

	std::vector<sf::Vector2f> m_storePositions;

	Grid* m_grid;



};
#endif // !UIBUILDMODE_HPP
