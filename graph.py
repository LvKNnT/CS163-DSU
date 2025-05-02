import matplotlib.pyplot as plt
import networkx as nx

def draw_array_dsu(parent):
    fig, ax = plt.subplots(figsize=(8, 2))
    ax.set_axis_off()

    # Draw boxes for elements and parents
    for idx, p in enumerate(parent):
        # Element index box
        ax.add_patch(plt.Rectangle((idx, 1), 1, 1, fill=True, color='lightblue', edgecolor='black'))
        ax.text(idx + 0.5, 1.5, str(idx), ha='center', va='center', fontsize=12)
        # Parent value box
        ax.add_patch(plt.Rectangle((idx, 0), 1, 1, fill=True, color='lightyellow', edgecolor='black'))
        ax.text(idx + 0.5, 0.5, str(p), ha='center', va='center', fontsize=12)

    # Labels
    ax.text(-0.5, 1.5, "Element", fontsize=12, ha='center')
    ax.text(-0.5, 0.5, "Parent", fontsize=12, ha='center')

    ax.set_xlim(-1, len(parent))
    ax.set_ylim(-0.5, 2.5)
    plt.title("Array-based DSU Representation", fontsize=14)
    plt.show()

def draw_tree_dsu(parent):
    G = nx.DiGraph()
    for idx, p in enumerate(parent):
        if idx != p:
            G.add_edge(p, idx)
        else:
            G.add_node(idx)

    pos = nx.spring_layout(G, seed=42)
    plt.figure(figsize=(6, 4))
    nx.draw(G, pos, with_labels=True, arrows=True, node_size=800, node_color='lightgreen', font_size=12)
    plt.title("Tree-based DSU Representation", fontsize=14)
    plt.show()

# Example DSU: 0-1 connected, 2-3 connected, 4 alone
parent_array = [0, 0, 0, 3, 3, 5, 5, 6]

draw_array_dsu(parent_array)
draw_tree_dsu(parent_array)
