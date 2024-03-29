//
// Created by nechamaverbov on 12/11/19.
//

#ifndef SENTENCEAUTOCOMPLETE_COMPLETION_VIEW_H
#define SENTENCEAUTOCOMPLETE_COMPLETION_VIEW_H

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

typedef pair<string, size_t> Pair;

class CompletionView {
public:
    void printCompletions(const vector<string>&);
};

inline void CompletionView::printCompletions(const vector<string>& v)
{
    for(string n : v)
    {
        std::cout << n << '\n';
    }
}
#endif //SENTENCEAUTOCOMPLETE_COMPLETION_VIEW_H
