"""
This python file provides a test interface for testing all the
different permutations of valid and invalid graphs that are checked
for in the graph_validator.py file.
The testing framework used is unittests and runs 7 different test cases
on different graph inputs to check if the graph algorithms are working.

To run the tests type the following in the command line:

Basic Tests: python graph_tests.py
Verbose Option (List all tests): python -v graph_tests.py
"""

from graph_validator import validate
from example_graphs import *
import unittest

# Testing Class
class TestGraphValidity(unittest.TestCase):
    
    # Testing Valid Graphs
    def test_valid_graphs(self):
        self.assertEqual(validate(OAK, 'A'), True)
        self.assertEqual(validate(VALIDGRAPH2, 'A'), True)
        self.assertEqual(validate(VALIDGRAPH3, 'A'), True)
    
    # Test graph that have self loops
    def test_self_loops(self):
        self.assertEqual(validate(SELFLOOP, 'A'), False)
        self.assertEqual(validate(SELFLOOP2, 'A'), False)

    # Test Singleton Graphs
    def test_singleton(self):
        self.assertEqual(validate(SINGLETON, 'A'), False)
    
    # Test graph with unreachable node
    def test_node_not_reached(self):
        self.assertEqual(validate(NODENOTREACHED, 'A'), False)
        self.assertEqual(validate(NODENOTREACHED2, 'A'), False)


    # Test graph that has infinite loop
    def test_infinite_loop(self):
        self.assertEqual(validate(INFINITELOOP, 'A'), False)
        self.assertEqual(validate(INFINITELOOPLONG, 'A'), False)

    # Test a graph that is circularly looping infinitely
    def test_infinite_circular(self):
        self.assertEqual(validate(INFINITECIRCLE, 'A'), False)
        self.assertEqual(validate(INFINITECIRCLE2, 'B'), False)

    # Test a graph that is valid at one point but invalid at other
    def test_valid_graph_invalid_start(self):
        self.assertEqual(validate(OAK, 'C'), False)
        self.assertEqual(validate(OAK, 'B'), False)


if __name__ == '__main__':
    unittest.main()