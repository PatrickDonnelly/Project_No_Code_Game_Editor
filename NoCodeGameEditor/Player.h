#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player
{

public:
	Player();
	~Player();

	sf::Sprite m_playerSprite;
	sf::Texture m_playerTexture;
	sf::RectangleShape m_playerCentre;

	//Collision m_Collision;

	bool m_colliding;
	void setUpSprite();
	void setUpPlayerBounds();
	void movement();
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);

	int m_frameSize;
	float m_speed;
	int m_velocity;
	int m_playerBoundsWidth;
	int m_playerBoundsHeight;
	std::string m_spriteSheetName;
	sf::RectangleShape m_playerBounds;

	sf::Sprite* getSprite();
	sf::RectangleShape* getBounds();

	void init();
	void loadAssets();

private:

	sf::IntRect m_rectSourceSprite{0,0,16,16};
};

#endif // !PLAYER_HPP


