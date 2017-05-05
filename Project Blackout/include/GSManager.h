#pragma once
#include "GameStates.h"
#include <vector>

class GameStateManager
{
public:
	~GameStateManager();//Game State Manager Destructor

	void addState(GameState* _gState); //adds a game state to the Game states Vector
	void changeState(GameState* _gState); //changes to a new game state
	void removeLastState(); //removes last state from the vector

	void updateState();//updates most recent Game State on the vector
	void drawState();//draws the most recent Game State on the vector
private:
	std::vector<GameState*> gameStatesVector;//vector that holds all Game states
};