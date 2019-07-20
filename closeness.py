import networkx as nx
import matplotlib.pyplot as plt

g=nx.MultiGraph();
g=nx.read_edgelist("eslam.txt",create_using=nx.MultiGraph(),nodetype=int,data=[('weight',int)])


d= dict(nx.closeness_centrality(g))
weight=nx.get_edge_attributes(g,'weight')
nx.draw_networkx(g,nodelist=d.keys(),node_size=[v*5000 for v in d.values()],edge_labels=weight,with_labels=True)

plt.show()
