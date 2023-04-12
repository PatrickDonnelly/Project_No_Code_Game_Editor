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
		if (m_gameState->getState() == State::MENU || m_gameState->getState() == State::ROOM_BUILD)
		{
			m_mainMenu.processEvents(newEvent, m_window);
		}
		if (m_gameState->getState() == State::GAME_LIST || m_gameState->getState() == State::ROOM_BUILD)
		{
			m_levelList.processEvents(newEvent, m_window);
		}
		if (m_gameState->getState() == State::SAVING_SCREEN)
		{
			m_saveGameScreen.processEvents(newEvent, m_window);
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
			//if (m_gameState->getState()==State::ROOM_PLACE_OBJECTS)
			//{
				m_uiBuildMode.processEvents(newEvent, m_window);
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
			if (m_gameState->m_currentGameState == State::ROOM_PLACE_OBJECTS)
			{
				m_objectPlacement->processEvents(newEvent, m_window);

			}
			if (m_gameState->m_currentGameState == State::ROOM_PLACE_OBJECTS || m_gameState->m_currentGameState == State::CREATE_DIALOGUE)
			{
				if (m_objectPlacement->m_currentlySelected != nullptr)
				{
					m_objectPlacement->m_currentlySelected->getInspector()->processEvents(newEvent, m_window, m_gameState, m_textEditor->GetTitle()->GetText(), (*m_objectPlacement->m_currentlySelected->getDialoguePaths()));
					m_textEditor->processTextEditorButtons(newEvent, m_window, m_objectPlacement->m_currentlySelected->getInspector()->m_currentLabel);
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
		// Prompt user to enter their games name - text editor, save button cancle button

		// pop up if name taken - options overwrite, cancel

		// if name not taken create folder directory with that name

		// create a button with that projects name

		// load data from that project if the button is clicked

		std::cout << "Saving Game" << std::endl;

		// creating an ifstream object named file
		std::ifstream file;

		// opening the file
		file.open("Dialogue/testSave.csv");
		if (file)
		{
			//saving = true;
			//std::cout << "File exists" << std::endl;
			//m_popUpBox.setPopUpEnabled();

			//unsigned lines = 0;
			//std::string line_content;
			//std::string lineContentAppended;
			//std::ifstream my_file("PopUpMessages/fileExists.txt");


			//while (std::getline(my_file, line_content)) {
			//	lines++;


			//	lineContentAppended.append(line_content);
			//	lineContentAppended.append("\n");


				//std::cout << "Line: " << lines << " content: " << line_content << std::endl;
			//}

			//my_file.close();

			//m_popUpBox.setPopUpBoxText(lineContentAppended);

			//for (int i = 0; i < 2; i++)
			//{

			//	m_popUpButtons.at(i)->setButtonPosition(
			//		sf::Vector2f{ m_popUpBox.getPopUpBoxPosition().x + (m_popUpBox.getPopUpBoxBounds().x / 2) + (i * 200) - 100,
			//						m_popUpBox.getPopUpBoxPosition().y + (m_popUpBox.getPopUpBoxBounds().y) - (m_popUpButtons.at(i)->getButtonSprite().getGlobalBounds().height) });
			//	m_popUpButtonLabels.at(i)->setTextPosition(m_popUpButtons.at(i)->getButtonPosition());
			//}
		}

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
		out << YAML::EndMap;
		out << YAML::EndDoc;
		// player save

		std::ofstream fout("output.yaml");
		fout << out.c_str();
		fout.close();

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
		// load files
		// switch to play game

		YAML::Node output = YAML::LoadFile("output.yaml");
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

		// m_grid->m_vectGrid


				//std::vector<ObjectData> objects;
		for (const auto& node : output["Tile"]) {
			textures.push_back(node["Texture"].as<std::string>());
			cellType.push_back(node["Cell Type"].as<std::string>());
			hasObject.push_back(node["Occupied"].as<bool>());
			positions.push_back(
				sf::Vector2f(node["Xpos"].as<float>(), node["Ypos"].as<float>()));
			//sf::Vector2f name = sf::Vector2f(node["Xpos"].as<float>(), node["Ypos"].as<float>());
			//break;
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
			//cellType.push_back(node["Cell Type"].as<std::string>());
			//sf::Vector2f name = sf::Vector2f(node["Xpos"].as<float>(), node["Ypos"].as<float>());
			//break;
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
			//cellType.push_back(node["Cell Type"].as<std::string>());
			//sf::Vector2f name = sf::Vector2f(node["Xpos"].as<float>(), node["Ypos"].as<float>());
			//break;
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
			//cellType.push_back(node["Cell Type"].as<std::string>());
			//sf::Vector2f name = sf::Vector2f(node["Xpos"].as<float>(), node["Ypos"].as<float>());
			//break;
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
			//cellType.push_back(node["Cell Type"].as<std::string>());
			//sf::Vector2f name = sf::Vector2f(node["Xpos"].as<float>(), node["Ypos"].as<float>());
			//break;
			//int r = m_objectPlacement->m_walls.at(m_objectPlacement->m_walls.size() - 1)->getBounds()->getPosition().x / 32;
			//int c = m_objectPlacement->m_walls.at(m_objectPlacement->m_walls.size() - 1)->getBounds()->getPosition().y / 32;

			//m_grid->m_vectGrid.at(r).at(c).cellType = node["CellType"].as<std::string>();

			std::cout << node["Xpos"].as<float>() << std::endl;
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
			m_spear->update(t_deltaTime, m_window);
		}

		if (m_gameState->getState() == State::ROOM_TEST)
		{
			// player and walls
			// objects and walls
			m_player->m_speed = m_player->m_defaultSpeed;

			if (m_roomCreation->m_vectColliders.size() > 0)
			{
				for (int i = 0; i < m_roomCreation->m_vectColliders.size(); i++)
				{
					m_checkCollision.checkCollision(m_player->getBounds(), m_roomCreation->m_vectColliders.at(i)->getBounds(), 0.0f);
				}
				for (int i = 0; i < m_objectPlacement->m_decorations.size(); i++)
				{
					for (int j = 0; j < m_roomCreation->m_vectColliders.size(); j++)
					{
						m_checkCollision.checkCollision(m_objectPlacement->m_decorations.at(i)->getBounds(), m_roomCreation->m_vectColliders.at(j)->getBounds(), 0.0f);
						m_checkCollision.checkCollision(m_player->getBounds(), m_objectPlacement->m_decorations.at(i)->getBounds(), 0.5f);
					}
				}
				for (int i = 0; i < m_objectPlacement->m_items.size(); i++)
				{
					for (int j = 0; j < m_roomCreation->m_vectColliders.size(); j++)
					{
						m_checkCollision.checkCollision(m_objectPlacement->m_items.at(i)->getBounds(), m_roomCreation->m_vectColliders.at(j)->getBounds(), 0.0f);
						m_checkCollision.checkCollision(m_player->getBounds(), m_objectPlacement->m_items.at(i)->getBounds(), 0.0f);

					}
				}
				for (int i = 0; i < m_objectPlacement->m_enemies.size(); i++)
				{
					for (int j = 0; j < m_roomCreation->m_vectColliders.size(); j++)
					{
						m_checkCollision.checkCollision(m_objectPlacement->m_enemies.at(i)->getBounds(), m_roomCreation->m_vectColliders.at(j)->getBounds(), 0.0f);
						m_checkCollision.checkCollision(m_player->getBounds(), m_objectPlacement->m_enemies.at(i)->getBounds(), 0.0f);




					}
				}
				m_player->setInteract(false);
				for (int i = 0; i < m_objectPlacement->m_enemies.size(); i++)
				{

					if (m_checkCollision.checkCollision(m_player->getInteractionBounds(), m_objectPlacement->m_enemies.at(i)->getBounds()))
					{
						m_player->setInteract(true);
						m_currentObject = m_objectPlacement->m_enemies.at(i);
						//std::cout << "Can Interact" << std::endl;
						break;
					}
					else
					{
						if (i == m_objectPlacement->m_enemies.size() - 1 && m_player->getInteract() == false)
						{
							m_currentObject = nullptr;
							//std::cout << "Cannot Interact" << std::endl;
						}
					}
				}

				for (int i = 0; i < m_objectPlacement->m_enemies.size(); i++)
				{

					if (m_checkCollision.checkCollision(m_player->getBounds(), m_objectPlacement->m_enemies.at(i)->getDetectionRadius()))
					{
						if (!m_objectPlacement->m_enemies.at(i)->getInRange())
						{
							m_objectPlacement->m_enemies.at(i)->getDialogueBox()->setEnabled();
							m_objectPlacement->m_enemies.at(i)->loadDialogue("InRange");
							m_currentObject = m_objectPlacement->m_enemies.at(i);
							m_gameState->setState(State::PAUSE_GAME);
						}
						//m_currentObject = m_objectPlacement->m_enemies.at(i);
						//m_currentObject->getDialogueBox()->setEnabled();
						//m_currentObject->loadDialogue();
						//std::cout << "Within Range Of Enemy" << std::endl;
						break;
					}
					else
					{
						//m_currentObject->getDialogueBox()->setEnabled();
						//m_currentObject->loadDialogue();
						//std::cout << "Out of Range Safe" << std::endl;

					}
				}

				for (int i = 0; i < m_objectPlacement->m_walls.size(); i++)
				{
					for (int j = 0; j < m_roomCreation->m_vectColliders.size(); j++)
					{
						m_checkCollision.checkCollision(m_objectPlacement->m_walls.at(i)->getBounds(), m_roomCreation->m_vectColliders.at(j)->getBounds(), 0.0f);
						m_checkCollision.checkCollision(m_player->getBounds(), m_objectPlacement->m_walls.at(i)->getBounds(), 0.0f);
					}
				}

				//if (m_grid->m_placedObjects.at(i)->isCollidable())
				//{
				//	m_player->m_speed = m_player->m_defaultSpeed;
				//	if (m_grid->m_placedObjects.at(i)->m_tag != "Hole")
				//	{
				//		m_checkCollision.checkCollision(m_player->getBounds(), m_grid->m_placedObjects.at(i)->getBounds(), 0.4f);
				//	}
				//	else
				//	{
				//		m_checkCollision.checkCollision(m_player->getBounds(), m_grid->m_placedObjects.at(i)->getBounds(), 0.0f);
				//	}
				//}
				//else // if not collidable
				//{
				//	if (m_grid->m_placedObjects.at(i)->m_tag == "Water")
				//	{
				//		if (m_checkCollision.checkCollision(m_player->getBounds(), m_grid->m_placedObjects.at(i)->getBounds()))
				//		{
				//			m_player->m_speed = m_player->m_defaultSpeed * 0.5f;
				//		}

				//		
				//	}
				//}
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
	//		for (int i = 0; i < m_grid->m_placedObjects.size(); i++)
	//		{
	//			for (int j = 0; j < m_grid->m_placedObjects.size(); j++)
	//			{

	//				if (j < m_grid->m_placedObjects.size() - 1)
	//				{
	//					if (m_grid->m_placedObjects.at(i)->isCollidable() && m_grid->m_placedObjects.at(j + 1)->isCollidable())
	//					{
	//						m_checkCollision.checkCollision(m_grid->m_placedObjects.at(i)->getBounds(), m_grid->m_placedObjects.at(j + 1)->getBounds(), 0.5f);
	//					}
	//				}
	//			}
	//		}
	//	}
		}
	}

	if (m_gameState->getState() != State::MENU)
	{
		// get the current mouse position in the window
		sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);

		// convert it to world coordinates
		sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos);
		//std::cout << " world x : " << worldPos.x << " world y : " << worldPos.y << std::endl;




		sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

		sf::Vector2u windowSize = m_window.getSize();

		int scrollDistance = 40;

		// scroll left

			if (mousePos.x < scrollDistance) {
				float newCenterX = m_window.getView().getCenter().x - scrollDistance / 4;

				sf::View view(sf::Vector2f(newCenterX, m_window.getView().getCenter().y), sf::Vector2f(m_gameView.getSize().x, m_gameView.getSize().y));
				m_gameView = view;
				//m_gameView.zoom(m_zoomRate);
				m_window.setView(m_gameView);
			}
			

			if (mousePos.x > windowSize.x - scrollDistance) {

				float newCenterX = m_window.getView().getCenter().x + scrollDistance / 4;


				sf::View view(sf::Vector2f(newCenterX, m_window.getView().getCenter().y), sf::Vector2f(m_gameView.getSize().x, m_gameView.getSize().y));
				m_gameView = view;
				//m_gameView.zoom(m_zoomRate);
				m_window.setView(m_gameView);
			}
			if (mousePos.y < scrollDistance) 
			{

				float newCenterY = m_window.getView().getCenter().y - scrollDistance / 4;


				sf::View view(sf::Vector2f(m_window.getView().getCenter().x, newCenterY), sf::Vector2f(m_gameView.getSize().x, m_gameView.getSize().y));
				m_gameView = view;
				//m_gameView.zoom(m_zoomRate);
				m_window.setView(m_gameView);
			}

			if (mousePos.y > windowSize.y - scrollDistance) {
				float newCenterY = m_window.getView().getCenter().y + scrollDistance / 4;

				sf::View view(sf::Vector2f(m_window.getView().getCenter().x, newCenterY), sf::Vector2f(m_gameView.getSize().x, m_gameView.getSize().y));
				m_gameView = view;
				//m_gameView.zoom(m_zoomRate);
				m_window.setView(m_gameView);
			}


			//std::cout << "centre x : " << m_view.getCenter().x << std::endl;
			if (m_gameView.getCenter().x - (windowSize.x / 2) < -544)
			{
				sf::View view(sf::Vector2f((windowSize.x / 2)-544, m_window.getView().getCenter().y), sf::Vector2f(m_gameView.getSize().x, m_gameView.getSize().y));
				m_gameView = view;
				//m_gameView.zoom(m_zoomRate);
				m_window.setView(m_gameView);
			}
			if (m_gameView.getCenter().x + (windowSize.x / 2) > 3680)
			{
				sf::View view(sf::Vector2f(3680 - (windowSize.x / 2), m_window.getView().getCenter().y), sf::Vector2f(m_gameView.getSize().x, m_gameView.getSize().y));
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
		m_saveGameScreen.render(&m_window);
		m_window.setView(m_gameView);
	}

	m_window.display();
}
