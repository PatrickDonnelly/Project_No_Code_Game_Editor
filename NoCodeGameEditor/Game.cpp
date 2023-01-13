#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 1920U, 1080U, 32U }, "No Code Game Editor" },
	m_exitGame{ false } //when true game will exit
{
	setUpFontAndText();
	m_grid = new Grid();
	m_player = new Player();
	m_spear = new Weapon(m_player);
	m_uiBuildMode = UiBuildMode(m_ArialFont, m_grid);
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::setUpFontAndText()
{
	if (!m_ArialFont.loadFromFile("ASSETS\\FONTS\\Arial.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_text.setFont(m_ArialFont);
	m_text.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_text.setPosition(400.0f, 400.0f);
	m_text.setCharacterSize(16U);
	m_text.setOutlineColor(sf::Color::White);
	m_text.setFillColor(sf::Color::Black);
	m_text.setOutlineThickness(1.0f);
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		m_spear->processEvents(newEvent);
		m_uiBuildMode.processEvents(newEvent, m_window);

		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	if (m_grid->firstFloorSet && m_grid->m_playerSet == false)
	{
		m_grid->m_playerSet = true;
		m_player->getBounds()->setPosition(m_grid->m_firstTilePosition.x+16, m_grid->m_firstTilePosition.y + 16);
		std::cout << m_player->getSprite()->getPosition().x << std::endl;
	}
	m_grid->update(t_deltaTime, m_window);
	m_player->update(t_deltaTime, m_window);
	m_spear->update(t_deltaTime, m_window);

	if (m_grid->m_vectColliders.size() > 0)
	{
		for (int i = 0; i < m_grid->m_vectColliders.size(); i++)
		{
			m_checkCollision.checkCollision(m_player->getBounds(), m_grid->m_vectColliders.at(i)->getBounds(), 0.0f);
		}
		for (int i = 0; i < m_grid->m_placedObjects.size(); i++)
		{
			for (int j = 0; j < m_grid->m_vectColliders.size(); j++)
			{
				m_checkCollision.checkCollision(m_grid->m_placedObjects.at(i)->getBounds(), m_grid->m_vectColliders.at(j)->getBounds(), 0.0f);
			}
			if (m_grid->m_placedObjects.at(i)->isCollidable())
			{
				m_player->m_speed = m_player->m_defaultSpeed;
				if (m_grid->m_placedObjects.at(i)->m_tag != "Hole")
				{
					m_checkCollision.checkCollision(m_player->getBounds(), m_grid->m_placedObjects.at(i)->getBounds(), 0.4f);
				}
				else
				{
					m_checkCollision.checkCollision(m_player->getBounds(), m_grid->m_placedObjects.at(i)->getBounds(), 0.0f);
				}
			}
		}
		std::vector<Obstacle*>::iterator it;
		if (m_spear->m_weaponUsed)
		{
			std::cout << m_spear->getWeaponBounds()->getSize().x << " : " << m_spear->getWeaponBounds()->getSize().y << std::endl;

			for (it = m_grid->m_placedObjects.begin(); it != m_grid->m_placedObjects.end();)
			{
				Obstacle* l_obstacle = *it;
				if (m_checkCollision.checkCollision(m_spear->getWeaponBounds(), l_obstacle->getBounds(), 0.4f))
				{
					it = m_grid->m_placedObjects.erase(it);

					m_grid->noOfObstacles--;
				}
				else
				{
					it++;
				}
			}
		}

		for (int i = 0; i < m_grid->m_placedObjects.size(); i++)
		{
			for (int j = 0; j < m_grid->m_placedObjects.size(); j++)
			{

				if (j < m_grid->m_placedObjects.size() - 1)
				{
					if (m_grid->m_placedObjects.at(i)->isCollidable() && m_grid->m_placedObjects.at(j+1)->isCollidable())
					{
						m_checkCollision.checkCollision(m_grid->m_placedObjects.at(i)->getBounds(), m_grid->m_placedObjects.at(j + 1)->getBounds(), 0.5f);
					}
				}
			}
		}
	}

}

void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_grid->render(&m_window);
	m_uiBuildMode.render(&m_window);
	m_spear->render(m_window);
	m_player->render(m_window);
	m_window.display();
}
