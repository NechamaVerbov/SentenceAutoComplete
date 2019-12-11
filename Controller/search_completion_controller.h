//
// Created by nechamaverbov on 12/11/19.
//

#ifndef SENTENCEAUTOCOMPLETE_SEARCH_COMPLETION_CONTROLLER_H
#define SENTENCEAUTOCOMPLETE_SEARCH_COMPLETION_CONTROLLER_H

#include "/home/nechamaverbov/Desktop/SentenceAutoComplete/json.hpp"
#include "/home/nechamaverbov/Desktop/SentenceAutoComplete/Model/sentence_data.h"
#include "/home/nechamaverbov/Desktop/SentenceAutoComplete/View/completion_view.h"

class SearchCompletionController {
public:
    void run();
    vector<pair<string, size_t>> GetBestKCompletions(const string& prefix);

private:
    SentenceData data;
    CompletionView view;
};


inline void SearchCompletionController::run()
{
    string prefix;
    //vector<AutoCompleteData> completions;
    vector<pair<string, size_t>> completions;

    while(1)
    {
        cout << "Enter search: " << endl;
        cin >> prefix;

        completions = GetBestKCompletions(prefix);
        view.printCompletions(completions);
        //printVector(completions);

        exit(1);
    }
}

inline vector<pair<string, size_t>> SearchCompletionController::GetBestKCompletions(const string& prefix)
{
    return SentenceData::completions_map[prefix];
}

#endif //SENTENCEAUTOCOMPLETE_SEARCH_COMPLETION_CONTROLLER_H
