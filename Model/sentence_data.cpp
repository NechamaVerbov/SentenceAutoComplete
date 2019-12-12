//
// Created by nechamaverbov on 12/11/19.
//

#include "sentence_data.h"

string SentenceData::name_data_json = "/home/nechamaverbov/Desktop/SentenceAutoComplete/test_a.json";
vector<string> SentenceData::name_data_file = {"/home/nechamaverbov/Desktop/SentenceAutoComplete/a.txt"};

CompletionMap SentenceData::completions_map = initCompletionMap();
unordered_map<string, vector<string> > SentenceData::sentences_map = initSentenceMap();



CompletionMap SentenceData::initCompletionMap()
{
    ifstream file(name_data_json);
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
            std::set<char> delimiter = {'/'};
            s_map[*(split_path(x, delimiter).end()-1)].push_back(line); // input them into the map
        }
    }

    return s_map;
}

vector<string> split_path(const std::string& str, const std::set<char> delimiters)
{
    std::vector<std::string> result;

    char const* pch = str.c_str();
    char const* start = pch;
    for(; *pch; ++pch)
    {
        if (delimiters.find(*pch) != delimiters.end())
        {
            if (start != pch)
            {
                std::string s(start, pch);
                result.push_back(s);
            }
            else
            {
                result.emplace_back("");
            }
            start = pch + 1;
        }
    }
    result.emplace_back(start);

    return result;
}

