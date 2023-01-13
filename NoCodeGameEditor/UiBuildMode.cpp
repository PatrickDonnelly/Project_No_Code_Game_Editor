#include "UiBuildMode.h"

void UiBuildMode::setUpPlaceableItemsButtons(sf::Font t_arialFont)
{
	for (int i = 0; i < 6; i++)
	{
		m_selectableObjects.push_back(Button());
		m_selectableObjects.at(i).setButtonPosition(sf::Vector2f{ 768.0f + (i * 64), 200.0f });
		m_selectableObjects.at(i).resize(0.25, 1.0f);

		m_texturedLabels.push_back(Label(t_arialFont));
		m_texturedLabels.at(i).setTextColor(sf::Color::White);
		m_texturedLabels.at(i).setTextOutlineColor(sf::Color::Black);
		m_texturedLabels.at(i).setTextSize(11.0f);
		m_texturedLabels.at(i).setTextOutlineThickness(2.0f);
		m_texturedLabels.at(i).setTexturePosition(m_selectableObjects.at(i).getButtonPosition());
		m_texturedLabels.at(i).setTextPosition(sf::Vector2f(m_selectableObjects.at(i).getButtonPosition().x + 2, m_selectableObjects.at(i).getButtonPosition().y + 24));
	}
	m_texturedLabels.at(0).setText("Statue");
	m_texturedLabels.at(0).setLabelSprite(m_texturedLabels.at(0).getText().getString());
	m_texturedLabels.at(1).setText("Grass");
	m_texturedLabels.at(1).setLabelSprite(m_texturedLabels.at(1).getText().getString());
	m_texturedLabels.at(2).setText("Potion");
	m_texturedLabels.at(2).setLabelSprite(m_texturedLabels.at(2).getText().getString());
	m_texturedLabels.at(3).setText("Enemy");
	m_texturedLabels.at(3).setLabelSprite(m_texturedLabels.at(3).getText().getString());
	m_texturedLabels.at(4).setText("Water");
	m_texturedLabels.at(4).setLabelSprite(m_texturedLabels.at(4).getText().getString());
	m_texturedLabels.at(5).setText("Hole");
	m_texturedLabels.at(5).setLabelSprite(m_texturedLabels.at(5).getText().getString());
}

void UiBuildMode::setUpGridFunctionButtons(sf::Font t_arialFont)
{
	for (int i = 0; i < 4; i++)
	{
		m_buildButtons[i] = Button();
		m_buildButtons[i].setButtonPosition(sf::Vector2f{ 820.0f + (i * 280), 900.0f });
		if (i == 2)
		{
			m_buildButtons[i] = Button();
			m_buildButtons[i].setButtonPosition(sf::Vector2f{ 820.0f, 1000.0f });
		}
		if (i == 3)
		{
			m_buildButtons[i] = Button();
			m_buildButtons[i].setButtonPosition(sf::Vector2f{ 820.0f + 280.0f, 1000.0f });
		}
		m_buildButtonLabels[i] = Label(t_arialFont);
		m_buildButtonLabels[i].setTextPosition(m_buildButtons[i].getButtonPosition());
	}
	m_buildButtonLabels[0].setText("Clear Grid");
	m_buildButtonLabels[1].setText("Generate Room");
	m_buildButtonLabels[2].setText("-");
	m_buildButtonLabels[3].setText("+");
}

void UiBuildMode::setUpTestBuildButtons(sf::Font t_arialFont)
{
	for (int i = 0; i < 4; i++)
	{
		m_buildButtons[i] = Button();
		m_buildButtons[i].setButtonPosition(sf::Vector2f{ 820.0f + (i * 280), 900.0f });
		if (i == 2)
		{
			m_buildButtons[i] = Button();
			m_buildButtons[i].setButtonPosition(sf::Vector2f{ 820.0f, 1000.0f });
		}
		m_buildButtonLabels[i] = Label(t_arialFont);
		m_buildButtonLabels[i].setTextPosition(m_buildButtons[i].getButtonPosition());
	}
	m_buildButtonLabels[0].setText("Place Objects");
	m_buildButtonLabels[1].setText("Save Room");
	m_buildButtonLabels[2].setText("Start Over");
}

void UiBuildMode::setUpTextureRoomButtons(sf::Font t_arialFont)
{
	for (int i = 0; i < 6; i++)
	{
		m_textureRoomButtons.push_back(Button());
		m_textureRoomButtons.at(i).setButtonPosition(sf::Vector2f{ 768.0f + (i * 64), 200.0f });
		m_textureRoomButtons.at(i).resize(0.25, 1.0f);

		m_textureRoomLabels.push_back(Label(t_arialFont));
		m_textureRoomLabels.at(i).setTextColor(sf::Color::White);
		m_textureRoomLabels.at(i).setTextOutlineColor(sf::Color::Black);
		m_textureRoomLabels.at(i).setTextSize(11.0f);
		m_textureRoomLabels.at(i).setTextOutlineThickness(2.0f);
		m_textureRoomLabels.at(i).setTexturePosition(m_selectableObjects.at(i).getButtonPosition());
		m_textureRoomLabels.at(i).setTextPosition(sf::Vector2f(m_selectableObjects.at(i).getButtonPosition().x + 2, m_selectableObjects.at(i).getButtonPosition().y + 24));
	}
	m_textureRoomLabels.at(0).setText("Grass");
	m_textureRoomLabels.at(0).setLabelSprite(m_texturedLabels.at(0).getText().getString());
	m_textureRoomLabels.at(1).setText("Dirt");
	m_textureRoomLabels.at(1).setLabelSprite(m_texturedLabels.at(1).getText().getString());
	m_textureRoomLabels.at(2).setText("Concrete");
	m_textureRoomLabels.at(2).setLabelSprite(m_texturedLabels.at(2).getText().getString());
	m_textureRoomLabels.at(3).setText("Brick");
	m_textureRoomLabels.at(3).setLabelSprite(m_texturedLabels.at(3).getText().getString());
	m_textureRoomLabels.at(4).setText("Stone");
	m_textureRoomLabels.at(4).setLabelSprite(m_texturedLabels.at(4).getText().getString());
	m_textureRoomLabels.at(5).setText("Wood");
	m_textureRoomLabels.at(5).setLabelSprite(m_texturedLabels.at(5).getText().getString());
}

UiBuildMode::UiBuildMode(sf::Font t_arialFont, Grid* t_grid, GameState* t_currentGameState)
{
	m_gameState = t_currentGameState;
	m_grid = t_grid;
	m_arialFont = t_arialFont;
	setUpPlaceableItemsButtons(m_arialFont);
	setUpGridFunctionButtons(m_arialFont);
	setUpTestBuildButtons(m_arialFont);
	setUpTextureRoomButtons(m_arialFont);
}

UiBuildMode::UiBuildMode()
{
}

UiBuildMode::~UiBuildMode()
{
}

void UiBuildMode::processEvents(sf::Event t_event, sf::RenderWindow& t_window)
{
	sf::Event newEvent = t_event;

		for (int i = 0; i < m_selectableObjects.size(); i++)
		{
			if (m_selectableObjects.at(i).getButtonSprite().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					for (int j = 0; j < m_selectableObjects.size(); j++)
					{
						m_selectableObjects.at(j).setSelected(false);
					}
					m_selectableObjects.at(i).setSelected(true);

					if (m_selectableObjects.at(i).getSelected())
					{
						m_selectableObjects.at(i).setColor(sf::Color::Red);
						// send selected object to grid
						m_grid->setSelectedObject(m_texturedLabels.at(i).getText().getString());
					}
				}
			}
			if (!m_selectableObjects.at(i).getSelected())
			{
				m_selectableObjects.at(i).setColor(sf::Color::White);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (m_buildButtons[i].getButtonSprite().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
			{
				m_buildButtons[i].highlighted();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					if (m_buildButtonLabels[i].getTextString() == "Clear Grid")
					{
						m_grid->regenerateGrid();
					}
					else if (m_buildButtonLabels[i].getTextString() == "Generate Room")
					{
						m_grid->checkRoomValidity();
					}
					else if (m_buildButtonLabels[i].getTextString() == "-")
					{
						m_grid->decreaseGridSize();
					}
					else if (m_buildButtonLabels[i].getTextString() == "+")
					{
						m_grid->increaseGridSize();
					}
				}
			}
			else
			{
				m_buildButtons[i].setButtonTexture();
			}
		}
}

void UiBuildMode::render(sf::RenderWindow* t_window)
{
	if (m_gameState->m_currentGameState == State::ROOM_BUILD)
	{
		for (int i = 0; i < 4; i++)
		{
			m_buildButtons[i].render(t_window);
			m_buildButtonLabels[i].render(t_window);
		}
	}
	if (m_gameState->m_currentGameState == State::ROOM_TEXTURE)
	{

	}
	if (m_gameState->m_currentGameState == State::ROOM_PLACE_OBJECTS)
	{
		for (int i = 0; i < m_selectableObjects.size(); i++)
		{
			m_selectableObjects.at(i).render(t_window);
			m_texturedLabels.at(i).render(t_window);
		}
	}
	if (m_gameState->m_currentGameState == State::ROOM_TEST)
	{

	}
}
