#include "Globals.h"

sf::View m_gameView = sf::View(sf::FloatRect(0, 0, 1920, 1080));
sf::View m_uiView = sf::View(sf::FloatRect(0, 0, 1920, 1080));
sf::FloatRect m_squareBounds(256.0f, 0.0f, 1408.0f, 824.0f);
float m_zoomRate = 1.1f;