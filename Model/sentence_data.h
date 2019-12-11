//
// Created by nechamaverbov on 12/11/19.
//

#ifndef SENTENCEAUTOCOMPLETE_SENTENCE_DATA_H
#define SENTENCEAUTOCOMPLETE_SENTENCE_DATA_H

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <set>
#include "/home/nechamaverbov/Desktop/SentenceAutoComplete/json.hpp"

using std::unordered_map, std::string, std::vector, std::pair, std::ifstream, nlohmann::json;

typedef unordered_map<string, vector<pair<string, size_t>> > CompletionMap;
typedef unordered_map<string, vector<string> > SentencesMap;


class SentenceData {
public:
    static CompletionMap initCompletionMap();
    static unordered_map<string, vector<string> > initSentenceMap();

    static string name_data_json;
    static vector<string> name_data_file;
    static CompletionMap completions_map;
    static SentencesMap sentences_map;
};

//global function used in Model
vector<string> split_path(const std::string& str, std::set<char> delimiters);


#endif //SENTENCEAUTOCOMPLETE_SENTENCE_DATA_H
