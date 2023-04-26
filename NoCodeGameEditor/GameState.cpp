#include "GameState.h"

/// <summary>
/// Sets the current game state
/// </summary>
/// <param name="t_state"></param>
GameState::GameState(State t_state)
{
	m_currentGameState = t_state;
}

/// <summary>
/// Deconstructor
/// </summary>
GameState::~GameState()
{
}
