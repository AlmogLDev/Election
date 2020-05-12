#ifndef AREA_H_
#define AREA_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tribe.h"
#include "map.h"

/**
* Area type
*
* Implements a area type.
* The type of the area_id is int
* area is a linked list that every node contains the list of the tribes votes.
* in that area.
*
*
* The following functions are available:
*   editTribeVotes      - Edits the number of votes for a specific tribe in specific area.
*   removeTribe		    - Removes the tribe from all the areas.
*   addTribe        	- Adds the tribe to all the area.
*   destroyAreaList	    - Deletes all the areas from the area list and frees all the memory
*                         that was allocated.
*   createArea		    - Creates a new area list and create tribe votes list for the area.
*   addArea       	    - Creates a new area node and adds it to the list.
*   removeArea  		- Removes the area from the area list and frees all the memory that
*                         was allocated.
*   validNameArea   	- Checks if the given name of the tribe is valid.
*   computePopularTribe - Calculates the tribe that has the most votes for the specific area.
*	getNextArea 		- Returns the next area in the list.
* 	getAreaId       	- Returns the area id of the area.
*/

/** Type for defining the area */
typedef struct node_a* Area;

/** Type used for returning error codes from area functions */
typedef enum AreaResult_t {
    AREA_OUT_OF_MEMORY,
    AREA_NULL_ARGUMENT,
    AREA_OR_TRIBE_NOT_EXIST,
    AREA_NOT_EXIST,
    AREA_INVALID_VOTES,
    AREA_SUCCESS

} AreaResult;


/**
*   editTribeVotes      - Edits the number of votes for a specific tribe in specific area.
* @param area_votes - The area list.
* @param tribe_id - The id of the tribe that we want to edit.
* @param area_id - The id of the area that we want to edit.
* @param number_of_votes - The amount of votes that we want to add or subtract.
* @param add - If add is true then we add the number of votes.
*              If add is false then we subtract the number of votes.
* @return
* 	AREA_INVALID_VOTES if the number of votes is not positive.
* 	AREA_NULL_ARGUMENT if area_votes is NULL.
* 	AREA_OR_TRIBE_NOT_EXIST if there is no area with this area id or there is no tribe
* 	                        with this tribe id.
*   AREA_SUCCESS if the function succeeded.
*/
AreaResult editTribeVotes (Area area_votes, const int tribe_id, const int area_id, int number_of_votes, bool add);

/**
*   removeTribe		    - Removes the tribe from all the areas.
* @param area_votes - The area list.
* @param tribe_id - The id of the tribe that we want to remove.
* @return
* 	AREA_NULL_ARGUMENT if area_votes is NULL.
*   AREA_SUCCESS if the function succeeded.
*/
AreaResult removeTribe (Area area_votes, const int tribe_id);

/**
*   addTribe        	- Adds the tribe to all the area.
* @param area_votes - The area list.
* @param tribe_id - The id of the tribe that we want to add.
* @return
* 	AREA_NULL_ARGUMENT if area_votes is NULL.
* 	AREA_OUT_OF_MEMORY if the memory allocation of the tribe creation failed.
*   AREA_SUCCESS if the function succeeded.
*/
AreaResult addTribe (Area area_votes, const int tribe_id);

/**
*   destroyAreaList	    - Deletes all the areas from the area list and frees all the memory
                          that was allocated.
* @param first - The head of the area list.
* @return
* 	AREA_NULL_ARGUMENT if first is NULL or if unexpected error.
*   AREA_SUCCESS if the function succeeded.
*/
AreaResult destroyAreaList(Area first);

/**
*   createArea		    - Creates a new area list and create tribe votes list for the area.
* @param tribes - The tribes map.
* @param area_id - The id of the area that we want to create.
* @return
*   NULL if tribe is NULL or the creation failed or unexpected error.
*   AREA the area that was created otherwise.
*/
Area createArea(Map tribes ,int area_id);

/**
*   addArea        	- Creates a new area node and adds it to the list.
* @param area_votes - The area list.
* @param tribes - The tribes map.
* @param area_id - The id of the area that we want to add.
* @return
* 	AREA_NULL_ARGUMENT if area_votes or tribes is NULL.
* 	AREA_OUT_OF_MEMORY if the memory allocation of the area creation failed.
*   AREA_SUCCESS if the function succeeded.
*/
AreaResult addArea (Area area_votes, Map tribes, const int area_id);

/**
*   removeArea  		- Removes the area from the area list and frees all the memory that
                          was allocated.
* @param *area_votes - Pointer to the area list.
* @param area_id - The id of the area that we want to remove.
* @return
* 	AREA_NULL_ARGUMENT if *area_votes is NULL.
* 	AREA_NOT_EXIST if there is no area with this area id.
*   AREA_SUCCESS if the function succeeded.
*/
AreaResult removeArea(Area *area_votes, const int area_id);

/**
*   validNameArea   	- Checks if the given name of the tribe is valid.
* @param area_name - The name that we validate.
* @return
* 	True if the name of the area is valid, which means that the name
*   consists only lower case letters and spaces.
*   False if the name of the area isn't valid.
*/
bool validNameArea(const char* area_name);

/**
*   computePopularTribe - Calculates the tribe that has the most votes for the specific area.
* @param area_votes - The area list.
* @param area_id - The id of the area that we want to compute the popular tribe of.
* @param *tribe_id_result - Pointer to the result of the calculation.
* @return
* 	AREA_NULL_ARGUMENT if area_votes is NULL.
* 	AREA_NOT_EXIST if there is no area with this area id.
*   AREA_SUCCESS if the function succeeded.
*/
AreaResult computePopularTribe (Area area_votes, int area_id, int* tribe_id_result);

/**
*	getNextArea 		- Returns the next area in the list.
* @param current_area - The area that we want to return the following area of.
* @return
* 	NULL if current_area is NULL.
*   AREA the following area otherwise.
*/
Area getNextArea (Area current_area);

/**
* 	getAreaId       	- Returns the area id of the area.
* @param current_area - The area that we want to return the area id of.
* @return
* 	INVALID_ID if current_area is NULL.
*   area id    the area id of the area.
*/
int getAreaId (Area current_area);

#endif /* AREA_H_ */



