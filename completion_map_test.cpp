//
// Created by nechamaverbov on 12/10/19.
//

#include <iostream>
#include <unordered_map>
#include <vector>
#include "auto_complete_data.h"

using std::vector;
using std::unordered_map;

AutoCompleteData data1("YOU don't know about me without you have read a book by the name of The",
                          "Mark_Twain__Adventures_of_Huckleberry_Finn", 12230, 3);
AutoCompleteData data2("1:1 In the beginning God created the heaven and the earth.",
                       "Moses_and_the_Sages__Bible", 1, 4);
AutoCompleteData data3("CHAPTER VIII. Tom Decides on his Course--Old Scenes Re-enacted",
                       "tom-sawyer", 45, 9);
AutoCompleteData data4("CHAPTER XXII. Tom's Confidence Betrayed--Expects Signal Punishment",
                       "tom-sawyer", 98, 7);
AutoCompleteData data5("And foreign mart for implements of war;",
                       "William_Shakespeare__Hamlet", 100, 6);

vector<AutoCompleteData> vec1 = {data2, data5};
vector<AutoCompleteData> vec2 = {data1, data2, data3,data4, data5};
vector<AutoCompleteData> vec3 = {data3, data4};

