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

	void setUpPlaceableItemsButtons(sf::Font t_arialFont);
	void setUpGridFunctionButtons(sf::Font t_arialFont);
	void setUpTestBuildButtons(sf::Font t_arialFont);
	void setUpTextureRoomButtons(sf::Font t_arialFont);
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
	std::vector<Label> m_buildButtonLabels;

	// buttons for texturing the room
	// save, rebuild room, texture buttons floor, texture buttons walls
	std::vector<Button> m_textureRoomButtons;
	std::vector<Label> m_textureRoomLabels;


	// buttons for placing objects
	// object buttons, test, rebuild room, clear objects
	std::vector<Button> m_selectableObjects;
	std::vector<Label> m_texturedLabels;

	// buttons for testing
	// save room, place more objects, start over
	std::vector<Button> m_testingButtons;
	std::vector<Label*> m_testingButtonLabels;

	Grid* m_grid;

};
#endif // !UIBUILDMODE_HPP
