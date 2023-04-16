#include "MainMenu.h"

MainMenu::MainMenu()
{

}

MainMenu::MainMenu(GameState* t_gameState)
{
	m_currentGameState = t_gameState;
	initButtons();
}

MainMenu::~MainMenu()
{
}


void MainMenu::initButtons()
{
	for (int i = 0; i < 3; i++)
	{
		if (i == 1)
		{
			m_mainMenuButtons.push_back(new Button("Exit"));
			m_mainMenuButtons.at(i)->setButtonPosition(sf::Vector2f{ 960.0f, 800.0f });
		}
		else if (i == 2)
		{
			m_mainMenuButtons.push_back(new Button("Create Game"));
			m_mainMenuButtons.at(i)->setButtonPosition(sf::Vector2f{960.0f, 500.0f });
		}
		else if(i == 0)
		{
			m_mainMenuButtons.push_back(new Button("Play Game"));
			m_mainMenuButtons.at(i)->setButtonPosition(sf::Vector2f{ 960.0f, 200.0f });
		}
		m_mainMenuButtons.at(i)->getButtonLabel()->setTextPosition(m_mainMenuButtons.at(i)->getButtonPosition());
	}

}

void MainMenu::render(sf::RenderWindow* t_window)
{
	if (m_currentGameState->getState() == State::MENU)
	{
		m_mainMenuButtons.at(0)->render(t_window);
		m_mainMenuButtons.at(1)->render(t_window);
		m_mainMenuButtons.at(2)->render(t_window);

	}
	else if (m_currentGameState->getState() == State::GAME_LIST || m_currentGameState->getState() == State::ROOM_BUILD)
	{
		for (auto& row : m_selectableGameButtons) {
			for (auto& col : row) 
			{
				col->render(t_window);
			}
		}
		m_mainMenuButtons.at(m_mainMenuButtons.size()-1)->render(t_window);
	}
}

void MainMenu::processEvents(sf::Event t_event, sf::RenderWindow& t_window)
{
    sf::Event newEvent = t_event;
	for (auto b : m_mainMenuButtons)
	{
		if (b->getButtonLabel()->getText()->getString() == "Exit")
		{
			if (b->isButtonClicked(t_event, &t_window))
			{
				std::cout << "Exit Clicked" << std::endl;
				t_window.close();
			}
		}
		else if (b->getButtonLabel()->getText()->getString() == "Create Game")
		{
			if (b->isButtonClicked(t_event, &t_window))
			{
				std::cout << "Create Game Clicked" << std::endl;
				m_currentGameState->setState(State::ROOM_PLACE_OBJECTS);
			}
		}
		else if (b->getButtonLabel()->getText()->getString() == "Play Game")
		{
			if (b->isButtonClicked(t_event, &t_window))
			{
				std::cout << "Play Game Clicked" << std::endl;
				m_currentGameState->setState(State::GAME_LIST);
			}
		}
	}

    
}
