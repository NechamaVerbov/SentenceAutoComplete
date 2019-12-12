//
// Created by nechamaverbov on 12/11/19.
//

#ifndef SENTENCEAUTOCOMPLETE_SEARCH_COMPLETION_CONTROLLER_H
#define SENTENCEAUTOCOMPLETE_SEARCH_COMPLETION_CONTROLLER_H

#include "/home/nechamaverbov/Desktop/SentenceAutoComplete/json.hpp"
#include "/home/nechamaverbov/Desktop/SentenceAutoComplete/Model/sentence_data.h"
#include "/home/nechamaverbov/Desktop/SentenceAutoComplete/View/completion_view.h"
#include "/home/nechamaverbov/Desktop/SentenceAutoComplete/Model/auto_complete_data.h"

// Ranking all subtracting points for score
const int ADD_REMOVE_MARK[] = {10, 8, 6, 4, 2, 2, 2, 2, 2, 2};
const int EXCHANGE_MARK[] = {5, 4, 3, 2, 1, 1, 1, 1, 1, 1};

class SearchCompletionController {
public:
    void run();

    static const int K = 5;

private:
    CompletionView view;
};


// Global functions used in Controller
vector<string> GetBestKCompletions(const string& prefix);
vector<string> checkForMistakes(const string& prefix);
vector<string> checkWithoutMistakes(const string& prefix);
void createScoreVector(string sub_str, int score, int j, vector<AutoCompleteData>& options);
vector<AutoCompleteData> checkRemoveCharacter(const string& prefix);
vector<AutoCompleteData> checkExchangeCharacter(const string& prefix);
vector<AutoCompleteData> checkAddCharacter(const string& prefix);
vector<string> getHighestScoreVec(const vector<AutoCompleteData>&, const vector<AutoCompleteData>&, const vector<AutoCompleteData>&);
string removeExtraSpace(const string & prefix);



#endif //SENTENCEAUTOCOMPLETE_SEARCH_COMPLETION_CONTROLLER_H
