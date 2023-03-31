#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "Animator.h"
#include "AnimationState.h"

class Player
{

public:
	Player();
	~Player();

	sf::RectangleShape m_playerInteractionRadius;
	bool isInteracting(sf::Event newEvent);
	bool m_canInteract = false;
	void setInteract(bool tf) { m_canInteract = tf; }
	bool getInteract() { return m_canInteract; }

	float m_defaultSpeed;
	bool m_weaponEnabled = false;
	sf::Sprite m_playerSprite;
	sf::Texture m_playerTexture;
	sf::RectangleShape m_playerCentre;

	sf::Sprite m_weaponSprite;
	sf::Texture m_weaponTexture;
	int m_weaponBoundsWidth;
	int m_weaponBoundsHeight;
	sf::RectangleShape m_weaponBounds;

	bool m_colliding;
	void setUpSprite();
	void setUpPlayerBounds();
	void setUpAnimation();
	bool movement(sf::Time deltaTime);
	void update(sf::Time deltaTime, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	bool moving = false;
	int m_frameSize;
	float m_speed;
	int m_velocity;
	int m_playerBoundsWidth;
	int m_playerBoundsHeight;
	std::string m_spriteSheetName;
	sf::RectangleShape m_playerBounds;

	sf::Sprite* getSprite();
	sf::RectangleShape* getBounds();
	sf::RectangleShape* getInteractionBounds();

	sf::RectangleShape* getWeaponBounds();

	AnimationState getAnimationState();
	void setAnimationState(AnimationState& t_current, AnimationState t_new);
	void animate(sf::Time deltaTime);

	void init();
	void loadAssets();

private:

	sf::IntRect m_rectSourceSprite{0,0,16,16};
	Animator animations[int(AnimationState::Count)];
	AnimationState currentAnimationState = AnimationState::IdleLeft;
};

#endif // !PLAYER_HPP


