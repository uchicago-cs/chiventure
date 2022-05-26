"""
Graph validator algorithm
Example Input: python src/graph_validator.py
"""
from doctest import FAIL_FAST
from example_graphs import *

# Main Function to validate cyclicality, all valid paths, singleton, and self loops
# Return True if graph is valid
def validate(graph, start):
    cyclical = check_cylicality(graph)
    valid_paths = check_all_nodes(graph, start)
    single = singleton_node(graph)
    loop = self_loop(graph)
    if cyclical or valid_paths or single or loop:
        return False
    return True


# Helper function for cyclicality check
def check_node(graph, vertex, visited, recStack):
        visited[vertex] = True
        recStack[vertex] = True
        for neighbour in graph[vertex]:
            if visited[neighbour] == False:
                if check_node(graph, neighbour, visited, recStack) == True:
                    return True
            elif recStack[neighbour] == True:
                return True
        recStack[vertex] = False
        return False
 
# Checks if there is any cyclicality in a graph
def check_cylicality(graph):
    vertices = len(graph)
    visited = [False] * (vertices + 1)
    visited = dict(zip(graph.keys(), visited))
    recStack = [False] * (vertices + 1)
    recStack = dict(zip(graph.keys(), recStack))
    for node in visited.keys():
        if visited[node] == False:
            if check_node(graph, node, visited,recStack) == True:
                return True
    return False
    


# Validates whether every node can be visited using the total count of edges to each node
def check_all_nodes(graph, start):
    visited = num_times_visit_node(graph, start)
    for i in graph.keys():
        if visited[i] == 0 and i != start:
            return True
    return False
    

# Checks if graph is a singleton
def singleton_node(graph):
    return len(graph) == 1

# Checks if graph has any nodes that refer to itself
def self_loop(graph):
    for n in graph.keys():
        edges = graph[n]
        if n in edges:
            return True 
    return False

# Count the total number of connections to each node
def num_times_visit_node(graph, node):
    count = [0 for i in range(len(graph))]
    visited = dict(zip(graph.keys(), count))

    for node in graph.keys():
        edges = graph[node]
        for n in edges:
            visited[n] += 1
    return visited



def main():
    # Tests
    print(f"Testing Graph Validity - OAK. Expecting: True | Actual: {validate(OAK, 'A')}")
    print(f"Testing Graph Validity - SELFLOOP. Expecting: False | Actual: {validate(SELFLOOP, 'A')}")
    print(f"Testing Graph Validity - SINGLETON. Expecting: False | Actual: {validate(SINGLETON, 'A')}")
    print(f"Testing Graph Validity - NODENOTREACHED. Expecting: False | Actual: {validate(NODENOTREACHED, 'A')}")
    print(f"Testing Graph Validity - INFINITELOOP. Expecting: False | Actual: {validate(INFINITELOOP, 'A')}")
    print(f"Testing Graph Validity - INFINITECIRCLE. Expecting: False | Actual: {validate(INFINITECIRCLE, 'A')}")
    print(f"Testing Graph Validity - INFINITELOOPLONG. Expecting: False | Actual: {validate(INFINITELOOPLONG, 'A')}")
    print(f"Testing Graph Validity - VALIDGRAPH2. Expecting: True | Actual: {validate(VALIDGRAPH2, 'A')}")
    print(f"Testing Graph Validity - VALIDGRAPH3. Expecting: True | Actual: {validate(VALIDGRAPH3, 'A')}")
    print(f"Testing Graph Validity - OAK(from node C). Expecting: False | Actual: {validate(OAK, 'C')}")
    print(f"Testing Graph Validity - NODENOTREACHED2. Expecting: False | Actual: {validate(NODENOTREACHED2, 'A')}")
    print(f"Testing Graph Validity - SELFLOOP2. Expecting: False | Actual: {validate(SELFLOOP2, 'A')}")
    print(f"Testing Graph Validity - INFINITECIRCLE2. Expecting: False | Actual: {validate(INFINITECIRCLE2, 'B')}")
    


if __name__ == "__main__":
    main()