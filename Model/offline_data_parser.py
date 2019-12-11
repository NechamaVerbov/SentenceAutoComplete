from itertools import combinations
import json
import glob
import re
import os

AMOUNT_SENTENCES = 5

map_data = dict()
file_data = dict()


def get_keys(sentence) -> list:
    """For a given sentence returns all sub word that will be used as keys"""
    return [sentence[x:y] for x, y in combinations(range(len(sentence) + 1), r=2) if not sentence[x:y].startswith(" ")
            and y - x <= 10]


def clean_sentence(sentence: str) -> str:
    """For a given sentence removes all characters that aren't letters (not /w in regex)"""
    return re.sub(r'[^\w|" "]', '', sentence)


def insert_idx(sentence_lst: list, sentence: str) -> int:
    """Returns the position where sentence should be inserted"""
    for idx, s in enumerate(sentence_lst):
        if file_data[s[0]][s[1]] > sentence:
            return idx

    return len(sentence_lst)


def add_to_dict(key: str, sentence: str, file: str, offset: int):
    """Adds to map_data the item. If exists already and under AMOUNT_SENTENCES, "file + offset" will be added
       to the existing key in lexical order, otherwise won't do anything"""
    if key in map_data.keys():
        if len(map_data[key]) < AMOUNT_SENTENCES:
            index = insert_idx(map_data[key], sentence)
            map_data[key].insert(index,  [file, offset])
    else:
        map_data[key] = [[file, offset]]


def read_file_data(file: str):
    with open(file, 'r') as f:
        file_data[file] = f.readlines()


def write_parsed_data_to_json():
    """Stores parsed data in Json file"""
    with open('data.json', 'w', encoding='utf-8') as f:
        json.dump(map_data, f, ensure_ascii=False, indent=4)


def iterate_and_parse_file_data(file):
    """Iterates over sentences in file and adds there sub words to the map_data"""
    for index, sentence in enumerate(file_data[file]):
        if index == 4:
            pass
        cln_sentence = clean_sentence(sentence)
        keys = get_keys(cln_sentence)
        for key in keys:
            add_to_dict(key, sentence, file, index)


def offline_data_parser_flow(dir_name=os.getcwd()):
    """ Iterate over all txt files in the given directory
        parses each file content
        stores parsed data in Json file"""

    for file in glob.iglob(f'{dir_name}/*.txt'):
        file = file.split("\\")[-1]  # getting file name from real path

        read_file_data(file)
        iterate_and_parse_file_data(file)

    write_parsed_data_to_json()


offline_data_parser_flow()