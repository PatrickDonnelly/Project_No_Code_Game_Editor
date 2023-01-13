#pragma once

enum class State {
	MENU = 0,
	ROOM_BUILD = 1,
	ROOM_TEXTURE = 2,
	ROOM_PLACE_OBJECTS = 3,
	ROOM_TEST = 4,
	ROOM_SAVE = 5
};


class GameState
{
private:

public:
	GameState(State t_state);
	~GameState();

	State m_currentGameState;
	State m_previousGameState;

	void setState(State t_state) { m_currentGameState = t_state; }
	State getState() { return m_currentGameState; }
};

