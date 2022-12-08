#include "Animator.h"
#include <iostream>

Animator::Animator()
{
	m_x = 0;
	m_y = 0;
	m_width = 16;
	m_height = 16;
}

Animator::Animator(int t_x, int t_y, int t_width, int t_height, std::string t_fileName, int t_noOfFrames)
{
	maxFrames = t_noOfFrames;
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\" + t_fileName))
	{
		std::cout << "Can't load main menu bgt" << std::endl;
	}

	for (int i = 0; i < maxFrames; i++)
	{
		frames[i] = { t_x , t_y + i * t_height, t_width, t_height };
	}
}

Animator::Animator(int t_x, int t_y, int t_width, int t_height, std::string t_fileName, int t_noOfFrames, bool m_reverse)
{
	// reverses an animation 
	maxFrames = t_noOfFrames;
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\" + t_fileName))
	{
		std::cout << "Can't load main menu bgt" << std::endl;
	}

	for (int i = maxFrames; i > 0; i--)
	{
		frames[i] = { t_x - i * t_width, t_y, t_width, t_height };
	}
}

void Animator::ApplyChangesToSprite(sf::Sprite& t_sprite)
{
	t_sprite.setTexture(m_texture);
	t_sprite.setTextureRect(frames[indexOfFrame]);
}

void Animator::Update(float deltaTime)
{
	elapsedTime += deltaTime;
	while (elapsedTime >= timeBetweenFrames)
	{
		elapsedTime -= timeBetweenFrames;
		Advance();
	}
}

void Animator::Advance()
{
	if (++indexOfFrame >= maxFrames)
	{
		indexOfFrame = 0;
	}
}