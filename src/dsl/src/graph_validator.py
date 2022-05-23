# Graph validator algorithm
import sys
import json

def validate(graph):
    npcs = {}
    if "NPCS" in graph:
        npcs = graph["NPCS"]



        
    else:
        return 0
    
# This function checks that every node can be reached
# in the graph
def check_all_nodes(graph):
    if singleton_node(graph, node):
        return 0

# Given a start node, check if there is a closed loop
def closed_loop(graph, start_node):

# Checks if a node is a singleton
def singleton_node(graph, node):

# Returns 1 if a node has a connection with itself
def self_loop(graph, node):

# Looks through graph to find number of connections
# with a specific node 
def num_times_visit_node(graph, node):


def main():
    graph_file = sys.argv[1]
    if "wdl" in graph_file:
        f = open(graph_file)
        graph_json = json.load(f)
        validate(graph_json)
    return 0


if __name__ == "__main__":
    main()
