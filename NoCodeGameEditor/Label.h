#ifndef LABEL_HPP
#define LABEL_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include "FontManager.h"


class Label
{

public:

	Label();
	Label(sf::Font& t_font);
	Label(sf::Font& t_font, bool t_isOn);
	Label(std::string t_labelText);
	~Label();


	sf::Vector2f getTextPosition();
	sf::Text getText();
	std::string	getTextString();

	void setText(std::string t_text);
	void initText();
	void setTextPosition(sf::Vector2f t_pos);
	void clear();
	void render(sf::RenderWindow* t_window);
	void setLabelSprite(std::string t_spriteName, std::string t_path);
	void setTexturePosition(sf::Vector2f t_pos);

	void setTextColor(sf::Color t_color);
	void setTextOutlineColor(sf::Color t_color);
	void setTextOutlineThickness(float t_thickness);
	void setTextSize(float t_size);

	void updateLabelBG();

private:
	FontManager m_fontManager;
	sf::Text m_labelText;//the text proper
	sf::Font m_labelFont;
	sf::Texture m_labelTexture;
	sf::Sprite m_labelSprite;
	bool m_image;

	sf::RectangleShape m_labelBG;
	bool m_hasBG = false;
	void setLabelBG(bool t_isOn) { m_hasBG = t_isOn; }
	void setUpBG();



};
#endif // !LABEL_HPP

