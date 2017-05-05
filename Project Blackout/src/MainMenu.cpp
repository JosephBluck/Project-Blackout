#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* rendererInput, InputManager* _input, GameStateManager* manager) :
	GameState(manager, rendererInput)
{
	initSuccess = false;
	timer = 0;
	exit = false;

	input = _input; //Assign input manager for keyboard controls

	stateName = "Main Menu";

	if (!InitMenu())
	{
		exit = true;
	}
}

MainMenu::~MainMenu()
{
	//If initialisation succeeded, remove loaded assets on closing
	if (initSuccess) {
		delete title1;
		delete title2;
		delete flash;
		delete particle;
		delete backGlow;

		delete newGameButton;
		delete loadGameButton;
		delete optionsButton;
		delete exitButton;
		delete cursorSprite;
		delete  menuSounds;
		delete monoFont;
		delete textTest;
	}
}

//Initialise all objects the menu uses
bool MainMenu::InitMenu()
{
	//Main Visuals
	title1 = new Sprite(renderer, "resources\\sprites\\mainmenu\\title1.png", 2000, 0, 550, 200);
	title2 = new Sprite(renderer, "resources\\sprites\\mainmenu\\title2.png", 2000, 0, 670, 200);
	flash = new Sprite(renderer, "resources\\sprites\\mainmenu\\flash.png", 3000, 0, 1280, 1280);
	flash->SetSize(20, 20);
	particle = new Sprite(renderer, "resources\\sprites\\mainmenu\\menuparticle.png", 4000, 0, 24, 24);
	backGlow = new Sprite(renderer, "resources\\sprites\\mainmenu\\redglow.png", 0, 720, 1280, 360);

	//BUTTONS
	newGameButton = new Sprite(renderer, "resources\\sprites\\mainmenu\\newgame.png", 1000, 0, 420, 100);
	loadGameButton = new Sprite(renderer, "resources\\sprites\\mainmenu\\Loadgame.png", 1000, 0, 440, 100);
	optionsButton = new Sprite(renderer, "resources\\sprites\\mainmenu\\Options.png", 1000, 0, 305, 100);
	exitButton = new Sprite(renderer, "resources\\sprites\\mainmenu\\Exit.png", 1000, 0, 400, 100);

	cursorSprite = new Sprite(renderer, "resources\\sprites\\mainmenu\\cursor.png", 1000, 0, 50, 100); //CURSOR

	//SOUNDS
	menuSounds = new SoundManager(4, "resources\\sounds\\mainmenu\\zapper.mp3");
	menuSounds->LoadSound(0, "resources\\sounds\\mainmenu\\select.wav");
	menuSounds->LoadSound(1, "resources\\sounds\\mainmenu\\dropping.wav");
	menuSounds->LoadSound(2, "resources\\sounds\\mainmenu\\explosion.wav");
	menuSounds->LoadSound(3, "resources\\sounds\\mainmenu\\Begin.wav");

	//TEXT TESTING DEBUG

	//If assets haven't loaded, delete everything and return false on initialisation
	if (!title1->isValid || !title2->isValid || !flash->isValid) {
		std::cout << "Main menu failed to initialise!" << "\n";
		delete title1;
		delete title2;
		delete flash;
		delete particle;
		delete backGlow;

		delete newGameButton;
		delete loadGameButton;
		delete optionsButton;
		delete exitButton;
		delete cursorSprite;

		delete menuSounds;

		return false;
	}

	//TEXT TESTING
	monoFont = new AnimSprite(renderer, "resources\\sprites\\text\\monofonto.png", 0, 0, 1222, 213, 26, 3);
	textTest = new TextSprite(renderer, monoFont, 50, 50);
	textTest->SetText("Ok, so get this... we now got NUMBE- and I mean like 123456789 of them c:");
	monoFont->SetSize(15, 20);

	menuSounds->PlaySound(1);
	initSuccess = true; //Success
	return true;
}

//MENU UPDATING
void MainMenu::Update()
{
	timer++; //CORE TIMER
	
	if (timer > 360) { //Backglow effect
		backGlow->Draw(0, 540 + (sin(timer * 0.02) * 120));
	}

	if (timer < 450) {
		Intro();
	}
	else if (!startGame) {
		MenuIdle();
	}

	//TEXT TESTING
	textTest->Draw();
}

void MainMenu::Intro() //Intro cinematic
{
	//Intro
	if (timer < 120) { //"Bomb" drops
		flash->Draw(630, (680.0f / 120.0f) * timer);
	}
	else if (timer < 180) { //Bomb explosion and screen turns to white
		int scale = (timer - 120) * 40;
		int flashColour = (255.0f / 60.0f) * (timer - 120);
		flash->SetSize(scale, scale);
		flash->Draw(630 - (scale / 2), 680 - (scale / 2));
		SDL_SetRenderDrawColor(renderer, flashColour, flashColour, flashColour, 0);
	}
	else if (timer < 240) {
		//DELAY
	}
	else if (timer < 300) { //Flash fades out
		int flashColour = 255 - ((255.0f / 60.0f) * (timer - 240));
		SDL_SetRenderDrawColor(renderer, flashColour, flashColour, flashColour, 0);
	}
	else if (timer < 360) { //TITLE APPEARS!
		title1->Draw(1280 - ((timer - 300) * 15), 20);
	}
	else if (timer < 420) {
		title1->Draw(380, 20);
		title2->Draw(1280 - ((timer - 360) * 16), 180);
	}
	else if (timer < 450) { //Buttons appear on screen
		newGameButton->Draw(200, 720 - ((timer - 420) * (370 / 30)));
		loadGameButton->Draw(650, 720 - ((timer - 420) * (370 / 30)));
		optionsButton->Draw(200, 720 - ((timer - 420) * (270 / 30)));
		exitButton->Draw(650, 720 - ((timer - 420) * (270 / 30)));
	}

	if (timer >= 420) {
		title1->Draw(380, 20);
		title2->Draw(320, 180);
	}

	//SOUNDS
	if (timer == 120) { //Explosion
		menuSounds->PlaySound(2);
	}
	if (timer == 300) { //Music
		menuSounds->PlayBGM(-1);
	}

}

//MOUSE CHECKING
void MainMenu::MouseInput()
{
	mouseState = SDL_GetMouseState(&mouseX, &mouseY); //Get the current position of the cursor and button state

	//SDL_PumpEvents();
	if ((mouseX > 200 && mouseX < 620) && (mouseY > 350 && mouseY < 450)) { //New Game Button
		cursorSprite->Draw(155 - abs((sin(timer * 0.04) * 15)), 350, SDL_FLIP_NONE);
		hover = 0;
	}
	else if ((mouseX > 200 && mouseX < 620) && (mouseY > 450 && mouseY < 550)) { //Options Button
		cursorSprite->Draw(155 - abs((sin(timer * 0.04) * 15)), 450, SDL_FLIP_NONE);
		hover = 2;
	}
	else if ((mouseX > 650 && mouseX < 1090) && (mouseY > 350 && mouseY < 450)) { //Load game button
		cursorSprite->Draw(1090 + abs((sin(timer * 0.04) * 15)), 350, SDL_FLIP_HORIZONTAL);
		hover = 3;
	}
	else if ((mouseX > 650 && mouseX < 1090) && (mouseY > 450 && mouseY < 550)) { //Exit game button
		cursorSprite->Draw(1090 + abs((sin(timer * 0.04) * 15)), 450, SDL_FLIP_HORIZONTAL);
		hover = 4;

		if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) || input->keys[SDL_SCANCODE_RETURN]) { //Check for Click
			exit = true;
		}
	}
	else {
		hover = 0;
		deltaHover = 0;
	}

	if (hover != deltaHover) {
		deltaHover = hover;
		menuSounds->PlaySound(0);
	}
}

//Menu when it is idle
void MainMenu::MenuIdle()
{
	MouseInput();

	if (timer % 2 == 0) { //GENERATE NEW MENU PARTICLES
		int randSize = 16 + (rand() % 9);
		menuParticles.push_back(new FloatParticle(particle, rand() % 1260, 720, randSize, randSize, 0, -1 - (rand() % 2), 60, 30));
		menuParticles.push_back(new FloatParticle(particle, rand() % 1260, 720, randSize, randSize, 0, -1 - (rand() % 2), 60, 30));
	}

	for (int i = 0; i < menuParticles.size(); i++) { //UPDATE ALL PARTICLES
		if (!menuParticles[i]->isExpired) {
			menuParticles[i]->Update();
		}
		else {
			delete menuParticles[i];
			menuParticles[i] = nullptr;
		}
	}

	//Clear out expired particles
	menuParticles.erase(std::remove(menuParticles.begin(), menuParticles.end(), nullptr), menuParticles.end());

	title1->Draw(380, 20);
	title2->Draw(320, 180);
	newGameButton->Draw(200, 350);
	loadGameButton->Draw(650, 350);
	optionsButton->Draw(200, 450);
	exitButton->Draw(650, 450);
}