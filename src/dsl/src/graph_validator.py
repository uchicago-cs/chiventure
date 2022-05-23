# Graph validator algorithm
import sys
import json

def validate(graph):
    npcs = {}
    if "NPCS" in graph:
        npcs = graph["NPCS"]



        
    else:
        return 0
    




def main():
    graph_file = sys.argv[1]
    if "wdl" in graph_file:
        f = open(graph_file)
        graph_json = json.load(f)
        validate(graph_json)
    return 0


if __name__ == "__main__":
    main()