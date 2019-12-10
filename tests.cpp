//
// Created by nechamaverbov on 12/10/19.
//

#include <gtest/gtest.h>
#include "search.h"

using std::cout;
using std::endl;

class SentenceCompletion : public ::testing::Test
{
protected:
    virtual void SetUp( ){
    }

    Search search;
};

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(SentenceCompletion, containsPerfix)
{
    cout<< "-------------------containsPerfix TEST START----------------------" << endl << endl;

    cout<< "-------------------------HIT SEARCH 1: n--------------------------" << endl;
    vector<AutoCompleteData> completions = search.GetBestCompletions("n");
    printVector(completions);

    cout<< "--------------------------HIT SEARCH 2: and-----------------------" << endl;
    completions = search.GetBestCompletions("and");
    printVector(completions);

    cout<< "--------------------------HIT SEARCH 3: tom-----------------------" << endl;
    completions = search.GetBestCompletions("tom");
    printVector(completions);

    cout<< "-------------------containsPerfix TEST ENDS----------------------" << endl << endl;
}

TEST(SentenceCompletion, doesntContainsPerfix)
{
    cout<< "-----------------doesntContainsPerfix TEST START--------------------" << endl << endl;

    cout<< "-------------------MISS SEARCH 1: NO OUTPUT-----------------------" << endl << endl;
    completions = search.GetBestCompletions("s");
    printVector(completions);

    cout<< "------------------doesntContainsPerfix TEST ENDS--------------------" << endl << endl;
}
