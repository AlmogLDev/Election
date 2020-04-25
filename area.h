#ifndef AREA_H_
#define AREA_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tribe.h"
#include "map.h"

//TODO: enum_result

typedef struct node_a* Area;

typedef enum AreaResult_t {
    AREA_OUT_OF_MEMORY,
    AREA_NULL_ARGUMENT,
    AREA_SUCCESS,
    AREA_OR_TRIBE_NOT_EXIST,
    AREA_NOT_EXIST

} AreaResult;

//if add is true than we add, else we subtract.
AreaResult editTribeVotes (Area area_votes, const int tribe_id, const int area_id, int number_of_votes, bool add);

AreaResult removeTribe (Area area_votes, const int tribe_id);

AreaResult addTribe (Area area_votes, const int tribe_id);

AreaResult destroyAreaList(Area first);

Area createArea(Map tribes ,int area_id);

AreaResult addArea (Area area_votes, Map tribes, const int area_id);

AreaResult removeArea(Area *area_votes, const int area_id);

bool validNameArea(const char* area_name);

AreaResult computePopularTribe (Area area_votes, int area_id, char* tribe_id_new);

Area getNextArea (Area current_area);

int getAreaId (Area current_area);

#endif /* AREA_H_ */



