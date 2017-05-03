#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* rendererInput)
{
	initSuccess = false;
	renderer = rendererInput;
	timer = 0;
}

MainMenu::~MainMenu()
{
	//If initialisation succeeded, remove loaded assets
	if (initSuccess) {
		delete title1;
		delete title2;
		delete flash;
		delete particle;
		delete backGlow;
	}
}

//Initialise all objects the menu uses
bool MainMenu::InitMenu()
{
	title1 = new Sprite(renderer, "resources\\sprites\\mainmenu\\title1.png", 2000, 0, 550, 200);
	title2 = new Sprite(renderer, "resources\\sprites\\mainmenu\\title2.png", 2000, 0, 670, 200);
	flash = new Sprite(renderer, "resources\\sprites\\mainmenu\\flash.png", 3000, 0, 1280, 1280);
	flash->SetSize(20, 20);
	particle = new Sprite(renderer, "resources\\sprites\\mainmenu\\menuparticle.png", 4000, 0, 24, 24);
	backGlow = new Sprite(renderer, "resources\\sprites\\mainmenu\\redglow.png", 0, 720, 1280, 360);

	//BUTTONS
	newGameButton = new Sprite(renderer, "resources\\spriates\\mainmenu\\newgame.png", 1000, 0, 420, 100);


	if (!title1->isValid || !title2->isValid || !flash->isValid) {
		std::cout << "Main menu failed to initialise!" << "\n";
		delete title1;
		delete title2;
		delete flash;
		delete particle;
		delete backGlow;
		delete newGameButton;
		delete newGameButton;

		return false;
	}

	initSuccess = true;
	return true;
}

//MENU UPDATING
void MainMenu::Update()
{
	timer++;
	if (timer > 300) {
		backGlow->Draw(0, 540 + (sin(timer * 0.02) * 120));
	}

	if (timer < 420) {
		Intro();
	}
	else {
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
	}

}

void MainMenu::Intro()
{
	//Intro
	if (timer < 120) {
		flash->Draw(630, (680.0f / 120.0f) * timer);
	}
	else if (timer < 180) {
		int scale = (timer - 120) * 40;
		int flashColour = (255.0f / 60.0f) * (timer - 120);
		flash->SetSize(scale, scale);
		flash->Draw(630 - (scale / 2), 680 - (scale / 2));
		SDL_SetRenderDrawColor(renderer, flashColour, flashColour, flashColour, 0);
	}
	else if (timer < 240) {
		//DELAY
	}
	else if (timer < 300) {
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


}