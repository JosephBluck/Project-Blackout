#include "GSManager.h"

GameStateManager::~GameStateManager()
{
	for (unsigned int i = 0; i < gameStatesVector.size(); i++)//deletes all game states on the vector
	{
		delete gameStatesVector.at(i);
	}
}

void GameStateManager::addState(GameState* _gState)
{
	gameStatesVector.push_back(_gState);//add game state to the top of the vector
}

void GameStateManager::changeState(GameState* _gState)
{
	for (unsigned int i = 0; i < gameStatesVector.size(); i++)//delete all current States on the vector
	{
		delete gameStatesVector.at(i);
	}
	gameStatesVector.clear();//clears the vector
	addState(_gState);//adds new state to the vector
}

void GameStateManager::removeLastState()
{
	delete gameStatesVector.back();//delete game state at top of vector
	gameStatesVector.pop_back();//pops deleted game state off of vector
}

void GameStateManager::updateState()
{
	gameStatesVector.back()->Update();//updates current game state
}

void GameStateManager::drawState()
{
	for (unsigned int i = 0; i < gameStatesVector.size(); i++)//draws all states in the vector
	{
		gameStatesVector.at(i)->Draw();
	}
}