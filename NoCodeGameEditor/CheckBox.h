#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP
#include <SFML/Graphics.hpp>
#include "Label.h"

class CheckBox
{
public:

	CheckBox();
	CheckBox(sf::Font& t_font, std::string t_tag);
	~CheckBox();


	void initCheckBox();

	void render(sf::RenderWindow* t_window);
	bool isEnabled() { return m_enabled; };
	void setEnabled() { m_enabled = !m_enabled; }
	sf::Sprite getCheckBoxSprite() { return sf::Sprite(); }
	sf::RectangleShape getCheckBoxBounds() { return m_checkBox; }
	void setCheckBoxPosition(sf::Vector2f t_pos);

	sf::Vector2f getCheckBoxPosition() { return m_checkBoxSprite.getPosition(); }
	std::string getText() { return m_text.getString(); }
	void setCheckBoxSprite(sf::Sprite t_dialogueSprite) { m_checkBoxSprite = t_dialogueSprite; }
	void toggleColor();
	void update(sf::Time deltaTime, sf::RenderWindow& window);
private:

	Label* m_checkBoxLabel;
	std::string m_tag;
	bool m_enabled = false;
	sf::Sprite m_checkBoxSprite;
	sf::Texture m_checkBoxTexture;
	sf::RectangleShape m_checkBox;


	sf::Text m_text;
	sf::Font m_font;
	void initText();


};
#endif  // !CHECKBOX_HPP

