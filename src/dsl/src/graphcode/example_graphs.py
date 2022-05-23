# Example dialogue graphs represented as adjacency list to check different test cases
from collections import defaultdict
# Valid Graph
OAK = {
    'A': ['B', 'C', 'E'],
    'B': ['C'],
    'C': ['D', 'F'],
    'D': [],
    'E': ['C'],
    'F': ['G'],
    'G': [] 
}

# A is singleton
SINGLETON = {
    'A': []
}

INFINITELOOPLONG = {
    'A': ['B', 'C'], 
    'B': ['C'], 
    'C': ['A', 'D'], 
    'D': ['D']
}

# Node B can't be reached
NODENOTREACHED = {
    'A': ['C', 'E'],
    'B': ['C'],
    'C': ['D', 'F'],
    'D': [],
    'E': ['C'],
    'F': ['G'],
    'G': []  
}

# Two nodes refer to eachother infinitely 
INFINITELOOP = {
    'A': ['B'],
    'B': ['A']
}

# G is self looping
SELFLOOP = {
    'A': ['B', 'C', 'E'],
    'B': ['C'],
    'C': ['D', 'F'],
    'D': [],
    'E': ['C'],
    'F': ['G'],
    'G': ['G'] 
}



