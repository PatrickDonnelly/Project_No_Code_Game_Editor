#ifndef UIBUILDMODE_HPP
#define UIBUILDMODE_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "Button.h"
#include "Label.h"
#include "Grid.h"
#include "Inspector.h"
#include "GameState.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include "ObjectPlacement.h"

namespace fs = std::filesystem;

enum class TabState {
	TAB_WALLS = 0,
	TAB_TERRAIN = 1,
	TAB_ENEMIES = 2,
	TAB_ITEMS = 3,
	TAB_DECORATIONS = 4,
	TAB_MISC = 5
};

class UiBuildMode
{
private:
	Inspector* m_inspector;

	TabState m_currentTab;
	void setUpPlaceableItemsButtons(sf::Font& t_arialFont, int& t_rows, std::vector<std::vector<Button*>>& t_objectButtons, std::vector<std::vector<Label*>>& t_labels, std::vector<std::string> t_objects, std::string t_path);
	void setUpGridFunctionButtons(sf::Font& t_arialFont);
	void setUpTestBuildButtons(sf::Font& t_arialFont);
	void setUpTextureRoomButtons(sf::Font& t_arialFont);
	void setUpPlacementModeButtons(sf::Font& t_arialFont);
	void setUpCategoryButtons(sf::Font& t_arialFont);
	void setUpLabels(std::vector<Button>::iterator t_col, std::vector<Label*>& t_labels, std::vector<std::vector<Button*>>& t_objectButtons, std::vector<std::string>t_objects);
	void setVisibleRow(sf::Event t_event, sf::RenderWindow& t_window, int t_rows, std::vector<std::vector<Button*>>& t_objectButtons);
	void toggleGridAndColliders(sf::Event t_event, sf::RenderWindow& t_window);
	void processDialogueButtons(sf::Event t_event, sf::RenderWindow& t_window);
	void processBuildRoomButtonInput(sf::Event t_event, sf::RenderWindow& t_window);
	void processPlaceObjectsButtonInput(sf::Event t_event, sf::RenderWindow& t_window, std::string& t_path, std::vector<std::vector<Label*>>& t_labels, std::vector<std::vector<Button*>>& t_objectButtons);
	void processTestRoomButtonInput(sf::Event t_event, sf::RenderWindow& t_window);

	void zoomViewAtPoint(sf::Vector2i pixel, sf::RenderWindow& window, float zoom, bool t_zoomIn);

	sf::RectangleShape m_bgBottom;
	sf::RectangleShape m_bgLeft;
	sf::RectangleShape m_bgRight;


	sf::Font m_arialFont;
public:
	UiBuildMode(sf::Font& t_arialFont, Grid* t_grid, GameState* t_currentGameState, ObjectPlacement* t_objectPlacement);
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
	int m_rowsWalls = 0;


	std::vector<std::vector<Button*>> m_selectableFloorButtons;
	std::vector<std::vector<Label*>> m_selectableFloorLabels;
	std::vector<std::string> m_floors;
	std::string m_pathFloors = "ASSETS/IMAGES/Terrain/Grass/";
	int m_rowsFloors = 0;


	std::vector<std::vector<Button*>> m_selectableDecorationButtons;
	std::vector<std::vector<Label*>> m_selectableDecorationLabels;
	std::vector<std::string> m_decorations;
	std::string m_pathDecorations = "ASSETS/IMAGES/Decorations/";
	int m_rowsDecorations = 0;

	std::vector<std::vector<Button*>> m_selectableItemButtons;
	std::vector<std::vector<Label*>> m_selectableItemLabels;
	std::vector<std::string> m_items;
	std::string m_pathItems = "ASSETS/IMAGES/Items/";
	int m_rowsItems = 0;



	std::vector<std::vector<Button*>> m_selectableEnemiesButtons;
	std::vector<std::vector<Label*>> m_selectableEnemiesLabels;
	std::vector<std::string> m_enemies;
	std::string m_pathEnemies = "ASSETS/IMAGES/Enemies/";
	int m_rowsEnemies = 0;

	std::vector<std::vector<Button*>> m_selectableMiscButtons;
	std::vector<std::vector<Label*>> m_selectableMiscLabels;
	std::vector<std::string> m_miscObjects;
	std::string m_pathMiscObjects = "ASSETS/IMAGES/Misc/";
	int m_rowsMisc = 0;


	std::vector<Button*> m_prevNextbuttons;
	std::vector<Button*> m_toggleGridButtons;
	int m_currentRowIndex = 0;
	sf::Text m_currentRowText;
	sf::Text m_collidersOnOffText;
	sf::Text m_gridOnOffText;
	void deselectButtons(std::vector<std::vector<Button*>>& t_objectButtons);

	// buttons for testing
	// save room, place more objects, start over
	std::vector<Button> m_testingButtons;
	std::vector<Label*> m_testingButtonLabels;

	std::vector<sf::Vector2f> m_storePositions;

	Grid* m_grid;
	ObjectPlacement* m_objectPlacement;
};
#endif // !UIBUILDMODE_HPP
