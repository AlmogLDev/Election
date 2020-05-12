#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "map.h"

#define  GO_TO_FIRST_ELEMENT\
    while (map->info->previous){\
        map->info = map->info->previous;\
    }

#define FAIL -1


typedef struct node{
    char* key;
    char* value;
    struct node* next;
    struct node* previous;

}*Node;


struct Map_t{

    Node iterator;
    Node info;

};

static Node createNode(){

    Node new = malloc(sizeof(*new));
    if (!new){
        return NULL;
    }

    new->key = NULL;
    new->value = NULL;
    new->previous = NULL;
    new->next = NULL;

    return new;
}

static void initializeMapInfo(Node info){

    free (info->key);
    free (info->value);
    info->key = NULL;
    info->value = NULL;
    info->next = NULL;
    info->previous = NULL;
}

char* mapGetNext(Map map){

    if (!map){
        return NULL;
    }

    if (!map->iterator->next){
        return NULL;
    }

    map->iterator = map->iterator->next;

    return map->iterator->key;
}


void mapDestroy(Map map){

    if (!map){
        return;
    }

    GO_TO_FIRST_ELEMENT

    Node temp = NULL;

    while (map->info){
        temp = map->info;
        free(map->info->key);
        free(map->info->value);
        map->info = map->info->next;
        free(temp);
    }

    free(map);
}

Map mapCreate(){

    Map new_map = malloc(sizeof(*new_map));
    if (!new_map){
        return NULL;
    }

    new_map->info = createNode();
    if (!new_map->info){
        free(new_map);
        return NULL;
    }
    new_map->iterator = new_map->info;

    return new_map;
}

Map mapCopy(Map map){

    if (!map){
        return NULL;
    }

    Map new_map = mapCreate();
    if (!new_map){
        return NULL;
    }

    GO_TO_FIRST_ELEMENT

    assert(map->info != NULL);
    while (map->info){
        if (mapPut(new_map, map->info->key, map->info->value) != MAP_SUCCESS){
            mapDestroy(new_map);
            return NULL;
        }

        if(map->info->next){
            map->info = map->info->next;
        }else{
            break;
        }
    }

    return new_map;
}

char* mapGet(Map map, const char* key){

    if (!map || !key){
        return NULL;
    }

    assert(map->info != NULL);
    GO_TO_FIRST_ELEMENT

    Node temp = map->info;
    while (temp){
        if (!strcmp(temp->key, key)){
            return (temp->value);
        }
        temp = temp->next;

    }

    return NULL;
}

MapResult mapPut(Map map, const char* key, const char* data){

    if (!map || !key || !data){
        return MAP_NULL_ARGUMENT;
    }

    GO_TO_FIRST_ELEMENT

    if (!map->info->key){
        map->info->key = malloc(sizeof(*key)*strlen(key)+1);
        if (!map->info->key) {
            return MAP_OUT_OF_MEMORY;
        }

        map->info->value = malloc(sizeof(*data)*strlen(data)+1);
        if (!map->info->value) {
            free(map->info->key);
            return MAP_OUT_OF_MEMORY;
        }

        strcpy(map->info->key, key);
        strcpy(map->info->value, data);

        return MAP_SUCCESS;
    }

    while (map->info->next){

        if (!strcmp(map->info->key, key)){
            free(map->info->value);
            map->info->value = malloc(sizeof(*data)*strlen(data)+1);
            if (!map->info->value) {
                free(map->info->key);
                return MAP_OUT_OF_MEMORY;
            }
            strcpy(map->info->value, data);
            return MAP_SUCCESS;
        }
        map->info = map->info->next;
    }

    if (!strcmp(map->info->key, key)){
        free(map->info->value);
        map->info->value = malloc(sizeof(*data)*strlen(data)+1);
        if (!map->info->value) {
            free(map->info->key);
            return MAP_OUT_OF_MEMORY;
        }
        strcpy(map->info->value, data);
        return MAP_SUCCESS;
    }


    Node new = createNode();
    if (!new){
        return MAP_OUT_OF_MEMORY;
    }

    new->key = malloc(sizeof(*key)*strlen(key)+1);
    if (!new->key) {
        free(new);
        return MAP_OUT_OF_MEMORY;
    }

    new->value = malloc(sizeof(*data)*strlen(data)+1);
    if (!new->value) {
        free(new->key);
        free(new);
        return MAP_OUT_OF_MEMORY;
    }

    new->previous = map->info;
    map->info->next = new;

    strcpy(new->key, key);
    strcpy(new->value, data);

    return MAP_SUCCESS;
}


char* mapGetFirst(Map map){

    GO_TO_FIRST_ELEMENT

    map->iterator = map->info;
    return map->info->key;
}

int mapGetSize(Map map){

    if (!map){
        return FAIL;
    }
    assert(map->info != NULL);

    if(!map->info->key){
        return 0;
    }
    int counter = 1;

    GO_TO_FIRST_ELEMENT

    while (map->info->next){
        counter++;
        map->info = map->info->next;
    }


    return counter;
}

bool mapContains(Map map, const char* key){

    if (!map || !key){
        return false;
    }


    GO_TO_FIRST_ELEMENT


    while (map->info->next){

        if (!strcmp((map->info)->key,key)){
            return true;
        }
        map->info = map->info->next;

    }
    if (map->info && map->info->key){
        if (!strcmp((map->info)->key,key)){
            return true;
        }
    }

    return false;
}

MapResult mapRemove(Map map, const char* key){

    if (!map || !key){
        return MAP_NULL_ARGUMENT;
    }

    GO_TO_FIRST_ELEMENT

    while (map->info && map->info->key){

        if (!strcmp(map->info->key , key)){

            if (!map->info->previous){ // first key
                if (!map->info->next){
                    initializeMapInfo(map->info);
                    return MAP_SUCCESS;
                }
                Node temp = map->info->next;
                temp->previous = NULL;
                free (map->info->key);
                free (map->info->value);
                free (map->info);
                map->info = temp;
                map->iterator = map->info;
                return MAP_SUCCESS;

            }else{
                Node temp = map->info->previous;
                temp->next = map->info->next;
                if (temp->next){
                    temp->next->previous = temp;
                }
                free (map->info->key);
                free (map->info->value);
                free(map->info);
                map->iterator = temp;
                map->info = temp;
                return MAP_SUCCESS;
            }

        }
        if (map->info->next){
            map->info = map->info->next;
        }else{
            break;
        }


    }


    return MAP_ITEM_DOES_NOT_EXIST;
}

MapResult mapClear(Map map){

    if (!map){
        return MAP_NULL_ARGUMENT;
    }

    GO_TO_FIRST_ELEMENT

    if (!map->info->next){
        initializeMapInfo(map->info);
        return MAP_SUCCESS;
    }

    map->info = map->info->next;
    initializeMapInfo(map->info->previous);
    Node first = map->info->previous;

    Node temp = NULL;

    while (map->info){
        temp = map->info;
        map->info = map->info->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
    map->info = first;
    map->iterator = map->info;

    return MAP_SUCCESS;
}