#ifndef UIBUILDMODE_HPP
#define UIBUILDMODE_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "Button.h"
#include "Label.h"
#include "Grid.h"



class UiBuildMode
{
private:

	void setUpPlaceableItemsButtons(sf::Font t_arialFont);
	void setUpGridFunctionButtons(sf::Font t_arialFont);
	sf::Font m_arialFont;
public:

	UiBuildMode(sf::Font t_arialFont, Grid* t_grid);
	UiBuildMode();
	~UiBuildMode();
	void render(sf::RenderWindow* t_window);
	void processEvents(sf::Event t_event, sf::RenderWindow& t_window);


	const static int noOfButtons = 4;
	Button m_buttons[noOfButtons];
	Label* m_labels[noOfButtons];
	Grid* m_grid;

	std::vector<Button> m_selectableObjects;
	std::vector<Label*> m_texturedLabels;

};
#endif // !UIBUILDMODE_HPP
