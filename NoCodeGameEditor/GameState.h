#pragma once

enum class State {
	MENU = 0,
	ROOM_BUILD = 1,
	ROOM_TEXTURE = 2,
	ROOM_PLACE_OBJECTS = 3,
	ROOM_TEST = 4,
	ROOM_SAVE = 5,
	CREATE_DIALOGUE = 6,
	PAUSE_GAME =7, 
	LOAD_GAME = 8,
	PLAY_GAME = 9,
	GAME_LIST = 10,
	SAVING = 11,
	LEVEL_LIST = 12,
	SAVING_SCREEN =13
};


class GameState
{
private:

public:
	GameState(State t_state);
	~GameState();

	State m_currentGameState;
	State m_previousGameState;

	void setState(State t_state) { m_previousGameState = m_currentGameState; m_currentGameState = t_state; }
	State getState() { return m_currentGameState; }
	State getPreviousState() { return m_previousGameState; }
};

