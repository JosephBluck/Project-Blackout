#pragma once
#include "GameStates.h"
#include"InputManager.h"
#include"SoundManager.h"
#include "Sprite.h"
#include "Player.h"

class InGame : public GameState
{
public:
	InGame(SDL_Renderer* _renderer, InputManager* _input, GameStateManager* manager);
	~InGame();

	void Update() override;
	void Draw() override;
private:
	bool InitInGame();
	bool initSuccess;
	void UpdateCamera();

	SDL_Rect Camera{ 0,0,1280,720 };
	SDL_Rect screen{ 0, 0, 1280, 720 };

	Player* player;
	AnimSprite* background;
	SDL_Texture* cameraRenderBuffer;

	InputManager* input = NULL;//input manager
};