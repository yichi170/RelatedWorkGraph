import matplotlib.pyplot as plt
import pyvis.network as net
import networkx as nx
import paperpy
import nodepy as ndp

def main():
    # get input from the terminal 
    mode = input("Input the mode (citations/[references]): ")
    maxbranch = input("Input the maximum branches of node [10]: ")
    maxnode = input("Input the maximum number of node [1000]: ")
    title = input("Input the title of the paper [off policy actor critic 2012]: ").replace(' ', '+')

    # for fast test
    if title == "":
        title = "off+policy+actor+critic+2012"

    if maxbranch == "":
        maxbranch = 10
    else:
        maxbranch = int(maxbranch)

    if maxnode == "":
        maxnode = 1000
    else:
        maxnode = int(maxnode)

    # get the relationship of papers
    paper_list, paper_id_list, paper_relation = paperpy.get_relation(mode, maxbranch, maxnode, title)
    print("get the network of papers")

    # construct the system, pass the needed parameters, and get the position of the nodes
    system = ndp.NodeSystem(len(paper_id_list), 10000, 10000, 5e3, paper_relation)
    system.run_times(100000)
    position = system.getPos()

    print("get position of nodes from nodepy")

    pos_dict = {i: pos for i, pos in enumerate(position)}

    # visualization
    nx_graph = nx.Graph()
    nx_graph.add_nodes_from(paper_id_list)
    nx_graph.add_edges_from(paper_relation)
    for i, pos in enumerate(position):
        nx_graph.nodes[i]['pos'] = position
    
    # nx.draw(nx_graph, pos_dict, edge_cmap=plt.cm.Blues, node_color="#210070")
    # options = {"edgecolors": "tab:gray", "node_size": 800, "alpha": 0.9}
    plt.figure(figsize=(100, 100), dpi=80)
    nx.draw_networkx_nodes(nx_graph, pos=position, node_color="tab:red")
    nx.draw_networkx_edges(
        nx_graph,
        pos=position,
        width=3,
        alpha=0.5,
        edge_color="tab:red",
    )
    output_file = "visualization.png"
    plt.savefig("visualization.png")
    print(f"{output_file} is saved (node: {len(paper_id_list)})")
    # nt = net.Network('650px', '650px')
    # nt.from_nx(nx_graph)
    
    # # for i in nt.nodes:
    # for n in nt.nodes:
    #     n.update({'physics': False})

    # nt.toggle_physics(False)
    # nt.toggle_physics(False)
    # nt.show('visualization.html')


if __name__ == '__main__':
    main()
