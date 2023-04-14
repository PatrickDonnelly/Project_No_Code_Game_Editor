#include "MainMenu.h"

MainMenu::MainMenu()
{

}

MainMenu::MainMenu(GameState* t_gameState)
{
	m_currentGameState = t_gameState;
	initButtons();
	for (auto& entry : fs::directory_iterator(m_pathGames))
	{
		std::string temp = entry.path().filename().string();
		temp.resize(temp.size() - 4);
		m_gameNames.push_back(temp);
	}
	setUpGameButtons();
}

MainMenu::~MainMenu()
{
}

void MainMenu::setUpGameButtons()
{
	int buttonsMade = 0;
	int maxButtons = m_pathGames.size();
	int noOfButtonsPerRow = 16;
	int noOfRows = 0;

	if (m_gameNames.size() % noOfButtonsPerRow != 0)
	{
		noOfRows = (m_gameNames.size() / noOfButtonsPerRow) + 1;
		m_rowsGames = noOfRows;
	}
	else
	{
		noOfRows = m_gameNames.size() / noOfButtonsPerRow;
		m_rowsGames = noOfRows;
	}

	for (int i = 0; i < noOfRows; i++)
	{
		std::vector<Button*> row;
		for (int j = 0; j < maxButtons; j++)
		{
			if (j >= m_gameNames.size())
			{
				break;
			}
			if (buttonsMade < maxButtons)
			{
				buttonsMade++;
				row.push_back(new Button(m_gameNames.at(j)));
			}

		}
		m_selectableGameButtons.push_back(row);
	}
	std::vector<std::vector<Button>>::iterator row;
	std::vector<Button>::iterator col;
	int rowIndex = 0;
	int colIndex = 0;

	for (auto& row : m_selectableGameButtons)
	{
		colIndex = 0;
		for (auto& col : row)
		{
			if (rowIndex == 0)
			{
				col->setEnabled(true);
			}
			col->setButtonPosition(sf::Vector2f(250.0f, 200.0f + (colIndex * 80)));
			col->getButtonLabel()->setTextPosition(col->getButtonPosition());
			col->resize(2.5f, 1.0f);
			colIndex++;
		}
		rowIndex++;
	}
}


void MainMenu::initButtons()
{
	for (int i = 0; i < 4; i++)
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
		else if(i ==3)
		{
		m_mainMenuButtons.push_back(new Button("Main Menu"));
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
				m_currentGameState->setState(State::ROOM_BUILD);
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
		else if (b->getButtonLabel()->getText()->getString() == "Main Menu")
		{
			if (b->isButtonClicked(t_event, &t_window))
			{
				std::cout << "Main Menu Clicked" << std::endl;
				m_currentGameState->setState(State::MENU);
			}
		}
	}

    
}
