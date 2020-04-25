
#include "area.h"

#define NO_VOTES 0
#define MAX_DIGITS_INT 10


struct node_a {

    int area_id;
    struct node_t *tribe_votes;
    struct node_a *next;

};




AreaResult editTribeVotes (Area area_votes, const int tribe_id, const int area_id, int number_of_votes, bool add){

    if (!area_votes){
        return AREA_NULL_ARGUMENT;
    }
    Area current_area = area_votes;

    while (current_area){

        if (current_area->area_id == area_id){
            Tribe current_tribe = current_area->tribe_votes;

            while (current_tribe){

                if (getTribeId(current_tribe) == tribe_id){
                    if (setNumberOfVotes(current_tribe, number_of_votes, add) != TRIBE_SUCCESS){
                        return AREA_NULL_ARGUMENT;
                    }
                    return AREA_SUCCESS;
                }

                current_tribe = getNextTribe(current_tribe);

            }
        }

        current_area = current_area->next;

    }

    return AREA_OR_TRIBE_NOT_EXIST;
}

AreaResult removeTribe (Area area_votes, const int tribe_id){

    Area current_area = area_votes;

    while(current_area){
        Tribe current_tribe = current_area->tribe_votes;

        if (!(getNextTribe(current_tribe))){
            if (getTribeId(current_tribe) == tribe_id){
                if (destroyTribeList(current_tribe) != TRIBE_SUCCESS)
                    return AREA_NULL_ARGUMENT;
                current_area->tribe_votes = NULL;
            }
        }else{

            while (getNextTribe(current_tribe)){
                if (getTribeId(getNextTribe(current_tribe)) == tribe_id){
                    if (deleteNextTribe(current_tribe) != TRIBE_SUCCESS){
                        return AREA_NULL_ARGUMENT;
                    }
                }
                current_tribe = getNextTribe(current_tribe);
            }


        }

        current_area = current_area->next;
    }

    return AREA_SUCCESS;
}

AreaResult addTribe (Area area_votes, const int tribe_id){

    if (!area_votes){
        return AREA_NULL_ARGUMENT;
    }
    Area current_area = area_votes;

    while (current_area){

        Tribe current_tribe = current_area->tribe_votes;
        if (!current_tribe){
            current_area->tribe_votes = createTribe(tribe_id, NO_VOTES);
            if (!(current_area->tribe_votes)){
                return AREA_OUT_OF_MEMORY;
            }
        }else{
            while (getNextTribe(current_tribe)){

                current_tribe = getNextTribe(current_tribe);
            }
            TribeResult result = addNextTribe(current_tribe, tribe_id, NO_VOTES);
            if (result == TRIBE_NULL_ARGUMENT){
                return AREA_NULL_ARGUMENT;
            }else if(result == TRIBE_OUT_OF_MEMORY){
                return AREA_OUT_OF_MEMORY;
            }
        }

        current_area = current_area->next;

    }
    return AREA_SUCCESS;
}

AreaResult destroyAreaList(Area first) {

    if (!first){
        return AREA_NULL_ARGUMENT;
    }

    while (first) {
        Area temp = first;
        destroyTribeList(first->tribe_votes);
        first = first->next;
        free(temp);
    }

    return AREA_SUCCESS;
}

Area createArea(Map tribes, int area_id) {
    if (!tribes){
        return NULL;
    }
    Area new_area = malloc(sizeof(*new_area));
    if (!new_area){
        return NULL;
    }
    new_area->area_id = area_id;

    int number_of_tribes = mapGetSize(tribes);
    if (!number_of_tribes){
        new_area->tribe_votes = NULL;
        new_area->next = NULL;
        return new_area;
    }
    char* tribe_id = mapGetFirst(tribes);
    int tribe_id_int = 0;

    sscanf(tribe_id, "%d", &tribe_id_int);

    Tribe current_tribe = createTribe(tribe_id_int, NO_VOTES);
    if (!current_tribe) {
        return NULL;
    }
    Tribe head = current_tribe;

    for (int i = 0; i < number_of_tribes-1 ; ++i) {

        tribe_id = mapGetNext(tribes);

        int tribe_id_int = 0;
        sscanf(tribe_id, "%d", &tribe_id_int);

        Tribe temp = createTribe(tribe_id_int, NO_VOTES);
        if (!temp) {
            if (destroyTribeList(head) != TRIBE_SUCCESS){
                return NULL;
            }
            return NULL;
        }
        if (setNextTribe(current_tribe, temp) != TRIBE_SUCCESS){
            return NULL;
        }
        current_tribe = getNextTribe(current_tribe);
    }

    new_area->tribe_votes = head;
    new_area->next = NULL;
    return new_area;
}

AreaResult addArea(Area area_votes ,Map tribes, const int area_id) {

    if (!area_votes || !tribes){
        return AREA_NULL_ARGUMENT;
    }
    Area current_area = area_votes;

    while (current_area->next) {
        current_area = current_area->next;
    }

    current_area->next = createArea(tribes, area_id);
    if (!(current_area->next)) {
        return AREA_OUT_OF_MEMORY;
    }

    return AREA_SUCCESS;

}

AreaResult removeArea(Area *area_votes, const int area_id) {

    if (!*area_votes){
        return AREA_NULL_ARGUMENT;
    }
    Area current_area = *area_votes;

    if (!current_area->next) { //TODO: only one area
        if (current_area->area_id == area_id) {
            if (destroyTribeList(current_area->tribe_votes) != TRIBE_SUCCESS){
                if (destroyAreaList(current_area) != AREA_SUCCESS){
                    return AREA_NULL_ARGUMENT;
                }
                return AREA_SUCCESS;
            }
            if (destroyAreaList(current_area) != AREA_SUCCESS){
                return AREA_NULL_ARGUMENT;
            }
            return AREA_SUCCESS;
        }
    }

    if (current_area->area_id == area_id){
        *area_votes = current_area->next;
        destroyTribeList(current_area->tribe_votes);
        free(current_area);
        return AREA_SUCCESS;
    }

    while (current_area->next) {

        if (current_area->next->area_id == area_id) {
            Area to_delete = current_area->next;
            current_area->next = to_delete->next;
            destroyTribeList(to_delete->tribe_votes);
            free(to_delete);
            return AREA_SUCCESS;
        }
        current_area = current_area->next;
    }

    return AREA_NOT_EXIST;

}

bool validNameArea(const char *area_name) {

    int i = 0;

    while (area_name[i]) {
        if ((area_name[i] < 'a' || area_name[i] > 'z') && area_name[i] != ' ') {
            return false;
        }
        i++;
    }
    return true;
}

AreaResult computePopularTribe(Area area_votes, int area_id, char *tribe_id_new) {

    if (!area_votes){
        return AREA_NULL_ARGUMENT;
    }
    Area current_area = area_votes;

    if (!current_area) {
        *tribe_id_new = '\0';
    }

    while (current_area) {
        if (current_area->area_id == area_id) {
            Tribe current_tribe = current_area->tribe_votes;
            if (!current_tribe) {
                *tribe_id_new = '\0';
            }

            int max = 0;
            int max_tribe_id = 0;

            while (current_tribe) {

                if (getNumberOfVotes(current_tribe) > max) {
                    max = getNumberOfVotes(current_tribe);
                    max_tribe_id = getTribeId(current_tribe);
                } else if (getNumberOfVotes(current_tribe) == max) {
                    if (max_tribe_id > getTribeId(current_tribe)) {
                        max_tribe_id = getTribeId(current_tribe);
                    }


                }

                current_tribe = getNextTribe(current_tribe);
            }
            sprintf(tribe_id_new, "%d", max_tribe_id);

            return AREA_SUCCESS;
        }

        current_area = current_area->next;

    }

    *tribe_id_new = '\0';
    return AREA_NOT_EXIST;
}

Area getNextArea (Area current_area){

    return current_area->next;
}

int getAreaId (Area current_area){

    return current_area->area_id;
}