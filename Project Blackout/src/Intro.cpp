#include "Intro.h"

IntroState::IntroState(SDL_Renderer* _renderer, GameStateManager* _gsManager, InputManager* _input) :
	GameState(_gsManager, _renderer)
{
	input = _input;

	monoFont = new AnimSprite(renderer, "resources\\sprites\\text\\monofonto.png", 0, 0, 1222, 213, 26, 3); //Load font sheet
	monoFont->SetSize(15, 20); //Set font size
	introText = new TextSprite(renderer, monoFont, 20, 20); //Create textsprite object

	introSounds = new SoundManager(1, "resources\\sounds\\BGM\\Motivated.mp3");
	introSounds->LoadSound(0, "resources\\sounds\\voices\\typing.wav");
	introSounds->PlayBGM(-1);
	introText->ConfigureType(3, introSounds->GetChunk(0));

	//Placeholder intro text
	introText->SetText(
		"The current year is 213X... you have been sitting in stasis since 2024 and on~"
		"this day, May 7th, you are finally released from your stasis.~"
		"The world as you know it has changed... your life as you knew it is gone...~~"
		"Your home... your friends... even your loved ones... swept away by catastrophe,~"
		"while you have lain here sleeping.~~"
		"When you awake, you do not recognise the faces looking down at you, but you~"
		"don't refuse the hand being offered as you are lifted upright and helped~"
		"out of the strange pod. The room is dimly lit leaving little to be seen.~~"
		"The men call out to you, and at first you don't understand why it sounds~"
		"so familiar to you...~~"
		"Then it hits you and you remember everything... or at least... everything~"
		"that happened before your storage.~~"
		"You recognise that the men are calling you by your name, and that your~"
		"suspension wasn't infact enforced upon you, rather you chose to be frozen.~~"
		"You used to be a mercenary, and a pretty good one at that. A year prior to your~"
		"suspension you had secured a position working for the ITPA, the International~"
		"Terrorism Prevention Agency. During your time you did well for yourself and earned~"
		"yourself great recognision within the agency for your services.~~"
		"Press Enter to continue...");
}

IntroState::~IntroState()
{
	delete monoFont;
	delete introText;
	delete introSounds;
}

void IntroState::Update()
{
	if (input->WasKeyPressed(SDL_SCANCODE_RETURN)) { //ENTER to progress and enter
		exit = true; 
		GS_Manager->ChangeState(new InGame(renderer, input, GS_Manager));
	}

	introText->Type();
}