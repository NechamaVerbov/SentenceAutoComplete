import unittest
from offline_data_parser import get_keys
from offline_data_parser import clean_sentence
from offline_data_parser import add_to_dict
from offline_data_parser import map_data
from offline_data_parser import file_data
from offline_data_parser import insert_idx
from offline_data_parser import offline_data_parser_flow


class MyTestCase(unittest.TestCase):
    def test_get_keys(self):
        self.assertEqual(get_keys('Test'), ['T', 'Te', 'Tes', 'Test', 'e', 'es', 'est', 's', 'st', 't'])
        self.assertEqual(get_keys('Test o'), ['T', 'Te', 'Tes', 'Test', 'Test ', 'Test o',
                                              'e', 'es', 'est', 'est ', 'est o',
                                              's', 'st', 'st ', 'st o', 't', 't ', 't o',
                                              'o'])

    def test_clean_sentence(self):
        self.assertEqual(clean_sentence('&*Test to!'), "Test to")

    def test_add_to_dict(self):
        file_data['one'] = ['ar', 'z']
        file_data['two'] = ['a', 'g']

        true_data = {"h": ["one 0"]}
        add_to_dict('h', 'hi', 'one', 0)
        self.assertEqual(true_data, map_data)

        true_data = {"th": ["two 1"], "h": ["one 0"]}
        add_to_dict('th', 'bye', 'two', 1)
        self.assertEqual(true_data, map_data)

        true_data = {"h": ["two 0", "one 0"], "th": ["two 1"]}
        add_to_dict('h', 'ai', 'two', 0)
        self.assertEqual(true_data, map_data)

    def test_insert_idx(self):
        file_data['a.txt'] = ['a', 'z']
        self.assertEqual(insert_idx(['a.txt 0'], 'bye'), 1)

    def test_offline_data_parser_flow(self):
        offline_data_parser_flow()
        for i, j in map_data.items():
            print(f'[{i}] : {j}')


if __name__ == '__main__':
    unittest.main()
