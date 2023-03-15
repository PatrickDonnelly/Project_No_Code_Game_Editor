#ifndef POPUP_HPP
#define POPUP_HPP
#include <SFML/Graphics.hpp>

class PopUp
{
public:

	PopUp();
	PopUp(sf::Font* t_font);
	~PopUp();

	sf::Sprite getPopUpBoxSprite();
	sf::Vector2f getPopUpBoxPosition();

	void initPopUpBox();

	void setPopUpBoxSprite(sf::Sprite t_dialogueSprite);
	void render(sf::RenderWindow* t_window);
	bool isEnabled();
	//void setEnabled(bool t_onOff) { m_enabled = t_onOff; }
	void setPopUpBoxText(std::string t_text);
	void setPopUpEnabled() { m_enabled = !m_enabled; }
	sf::Vector2f getPopUpBoxBounds();
	

private:

	bool m_enabled = false;
	sf::Sprite m_popUpBoxSprite;
	sf::Texture m_popUpBoxTexture;
	sf::RectangleShape m_popUpBox;

	sf::Text m_text;
	sf::Font* m_font;
	void initText();
};
#endif  // !POPUP_HPP
