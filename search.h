//
// Created by nechamaverbov on 12/10/19.
//

#ifndef SENTENCEAUTOCOMPLETE_SEARCH_H
#define SENTENCEAUTOCOMPLETE_SEARCH_H

#include <iostream>
#include "completion_map_test.cpp"
#include "auto_complete_data.h"


class Search {
public:
    Search();

    void run();

    vector<AutoCompleteData> GetBestCompletions(const string& prefix);

private:
    unordered_map<string, vector<AutoCompleteData> > completions_map;
};

void printVector(const vector<AutoCompleteData>& v);

inline Search::Search()
{
    // Import map from file
    completions_map = {
            {"and", vec1},
            {"n", vec2},
            {"tom", vec3}
    };
}

inline vector<AutoCompleteData> Search::GetBestCompletions(const string& prefix)
{
    return completions_map[prefix];
}

inline void Search::run()
{
    string prefix;
    vector<AutoCompleteData> completions;

    while(1)
    {
        std::cout << "Enter search: " << std::endl;
        std::cin >> prefix;

        completions = GetBestCompletions(prefix);
        printVector(completions);

        exit(1);
    }
}

inline void printVector(const vector<AutoCompleteData>& v)
{
    for(AutoCompleteData n : v)
    {
        std::cout << n << '\n';
    }
}


#endif //SENTENCEAUTOCOMPLETE_SEARCH_H
