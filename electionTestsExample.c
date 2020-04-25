#include <stdlib.h>
#include <string.h>
#include "election.h"
#include "test_utilities.h"

/*The number of tests*/
#define NUMBER_TESTS 11




bool test_ElectionRemoveAreas();
bool test_ElectionRemoveTribe();
bool test_electionAddTribe();
bool test_electionAddArea();
bool test_electionGetTribeName();
bool test_electionAddVote();
bool test_electionRemoveVote();
bool test_electionSetTribeName();
bool test_electionRemoveTribe();
bool test_electionRemoveArea();
bool test_electionComputeAreasToTribesMapping();


bool deleteOnlyFirstArea (int area_id) {
    return area_id == 1;
}









bool test_ElectionRemoveAreas() {

    Election election = electionCreate();
    ASSERT_TEST(electionAddArea(election, 1, "first area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 2, "second area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 2, "second area") == ELECTION_AREA_ALREADY_EXIST);

    ASSERT_TEST(electionRemoveAreas(election, deleteOnlyFirstArea) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 1, "first area") == ELECTION_SUCCESS);
    electionDestroy(election);

    return true;
}


bool test_ElectionRemoveTribe() {

    Election election = electionCreate();
    ASSERT_TEST(electionAddTribe(election, 1, "first tribe") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddTribe(election, 2, "second tribe") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddTribe(election, 2, "second tribe") == ELECTION_TRIBE_ALREADY_EXIST);

    ASSERT_TEST(electionRemoveAreas(election, deleteOnlyFirstArea) == ELECTION_SUCCESS);
    electionDestroy(election);

    return true;
}




bool test_electionAddTribe()
{

    Election election = electionCreate();
    ASSERT_TEST(electionAddTribe(election, 1, "first tribe") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddTribe(election, 2, "first tribe") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddTribe(election, 1, "third tribe") == ELECTION_TRIBE_ALREADY_EXIST);
    ASSERT_TEST(electionAddTribe(NULL, 1, "third tribe") == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionAddTribe(election, 1, NULL) == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionRemoveTribe(election, 1) == ELECTION_SUCCESS);
    ASSERT_TEST(electionRemoveTribe(election, 1) == ELECTION_TRIBE_NOT_EXIST);


    ASSERT_TEST(electionAddTribe(election, 1, "Ab tribe") == ELECTION_INVALID_NAME);
    ASSERT_TEST(electionAddTribe(election, 1, "ab tribZ") == ELECTION_INVALID_NAME);
    ASSERT_TEST(electionAddTribe(election, 1, "1") == ELECTION_INVALID_NAME);
    ASSERT_TEST(electionAddTribe(election, 0, "zero tribe") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddTribe(election, -1, "zero tribe") == ELECTION_INVALID_ID);

    electionDestroy(election);

    return true;
}

bool test_electionAddArea()
{

    Election election = electionCreate();
    ASSERT_TEST(electionAddArea(election, 1, "first") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 2, "first ") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 1, "third ") == ELECTION_AREA_ALREADY_EXIST);
    ASSERT_TEST(electionAddArea(NULL, 1, "third") == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionAddArea(election, 1, NULL) == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionAddArea(election, 1, "Ab ") == ELECTION_AREA_ALREADY_EXIST);
    ASSERT_TEST(electionAddTribe(election, 1, "ab areA") == ELECTION_INVALID_NAME);
    ASSERT_TEST(electionAddArea(election, 1, "1") == ELECTION_AREA_ALREADY_EXIST);
    ASSERT_TEST(electionAddArea(election, 0, "zero") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, -1, "zero") == ELECTION_INVALID_ID);


    electionDestroy(election);

    return true;
}

bool test_electionGetTribeName()
{

    Election election = electionCreate();
    ASSERT_TEST(electionAddTribe(election, 1, "test test") == ELECTION_SUCCESS);

    ASSERT_TEST(electionGetTribeName(election,-1) == NULL);
    ASSERT_TEST(electionGetTribeName(election,10) == NULL);
    ASSERT_TEST(electionGetTribeName(election,44) == NULL);
    ASSERT_TEST(electionGetTribeName(NULL,5) == NULL);
    char *name;
    name = electionGetTribeName(election,1);
    ASSERT_TEST(strcmp(name, "test test") == 0);
    free(name);


    electionDestroy(election);

    return true;

}







bool test_electionAddVote()
{

    Election election = electionCreate();
    ASSERT_TEST(electionAddArea(election, 1, "first") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 2, "first ") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddTribe(election, 3, "first tribe") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddTribe(election, 4, "first tribe") == ELECTION_SUCCESS);

    ASSERT_TEST(electionAddVote(election, 1,3,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 0,3,10) == ELECTION_AREA_NOT_EXIST); //V
    ASSERT_TEST(electionAddVote(election, 1,5,10) == ELECTION_TRIBE_NOT_EXIST);// V
    ASSERT_TEST(electionAddVote(NULL, 2,3,10) == ELECTION_NULL_ARGUMENT); //V
    ASSERT_TEST(electionAddVote(election, 1,3,0) == ELECTION_INVALID_VOTES); //V
    ASSERT_TEST(electionAddVote(election, 1,3,-1) == ELECTION_INVALID_VOTES);//V
    ASSERT_TEST(electionAddVote(election, 2,4,10) == ELECTION_SUCCESS);

    ASSERT_TEST(electionAddVote(election, 1,4,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 2,3,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 2,4,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 1,4,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 2,3,10) == ELECTION_SUCCESS);

    electionDestroy(election);

    return true;

}

bool test_electionRemoveVote()
{
    /** almost the same as test_electionAddVote */

    Election election = electionCreate();
    ASSERT_TEST(electionAddArea(election, 1, "first") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 2, "first ") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddTribe(election, 3, "first tribe") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddTribe(election, 4, "first tribe") == ELECTION_SUCCESS);

    ASSERT_TEST(electionAddVote(election, 1,3,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 0,3,10) == ELECTION_AREA_NOT_EXIST);
    ASSERT_TEST(electionAddVote(election, 1,5,10) == ELECTION_TRIBE_NOT_EXIST);
    ASSERT_TEST(electionAddVote(NULL, 2,3,10) == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionAddVote(election, 1,3,0) == ELECTION_INVALID_VOTES);
    ASSERT_TEST(electionAddVote(election, 1,3,-1) == ELECTION_INVALID_VOTES);
    ASSERT_TEST(electionAddVote(election, 2,4,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 1,4,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 2,3,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 2,4,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 1,4,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 2,3,10) == ELECTION_SUCCESS);


    ASSERT_TEST(electionRemoveVote(election, 1,3,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionRemoveVote(NULL, 1,3,10) == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionRemoveVote(election, 1,3,-10) == ELECTION_INVALID_VOTES);
    ASSERT_TEST(electionRemoveVote(election, 1,3,0) == ELECTION_INVALID_VOTES);
    ASSERT_TEST(electionRemoveVote(election, -1,3,0) == ELECTION_INVALID_ID);
    ASSERT_TEST(electionRemoveVote(election, 1,-3,0) == ELECTION_INVALID_ID);
    ASSERT_TEST(electionRemoveVote(election, 6,3,3) == ELECTION_AREA_NOT_EXIST);
    ASSERT_TEST(electionRemoveVote(election, 6, 6, 1) == ELECTION_AREA_NOT_EXIST);
    ASSERT_TEST(electionRemoveVote(election, 1, 15, 1) == ELECTION_TRIBE_NOT_EXIST);
    ASSERT_TEST(electionRemoveVote(election, 3,6,1) == ELECTION_AREA_NOT_EXIST);
    ASSERT_TEST(electionRemoveVote(election, 2,4,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionRemoveVote(election, 2,4,35) == ELECTION_SUCCESS);
    ASSERT_TEST(electionRemoveVote(election, 2,4,35) == ELECTION_SUCCESS);


    electionDestroy(election);


    return true;

}


bool test_electionSetTribeName()
{

    Election election = electionCreate();
    ASSERT_TEST(electionAddTribe(election, 1, "first tribe") == ELECTION_SUCCESS);
    ASSERT_TEST(electionSetTribeName(NULL, 1,"first tribe") == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionSetTribeName(election,1,NULL) == ELECTION_NULL_ARGUMENT);


    ASSERT_TEST(electionAddTribe(election, 2, "second tribe") == ELECTION_SUCCESS);
    ASSERT_TEST(electionSetTribeName(election, -2,"second tribe") == ELECTION_INVALID_ID);

    ASSERT_TEST(electionSetTribeName(election, 43939427,"unexisting tribe") == ELECTION_TRIBE_NOT_EXIST);

    ASSERT_TEST(electionAddTribe(election, 3, "third tribe") == ELECTION_SUCCESS);
    ASSERT_TEST(electionSetTribeName(election, 3,"thIrd tribe") == ELECTION_INVALID_NAME);
    ASSERT_TEST(electionSetTribeName(election, 3,"third_tribe") == ELECTION_INVALID_NAME);
    ASSERT_TEST(electionSetTribeName(election, 3,"third2 tribe") == ELECTION_INVALID_NAME);
    ASSERT_TEST(electionSetTribeName(election, 3,"third tribeE") == ELECTION_INVALID_NAME);

    ASSERT_TEST(electionAddTribe(election, 4, "fourth tribe") == ELECTION_SUCCESS);
    ASSERT_TEST(electionSetTribeName(election, 4 ,"fourth tribenew") == ELECTION_SUCCESS);

    ASSERT_TEST(electionSetTribeName(election, 4, NULL) == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionSetTribeName(NULL, 4, "test1") == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionSetTribeName(election, -4, "first tribe") == ELECTION_INVALID_ID);
    ASSERT_TEST(electionSetTribeName(election, -1, "first tribeA") == ELECTION_INVALID_ID);
    ASSERT_TEST(electionSetTribeName(election, 8, "first tribe") == ELECTION_TRIBE_NOT_EXIST);
    ASSERT_TEST(electionSetTribeName(election, 3, "new name1") == ELECTION_INVALID_NAME);
    ASSERT_TEST(electionSetTribeName(election, 8, "new name1") == ELECTION_TRIBE_NOT_EXIST);
    ASSERT_TEST(electionSetTribeName(election, 3, "new name") == ELECTION_SUCCESS);

    electionDestroy(election);


    return true;

}




bool test_electionRemoveTribe()
{

    Election election = electionCreate();
    ASSERT_TEST(electionAddArea(election, 1, "first area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 2, "sec area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddTribe(election, 3, "first tribe") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddTribe(election, 4, "sec tribe") == ELECTION_SUCCESS);

    ASSERT_TEST(electionAddVote(election, 1,3,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 0,3,10) == ELECTION_AREA_NOT_EXIST);
    ASSERT_TEST(electionAddVote(election, 1,5,10) == ELECTION_TRIBE_NOT_EXIST);
    ASSERT_TEST(electionAddVote(NULL, 2,3,10) == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionAddVote(election, 1,3,0) == ELECTION_INVALID_VOTES);
    ASSERT_TEST(electionAddVote(election, 1,3,-1) == ELECTION_INVALID_VOTES);
    ASSERT_TEST(electionAddVote(election, 2,4,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 1,4,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 2,3,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 2,4,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 1,4,10) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 2,3,10) == ELECTION_SUCCESS);

    ASSERT_TEST(electionRemoveTribe(NULL, 10) == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionRemoveTribe(NULL, -1) == ELECTION_NULL_ARGUMENT);
    ASSERT_TEST(electionRemoveTribe(election, -1) == ELECTION_INVALID_ID);
    ASSERT_TEST(electionRemoveTribe(election, 8) == ELECTION_TRIBE_NOT_EXIST);
    ASSERT_TEST(electionRemoveTribe(election, 3) == ELECTION_SUCCESS); //deleted
    ASSERT_TEST(electionRemoveTribe(election, 3) == ELECTION_TRIBE_NOT_EXIST);

    ASSERT_TEST(electionAddTribe(election, 3, "first tribe") == ELECTION_SUCCESS);

    electionDestroy(election);

    return true;


}



static bool electionRemoveAreaConditionFunc1(int area_id) // area_id is bigger then 5
{
    if (area_id > 5)
    {
        return true;
    }
    return false;

}
static bool electionRemoveAreaConditionFunc2(int area_id) // area_id is odd
{
    if ((area_id % 2) == 1)
    {
        return true;
    }
    return false;

}
static bool electionRemoveAreaConditionFunc3(int area_id) // area_id is divisible by 3
{
    if ((area_id % 3) == 0)
    {
        return true;
    }
    return false;
}

bool test_electionRemoveArea()
{

    Election election = electionCreate();
    ASSERT_TEST(electionAddArea(election, 10, "first area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 5, "first area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 1, "first area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 12, "first area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionRemoveAreas(election,electionRemoveAreaConditionFunc1) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 12, "first area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 10, "first area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 1, "first area") == ELECTION_AREA_ALREADY_EXIST);
    ASSERT_TEST(electionAddArea(election, 5, "first area") == ELECTION_AREA_ALREADY_EXIST);



    ASSERT_TEST(electionAddTribe(election, 2, "tribe two"));
    ASSERT_TEST(electionAddTribe(election, 5, "tribe five"));
    ASSERT_TEST(electionAddVote(election, 1, 2, 10));
    ASSERT_TEST(electionAddVote(election, 1, 5, 15));
    ASSERT_TEST(electionAddVote(election, 10, 5, 20));


    ASSERT_TEST(electionAddArea(election, 21, "second area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 2, "second area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 1, "second area") == ELECTION_AREA_ALREADY_EXIST);
    ASSERT_TEST(electionAddArea(election, 14, "second area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionRemoveAreas(election,electionRemoveAreaConditionFunc2) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 21, "second area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 2, "second area") == ELECTION_AREA_ALREADY_EXIST);
    ASSERT_TEST(electionAddArea(election, 1, "second area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 14, "second area") == ELECTION_AREA_ALREADY_EXIST);

    ASSERT_TEST(electionAddArea(election, 33, "third area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 30, "third area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 34, "third area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 37, "third area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionRemoveAreas(election,electionRemoveAreaConditionFunc3) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 33, "third area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 30, "third area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 34, "third area") == ELECTION_AREA_ALREADY_EXIST);
    ASSERT_TEST(electionAddArea(election, 37, "third area") == ELECTION_AREA_ALREADY_EXIST);

    electionDestroy(election);

    return true;

}








bool test_electionComputeAreasToTribesMapping()
{

    Election election = electionCreate();
    ASSERT_TEST(electionAddArea(election, 1, "first area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddArea(election, 2, "sec area") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddTribe(election, 3, "first tribe") == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddTribe(election, 4, "sec tribe") == ELECTION_SUCCESS);

    ASSERT_TEST(electionAddVote(election, 1, 3, 100) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 1, 4, 100) == ELECTION_SUCCESS);
    Map max1 = electionComputeAreasToTribesMapping(election);
    ASSERT_TEST(max1 != NULL);
    ASSERT_TEST( strcmp(mapGet(max1, "1"), "3") == 0 );
    //should be 3.

    ASSERT_TEST(electionRemoveVote(election, 1, 3, 100) == ELECTION_SUCCESS);
    ASSERT_TEST(electionRemoveVote(election, 1, 4, 100) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 1, 3, 300) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 1, 4, 400) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 2, 4, 300) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 2, 3, 400) == ELECTION_SUCCESS);
    ASSERT_TEST(electionAddVote(election, 2, 3, 401) == ELECTION_SUCCESS);

    Map max2 = electionComputeAreasToTribesMapping(election);
    ASSERT_TEST(max2 != NULL);
    ASSERT_TEST( strcmp(mapGet(max2, "1"), "4") == 0 );
    ASSERT_TEST( strcmp(mapGet(max2, "2"), "3") == 0 );

    mapDestroy(max1);
    mapDestroy(max2);
    electionDestroy(election);


    return true;


}









/*The functions for the tests should be added here*/
bool (*tests[]) (void) = {
        test_ElectionRemoveAreas,
        test_ElectionRemoveTribe,
        test_electionAddTribe,
        test_electionAddArea,
        test_electionGetTribeName,
        test_electionAddVote,
        test_electionRemoveVote,
        test_electionSetTribeName,
        test_electionRemoveTribe,
        test_electionRemoveArea,
        test_electionComputeAreasToTribesMapping,

};

/*The names of the test functions should be added here*/
const char* testNames[] = {
        "test_ElectionRemoveAreas",
        "test_ElectionRemoveTribe",
        "test_electionAddTribe",
        "test_electionAddArea",
        "test_electionGetTribeName",
        "test_electionAddVote",
        "test_electionRemoveVote",
        "test_electionSetTribeName",
        "test_electionRemoveTribe",
        "test_electionRemoveArea",
        "test_electionComputeAreasToTribesMapping"
};

int main(int argc, char *argv[]) {
    if (argc == 1) {
        for (int test_idx = 0; test_idx < NUMBER_TESTS; test_idx++) {
            RUN_TEST(tests[test_idx], testNames[test_idx]);
        }
        return 0;
    }
    if (argc != 2) {
        fprintf(stdout, "Usage: election <test index>\n");
        return 0;
    }

    int test_idx = strtol(argv[1], NULL, 10);
    if (test_idx < 1 || test_idx > NUMBER_TESTS) {
        fprintf(stderr, "Invalid test index %d\n", test_idx);
        return 0;
    }

    RUN_TEST(tests[test_idx - 1], testNames[test_idx - 1]);
    return 0;
}
