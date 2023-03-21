#ifndef LABEL_HPP
#define LABEL_HPP
#include <SFML/Graphics.hpp>
#include <iostream>


class Label
{

public:

	Label();
	Label(sf::Font& t_font);
	~Label();


	sf::Vector2f getTextPosition();
	sf::Text getText();
	std::string	getTextString();

	void setText(std::string t_text);
	void initText(sf::Font t_font);
	void setTextPosition(sf::Vector2f t_pos);
	void clear();
	void render(sf::RenderWindow* t_window);
	void setLabelSprite(std::string t_spriteName, std::string t_path);
	void setTexturePosition(sf::Vector2f t_pos);

	void setTextColor(sf::Color t_color);
	void setTextOutlineColor(sf::Color t_color);
	void setTextOutlineThickness(float t_thickness);
	void setTextSize(float t_size);

private:

	sf::Text m_labelText;//the text proper
	sf::Font m_labelFont;
	sf::Texture m_labelTexture;
	sf::Sprite m_labelSprite;
	bool m_image;

};
#endif // !LABEL_HPP

