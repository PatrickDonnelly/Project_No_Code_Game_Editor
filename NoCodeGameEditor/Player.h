#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "Animator.h"

enum class AnimationState
{
	None,
	Idle,
	WalkingLeft,
	WalkingRight,
	WalkingUp,
	WalkingDown,
	Count
};

class Player
{

public:
	Player();
	~Player();

	sf::Sprite m_playerSprite;
	sf::Texture m_playerTexture;
	sf::RectangleShape m_playerCentre;

	bool m_colliding;
	void setUpSprite();
	void setUpPlayerBounds();
	void setUpAnimation();
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

	AnimationState getAnimationState();
	void setAnimationState(AnimationState& t_current, AnimationState t_new);
	void animate(sf::Time deltaTime);

	void init();
	void loadAssets();

private:

	sf::IntRect m_rectSourceSprite{0,0,16,16};
	Animator animations[int(AnimationState::Count)];
	AnimationState currentAnimationState = AnimationState::Idle;
};

#endif // !PLAYER_HPP


