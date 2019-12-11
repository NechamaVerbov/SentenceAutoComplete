//
// Created by nechamaverbov on 12/10/19.
//

#ifndef SENTENCEAUTOCOMPLETE_AUTO_COMPLETE_DATA_H
#define SENTENCEAUTOCOMPLETE_AUTO_COMPLETE_DATA_H

#include <string>

using std::string;

class AutoCompleteData {

public:
    AutoCompleteData(string, string, int, int);

    string toString() const;

    friend std::ostream& operator<<(std::ostream&, AutoCompleteData&);

private:
    string completed_sentence;
    string source_text;
    int offset;
    int score;
};

inline AutoCompleteData::AutoCompleteData(string sentence, string source, int _offset, int _score)
{
    completed_sentence = sentence;
    source_text = source;
    offset = _offset;
    score = _score;
}

inline string AutoCompleteData::toString() const
{
    return std::to_string(score) + " " + source_text + " " + std::to_string(offset) + " " + completed_sentence;
}

inline std::ostream& operator<<(std::ostream& os, AutoCompleteData& data)
{
    os <<  data.source_text << " " << data.offset << ": " << data.completed_sentence << std::endl;
    return os;
}

#endif //SENTENCEAUTOCOMPLETE_AUTO_COMPLETE_DATA_H