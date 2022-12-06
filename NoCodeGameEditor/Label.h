#ifndef LABEL_HPP
#define LABEL_HPP
#include <SFML/Graphics.hpp>


class Label
{

public:

	Label();
	Label(sf::Font t_font);
	~Label();


	sf::Vector2f getTextPosition();
	sf::Text getText();
	std::string	getTextString();

	void setText(std::string t_text);
	void initText(sf::Font t_font);
	void setTextPosition(sf::Vector2f t_pos);
	void clear();
	void render(sf::RenderWindow* t_window);

private:

	sf::Text m_labelText;//the text proper
	sf::Font m_labelFont;

};
#endif // !LABEL_HPP

