//
// Created by nechamaverbov on 12/11/19.
//

#ifndef SENTENCEAUTOCOMPLETE_SEARCH_COMPLETION_CONTROLLER_H
#define SENTENCEAUTOCOMPLETE_SEARCH_COMPLETION_CONTROLLER_H

#include "/home/nechamaverbov/Desktop/SentenceAutoComplete/json.hpp"
#include "/home/nechamaverbov/Desktop/SentenceAutoComplete/Model/sentence_data.h"
#include "/home/nechamaverbov/Desktop/SentenceAutoComplete/View/completion_view.h"
#include "/home/nechamaverbov/Desktop/SentenceAutoComplete/Model/auto_complete_data.h"


class SearchCompletionController {
public:
    void run();
    vector<string> GetBestKCompletions(const string& prefix);

private:
    SentenceData data;
    CompletionView view;
};


inline void SearchCompletionController::run()
{
    string prefix;
    //vector<AutoCompleteData> completions;
    vector<string> completions;

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

inline vector<string> SearchCompletionController::GetBestKCompletions(const string& prefix)
{
    vector<pair<string, size_t>> values = SentenceData::completions_map[prefix];
    vector<string> c_sentences;
    string sentence;

    for(Pair file_offset : values)
    {
        sentence = SentenceData::sentences_map[file_offset.first][file_offset.second];
        c_sentences.push_back(AutoCompleteData(sentence, file_offset.first, file_offset.second, 0).toString());
    }

    return c_sentences;
}

#endif //SENTENCEAUTOCOMPLETE_SEARCH_COMPLETION_CONTROLLER_H
