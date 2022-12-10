#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "Tile.h"
#include "Grid.h"
#include "Button.h"
#include "Label.h"
#include "Player.h"
#include "Collision.h"
#include "Obstacle.h"
#include "Weapon.h"
#include "RoomCreator.h"

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	Grid* m_grid{ nullptr };
	Player* m_player;
	Collision m_checkCollision;
	Weapon* m_spear;
	Colliders* m_wallCollider;
	RoomData* m_roomData;
	RoomCreator* m_roomCreator;

	void setUpFontAndText();
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	sf::Font m_ArialFont;
	sf::Text m_text;

	const static int noOfButtons = 2;
	Button m_buttons[noOfButtons];
	Label* m_labels[noOfButtons];

	sf::RenderWindow m_window;
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP
