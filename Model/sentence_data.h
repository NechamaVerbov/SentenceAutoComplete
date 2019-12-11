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
#include "/home/nechamaverbov/Desktop/SentenceAutoComplete/json.hpp"
using std::unordered_map;
using std::string;
using std::vector;
using std::pair;
using std::ifstream;
using nlohmann::json;

typedef unordered_map<string, vector<pair<string, size_t>> > CompletionMap;
typedef unordered_map<string, vector<string> > SentencesMap;


class SentenceData {
public:
    static CompletionMap initCompletionMap();
    static unordered_map<string, vector<string> > initSentenceMap();

    static string name_data_json;
    static vector<string> name_data_file;
    static CompletionMap completions_map;
    static unordered_map<string, vector<string> > sentences_map;
private:

};

string SentenceData::name_data_json = "/home/nechamaverbov/Desktop/SentenceAutoComplete/Model/test.json";
vector<string> SentenceData::name_data_file = {"/home/nechamaverbov/Desktop/SentenceAutoComplete/Model/a.txt"};

CompletionMap SentenceData::completions_map = initCompletionMap();
unordered_map<string, vector<string> > SentenceData::sentences_map = initSentenceMap();


CompletionMap SentenceData::initCompletionMap()
{
    std::ifstream file(name_data_json);
    if (file.is_open())
    {
        json json_data = json::parse(file);
        CompletionMap c_map;

        /* parse the json into map*/
        for (json::iterator it = json_data.begin(); it != json_data.end(); ++it) //json keys
        {
            std::cout << it.key() << " : " << it.value() << std::endl;
            vector<pair<string, size_t>> values;
            for (int i = 0; i < it.value().size(); ++i) //values of each key
            {
                values.emplace_back(it.value()[i][0], it.value()[i][1]);
            }
            c_map[it.key()] = values;
        }
        return c_map;
    }
    else { throw "Unable to open file";}
}


unordered_map<string, vector<string> > SentenceData::initSentenceMap()
{
    SentencesMap s_map;
    for(auto&& x: name_data_file)
    {
        ifstream file;
        file.open(x);
        string line;
        while (getline(file, line))
        {
            s_map[x].push_back(line); // input them into the map
            std::cout << x << " " << line << std::endl;
        }
    }

    return s_map;
}

#endif //SENTENCEAUTOCOMPLETE_SENTENCE_DATA_H
