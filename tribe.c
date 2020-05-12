
#include "tribe.h"
#include <assert.h>

#define NO_VOTES 0
#define MAX_DIGITS_INT 12
#define ILLEGAL_VOTES -1
#define INVALID_TRIBE_ID -1

struct node_t{

    int tribe_id;
    int number_of_tribe_votes;
    struct node_t *next;

};


TribeResult setNumberOfVotes(Tribe tribe, int number_of_votes_new, bool add){

    if (number_of_votes_new<=0){
        return TRIBE_INVALID_VOTES;
    }

    if (!tribe){
        return TRIBE_NULL_ARGUMENT;
    }

    if (add){
        tribe->number_of_tribe_votes += number_of_votes_new;
    }else{
        tribe->number_of_tribe_votes -= number_of_votes_new;
        if (tribe->number_of_tribe_votes<0){
            tribe->number_of_tribe_votes = 0;
        }
    }

    return TRIBE_SUCCESS;
}

TribeResult deleteNextTribe(Tribe current_tribe){

    if (current_tribe == NULL){
        return TRIBE_NULL_ARGUMENT;
    }
    Tribe to_delete = current_tribe->next;
    current_tribe->next = to_delete->next;
    free(to_delete);

    return TRIBE_SUCCESS;
}

TribeResult addNextTribe (Tribe current_tribe, int tribe_id, int number_of_votes){
    if (!current_tribe){
        return TRIBE_NULL_ARGUMENT;
    }
    current_tribe->next = createTribe(tribe_id, number_of_votes);
    if (!current_tribe->next){
        return TRIBE_OUT_OF_MEMORY;
    }
    return TRIBE_SUCCESS;
}

TribeResult setNextTribe (Tribe current_tribe, Tribe next_tribe){

    if (!current_tribe || !next_tribe){
        return TRIBE_NULL_ARGUMENT;
    }

    current_tribe->next = next_tribe;
    return TRIBE_SUCCESS;
}

Tribe getNextTribe (Tribe current_tribe){

    if (current_tribe == NULL){
        return NULL;
    }

    return current_tribe->next;
}

int getTribeId(Tribe tribe){

    if(tribe == NULL){
        return INVALID_TRIBE_ID;
    }
    return tribe->tribe_id;
}

int getNumberOfVotes(Tribe tribe){

    if (tribe == NULL){
       return ILLEGAL_VOTES;
    }
    return tribe->number_of_tribe_votes;
}

TribeResult destroyTribeList(Tribe first){

    if (!first){
        return TRIBE_NULL_ARGUMENT;
    }

    while (first){
        Tribe temp = first;
        first = first->next;
        free(temp);
    }

    return TRIBE_SUCCESS;
}

Tribe createTribe(int tribe_id, int number_of_tribe_votes){

    Tribe new = malloc(sizeof(*new));
    if (new == NULL){
        return NULL;
    }

    new->tribe_id = tribe_id;
    new->number_of_tribe_votes = number_of_tribe_votes;
    new->next = NULL;

    return new;
}


bool validNameTribe(const char* tribe_name){

    int i=0;

    while (tribe_name[i]){
        if ((tribe_name[i]<'a' || tribe_name[i]>'z') && tribe_name[i]!=' '){
            return false;
        }
        i++;
    }
    return true;
}

TribeResult deleteFirstTribe(Tribe current_tribe){

    if (!current_tribe){
        return TRIBE_NULL_ARGUMENT;
    }

    free(current_tribe);

    return TRIBE_SUCCESS;
}


