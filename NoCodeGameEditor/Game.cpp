#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 1920U, 1080U, 32U }, "No Code Game Editor" },
	m_exitGame{ false } //when true game will exit
{
	setUpFontAndText();
	m_grid = new Grid();
	for (int i = 0; i < noOfButtons; i++)
	{
		m_buttons[i] = Button();
		m_buttons[i].m_buttonIndex = i;
		m_buttons[i].setButtonPosition(sf::Vector2f{ 820.0f + (i * 280), 900.0f });

		m_labels[i] = new Label(m_ArialFont);
		m_labels[i]->setTextPosition(m_buttons[i].getButtonPosition());
	}
	m_labels[0]->setText("Clear Grid");
	m_labels[1]->setText("Generate Room");
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
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		for (int i = 0; i < noOfButtons; i++)
		{
			if (m_buttons[i].getButtonSprite().getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
			{
				m_buttons[i].highlighted();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					if (m_labels[i]->getTextString() == "Clear Grid")
					{
						m_grid->regenerateGrid();
					}
					else if (m_labels[i]->getTextString() == "Generate Room")
					{
						m_grid->checkRoomValidity();
					}
				}
			}
			else
			{
				m_buttons[i].setButtonTexture();
			}
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
	m_grid->update(t_deltaTime, m_window);
}

void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_grid->render(&m_window);
	for (int i = 0; i < noOfButtons; i++)
	{
		m_window.draw(m_buttons[i].getButtonSprite());
		m_labels[i]->render(&m_window);
	}
	m_window.display();
}
