#define SDL_MAIN_HANDLED

#include "../srch/include/SDL2/SDL.h"
#include "../srch/init.h"
#include "../srch/draw.h"
#include "../srch/spawn.h"
#include "../srch/defs.h"
#include "../srch/splash.h"
#include "../srch/input.h"
#include "../srch/structs.h"
#include "../srch/hero.h"
#include "../srch/sound.h"
#include <stdio.h>
#include <string.h>

Entity storyEntity;

void cleanup(){

}

void start(){
	memset(&app, 0, sizeof(App));
    memset(&Hero, 0, sizeof(Entity));
	memset(&storyEntity, 0, sizeof(Entity));
#if SPLASH
	memset(&splash, 0, sizeof(UI_Entity));
	splashState = 0;
#endif

	initSDL();
	initSpawn();
	initSound();
	atexit(cleanup);

	createHero();
	storyEntity.texture = loadTexture("resources/intro.png");
	storyEntity.y = app.w_Y;
	storyEntity.x = (app.w_X/2)+300;
	storyEntity.moveSpeed = 1;

#if SPLASH
	initSplash();
#endif
}


int main(int argc, char *argv[]){
	start();

	//splash screen loop
#if SPLASH
	while(!splashState)
	{
		prepareScene();

		doInput();

		splashInput();

		blit(splash.texture, 4, 0, 0, 1, 1);

		presentScene();

		SDL_Delay(32);
	}
	//playSound(0, 0);
#endif
	while(storyEntity.y >= app.w_Y/5){
		prepareScene();

		doInput();

		blit(storyEntity.texture, 4, storyEntity.x, storyEntity.y, 0, 1);
		storyEntity.y -= storyEntity.moveSpeed;

		presentScene();


		SDL_Delay(32);
	}
	
	//main loop
	while (1)
	{
        
		prepareScene();

		doInput();

		playerInputs();

		animatePlayer();
        blit(Hero.texture, 3, Hero.x, Hero.y, 0, 0);
		readSpawn();

		presentScene();


		SDL_Delay(16);
	}

	return 0;
}
