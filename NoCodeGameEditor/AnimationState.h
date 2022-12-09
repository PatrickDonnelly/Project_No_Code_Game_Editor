#pragma once
#ifndef ANIMATIONSTATE_HPP
#define ANIMATIONSTATE_HPP

#include <SFML/Graphics.hpp>

enum class AnimationState
{
	None,
	IdleLeft,
	IdleRight,
	IdleUp,
	IdleDown,
	WalkingLeft,
	WalkingRight,
	WalkingUp,
	WalkingDown,
	Count
};
#endif // !ANIMATIONSTATE_HPP