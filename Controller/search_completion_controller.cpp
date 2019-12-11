//
// Created by nechamaverbov on 12/11/19.
//

//#include <bits/regex.h>
#include "search_completion_controller.h"
#include <regex>


void SearchCompletionController::run()
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

vector<string> GetBestKCompletions(const string& prefix)
{
    if (!(SentenceData::completions_map[prefix]).empty())
    {
        return checkWithoutMistakes(prefix);
    }
    else
        return checkForMistakes(prefix);
}

string removeExtraSpace(const string & prefix)
{
    std::regex re("\\s{2,}");
    return regex_replace(prefix, re, " ");
}

vector<string> checkWithoutMistakes(const string& pre)
{
    string prefix = removeExtraSpace(pre);
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

vector<string> checkForMistakes(const string& prefix)
{
    vector<AutoCompleteData> exchange_vec = checkExchangeCharacter(prefix);
    vector<AutoCompleteData> add_vec = checkAddCharacter(prefix);
    vector<AutoCompleteData> remove_vec = checkRemoveCharacter(prefix);

    return getHighestScoreVec(exchange_vec, add_vec, remove_vec);
}

string highestScore(const AutoCompleteData& v1, const AutoCompleteData& v2, const AutoCompleteData& v3)
{
    AutoCompleteData tmp(v1);
    int max = v1.getScore();

    if (v2.getScore() > max) {max = v2.getScore(); tmp = v2;}
    if (v3.getScore() > max) {tmp = v3;}

    return tmp.toString();
}

string highestScore(const AutoCompleteData& v1, const AutoCompleteData& v2)
{
    return v1.getScore() > v2.getScore() ? v1.toString() : v2.toString();
}

vector<string> getHighestScoreVec(const vector<AutoCompleteData>& v1, const vector<AutoCompleteData>& v2, const vector<AutoCompleteData>& v3)
{
    vector<string> best_vec;
    vector<AutoCompleteData> tmp = v1;

    tmp.insert(v1.end(), v2.begin(), v2.end());
    tmp.insert(tmp.end(), v3.begin(), v3.end());

    sort(tmp.begin(), tmp.end(), std::greater<AutoCompleteData>());
    for(int i = 0; i < tmp.size() && i < SearchCompletionController::K; ++i)
        best_vec.emplace_back(tmp[i].toString());

    return best_vec;
}

vector<string> parseToAutoCompleteDataStrings(const vector<pair<string, size_t>>& values, size_t len, int idx)
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

size_t isScoreBigger(const vector<AutoCompleteData>& values, int score)
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

void createScoreVector(string sub_str, int score, int j, vector<AutoCompleteData>& options)
{
    const vector<pair<string, size_t>> values = SentenceData::completions_map[sub_str];
    string sentence;

    if (!values.empty())
    {
        while (options.size() < SearchCompletionController::K && j < values.size()) //first fill
        {
            sentence = SentenceData::sentences_map[values[j].first][values[j].second];
            options.emplace_back(AutoCompleteData(sentence, values[j].first, values[j].second, score));
            ++j;
        }
    }
}

vector<AutoCompleteData> checkRemoveCharacter(const string& prefix)
{
    vector<AutoCompleteData> options;
    string sentence, sub_str;

    for(int i = prefix.length() - 1, j = 0; i >= 0; --i, j = 0)
    {
        sub_str = prefix.substr(0, i) + prefix.substr(i + 1, prefix.length() - i - 1);

        int score = (prefix.length() * 2) - ADD_REMOVE_MARK[i];

        createScoreVector(sub_str, score, j, options);

        if(options.size() == SearchCompletionController::K)
            break;

    }
    return options;
}

vector<AutoCompleteData> checkExchangeCharacter(const string& prefix)
{
    vector<AutoCompleteData> options;
    string sentence, sub_str;

    for(int i = prefix.length() - 1, j = 0; i >= 0; --i, j = 0)
    {
        string alphanumeric = "abcdefghijklmnopqrstuvwxyz1234567890_ ";
        for(char letter : alphanumeric)
        {
            sub_str = prefix.substr(0, i) + letter + prefix.substr(i + 1, prefix.length() - i - 1);

            int score = (prefix.length() * 2) - EXCHANGE_MARK[i];

            createScoreVector(sub_str, score, j, options);

            if (options.size() == SearchCompletionController::K)
                break;
        }

    }
    return options;
}

vector<AutoCompleteData> checkAddCharacter(const string& prefix)
{
    vector<AutoCompleteData> options;
    string sentence, sub_str;

    for(int i = prefix.length() - 1, j = 0; i >= -1; --i, j = 0)
    {
        string alphanumeric = "abcdefghijklmnopqrstuvwxyz1234567890_ ";
        for(char letter : alphanumeric)
        {
            sub_str = prefix.substr(0, i + 1) + letter + prefix.substr(i + 1, prefix.length() - i - 1);

            int score = (prefix.length() * 2) - ADD_REMOVE_MARK[i];

            createScoreVector(sub_str, score, j, options);

            if (options.size() == SearchCompletionController::K)
                break;
        }

    }
    return options;
}
