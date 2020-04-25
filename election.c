#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "election.h"
#include "area.h"


#define MAX_DIGITS_INT 10


struct election_t{

    Map tribes;
    Map areas;
    Area area_votes;

};


Election electionCreate(){

    Election new_election = malloc (sizeof(*new_election));
    if (!new_election){
        return NULL;
    }

    new_election->tribes = mapCreate();
    if (!new_election->tribes){
        return NULL;
    }
    new_election->areas = mapCreate();
    if (!new_election->areas){
        mapDestroy(new_election->tribes);
        return NULL;
    }
    new_election->area_votes = NULL;

    return new_election;
}

void electionDestroy(Election election){

    if(!election){
        return;
    }
    mapDestroy(election->areas);
    mapDestroy(election->tribes);
    destroyAreaList(election->area_votes);
    free(election);

}

ElectionResult electionAddTribe (Election election, int tribe_id, const char* tribe_name){

    if (!election || !tribe_name){
        return ELECTION_NULL_ARGUMENT;
    }
    if (tribe_id<0){
        return ELECTION_INVALID_ID;
    }

    char tribe_id_new[MAX_DIGITS_INT] = "" ;
    sprintf(tribe_id_new, "%d", tribe_id);

    if (mapContains(election->tribes, tribe_id_new)){
        return ELECTION_TRIBE_ALREADY_EXIST;
    }

    if (!validNameTribe(tribe_name)){
        return ELECTION_INVALID_NAME;
    }

   if (mapPut(election->tribes, tribe_id_new, tribe_name) != MAP_SUCCESS){
       electionDestroy(election);
       return ELECTION_OUT_OF_MEMORY;
   }

   AreaResult result = addTribe(election->area_votes, tribe_id);
   if (result == AREA_OUT_OF_MEMORY){
       return ELECTION_OUT_OF_MEMORY;
   }

   return ELECTION_SUCCESS;
}

ElectionResult electionAddArea(Election election, int area_id, const char* area_name){

    if (!election || !area_name){
        return ELECTION_NULL_ARGUMENT;
    }
    if (area_id<0){
        return ELECTION_INVALID_ID;
    }

    char area_id_new[MAX_DIGITS_INT] = "" ;
    sprintf(area_id_new, "%d", area_id);

    if (mapContains(election->areas, area_id_new)){
        return ELECTION_AREA_ALREADY_EXIST;
    }

    if (!validNameArea(area_name)){
        return ELECTION_INVALID_NAME;
    }

    if (mapPut(election->areas, area_id_new, area_name) != MAP_SUCCESS){
        electionDestroy(election);
        return ELECTION_OUT_OF_MEMORY;
    }
    if (!election->area_votes){
        election->area_votes = createArea(election->tribes, area_id);
        if (!election->area_votes){
            return ELECTION_OUT_OF_MEMORY;
        }
    }else{

        AreaResult result = addArea(election->area_votes, election->tribes, area_id);
        if (result == AREA_NULL_ARGUMENT){
            return ELECTION_NULL_ARGUMENT;
        }else if (result == AREA_OUT_OF_MEMORY){
            return ELECTION_OUT_OF_MEMORY;
        }
    }


    return ELECTION_SUCCESS;
}


char* electionGetTribeName (Election election, int tribe_id){

    if (!election || tribe_id<0){
        return NULL;
    }

    char tribe_id_new[MAX_DIGITS_INT] = "" ;
    sprintf(tribe_id_new, "%d", tribe_id);

    if (!mapContains(election->tribes, tribe_id_new)){
        return NULL;
    }
    char* temp = mapGet(election->tribes, tribe_id_new);
    char* tribe_name = malloc(sizeof(*tribe_name)*strlen(temp)+1);
    strcpy(tribe_name, temp);

    return tribe_name;
}

ElectionResult electionSetTribeName (Election election, int tribe_id, const char* tribe_name){

    if (!election || !tribe_name){
        return ELECTION_NULL_ARGUMENT;
    }
    if (tribe_id<0){
        return ELECTION_INVALID_ID;
    }

    char tribe_id_new[MAX_DIGITS_INT] = "" ;
    sprintf(tribe_id_new, "%d", tribe_id);

    if (!mapContains(election->tribes, tribe_id_new)){
        return ELECTION_TRIBE_NOT_EXIST;
    }

    if (!validNameTribe(tribe_name)){
        return ELECTION_INVALID_NAME;
    }

    if (mapPut(election->tribes, tribe_id_new, tribe_name) != MAP_SUCCESS){
        electionDestroy(election);
        return ELECTION_OUT_OF_MEMORY;
    }

    return ELECTION_SUCCESS;

}

ElectionResult electionRemoveTribe (Election election, int tribe_id){

    if (!election){
        return ELECTION_NULL_ARGUMENT;
    }
    if (tribe_id<0){
        return ELECTION_INVALID_ID;
    }

    char tribe_id_new[MAX_DIGITS_INT] = "" ;
    sprintf(tribe_id_new, "%d", tribe_id);

    if (!mapContains(election->tribes, tribe_id_new)){
        return ELECTION_TRIBE_NOT_EXIST;
    }

    removeTribe(election->area_votes, tribe_id);

    if (mapRemove(election->tribes, tribe_id_new) != MAP_SUCCESS){
        electionDestroy(election);
        return ELECTION_OUT_OF_MEMORY;
    }

    return ELECTION_SUCCESS;
}

ElectionResult electionRemoveAreas(Election election, AreaConditionFunction should_delete_area){

    if (!election){
        return ELECTION_NULL_ARGUMENT;
    }

    char* current_area = mapGetFirst(election->areas);

    while (current_area){
        int area_id = 0;
        sscanf(current_area, "%d", &area_id);

        if (should_delete_area(area_id)){
            if (mapRemove(election->areas, current_area) != MAP_SUCCESS){
                return ELECTION_OUT_OF_MEMORY;
            }
            if (mapGetSize(election->areas)==1){
                if (removeArea(&election->area_votes, area_id) != AREA_SUCCESS){
                    return ELECTION_NULL_ARGUMENT;
                }
                election->area_votes = NULL;
                return ELECTION_SUCCESS;
            }else{
                if (removeArea(&election->area_votes, area_id) != AREA_SUCCESS){
                    return ELECTION_NULL_ARGUMENT;
                }
                current_area = mapGetFirst(election->areas);
                continue;
            }

        }
        current_area = mapGetNext(election->areas);
    }

    return ELECTION_SUCCESS;
}

ElectionResult electionAddVote (Election election, int area_id, int tribe_id, int num_of_votes){

    if (!election){
        return ELECTION_NULL_ARGUMENT;
    }

    if (area_id<0 || tribe_id<0){
        return ELECTION_INVALID_ID;
    }

    if (num_of_votes<=0){
        return ELECTION_INVALID_VOTES;
    }

    char area_id_new[MAX_DIGITS_INT] = "" ;
    sprintf(area_id_new, "%d", area_id);

    if (!mapContains(election->areas, area_id_new)){
        return ELECTION_AREA_NOT_EXIST;
    }

    char tribe_id_new[MAX_DIGITS_INT] = "" ;
    sprintf(tribe_id_new, "%d", tribe_id);

    if (!mapContains(election->tribes, tribe_id_new)){
        return ELECTION_TRIBE_NOT_EXIST;
    }

    if (editTribeVotes(election->area_votes, tribe_id, area_id, num_of_votes, true) != AREA_SUCCESS){
        return ELECTION_NULL_ARGUMENT;
    }

    return ELECTION_SUCCESS;
}

ElectionResult electionRemoveVote(Election election, int area_id, int tribe_id, int num_of_votes){

    if (!election){
        return ELECTION_NULL_ARGUMENT;
    }

    if (area_id<0 || tribe_id<0){
        return ELECTION_INVALID_ID;
    }

    if (num_of_votes<=0){
        return ELECTION_INVALID_VOTES;
    }

    char area_id_new[MAX_DIGITS_INT] = "" ;
    sprintf(area_id_new, "%d", area_id);

    if (!mapContains(election->areas, area_id_new)){
        return ELECTION_AREA_NOT_EXIST;
    }

    char tribe_id_new[MAX_DIGITS_INT] = "" ;
    sprintf(tribe_id_new, "%d", tribe_id);

    if (!mapContains(election->tribes, tribe_id_new)){
        return ELECTION_TRIBE_NOT_EXIST;
    }

    if (editTribeVotes(election->area_votes, tribe_id, area_id, num_of_votes, false) != AREA_SUCCESS){
        return ELECTION_NULL_ARGUMENT;
    }

    return ELECTION_SUCCESS;

}

Map electionComputeAreasToTribesMapping (Election election){

    if (!election){
        return NULL;
    }

    Map votes_results = mapCreate();
    if (!votes_results){
        return NULL;
    }

    Area current_area = election->area_votes;
    if (!current_area){
        return votes_results;
    }

    while (current_area){

        char area_id_new[MAX_DIGITS_INT] = "" ;
        sprintf(area_id_new, "%d", getAreaId(current_area));

        char tribe_id_max[MAX_DIGITS_INT] = "";

        if (computePopularTribe(election->area_votes, getAreaId(current_area), tribe_id_max) != AREA_SUCCESS){
            mapDestroy(votes_results);
            return NULL;
        }
        if (mapPut(votes_results, area_id_new, tribe_id_max) != MAP_SUCCESS){
            if (mapClear(votes_results) != MAP_SUCCESS){
                return NULL;
            }
            return votes_results;
        }

        current_area = getNextArea(current_area);
    }

    return votes_results;
}
