#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Animator
{
public:

	//default constructor
	Animator();
	// overloaded constructor
	// starting points of texture and width and height of each frame
	Animator(int t_x, int t_y, int t_width, int t_height, std::string t_fileName, int t_noOfFrames);

	Animator(int t_x, int t_y, int t_width, int t_height, std::string t_fileName, int t_noOfFrames, bool m_reverse);

	// applies texture and rectangles to set frame of animation
	void ApplyChangesToSprite(sf::Sprite& t_sprite);
	void Update(float deltaTime);
	int m_x; int m_y; int m_width; int m_height;


private:

	void Advance();

	//number of frames per animation
	static constexpr int noOfFrames = 3;
	int maxFrames = 3;
	// amount of time frame is on screen before cycling to the next frame in the animation
	// change this to slow or speed up animations
	static constexpr float timeBetweenFrames = 0.1f;
	sf::Texture m_texture;
	// stores rectangles of frames
	sf::IntRect frames[noOfFrames];
	// stores index of current frame in animation
	int indexOfFrame = 0;
	float elapsedTime = 0.0f;



};
#endif //!ANIMATOR_HPP