#include "../srch/structs.h"
#include "../srch/spawn.h"
#include "../srch/draw.h"
#include <stdio.h>
#include <stdlib.h>

Entity *fila = NULL;
Entity *r = NULL;
Entity baseEntity;
int increase = 16;
int yIncrease = 16;

void addEntity(Entity **spawn){
    printf("\nAdding a new entity with a x: %i", increase);
    Entity *aux, *entity = malloc(sizeof(Entity));
    if(entity){
        entity->x = baseEntity.x - increase;
        entity->y = baseEntity.y + yIncrease;
        entity->moveSpeed = baseEntity.moveSpeed;
        entity->health = baseEntity.health;
        entity->texture = baseEntity.texture;
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
        increase = 48;
        printf("Fila vazia!");
    }
    return remover;
}

void spawnRemove(){
    r = removeEntity(&fila);
    if(r){
        r->moveSpeed = 6;
        /*increase -= 18;
        printf("\n Removed memory for the first entity, the x is now at: %i", increase);
        free(r);*/
    }
}

void instaRemove(Entity **spawn){
    Entity *remo = NULL;
    if(*spawn){
        remo = *spawn;
        *spawn = remo->next;
        spawnRemove();
    }
}

void readEntities(Entity **spawn){
    Entity *aux, *entity = NULL;
    if(*spawn){
        aux = *spawn;
        //printf("\n Entity na posicao X: %d e posicao Y: %d", aux->x, aux->y);
        //this is used to draw with an atlas:
        if(aux->moveSpeed != 0){
            aux->y += aux->moveSpeed;
        }
        if(aux->y >= (app.w_Y - 32)){
            instaRemove(&fila);
        }
        blitAtlas(aux->texture, 8, 8, 0, 2, 2, aux->x, aux->y, 0);
        //normal blit
        //blit(aux->texture, 1, aux->x, aux->y, 0);
        entity = aux->next;
        readEntities(&entity);
    }
}

void add(){
    addEntity(&fila);
    increase += 18;
    if(increase >= (app.w_X)){
        increase = 16;
        yIncrease += 16;
    }
}

void initSpawn(){
    baseEntity.x = app.w_X;
    baseEntity.y = 0;
    baseEntity.moveSpeed = 0;
    baseEntity.health = 10;
    baseEntity.texture = loadTexture("resources/sprites/atlas.png");
    for (size_t i = 0; i < 140; i++)
    {
        /* code */  
        add();
    }
    
}

void readSpawn(){
    readEntities(&fila);
}
