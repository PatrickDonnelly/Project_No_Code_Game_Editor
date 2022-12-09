#pragma once
#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <SFML/Graphics.hpp>
#include "Player.h"

class Weapon
{
public:
	Weapon(Player* t_player);
	Weapon();
	~Weapon();

	void init();
	void loadAssets();
	void setUpSprite();
	void setUpWeaponBounds(float t_width, float t_height, float t_offsetX, float t_offsetY);
	void setUpBoundsColour();
	void processEvents(sf::Event t_event);
	void processKeys(sf::Event t_event);
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);

	sf::Sprite* getSprite();
	sf::RectangleShape* getWeaponBounds();

	Player* m_player;
	bool m_weaponEnabled = false;
	bool m_weaponUsed = false;
	bool m_weaponCanUse = true;
	float weaponCoolDown = 0.0f;
	sf::Clock m_timer;
	sf::Sprite m_weaponSprite;
	sf::Texture m_weaponTexture;
	float m_weaponBoundsWidth;
	float m_weaponBoundsHeight;
	sf::RectangleShape m_weaponBounds;
	int m_frameSize;
	bool m_colliding;





private:

};

#endif // !WEAPON_HPP


