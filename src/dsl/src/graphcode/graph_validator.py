# Graph validator algorithm
# example input: python src/graph_validator.py examples/wdl/npc_example.wdl
from doctest import FAIL_FAST
import sys
import json
from example_graphs import OAK, SELFLOOP, SINGLETON, NODENOTREACHED, INFINITECIRCLE, INFINITELOOP, INFINITELOOPLONG, VALIDGRAPH2, VALIDGRAPH3

def validate(graph, start):
    cyclical = check_cylicality(graph)
    valid_paths = check_all_nodes(graph, start)
    single = singleton_node(graph)
    loop = self_loop(graph)

    if cyclical or valid_paths or single or loop:
        return False
    return True


# Functions to check circularity of nodes
def check_node(graph, v, visited, recStack):
        visited[v] = True
        recStack[v] = True
 
        for neighbour in graph[v]:
            if visited[neighbour] == False:
                if check_node(graph, neighbour, visited, recStack) == True:
                    return True
            elif recStack[neighbour] == True:
                return True
        recStack[v] = False
        return False
 
# Returns true if graph is cyclic else false
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
    


# This function checks that every node can be reached
# in the graph
def check_all_nodes(graph, start):
    visited = num_times_visit_node(graph, start)
    for i in graph.keys():
        if visited[i] == 0 and i != start:
            return True
    return False
    


# # Checks if a node is a singleton
# # Count if nodes is 1
def singleton_node(graph):
    return len(graph) == 1

# Returns 1 if a node has a connection with itself
def self_loop(graph):
    for n in graph.keys():
        edges = graph[n]
        if n in edges:
            return True 
    return False

# Looks through graph to find number of connections
# with a specific node 
def num_times_visit_node(graph, node):
    count = [0 for i in range(len(graph))]
    visited = dict(zip(graph.keys(), count))

    for node in graph.keys():
        edges = graph[node]
        for n in edges:
            visited[n] += 1
    return visited



def main():
    
    print(f"Testing Valid Graph - OAK. Expecting: True | Actual: {validate(OAK, 'A')}")
    print(f"Testing Valid Graph - SELFLOOP. Expecting: False | Actual: {validate(SELFLOOP, 'A')}")
    print(f"Testing Valid Graph - SINGLETON. Expecting: False | Actual: {validate(SINGLETON, 'A')}")
    print(f"Testing Valid Graph - NODENOTREACHED. Expecting: False | Actual: {validate(NODENOTREACHED, 'A')}")
    print(f"Testing Valid Graph - INFINITELOOP. Expecting: False | Actual: {validate(INFINITELOOP, 'A')}")
    print(f"Testing Valid Graph - INFINITECIRCLE. Expecting: False | Actual: {validate(INFINITECIRCLE, 'A')}")
    print(f"Testing Valid Graph - INFINITELOOPLONG. Expecting: False | Actual: {validate(INFINITELOOPLONG, 'A')}")
    print(f"Testing Valid Graph - VALIDGRAPH2. Expecting: True | Actual: {validate(VALIDGRAPH2, 'A')}")
    print(f"Testing Valid Graph - VALIDGRAPH3. Expecting: True | Actual: {validate(VALIDGRAPH3, 'A')}")
    print(f"Testing Valid Graph - OAK(from node C). Expecting: False | Actual: {validate(OAK, 'C')}")




if __name__ == "__main__":
    main()
