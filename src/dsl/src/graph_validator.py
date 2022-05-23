# Graph validator algorithm
import sys
import json

def validate(graph):
    npcs = {}
    if "NPCS" in graph:
        npcs = graph["NPCS"]

        for npc, vals in npcs.items():
            edges = vals['dialogue']['edges']
            nodes = vals['dialogue']['nodes']
            print(nodes)




    else:
        return 0
    




def main():
    graph_file = sys.argv[1]
    print(graph_file)
    if "wdl" in graph_file:
        f = open(graph_file)
        graph_json = json.load(f)
        validate(graph_json)
    return 0


if __name__ == "__main__":
    main()