#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>


class Button
{
public:

	Button();
	~Button();

	sf::Sprite getButtonSprite();
	sf::Vector2f getButtonPosition();
	int	m_buttonIndex;

	void initButton();
	void setButtonPosition(sf::Vector2f t_position);
	void setButtonSprite(sf::Sprite t_buttonSprite);
	void highlighted();
	void setButtonTexture();

private:

	sf::Sprite m_buttonSprite;
	sf::Texture m_buttonTexture;
	sf::Texture m_buttonHighlightTexture;
	

};
#endif  // !BUTTON_HPP