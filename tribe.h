#ifndef TRIBE_H_
#define TRIBE_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//TODO: enum_result

typedef struct node_t* Tribe;

typedef enum TribeResult_t {
    TRIBE_OUT_OF_MEMORY,
    TRIBE_NULL_ARGUMENT,
    TRIBE_SUCCESS

} TribeResult;

TribeResult setNumberOfVotes(Tribe tribe, int number_of_votes_new, bool add);

void setTribeId(Tribe tribe, int tribe_id_new);

int getTribeId(Tribe tribe);

int getNumberOfVotes(Tribe tribe);

TribeResult deleteNextTribe(Tribe current_tribe);

TribeResult addNextTribe (Tribe current_tribe, int tribe_id, int number_of_votes);

TribeResult setNextTribe (Tribe current_tribe, Tribe next_tribe);

Tribe getNextTribe (Tribe current_tribe);

TribeResult destroyTribeList(Tribe first);

Tribe createTribe(int tribe_id, int number_of_tribe_votes);

bool validNameTribe(const char* tribe_name);

#endif /* TRIBE_H_ */



