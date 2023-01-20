#ifndef UIBUILDMODE_HPP
#define UIBUILDMODE_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "Button.h"
#include "Label.h"
#include "Grid.h"
#include "GameState.h"

class UiBuildMode
{
private:

	void setUpPlaceableItemsButtons(sf::Font t_arialFont, int t_noOfObjects, std::vector<std::vector<Button*>> t_objectButtons, std::vector<Label*> t_labels, std::vector<std::string> t_objects);
	void setUpGridFunctionButtons(sf::Font t_arialFont);
	void setUpTestBuildButtons(sf::Font t_arialFont);
	void setUpTextureRoomButtons(sf::Font t_arialFont);
	void setUpPlacementModeButtons(sf::Font t_arialFont);
	void setUpCategoryButtons(sf::Font t_arialFont);


	void processBuildRoomButtonInput(sf::Event t_event, sf::RenderWindow& t_window);
	void processPlaceObjectsButtonInput(sf::Event t_event, sf::RenderWindow& t_window);
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
	std::vector<Label*> m_selectableWallLabels;
	std::vector<std::string> m_walls;

	std::vector<std::vector<Button*>> m_selectableFloorButtons;
	std::vector<Label*> m_selectableFloorLabels;
	std::vector<std::string> m_floors;

	std::vector<std::vector<Button*>> m_selectableDecorationButtons;
	std::vector<Label*> m_selectableDecorationLabels;
	std::vector<std::string> m_decorations;

	std::vector<std::vector<Button*>> m_selectableItemButtons;
	std::vector<Label*> m_selectableItemLabels;
	std::vector<std::string> m_items;

	std::vector<std::vector<Button*>> m_selectableEnemiesButtons;
	std::vector<Label*> m_selectableEnemiesLabels;
	std::vector<std::string> m_enemies;


	// buttons for testing
	// save room, place more objects, start over
	std::vector<Button> m_testingButtons;
	std::vector<Label*> m_testingButtonLabels;

	std::vector<sf::Vector2f> m_storePositions;

	Grid* m_grid;

};
#endif // !UIBUILDMODE_HPP
