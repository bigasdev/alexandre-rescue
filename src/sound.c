#include "../srch/include/SDL2/SDL.h"
#include "../srch/include/SDL2/SDL_mixer.h"
#include "../srch/defs.h"
#include "../srch/sound.h"
#include <stdio.h>
#include <string.h>

Mix_Chunk* sounds[4];

void loadSounds(void){
    sounds[SND_SPLASH] = Mix_LoadWAV("resources/sounds/pickupCoin.ogg");
    sounds[SND_PLAYER_COLLECT] = Mix_LoadWAV("resources/sounds/collect.ogg");
    sounds[SND_FILA_REMOVE] = Mix_LoadWAV("resources/sounds/remove.ogg");
    sounds[SND_PLAYER_FAIL] = Mix_LoadWAV("resources/sounds/fail.ogg");
}

void initSound(){
    memset(sounds, 0, sizeof(Mix_Chunk*) * 4);

    loadSounds();
}

void playSound(int id, int channel){
    Mix_PlayChannel(channel, sounds[id], 0);
}
