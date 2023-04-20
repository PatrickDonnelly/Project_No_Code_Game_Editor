#include "Game.h"


Game::Game() :
	m_window{ sf::VideoMode{ 1920U, 1080U, 32U }, "No Code Game Editor" },
	m_exitGame{ false } //when true game will exit
{
	m_window.setView(m_gameView);
	m_textureManager = new TextureManager();
	m_gameState = new GameState(State::ROOM_PLACE_OBJECTS);
	m_mainMenu = MainMenu(m_gameState);
	m_levelList = LevelList(m_gameState);
	m_saveGameScreen = SaveGame(m_gameState);
	setUpFontAndText();
	m_grid = new Grid(m_gameState, m_textureManager);
	m_roomCreation = new RoomCreation(m_gameState, m_grid);
	m_objectPlacement = new ObjectPlacement(m_gameState, m_grid, m_textureManager);
	m_player = new Player();
	m_spear = new Weapon(m_player);
	m_uiBuildMode = UiBuildMode(m_ArialFont, m_grid, m_gameState, m_roomCreation, m_objectPlacement);
	m_dialogueBox = new DialogueBox(m_ArialFont);
	m_textEditor = new TextEditor(m_ArialFont, m_gameState);

	//m_inspector = new Inspector(m_objectPlacement);

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
	m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");


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
		if (m_gameState->getState() == State::MENU)
		{
			m_mainMenu.processEvents(newEvent, m_window);
		}
		if (m_gameState->getState() == State::LEVEL_LIST)
		{
			m_levelList.processEvents(newEvent, m_window);
		}
		if (m_gameState->getState() == State::GAME_LIST)
		{
			m_levelList.processEvents(newEvent, m_window);
		}
		if (m_gameState->getState() == State::SAVING_SCREEN)
		{
			m_saveGameScreen.processEvents(newEvent, m_window);
		}
		if (m_gameState->m_currentGameState == State::ROOM_PLACE_OBJECTS)
		{
			m_uiBuildMode.processEvents(newEvent, m_window);
			m_objectPlacement->processEvents(newEvent, m_window);
			if (m_objectPlacement->m_currentlySelected != nullptr)
			{
				if (m_objectPlacement->m_currentlySelected->m_hasAttributes)
				{
					m_objectPlacement->m_currentlySelected->getInspector()->processEvents(newEvent, m_window, m_gameState, m_textEditor->GetTitle()->GetText(), (*m_objectPlacement->m_currentlySelected->getDialoguePaths()));
					m_textEditor->processTextEditorButtons(newEvent, m_window, m_objectPlacement->m_currentlySelected->getInspector()->m_currentLabel);
				}
			}
		}
		if (m_gameState->m_currentGameState == State::CREATE_DIALOGUE)
		{
			m_uiBuildMode.processEvents(newEvent, m_window);

				if (m_objectPlacement->m_currentlySelected != nullptr)
				{
					m_objectPlacement->m_currentlySelected->getInspector()->processEvents(newEvent, m_window, m_gameState, m_textEditor->GetTitle()->GetText(), (*m_objectPlacement->m_currentlySelected->getDialoguePaths()));
					m_textEditor->processTextEditorButtons(newEvent, m_window, m_objectPlacement->m_currentlySelected->getInspector()->m_currentLabel);
				}
			
		}
		if (m_gameState->m_currentGameState == State::ROOM_TEST)
		{
			m_uiBuildMode.processEvents(newEvent, m_window);

		}
		if (m_gameState->getState() != State::PAUSE_GAME)
		{
			if (m_player->getInteract())
			{
				if (m_player->isInteracting(newEvent))
				{
					std::cout << "urggggh" << std::endl;
					//m_currentObject->getBounds()->setPosition(10.0f,10.0f);
					m_currentObject->getDialogueBox()->setEnabled();
					m_currentObject->loadDialogue("Interacted");
					m_gameState->setState(State::PAUSE_GAME);
					// play current enemies dialogue here.
				}
			}
			m_spear->processEvents(newEvent);
			//m_uiBuildMode.processEvents(newEvent, m_window);
			//if (m_gameState->getState()==State::ROOM_PLACE_OBJECTS)
			//{
				
		//	}

			//m_inspector->processEvents(newEvent, m_window);

			if (sf::Event::Closed == newEvent.type) // window message
			{
				m_exitGame = true;
			}
			if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
			{
				processKeys(newEvent);
			}
			if (m_gameState->m_currentGameState == State::CREATE_DIALOGUE)
			{
				if (sf::Event::TextEntered == newEvent.type)
				{
					//m_dialogueBox->typing(newEvent);
					//m_textEditor->typing(newEvent);
					if (m_textEditor->GetMainBody()->GetSelected())
					{
						m_textEditor->GetMainBody()->typing(newEvent);
					}
					else if (m_textEditor->GetTitle()->GetSelected())
					{
						m_textEditor->GetTitle()->typing(newEvent);
					}
				}
			}
		}
		else
		{
			if (m_player->isInteracting(newEvent))
			{
				m_gameState->setState(m_gameState->getPreviousState());
				m_currentObject->getDialogueBox()->setEnabled();
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
	if (m_gameState->getState() == State::SAVING_SCREEN)
	{
		m_saveGameScreen.setEnabled(true);
	}
	if (m_gameState->getState() == State::SAVING)
	{

		std::cout << "Saving Game" << std::endl;

		YAML::Emitter out;
		out << YAML::BeginDoc;
		out << YAML::BeginMap;
		out << YAML::Key << "Grid";
		out << YAML::Value << YAML::BeginSeq;
		out << YAML::BeginMap;
		out << YAML::Key << "Size" << YAML::Value << m_grid->m_vectGrid.size();
		out << YAML::EndMap;
		out << YAML::EndSeq;


		out << YAML::Key << "Enemy";
		out << YAML::BeginSeq;
		if (m_objectPlacement->m_enemies.size() != 0)
		{
			for (int i = 0; i < m_objectPlacement->m_enemies.size(); i++)
			{
				out << YAML::BeginMap;
				out << YAML::Key << "Tag" << YAML::Value << m_objectPlacement->m_enemies.at(i)->getTag();
				out << YAML::Key << "ID" << YAML::Value << m_objectPlacement->m_enemies.at(i)->getUUID();
				out << YAML::Key << "Xpos" << YAML::Value << m_objectPlacement->m_enemies.at(i)->getBounds()->getPosition().x;
				out << YAML::Key << "Ypos" << YAML::Value << m_objectPlacement->m_enemies.at(i)->getBounds()->getPosition().y;
				out << YAML::Key << "Texture" << YAML::Value << m_objectPlacement->m_enemies.at(i)->getPath();
				out << YAML::Key << "Dialogue" << YAML::Value << m_objectPlacement->m_enemies.at(i)->getHasDialogue();
				out << YAML::Key << "Row" << YAML::Value << m_objectPlacement->m_enemies.at(i)->getRow();
				out << YAML::Key << "Column" << YAML::Value << m_objectPlacement->m_enemies.at(i)->getColumn();
				out << YAML::EndMap;
			}
		}
		out << YAML::EndSeq;
		out << YAML::Key << "Decoration";
		out << YAML::BeginSeq;
		if (m_objectPlacement->m_decorations.size() != 0)
		{
			for (int i = 0; i < m_objectPlacement->m_decorations.size(); i++)
			{
				out << YAML::BeginMap;
				out << YAML::Key << "Tag" << YAML::Value << m_objectPlacement->m_decorations.at(i)->getTag();
				out << YAML::Key << "ID" << YAML::Value << m_objectPlacement->m_decorations.at(i)->getUUID();
				out << YAML::Key << "Xpos" << YAML::Value << m_objectPlacement->m_decorations.at(i)->getBounds()->getPosition().x;
				out << YAML::Key << "Ypos" << YAML::Value << m_objectPlacement->m_decorations.at(i)->getBounds()->getPosition().y;
				out << YAML::Key << "Texture" << YAML::Value << m_objectPlacement->m_decorations.at(i)->getPath();
				out << YAML::Key << "Dialogue" << YAML::Value << m_objectPlacement->m_decorations.at(i)->getHasDialogue();
				out << YAML::Key << "Row" << YAML::Value << m_objectPlacement->m_decorations.at(i)->getRow();
				out << YAML::Key << "Column" << YAML::Value << m_objectPlacement->m_decorations.at(i)->getColumn();
				out << YAML::EndMap;
			}
		}
		out << YAML::EndSeq;
		out << YAML::Key << "Item";
		out << YAML::BeginSeq;
		if (m_objectPlacement->m_items.size() != 0)
		{
			for (int i = 0; i < m_objectPlacement->m_items.size(); i++)
			{
				out << YAML::BeginMap;
				out << YAML::Key << "Tag" << YAML::Value << m_objectPlacement->m_items.at(i)->getTag();
				out << YAML::Key << "ID" << YAML::Value << m_objectPlacement->m_items.at(i)->getUUID();
				out << YAML::Key << "Xpos" << YAML::Value << m_objectPlacement->m_items.at(i)->getBounds()->getPosition().x;
				out << YAML::Key << "Ypos" << YAML::Value << m_objectPlacement->m_items.at(i)->getBounds()->getPosition().y;
				out << YAML::Key << "Texture" << YAML::Value << m_objectPlacement->m_items.at(i)->getPath();
				out << YAML::Key << "Dialogue" << YAML::Value << m_objectPlacement->m_items.at(i)->getHasDialogue();
				out << YAML::Key << "Row" << YAML::Value << m_objectPlacement->m_items.at(i)->getRow();
				out << YAML::Key << "Column" << YAML::Value << m_objectPlacement->m_items.at(i)->getColumn();
				out << YAML::EndMap;
			}
		}
		out << YAML::EndSeq;
		out << YAML::Key << "Wall";
		out << YAML::BeginSeq;
		if (m_objectPlacement->m_walls.size() != 0)
		{
			for (int i = 0; i < m_objectPlacement->m_walls.size(); i++)
			{
				out << YAML::BeginMap;
				out << YAML::Key << "Tag" << YAML::Value << m_objectPlacement->m_walls.at(i)->getTag();
				out << YAML::Key << "ID" << YAML::Value << m_objectPlacement->m_walls.at(i)->getUUID();
				out << YAML::Key << "Xpos" << YAML::Value << m_objectPlacement->m_walls.at(i)->getBounds()->getPosition().x;
				out << YAML::Key << "Ypos" << YAML::Value << m_objectPlacement->m_walls.at(i)->getBounds()->getPosition().y;
				out << YAML::Key << "Texture" << YAML::Value << m_objectPlacement->m_walls.at(i)->getPath();
				out << YAML::Key << "Dialogue" << YAML::Value << m_objectPlacement->m_walls.at(i)->getHasDialogue();
				out << YAML::Key << "Row" << YAML::Value << m_objectPlacement->m_walls.at(i)->getRow();
				out << YAML::Key << "Column" << YAML::Value << m_objectPlacement->m_walls.at(i)->getColumn();
				out << YAML::EndMap;
			}
		}
		out << YAML::EndSeq;
		out << YAML::Key << "Tile";
		out << YAML::BeginSeq;
		for (int i = 0; i < m_grid->m_vectGrid.size(); i++)
		{
			for (int j = 0; j < m_grid->m_vectGrid.size(); ++j)
			{

					out << YAML::BeginMap;
					out << YAML::Key << "Cell Type" << YAML::Value << m_grid->m_vectGrid.at(i).at(j).cellType;
					out << YAML::Key << "Occupied" << YAML::Value << m_grid->m_vectGrid.at(i).at(j).m_hasObject;
					out << YAML::Key << "Xpos" << YAML::Value << m_grid->m_vectGrid.at(i).at(j).getPos().x;
					out << YAML::Key << "Ypos" << YAML::Value << m_grid->m_vectGrid.at(i).at(j).getPos().y;
					out << YAML::Key << "Texture" << YAML::Value << m_grid->m_vectGrid.at(i).at(j).getPath();
					out << YAML::EndMap;
				
			}
		}
		out << YAML::EndSeq;
		out << YAML::Key << "GameName";
		out << YAML::BeginSeq;
	

				out << YAML::BeginMap;
				out << YAML::Key << "Name" << YAML::Value << m_saveGameScreen.getTitle(true);
				out << YAML::Key << "Italics" << YAML::Value << m_saveGameScreen.getItalics(true);
				out << YAML::Key << "Underlined" << YAML::Value << m_saveGameScreen.getUnderlined(true);
				out << YAML::Key << "Bold" << YAML::Value << m_saveGameScreen.getBold(true);
				out << YAML::Key << "Color Red Value" << YAML::Value << m_saveGameScreen.getColorRedValue(true);
				out << YAML::Key << "Color Green Value" << YAML::Value << m_saveGameScreen.getColorGreenValue(true);
				out << YAML::Key << "Color Blue Value" << YAML::Value << m_saveGameScreen.getColorBlueValue(true);


				out << YAML::EndMap;
				out << YAML::EndSeq;

				out << YAML::Key << "GameSubTitle";
				out << YAML::BeginSeq;
				out << YAML::BeginMap;
				out << YAML::Key << "Name" << YAML::Value << m_saveGameScreen.getTitle(false);
				out << YAML::Key << "Italics" << YAML::Value << m_saveGameScreen.getItalics(false);
				out << YAML::Key << "Underlined" << YAML::Value << m_saveGameScreen.getUnderlined(false);
				out << YAML::Key << "Bold" << YAML::Value << m_saveGameScreen.getBold(false);
				out << YAML::Key << "Color Red Value" << YAML::Value << m_saveGameScreen.getColorRedValue(false);
				out << YAML::Key << "Color Green Value" << YAML::Value << m_saveGameScreen.getColorGreenValue(false);
				out << YAML::Key << "Color Blue Value" << YAML::Value << m_saveGameScreen.getColorBlueValue(false);

				out << YAML::EndMap;
		
		out << YAML::EndSeq;


		out << YAML::EndMap;
		out << YAML::EndDoc;
		// player save
		std::string _filePath = m_saveGameScreen.getFolderPath();
		std::ofstream fout(_filePath + "\\" + m_saveGameScreen.getTitle(true) + ".yaml");
		fout << out.c_str();
		fout.close();

		m_levelList.refreshLevelList();
		m_gameState->setState(m_gameState->getPreviousState());
	}
	if (m_gameState->getState() == State::MENU)
	{
		// load files
		// switch to play game
		//m_gameState->setState(State::PLAY_GAME);
	}
	if (m_gameState->getState() == State::LOAD_GAME)
	{
		std::string _fileName = m_levelList.getGameToBeLoaded();
		std::cout << _fileName << std::endl;
		YAML::Node output = YAML::LoadFile("Games\\" + _fileName + "\\" + _fileName + ".yaml");
		int size = output["Grid"][0]["Size"].as<int>();
		m_objectPlacement->clearObjects();
		m_grid->clear();
		m_grid->setGridSize(size);
		m_grid->regenerateGrid();
		m_objectPlacement->clearObjects();
		std::vector<sf::Vector2f> positions;
		std::vector<std::string> textures;
		std::vector<std::string> cellType;
		std::vector<bool> hasObject;
		std::vector<Object> object;

		for (const auto& node : output["Tile"]) {
			textures.push_back(node["Texture"].as<std::string>());
			cellType.push_back(node["Cell Type"].as<std::string>());
			hasObject.push_back(node["Occupied"].as<bool>());
			positions.push_back(
				sf::Vector2f(node["Xpos"].as<float>(), node["Ypos"].as<float>()));
			std::cout << node["Xpos"].as<float>() << std::endl;
		}
		int k = 0;
		for (int i = 0; i < m_grid->m_vectGridSize;++i)
		{
			for (int j = 0; j < m_grid->m_vectGridSize; ++j)
			{
				if (cellType.at(k) != "Empty")
				{
					m_grid->m_vectGrid.at(i).at(j).setFloorSprite(textures.at(k));
					m_grid->m_vectGrid.at(i).at(j).cellType = cellType.at(k);
					m_grid->m_vectGrid.at(i).at(j).m_hasObject = hasObject.at(k);
				}
				k++;
			}
		}
		textures.clear();
		positions.clear();
		for (const auto& node : output["Enemy"]) {
			m_objectPlacement->m_enemies.push_back(new Enemy( node["Texture"].as<std::string>()));
			m_objectPlacement->m_enemies.at(m_objectPlacement->m_enemies.size() - 1)->setRowColumn(
				node["Row"].as<int>(), node["Column"].as<int>());
			m_objectPlacement->m_enemies.at(m_objectPlacement->m_enemies.size() - 1)->getBounds()->setPosition(
				node["Xpos"].as<float>(), node["Ypos"].as<float>()
			);
			m_objectPlacement->m_enemies.at(m_objectPlacement->m_enemies.size() - 1)->getSprite()->setPosition(
				m_objectPlacement->m_enemies.at(m_objectPlacement->m_enemies.size() - 1)->getBounds()->getPosition());
			std::cout << node["Xpos"].as<float>() << std::endl;
		}

		for (const auto& node : output["Item"]) {
			m_objectPlacement->m_items.push_back(new Item(node["Texture"].as<std::string>()));
			m_objectPlacement->m_items.at(m_objectPlacement->m_items.size() - 1)->setRowColumn(
				node["Row"].as<int>(), node["Column"].as<int>());
			m_objectPlacement->m_items.at(m_objectPlacement->m_items.size() - 1)->getBounds()->setPosition(
				node["Xpos"].as<float>(), node["Ypos"].as<float>()
			);
			m_objectPlacement->m_items.at(m_objectPlacement->m_items.size() - 1)->getSprite()->setPosition(
				m_objectPlacement->m_items.at(m_objectPlacement->m_items.size() - 1)->getBounds()->getPosition());
			std::cout << node["Xpos"].as<float>() << std::endl;
		}

		for (const auto& node : output["Decoration"]) {
			m_objectPlacement->m_decorations.push_back(new Decoration(node["Texture"].as<std::string>()));
			m_objectPlacement->m_decorations.at(m_objectPlacement->m_decorations.size() - 1)->setRowColumn(
				node["Row"].as<int>(), node["Column"].as<int>());
			m_objectPlacement->m_decorations.at(m_objectPlacement->m_decorations.size() - 1)->getBounds()->setPosition(
				node["Xpos"].as<float>(), node["Ypos"].as<float>()
			);
			m_objectPlacement->m_decorations.at(m_objectPlacement->m_decorations.size() - 1)->getSprite()->setPosition(
				m_objectPlacement->m_decorations.at(m_objectPlacement->m_decorations.size() - 1)->getBounds()->getPosition());
			std::cout << node["Xpos"].as<float>() << std::endl;
		}

		for (const auto& node : output["Wall"]) {
			m_objectPlacement->m_walls.push_back(new Wall(node["Texture"].as<std::string>()));
			m_objectPlacement->m_walls.at(m_objectPlacement->m_walls.size() - 1)->setRowColumn(
				node["Row"].as<int>(), node["Column"].as<int>());
			m_objectPlacement->m_walls.at(m_objectPlacement->m_walls.size() - 1)->getBounds()->setPosition(
				node["Xpos"].as<float>(), node["Ypos"].as<float>()
			);

			m_objectPlacement->m_walls.at(m_objectPlacement->m_walls.size() - 1)->getSprite()->setPosition(
				m_objectPlacement->m_walls.at(m_objectPlacement->m_walls.size() - 1)->getBounds()->getPosition());

			std::cout << node["Xpos"].as<float>() << std::endl;
		}

		for (const auto& node : output["GameName"]) {
			m_saveGameScreen.setMainTitle(node["Name"].as<std::string>());
			m_saveGameScreen.setMainTitleInputField(node["Name"].as<std::string>());
			m_saveGameScreen.setMainItalics(node["Italics"].as<bool>());
			m_saveGameScreen.setMainUnderlined(node["Underlined"].as<bool>());
			m_saveGameScreen.setMainBold(node["Bold"].as<bool>());
			m_saveGameScreen.setMainColor(node["Color Red Value"].as<int>(), node["Color Green Value"].as<int>(), node["Color Blue Value"].as<int>());

		}

		for (const auto& node : output["GameSubTitle"]) {
			m_saveGameScreen.setSubTitle(node["Name"].as<std::string>());
			m_saveGameScreen.setSubTitleInputField(node["Name"].as<std::string>());
			m_saveGameScreen.setSubItalics(node["Italics"].as<bool>());
			m_saveGameScreen.setSubUnderlined(node["Underlined"].as<bool>());
			m_saveGameScreen.setSubBold(node["Bold"].as<bool>());
			m_saveGameScreen.setSubColor(node["Color Red Value"].as<int>(), node["Color Green Value"].as<int>(), node["Color Blue Value"].as<int>());

		}
		m_gameState->setState(State::ROOM_PLACE_OBJECTS);
	}
	//std::cout << m_grid->m_vectGrid.size() << std::endl;
	if (m_gameState->getState() != State::PAUSE_GAME)
	{
		if (m_roomCreation->firstFloorSet && m_grid->m_playerSet == false)
		{
			m_grid->m_playerSet = true;
			m_player->getBounds()->setPosition(m_roomCreation->m_firstTilePosition.x + 16, m_roomCreation->m_firstTilePosition.y + 16);
			//std::cout << m_player->getSprite()->getPosition().x << std::endl;
		}

		//m_textureManager->getNumberOfTextures();
		//m_fontManager.getNumberOfFonts();
		m_objectPlacement->update(t_deltaTime, m_window);

		if (m_gameState->m_currentGameState == State::ROOM_BUILD)
		{
			m_roomCreation->update(t_deltaTime, m_window);
		}



		if (m_gameState->m_currentGameState == State::ROOM_TEST)
		{
			m_player->update(t_deltaTime, m_window);
			m_gameView.setCenter(sf::Vector2f(m_player->getCenterPos().x, m_player->getCenterPos().y +32));
			m_window.setView(m_gameView);
			m_spear->update(t_deltaTime, m_window);
			if (m_objectPlacement->m_enemies.size() > 0)
			{
				for (int i = 0; i < m_objectPlacement->m_enemies.size(); i++)
				{
					m_objectPlacement->m_enemies.at(i)->update(t_deltaTime, m_window);
				}
			}
		}

		if (m_gameState->getState() == State::ROOM_TEST)
		{
			// player and walls
			// objects and walls
			m_player->m_speed = m_player->m_defaultSpeed;

			if (m_objectPlacement->m_walls.size() > 0)
			{
				for (int i = 0; i < m_objectPlacement->m_walls.size(); i++)
				{
					m_checkCollision.checkCollision(m_player->getBounds(), m_objectPlacement->m_walls.at(i)->getBounds(), 0.0f);
				}
			}
			if (m_objectPlacement->m_decorations.size() > 0)
			{
				for (int i = 0; i < m_objectPlacement->m_decorations.size(); i++)
				{
					m_checkCollision.checkCollision(m_player->getBounds(), m_objectPlacement->m_decorations.at(i)->getBounds(), 0.0f);
				}
			}
			if (m_objectPlacement->m_enemies.size() > 0)
			{
				for (int i = 0; i < m_objectPlacement->m_enemies.size(); i++)
				{
					m_checkCollision.checkCollision(m_player->getBounds(), m_objectPlacement->m_enemies.at(i)->getBounds(), 0.5f);
				}
			}
			if (m_objectPlacement->m_colliders.size() > 0)
			{
				for (int i = 0; i < m_objectPlacement->m_colliders.size(); i++)
				{
					m_checkCollision.checkCollision(m_player->getBounds(), m_objectPlacement->m_colliders.at(i).getBounds(), 0.0f);
				}
			}
			if (m_objectPlacement->m_items.size() > 0)
			{
				for (int i = 0; i < m_objectPlacement->m_items.size(); i++)
				{
					if (m_checkCollision.checkCollision(m_player->getBounds(), m_objectPlacement->m_items.at(i)->getBounds()))
					{
						for (std::vector<Object*>::iterator iter = m_objectPlacement->m_items.begin(); iter != m_objectPlacement->m_items.end();)
						{
							(*iter)->setSelected(false);
							//(*iter)->getBounds()->getGlobalBounds();
							if ((*iter)->getBounds()->getGlobalBounds().contains(m_player->getBounds()->getPosition()))
							{
								// resets the right tile even if the object was moved
								m_grid->m_vectGrid.at((*iter)->getRow()).at((*iter)->getColumn()).m_hasObject = false;
								m_grid->m_vectGrid.at((*iter)->getRow()).at((*iter)->getColumn()).m_objectType = "";
								iter = m_objectPlacement->m_items.erase(iter);
							}
							else
							{
								iter++;
							}
						}
					}
				}
			}

				//for (int i = 0; i < m_objectPlacement->m_items.size(); i++)
				//{
				//	for (int j = 0; j < m_roomCreation->m_vectColliders.size(); j++)
				//	{
				//		m_checkCollision.checkCollision(m_objectPlacement->m_items.at(i)->getBounds(), m_roomCreation->m_vectColliders.at(j)->getBounds(), 0.0f);
				//		m_checkCollision.checkCollision(m_player->getBounds(), m_objectPlacement->m_items.at(i)->getBounds(), 0.0f);

				//	}
				//}

				//m_player->setInteract(false);
				//for (int i = 0; i < m_objectPlacement->m_enemies.size(); i++)
				//{

				//	if (m_checkCollision.checkCollision(m_player->getInteractionBounds(), m_objectPlacement->m_enemies.at(i)->getBounds()))
				//	{
				//		m_player->setInteract(true);
				//		m_currentObject = m_objectPlacement->m_enemies.at(i);
				//		//std::cout << "Can Interact" << std::endl;
				//		break;
				//	}
				//	else
				//	{
				//		if (i == m_objectPlacement->m_enemies.size() - 1 && m_player->getInteract() == false)
				//		{
				//			m_currentObject = nullptr;
				//			//std::cout << "Cannot Interact" << std::endl;
				//		}
				//	}
				//}

				//for (int i = 0; i < m_objectPlacement->m_enemies.size(); i++)
				//{

				//	if (m_checkCollision.checkCollision(m_player->getBounds(), m_objectPlacement->m_enemies.at(i)->getDetectionRadius()))
				//	{
				//		if (!m_objectPlacement->m_enemies.at(i)->getInRange())
				//		{
				//			m_objectPlacement->m_enemies.at(i)->getDialogueBox()->setEnabled();
				//			m_objectPlacement->m_enemies.at(i)->loadDialogue("InRange");
				//			m_currentObject = m_objectPlacement->m_enemies.at(i);
				//			m_gameState->setState(State::PAUSE_GAME);
				//		}
				//		m_currentObject = m_objectPlacement->m_enemies.at(i);
				//		m_currentObject->getDialogueBox()->setEnabled();
				//		m_currentObject->loadDialogue("Interacted");
				//		//std::cout << "Within Range Of Enemy" << std::endl;
				//		break;
				//	}
				//	else
				//	{
				//		m_currentObject->getDialogueBox()->setEnabled();
				//		m_currentObject->loadDialogue("Interacted");
				//		std::cout << "Out of Range Safe" << std::endl;

				//	}
				//}

			/*for (int i = 0; i < m_objectPlacement->m_enemies.size(); i++)
			{
				for (int j = 0; j < m_objectPlacement->m_enemies.size(); j++)
				{
					if (j < m_objectPlacement->m_enemies.size() - 1)
					{

						m_checkCollision.checkCollision(m_objectPlacement->m_enemies.at(i)->getBounds(), m_objectPlacement->m_enemies.at(j + 1)->getBounds(), 0.0f);

					}
				}
			}*/

			if (m_objectPlacement->m_enemies.size() > 0)
			{
				for (int i = 0; i < m_objectPlacement->m_enemies.size(); i++)
				{
					for (int j = 0; j < m_objectPlacement->m_walls.size(); j++)
					{

						m_checkCollision.checkCollision(m_objectPlacement->m_enemies.at(i)->getBounds(), m_objectPlacement->m_walls.at(j)->getBounds(), 0.0f);


					}
					for (int j = 0; j < m_objectPlacement->m_colliders.size(); j++)
					{

						m_checkCollision.checkCollision(m_objectPlacement->m_enemies.at(i)->getBounds(), m_objectPlacement->m_colliders.at(j).getBounds(), 0.0f);


					}
					for (int j = 0; j < m_objectPlacement->m_decorations.size(); j++)
					{

						m_checkCollision.checkCollision(m_objectPlacement->m_enemies.at(i)->getBounds(), m_objectPlacement->m_decorations.at(j)->getBounds(), 0.0f);


					}
				}
			}

			}

			// Spear vs Obstacles
	//		if (m_spear->m_weaponUsed)
	//		{
	//			std::vector<Obstacle*>::iterator it;
	//			std::cout << m_spear->getWeaponBounds()->getSize().x << " : " << m_spear->getWeaponBounds()->getSize().y << std::endl;

	//			for (it = m_grid->m_placedObjects.begin(); it != m_grid->m_placedObjects.end();)
	//			{
	//				Obstacle* l_obstacle = *it;
	//				if (l_obstacle->isCollidable())
	//				{
	//					if (m_checkCollision.checkCollision(m_spear->getWeaponBounds(), l_obstacle->getBounds(), 0.4f))
	//					{

	//						it = m_grid->m_placedObjects.erase(it);

	//						m_grid->noOfObstacles--;
	//					}
	//					else
	//					{
	//						it++;
	//					}

	//				}
	//				else
	//				{
	//					it++;
	//				}
	//			}
	//		}

	//		// grid objects against grid objects

	//	}
		
	}

	if (m_gameState->getState() == State::ROOM_PLACE_OBJECTS)
	{
		// get the current mouse position in the window
		sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);

		// convert it to world coordinates
		sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos);
		//std::cout << " world x : " << worldPos.x << " world y : " << worldPos.y << std::endl;




		sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

		sf::Vector2u windowSize = m_window.getSize();

		int scrollDistanceSides= 320;

		int scrollDistanceBottom = 40;


		// scroll left

			if (mousePos.x < scrollDistanceSides && mousePos.x >= 256 && mousePos.y < windowSize.y - 256) 
			{
				float newCenterX = m_window.getView().getCenter().x - 6;

				sf::View view(sf::Vector2f(newCenterX, m_window.getView().getCenter().y), sf::Vector2f(m_gameView.getSize().x, m_gameView.getSize().y));
				m_gameView = view;
				//m_gameView.zoom(m_zoomRate);
				m_window.setView(m_gameView);
			}
			

			if (mousePos.x > windowSize.x - scrollDistanceSides && mousePos.x < windowSize.x - 256
				&& mousePos.y < windowSize.y - 256) 
			{

				float newCenterX = m_window.getView().getCenter().x + 6;


				sf::View view(sf::Vector2f(newCenterX, m_window.getView().getCenter().y), sf::Vector2f(m_gameView.getSize().x, m_gameView.getSize().y));
				m_gameView = view;
				//m_gameView.zoom(m_zoomRate);
				m_window.setView(m_gameView);
			}
			if (mousePos.y < 96 && mousePos.x > 256 && mousePos.x < windowSize.x - 256)
			{

				float newCenterY = m_window.getView().getCenter().y - 6;


				sf::View view(sf::Vector2f(m_window.getView().getCenter().x, newCenterY), sf::Vector2f(m_gameView.getSize().x, m_gameView.getSize().y));
				m_gameView = view;
				//m_gameView.zoom(m_zoomRate);
				m_window.setView(m_gameView);
			}

			if (mousePos.y > windowSize.y - scrollDistanceSides && mousePos.y < windowSize.y - 256
				&& mousePos.x > 256 && mousePos.x < windowSize.x - 256)
			{
				float newCenterY = m_window.getView().getCenter().y + 6;

				sf::View view(sf::Vector2f(m_window.getView().getCenter().x, newCenterY), sf::Vector2f(m_gameView.getSize().x, m_gameView.getSize().y));
				m_gameView = view;
				//m_gameView.zoom(m_zoomRate);
				m_window.setView(m_gameView);
			}


			//std::cout << "centre x : " << m_view.getCenter().x << std::endl;
			if (m_gameView.getCenter().x - (windowSize.x / 2) < -800)
			{
				sf::View view(sf::Vector2f((windowSize.x / 2)- 800, m_window.getView().getCenter().y), sf::Vector2f(m_gameView.getSize().x, m_gameView.getSize().y));
				m_gameView = view;
				//m_gameView.zoom(m_zoomRate);
				m_window.setView(m_gameView);
			}
			if (m_gameView.getCenter().x + (windowSize.x / 2) > 4000)
			{
				sf::View view(sf::Vector2f(4000 - (windowSize.x / 2), m_window.getView().getCenter().y), sf::Vector2f(m_gameView.getSize().x, m_gameView.getSize().y));
				m_gameView = view;
				//m_gameView.zoom(m_zoomRate);
				m_window.setView(m_gameView);
			}
			if (m_gameView.getCenter().y - (windowSize.y / 2) < -480)
			{
				sf::View view(sf::Vector2f(m_window.getView().getCenter().x, (windowSize.y / 2) - 480), sf::Vector2f(m_gameView.getSize().x, m_gameView.getSize().y));
				m_gameView = view;
				//m_gameView.zoom(m_zoomRate);
				m_window.setView(m_gameView);
			}
			if (m_gameView.getCenter().y + (windowSize.y / 2) > 3680)
			{
				sf::View view(sf::Vector2f(m_window.getView().getCenter().x, 3680 - (windowSize.y / 2)), sf::Vector2f(m_gameView.getSize().x, m_gameView.getSize().y));
				m_gameView = view;
				//m_gameView.zoom(m_zoomRate);
				m_window.setView(m_gameView);
			}
			//std::cout << m_gameView.getSize().x << " : " << m_gameView.getSize().y << std::endl;
			//std::cout << m_gameView.getCenter().x << " centre " << m_gameView.getCenter().y << std::endl;

			//m_squareBounds = sf::FloatRect(m_gameView.getCenter().x - (m_gameView.getSize().x / 2) + 256, m_gameView.getCenter().y - m_gameView.getSize().y /2, m_gameView.getSize().x -512, m_gameView.getSize().y -256);

	}


}

void Game::render()
{
	m_window.clear(sf::Color::Black);
	if (m_gameState->getState() == State::ROOM_PLACE_OBJECTS)
	{
		m_window.setView(m_gameView);
		m_grid->render(&m_window);
		m_objectPlacement->render(&m_window);

		m_window.setView(m_uiView);
		m_levelList.render(&m_window);
		m_uiBuildMode.render(&m_window);
		m_player->render(m_window);
		for (int i = 0; i < m_objectPlacement->m_enemies.size(); i++)
		{
			m_objectPlacement->m_enemies.at(i)->renderInspector(m_window);
		}

		m_window.setView(m_gameView);
	}
	else if (m_gameState->getState() == State::ROOM_TEST)
	{
		m_window.setView(m_gameView);
		m_grid->render(&m_window);
		m_objectPlacement->render(&m_window);
		m_spear->render(m_window);
		m_player->render(m_window);

		m_window.setView(m_uiView);
		m_uiBuildMode.render(&m_window);
		m_window.setView(m_gameView);
	}
	else if (m_gameState->getState() == State::CREATE_DIALOGUE)
	{
		m_window.setView(m_uiView);
		m_textEditor->render(&m_window);
	}
	else if (m_gameState->getState() == State::MENU)
	{
		m_window.setView(m_uiView);
		m_mainMenu.render(&m_window);
		m_window.setView(m_gameView);
	}
	else if (m_gameState->getState() == State::PLAY_GAME)
	{

	}
	else if (m_gameState->getState() == State::PAUSE_GAME)
	{

	}
	else if (m_gameState->getState() == State::ROOM_BUILD)
	{
		m_levelList.render(&m_window);
	}
	else if (m_gameState->getState() == State::SAVING_SCREEN)
	{
		m_window.setView(m_gameView);
		m_grid->render(&m_window);
		m_objectPlacement->render(&m_window);
		m_window.setView(m_uiView);
		m_uiBuildMode.render(&m_window);
		m_saveGameScreen.render(&m_window);
		m_window.setView(m_gameView);
	}
	else if (m_gameState->getState() == State::LEVEL_LIST)
	{
		m_window.setView(m_gameView);
		m_grid->render(&m_window);
		m_objectPlacement->render(&m_window);

		m_window.setView(m_uiView);
		m_levelList.render(&m_window);
		m_uiBuildMode.render(&m_window);

		m_window.setView(m_gameView);
	}

	else if (m_gameState->getState() == State::GAME_LIST)
	{
		m_window.setView(m_gameView);
		// m_grid->render(&m_window);
		m_objectPlacement->render(&m_window);

		m_window.setView(m_uiView);
		m_levelList.render(&m_window);
		//m_uiBuildMode.render(&m_window);

		m_window.setView(m_gameView);
	}

	m_window.display();
}
