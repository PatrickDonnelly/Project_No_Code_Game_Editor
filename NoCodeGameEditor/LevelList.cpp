#include "LevelList.h"

LevelList::LevelList()
{

}

LevelList::LevelList(GameState* t_gameState)
{
	m_currentGameState = t_gameState;
	initButtons();
	for (auto& entry : fs::directory_iterator(m_pathGames))
	{
		//std::string temp = entry.path().().string();
		//temp.resize(temp.size() - 4);
		//m_gameNames.push_back(temp);
	}


	fs::path folder_path = m_pathGames;
	if (fs::exists(folder_path) && fs::is_directory(folder_path)) {
		// Read the contents of the folder
		for (const auto& entry : fs::directory_iterator(folder_path)) {
			// Check if the entry is a directory
			if (entry.is_directory()) {
				// Store the name of the directory in the vector
				m_gameNames.push_back(entry.path().filename().string());
			}
		}
	}
	else {
		// Error opening directory
		std::cerr << "Error opening directory." << std::endl;
		}

	for (const auto& folder_name : m_gameNames) {
		std::cout << folder_name << std::endl;
	}

	setUpGameButtons();
}

LevelList::~LevelList()
{
}

void LevelList::setUpGameButtons()
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


void LevelList::initButtons()
{


}

void LevelList::render(sf::RenderWindow* t_window)
{

	if (m_currentGameState->getState() == State::GAME_LIST || m_currentGameState->getState() == State::ROOM_BUILD)
	{
		for (auto& row : m_selectableGameButtons)
		{
			for (auto& col : row)
			{
				col->render(t_window);
			}
		}
	}
}

void LevelList::processEvents(sf::Event t_event, sf::RenderWindow& t_window)
{
	sf::Event newEvent = t_event;
	for (auto& row : m_selectableGameButtons) 
	{
		for (auto& col : row)
		{

				if (col->isButtonClicked(t_event, &t_window))
				{
					m_gameName = col->getButtonLabel()->getText()->getString();
					m_currentGameState->setState(State::LOAD_GAME);
				}
			
		}
	}
}

std::string LevelList::getGameToBeLoaded()
{
	return m_gameName;
}

