#include "../srch/include/SDL2/SDL.h"
#include "../srch/draw.h"
#include <stdio.h>
#include <inttypes.h>
#include "../srch/spawn.h"
#include "../srch/structs.h"
#include "../srch/hero.h"


Entity Hero;
int idleAnim = 0;
int interacted = 0;
//our main thread runs at 16ms, so we can use this to multiply for the cd i.e 16x2 = 32ms
int i_cooldown = 0;
//cd for the interaction
int int_cd = 16;

int jumped = 0;
//our main thread runs at 16ms, so we can use this to multiply for the cd i.e 16x2 = 32ms
int j_cooldown = 0;
//cd for the interaction
int jump_cd = 16;

//constraints
int limitX, limitY;

void createHero(void){
    Hero.x = app.w_X/2;
    Hero.y = app.w_Y-48;
    Hero.moveSpeed = 18;
    Hero.framesCount = 1;
    Hero.health = 10;
    Hero.texture = loadTexture("resources/sprites/turboC.png");

    limitX = app.w_X;
    limitY = app.w_Y;
    //Hero.frames[0] = loadTexture("resources/sprites/player.png");
    //Hero.frames[1] = loadTexture("resources/sprites/player1.png");
    //hero = &_hero;
}

void animatePlayer(){
    Uint32 ticks = SDL_GetTicks();
    Uint32 sprite = (ticks / 300) % Hero.framesCount;
    Hero.currentFrame = sprite;
    //Hero.texture = Hero.frames[sprite];
}

void cd(){
    if(interacted){
        i_cooldown++;
        if(i_cooldown >= int_cd){
            interacted = 0;
        }
    }   

    if(jumped){
        j_cooldown++;
        if(j_cooldown >= jump_cd){
            jumped = 0;
        }
    }
}

void debug(){
    printf("\n Size of the scren: X%i Y%i", app.w_X, app.w_Y);
}


void interact(){
    if(interacted)return;
    interacted = 1;
    i_cooldown = 0;
    printf("\n Player trying to interact");
#if DEMO
    debug();
#endif
    //add();
}

void jump(){
    if(jumped)return;
    jumped = 1;
    j_cooldown = 0;
    printf("\n Starting game!");
    for(int i = 0; i < 3; i++){
        spawnRemove(i);
    }
}

void playerInputs(){
    /*if(app.up){
        if(Hero.y <= 0)return;
        Hero.y -= Hero.moveSpeed;
    }
    if(app.down){
        if(Hero.y >= app.w_Y-16)return;
        Hero.y += Hero.moveSpeed;
    }*/
    if(app.right){
        if(Hero.x >= app.w_X-16)return;
        Hero.x += Hero.moveSpeed;
    }
    if(app.left){
        if(Hero.x <= 0)return;
        Hero.x -= Hero.moveSpeed;
    }
    if(app.interacted){
        interact();
    }
    if(app.jump){
        jump();
    }
    /*if(app.up && app.right || app.up && app.left || app.down && app.right || app.down && app.left){
        Hero.slowed = true;
    }else{
        Hero.slowed = false;
    }*/
    cd();
}