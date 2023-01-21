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
	void setColor(sf::Color t_color);
	void setButtonTexture();
	void render(sf::RenderWindow* t_window);
	void resize(float m_xScale, float m_yScale);
	bool getSelected();
	void setSelected(bool t_tf);
	bool isEnabled();
	void setEnabled(bool t_onOff) { m_enabled = t_onOff; }

private:

	bool m_selected;
	bool m_enabled = false;
	sf::Sprite m_buttonSprite;
	sf::Texture m_buttonTexture;
	sf::Texture m_buttonHighlightTexture;
	

};
#endif  // !BUTTON_HPP