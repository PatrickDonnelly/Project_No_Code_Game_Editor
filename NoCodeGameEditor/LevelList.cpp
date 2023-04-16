#include "LevelList.h"

LevelList::LevelList()
{

}

LevelList::LevelList(GameState* t_gameState)
{
	m_fontManager = FontManager();
	m_font = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");
	m_currentGameState = t_gameState;
	loadLevelList();
	setUpGameButtons();
	for (int i = 0; i < 2; ++i)
	{
		m_prevNextbuttons.push_back(new Button());
		m_prevNextbuttons.at(i)->resize(0.1f, 0.4f);
		m_prevNextbuttons.at(i)->setButtonPosition(sf::Vector2f(672.0f + (i * 608), 448.0f));
	}
	m_closeButton = new Button();
	m_closeButton->resize(0.1f, 0.3f);
	m_closeButton->setButtonPosition(sf::Vector2f(592, 16));
	m_bg.setSize(sf::Vector2f(766.0f, 800.0f));
	m_bg.setPosition(592.0f, 12.0f);
	m_bg.setOutlineThickness(1.0f);
	m_bg.setOutlineColor(sf::Color(sf::Color(140, 140, 140)));
	m_bg.setFillColor(G_COLOR_UI_GREY);
	initText();
}

LevelList::~LevelList()
{
}

void LevelList::initText()
{
	m_text.setFont(m_font);
	m_text.setCharacterSize(48.0f);
	m_text.setFillColor(sf::Color::White);
	m_text.setOutlineColor(sf::Color::Black);
	m_text.setOutlineThickness(2.0f);
	m_text.setString("Games");
	m_text.setPosition(m_bg.getPosition().x + (m_bg.getGlobalBounds().width /2) - (m_text.getGlobalBounds().width /2),
		m_bg.getPosition().y + m_text.getGlobalBounds().height / 2);
}

void LevelList::setVisibleRow(sf::Event t_event, sf::RenderWindow& t_window)
{
	sf::Vector2f pixelPos = sf::Vector2f(sf::Mouse::getPosition(t_window).x, sf::Mouse::getPosition(t_window).y);

	for (int i = 0; i < m_prevNextbuttons.size(); ++i)
	{
		if (m_prevNextbuttons.at(i)->getButtonSprite().getGlobalBounds().contains(pixelPos))
		{
			m_prevNextbuttons.at(i)->highlighted();
			if (t_event.type == sf::Event::MouseButtonReleased)
			{
				if (t_event.key.code == sf::Mouse::Left)
				{
					if (i == 0)
					{
						m_currentRowIndex -= 1;
					}
					else
					{
						m_currentRowIndex += 1;
					}
					if (m_currentRowIndex >= m_rowsGames)
					{
						m_currentRowIndex = 0;
					}
					else if (m_currentRowIndex < 0)
					{
						m_currentRowIndex = m_rowsGames - 1;
					}
					//m_currentRowText.setString(std::to_string(m_currentRowIndex + 1) + " / " + std::to_string(t_rows));
					std::vector<std::vector<Button>>::iterator row;
					std::vector<Button>::iterator col;
					int rowIndex = 0;
					int colIndex = 0;

					for (auto& row : m_selectableGameButtons)
					{
						colIndex = 0;
						for (auto& col : row)
						{
							if (m_currentRowIndex == rowIndex)
							{
								m_selectableGameButtons.at(m_currentRowIndex).at(colIndex)->setEnabled(true);
							}
							else
							{
								m_selectableGameButtons.at(rowIndex).at(colIndex)->setEnabled(false);
							}
							colIndex++;
						}
						rowIndex++;
					}
				}
			}
		}
		else
		{
			m_prevNextbuttons.at(i)->setButtonTexture();
		}
	}
	//std::cout << m_currentRowIndex << std::endl;
}

void LevelList::loadLevelList()
{
	fs::path folder_path = m_pathGames;
	if (fs::exists(folder_path) && fs::is_directory(folder_path)) {
		// Read the contents of the folder
		for (const auto& entry : fs::directory_iterator(folder_path)) {
			// Check if the entry is a directory
			if (entry.is_directory()) {
				// Store the name of the directory in the vector
				m_gameNames.push_back(entry.path().filename().string());
				m_noOfGamesFound++;
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

	//for (auto& name : m_gameNames)
	//{
	//	//std::cout << "Game Names : " << name << std::endl;
	//}
}

void LevelList::setUpGameButtons()
{
	int buttonsMade = 0;
	int maxButtons = m_noOfGamesFound;
	int noOfButtonsPerRow = 8;
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
		for (int j = 0; j < noOfButtonsPerRow; j++)
		{
			if (buttonsMade < maxButtons)
			{
				buttonsMade++;
				//std::cout << "Game Names : " << m_gameNames.at(j) << std::endl;
				row.push_back(new Button(m_gameNames.at(j)));
			}

		}
		m_selectableGameButtons.push_back(row);
	}
	std::vector<std::vector<Button>>::iterator row;
	std::vector<Button>::iterator col;
	int rowIndex = 0;
	int colIndex = 0;
	int index = 0;
	for (auto& row : m_selectableGameButtons)
	{
		colIndex = 0;
		for (auto& col : row)
		{
			if (rowIndex == 0)
			{
				col->setEnabled(true);
			}
			col->resize(2.5f, 1.0f);
			
			col->setButtonPosition(sf::Vector2f((704 + col->getButtonSprite().getGlobalBounds().width / 2), 160.0f + (colIndex * 80)));
			col->getButtonLabel()->setText(m_gameNames.at(index));
			col->getButtonLabel()->setTextPosition(col->getButtonPosition());
			index++;
			colIndex++;
		}
		rowIndex++;
	}
}

void LevelList::refreshLevelList()
{
	m_gameNames.clear();
	m_selectableGameButtons.clear();
	loadLevelList();
	setUpGameButtons();
}

void LevelList::render(sf::RenderWindow* t_window)
{

	if (m_currentGameState->getState() == State::GAME_LIST || m_currentGameState->getState() == State::LEVEL_LIST)
	{
		t_window->draw(m_bg);
		m_closeButton->render(t_window);
		m_text.setFont(m_font);
		t_window->draw(m_text);
		//for (auto& row : m_selectableGameButtons)
		//{
		//	for (auto& col : row)
		//	{
		//		col->render(t_window);
		//	}
		//}
		int rowIndex = 0;
		for (const auto& row : m_selectableGameButtons)
		{
			for (const auto& col : row)
			{
				if (rowIndex == m_currentRowIndex)
				{
					col->render(t_window);
				}
			}
			rowIndex++;
		}
		for (int i = 0; i < 2; ++i)
		{
			m_prevNextbuttons.at(i)->render(t_window);
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
	if (m_closeButton->isButtonClicked(t_event, &t_window))
	{
		m_currentGameState->setState(m_currentGameState->getPreviousState());
	}
	setVisibleRow(t_event, t_window);
}

std::string LevelList::getGameToBeLoaded()
{
	return m_gameName;
}

