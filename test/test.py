import nodepy as ndp
import networkx as nx
import matplotlib.pyplot as plt

def test():
    nx_graph = nx.Graph()
    node = 10
    relation = [
[0, 1]
,[0, 2]
,[0, 3]
,[0, 4]
,[0, 5]
,[0, 6]
,[0, 7]
,[0, 8]
,[0, 9]
]

    system = ndp.NodeSystem(node, 10000, 10000, 5e3, relation)
    system.run_times(100000)
    position = system.getPos()

    nx_graph.add_nodes_from([0, 1, 2])
    nx_graph.add_edges_from(relation)

    pos_dict = {i: pos for i, pos in enumerate(position)}
    nx.draw(nx_graph, pos_dict)
    output_file = "test.png"
    plt.savefig(output_file)
    print(f"{output_file} is saved. (node: {node}, edge: {len(relation)})")

if __name__ == '__main__':
    test()
