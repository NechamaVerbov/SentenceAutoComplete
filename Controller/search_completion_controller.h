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
const int POINTS[] = {10, 8, 6, 4, 2, 2, 2, 2, 2, 2};

class SearchCompletionController {
public:
    void run();

    static const int K = 5;
private:
    CompletionView view;
};

vector<string> GetBestKCompletions(const string& prefix);
vector<string> checkForMistakes(const string& prefix);
vector<string> checkWithoutMistakes(const string& prefix);
vector<string> checkExtraCharacter(const string& prefix);
vector<string> parseToAutoCompleteDataStrings(const vector<pair<string, size_t>>&, size_t,int idx=0);
size_t isScoreBigger(const vector<AutoCompleteData>&, int);


inline void SearchCompletionController::run()
{
    string prefix;
    vector<string> completions;

    while(1)
    {
        cout << "Enter search: " << endl;
        cin >> prefix;

        completions = GetBestKCompletions(prefix);
        view.printCompletions(completions);

        exit(1);
    }
}

inline vector<string> parseToAutoCompleteDataStrings(const vector<pair<string, size_t>>& values, size_t len, int idx)
{
    vector<string> c_sentences;
    string sentence;
    int score;

    for (Pair file_offset : values)
    {
        sentence = SentenceData::sentences_map[file_offset.first][file_offset.second];
        c_sentences.emplace_back(AutoCompleteData(sentence, file_offset.first, file_offset.second, score).toString());
    }

    return c_sentences;
}

inline vector<string> GetBestKCompletions(const string& prefix)
{
    if (!(SentenceData::completions_map[prefix]).empty())
    {
        return checkWithoutMistakes(prefix);
    }
    else
        return checkForMistakes(prefix);
}

inline vector<string> checkWithoutMistakes(const string& prefix)
{
    const vector<pair<string, size_t>> values = SentenceData::completions_map[prefix];

    vector<string> c_sentences;
    string sentence;

    for (Pair file_offset : values)
    {
        sentence = SentenceData::sentences_map[file_offset.first][file_offset.second];
        c_sentences.emplace_back(AutoCompleteData(sentence, file_offset.first, file_offset.second, prefix.length() * 2).toString());
    }

    return c_sentences;
}

inline vector<string> checkForMistakes(const string& prefix)
{
    // add adding and change
    return checkExtraCharacter(prefix);
}

inline size_t isScoreBigger(const vector<AutoCompleteData>& values, int score)
{
    // If there's a score smaller then the given score the function returns the index,
    // otherwise returns -1.
    for(int i = 0; i < values.size(); ++i)
    {
        if (values[i].getScore() < score)
            return i;
    }
    return -1;
}

vector<string> checkExtraCharacter(const string& prefix)
{
    vector<string> options;
    string sentence, sub_str;

    for(int i = prefix.length() - 1, j = 0; i >= 0; --i, j = 0)
    {
        sub_str = prefix.substr(0, i) + prefix.substr(i + 1, prefix.length() - i - 1);

        const vector<pair<string, size_t>> values = SentenceData::completions_map[sub_str];

        if(!values.empty())
        {
            int score = (prefix.length() * 2) - POINTS[i];

            while (options.size() < SearchCompletionController::K && j < values.size()) //first fill
            {
                sentence = SentenceData::sentences_map[values[j].first][values[j].second];
                options.emplace_back(AutoCompleteData(sentence, values[j].first, values[j].second, score).toString());
                ++j;
            }
        }
        if(options.size() == SearchCompletionController::K)
            break;

    }
    return options;
}

#endif //SENTENCEAUTOCOMPLETE_SEARCH_COMPLETION_CONTROLLER_H
