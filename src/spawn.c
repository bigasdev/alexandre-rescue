#include "../srch/structs.h"
#include "../srch/spawn.h"
#include "../srch/draw.h"
#include "../srch/hero.h"
#include <stdio.h>
#include <stdlib.h>

Entity *filaE = NULL;
Entity *filaM = NULL;
Entity *filaF = NULL;

Entity *r = NULL;
Entity baseEntityE;
Entity baseEntityM;
Entity baseEntityF;

Entity entities[3];

int limitE, limitM, limitF;

int collisionBox[] = {40,30};

void addEntity(Entity **spawn, int spn){
    printf("\nAdding a new entity for x: %i the entity X is: %i", spn, entities[spn].x);
    Entity *aux, *entity = malloc(sizeof(Entity));
    if(entity){
        entity->x = entities[spn].x;
        entity->y = entities[spn].y;
        entity->moveSpeed = entities[spn].moveSpeed;
        entity->health = entities[spn].health;
        entity->texture = entities[spn].texture;
        entity->next = NULL;
        
        // Caso a fila esteja NULL a gente vai iniciar ela com a entity criada como objeto
        if(*spawn == NULL){
          *spawn = entity;  
        }else{
            // Caso contrario a gente vai utilizar como auxiliar o objeto que estava armazenado no next;
            aux = *spawn;
            while(aux->next){
                aux = aux->next;
                // A gente vai entao pegar o next do auxiliar e assignar com a entity que criamos
            }
            aux->next = entity;
        }
        
    
    }else{
        // Caso nao seja possivel criar o entity a gente printa um erro de alolcacao de memoria
        printf("Erro de alocacao de memoria");
    }
}

Entity* removeEntity(Entity **spawn){
    Entity *remover = NULL;
    if(*spawn){
        //Se nao estiver null a gente vai remover o next
        remover = *spawn;
        //*spawn = remover->next;
    }else{
        //increase = 48;
        printf("Fila vazia!");
    }
    return remover;
}

void spawnRemove(int spn){
    switch(spn){
        case 0:
                r = removeEntity(&filaE);
                if(r){
                    r->moveSpeed = 6;
                    /*increase -= 18;
                    printf("\n Removed memory for the first entity, the x is now at: %i", increase);
                    free(r);*/
                }
            break;
        case 1:
                r = removeEntity(&filaM);
                if(r){
                    r->moveSpeed = 6;
                    /*increase -= 18;
                    printf("\n Removed memory for the first entity, the x is now at: %i", increase);
                    free(r);*/
                }
            break;
        case 2:
                r = removeEntity(&filaF);
                if(r){
                    r->moveSpeed = 6;
                    /*increase -= 18;
                    printf("\n Removed memory for the first entity, the x is now at: %i", increase);
                    free(r);*/
                }
            break;
    }
}
void removeSpawn(Entity **spawn, int spn){
    Entity *remo = NULL;
    if(*spawn){
        remo = *spawn;
        *spawn = remo->next;
        spawnRemove(spn);
    }
}

void instaRemove(){
    Entity *remo = NULL;
    int r = rand() % 3;
    switch(r){
        case 0:
            removeSpawn(&filaE, r);
            break;
        case 1:
            removeSpawn(&filaM, r);
            break;
        case 2:
            removeSpawn(&filaF, r);
            break;
    }
    /*if(*spawn){
        remo = *spawn;
        *spawn = remo->next;
        spawnRemove();
    }*/
}

void readEntities(Entity **spawn){
    Entity *aux, *entity = NULL;
    if(*spawn){
        aux = *spawn;
        //printf("\n Entity na posicao X: %d e posicao Y: %d", aux->x, aux->y);
        //this is used to draw with an atlas:
        if(aux->moveSpeed != 0){
            if(aux->x + collisionBox[0] >= Hero.x && aux->x <= (Hero.x + 20) &&
               aux->y + collisionBox[1] >= Hero.y && aux->y <= (Hero.y + 20)){
                instaRemove();
                printf("\n Collided!");
            }
            aux->y += aux->moveSpeed;
        }
        if(aux->y >= (app.w_Y - 5)){
            instaRemove();
        }
        blitAtlas(aux->texture, 22, 19, 1, 0, 2, aux->x, aux->y, 0);
        //normal blit
        //blit(aux->texture, 1, aux->x, aux->y, 0);
        entity = aux->next;
        readEntities(&entity);
    }
}

void add(){
    addEntity(&filaE, 0);
    addEntity(&filaM, 1);
    addEntity(&filaF, 2);
    /*increase += 30;
    if(increase >= (app.w_X)){
        increase = 30;
        yIncrease += 30;
    }*/
}

void initSpawn(){
    baseEntityF.x = app.w_X - 64;
    baseEntityF.y = 0;
    baseEntityF.moveSpeed = 0;
    baseEntityF.health = 10;
    baseEntityF.texture = loadTexture("resources/sprites/atlas.png");

    baseEntityE = baseEntityF;
    baseEntityE.x = 16;

    baseEntityM = baseEntityF;
    baseEntityM.x= app.w_X/2;

    entities[0] = baseEntityE;
    entities[1] = baseEntityM;
    entities[2] = baseEntityF;

    for (size_t i = 0; i < 5; i++)
    {
        /* code */  
        add();
    }
    
}

void readSpawn(){
    readEntities(&filaE);
    readEntities(&filaM);
    readEntities(&filaF);
}
