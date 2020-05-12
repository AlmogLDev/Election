#ifndef TRIBE_H_
#define TRIBE_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
* Tribe type
*
* Implements a tribe type.
* The type of the tribe_id and the number_of_num_votes is int
* Tribe is a linked list that contains all the existing tribes and the
* number of votes for this tribe.
*
*
* The following functions are available:
*   setNumberOfVotes    - Sets the number of votes for this tribe.
*   getTribeId		    - Returns the tribe id of this tribe.
*   getNumberOfVotes	- Returns the number of votes of this tribe.
*   deleteNextTribe	    - Deletes the following tribe of this tribe.
*   addNextTribe		- Gets the last tribe on the list and Adds a tribe in the end
*   				      of the list.
*   setNextTribe  	    - Sets the following tribe of this tribe.
*   getNextTribe		- Returns the following tribe of this tribe.
*   destroyTribeList	- Destroys the whole list and freed all the memory
*                         that was allocated.
*   createTribe		    - Creates a new tribe.
*	validNameTribe		- Checks if the given name of the tribe is valid.
* 	 deleteFirstTribe	- Deletes the first tribe of the tribes list.
*/

/** Type for defining the tribe */
typedef struct node_t* Tribe;

/** Type used for returning error codes from tribe functions */
typedef enum TribeResult_t {
    TRIBE_OUT_OF_MEMORY,
    TRIBE_NULL_ARGUMENT,
    TRIBE_SUCCESS,
    TRIBE_INVALID_VOTES

} TribeResult;



/**
*	setNumberOfVotes    - Sets the number of votes for this tribe.
* @param tribe - The tribe for which to set the number of votes.
* @param number_of_votes_new - The new number of votes to set.
* @param add - If add is true then we add to the current number of votes.
*              If add is false then we subtract to the current number of votes.
* @return
* 	TRIBE_INVALID_VOTES if the number of votes is negative or zero.
* 	TRIBE_NULL_ARGUMENT if the tribe is NULL.
* 	TRIBE_SUCCESS if the function succeeded.
*/
TribeResult setNumberOfVotes(Tribe tribe, int number_of_votes_new, bool add);

/**
*	getTribeId		    - Returns the tribe id of this tribe.
* @param tribe - The tribe from which to return the tribe id.
* @return
* 	The tribe id of this tribe.
*/
int getTribeId(Tribe tribe);

/**
*	getNumberOfVotes	- Returns the number of votes of this tribe.
* @param tribe - The tribe from which to return the number of votes.
* @return
* 	The number of votes of this tribe.
*/
int getNumberOfVotes(Tribe tribe);

/**
*	deleteNextTribe	    - Deletes the following tribe of this tribe.
* @param current_tribe - The tribe that we delete the following tribe of.
* @return
* 	TRIBE_NULL_ARGUMENT if the current_tribe is NULL.
* 	TRIBE_SUCCESS if the function succeeded.
*/
TribeResult deleteNextTribe(Tribe current_tribe);

/**
*   addNextTribe		- Gets the last tribe on the list and Adds a tribe in the end
    				      of the list.
* @param current_tribe - The tribe that we add the following tribe of.
* @param tribe_id - The id of the tribe to add.
* @param number_of_votes - The number of votes of the tribe to add.
* @return
* 	TRIBE_NULL_ARGUMENT if the current_tribe is NULL.
* 	TRIBE_OUT_OF_MEMORY if the memory allocation failed.
* 	TRIBE_SUCCESS if the function succeeded.
*/
TribeResult addNextTribe (Tribe current_tribe, int tribe_id, int number_of_votes);

/**
*   setNextTribe  	    - Sets the following tribe of this tribe.
* @param current_tribe - The tribe that we set the following tribe of.
* @param next_tribe - The tribe that we set.
* @return
* 	TRIBE_NULL_ARGUMENT if the current_tribe is NULL.
* 	TRIBE_SUCCESS if the function succeeded.
*/
TribeResult setNextTribe (Tribe current_tribe, Tribe next_tribe);

/**
*   getNextTribe		- Returns the following tribe of this tribe.
* @param current_tribe - The tribe that we return the following of.
* @return
* 	The following tribe of current_tribe.
*/
Tribe getNextTribe (Tribe current_tribe);

/**
*   destroyTribeList	- Destroys the whole list and freed all the memory
                          that was allocated.
* @param first - The first tribe of the list.
* @return
* 	TRIBE_NULL_ARGUMENT if the first is NULL.
* 	TRIBE_SUCCESS if the function succeeded.
*/
TribeResult destroyTribeList(Tribe first);

/**
*   createTribe		    - Creates a new tribe.
* @param tribe_id - The id of the tribe to create.
* @param number_of_tribe_votes - The number of votes of the tribe to create.
* @return
* 	The created tribe.
* 	Returns NULL if the creation failed.
*/
Tribe createTribe(int tribe_id, int number_of_tribe_votes);


/**
*	validNameTribe		- Checks if the given name of the tribe is valid.
* @param tribe_name - The name that we validate.
* @return
* 	True if the name of the tribe is valid, which means that the name
*   consists only lower case letters and spaces.
*   False if the name isn't valid.
*/
bool validNameTribe(const char* tribe_name);

/**
* 	 deleteFirstTribe	- Deletes the first tribe of the tribes list.
* @param current_tribe - The tribe that we delete.
* @return
* 	TRIBE_NULL_ARGUMENT if current_tribe is NULL.
* 	TRIBE_SUCCESS if the function succeeded.
*/
TribeResult deleteFirstTribe(Tribe current_tribe);

#endif /* TRIBE_H_ */



