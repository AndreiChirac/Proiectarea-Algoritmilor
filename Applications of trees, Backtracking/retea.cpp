#include <bits/stdc++.h>
#define NIL -1
using namespace std;
/* a class that represents an undirected graph */
class Graph {
    int V;
    list<int> *adj;
    void APUtil(int v, bool visited[], int disc[], int low[],
                int parent[], bool ap[]);
    void dfs(int curr, int& cnt, int*
             visited, vector<int>& duringdfs);
 public:
    explicit Graph(int V);
    void addEdge(int v, int w);
    bool * AP();
    int MaximumVisit(int n , int visited_node);
};
Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}
void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}
void Graph::APUtil(int u, bool visited[], int disc[],
                                      int low[], int parent[], bool ap[]) {
    static int time = 0;

	/* count of children in DFS Tree */
	int children = 0;

	/* mark the current node as visited */
	visited[u] = true;

    /* initialize discovery time and low value */
    disc[u] = low[u] = ++time;

    /* go through all vertices aadjacent to this */
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;

        /* if v is not visited yet, then make it a child of u in DFS tree and
        recur for it */
        if (!visited[v]) {
            children++;
            parent[v] = u;
            APUtil(v, visited, disc, low, parent, ap);
            /* check if the subtree rooted with v has a connection to one of
            the ancestors of u */
            low[u]  = min(low[u], low[v]);
            /* u is an articulation point in following cases u is root of DFS
            tree and has two or more chilren */
            if (parent[u] == NIL && children > 1) {
               ap[u] = true;
            }
            /* if u is not root and low value of one of its child is more
            than discovery value of u */
            if (parent[u] != NIL && low[v] >= disc[u]) {
            	ap[u] = true;
            }
        } else if (v != parent[u]) {
            low[u]  = min(low[u], disc[v]);
        }
    }
}

bool * Graph::AP() {
    /* mark all the vertices as not visited */
    bool *visited = new bool[V];
    int *disc = new int[V];
    int *low = new int[V];
    int *parent = new int[V];
    bool *ap = new bool[V];
    /* initialize parent and visited, and ap(articulation point) arrays */
    for (int i = 0; i < V; i++) {
        parent[i] = NIL;
        visited[i] = false;
        ap[i] = false;
    }
    /* call the recursive helper function to find articulation points in DFS
    tree rooted with vertex 'i' */
    for (int i = 0; i < V; i++) {
        if (visited[i] == false) {
            APUtil(i, visited, disc, low, parent, ap);
        }
    }
    return ap;
}

/* function to perform the DFS calculating the count of the elements in a
connected component */
void Graph::dfs(int curr, int& cnt, int*
             visited, vector<int>& duringdfs) {
    visited[curr] = 1;

    /* number of nodes in this component */
    ++cnt;
    /* stores the nodes which belong to current component */
    duringdfs.push_back(curr);
    for (auto& child : adj[curr]) {
        /* if the child is not visited */
        if (visited[child] == 0) {
            dfs(child, cnt, visited, duringdfs);
        }
    }
}

int Graph::MaximumVisit(int N , int visited_node) {
	int global = 0;
    /* To keep track of nodes we visit */
    int visited[N + 1];
    /* mark every node unvisited */
    memset(visited, 0, sizeof visited);
    visited[visited_node] = 1;
    vector<int> duringdfs;
    for (int i = 0; i < N; ++i) {
        duringdfs.clear();
      	int cnt = 0;
        /* if a node is not visited, perform a DFS as this node belongs to a
        different component which is not yet visited */
        if (visited[i] == 0) {
            cnt = 0;
            dfs(i, cnt, visited, duringdfs);
        }
        /* now store the count of all the visited nodes for any particular
        component */
        for (auto& x : duringdfs) {
        	global = global + cnt;
        }
    }
    return global;
}

int main() {
    ifstream input_file("retea.in");
	ofstream output_file("retea.out");

	int N, M;
	input_file >> N >> M;
	bool *ap = new bool[N];
	Graph g(N);

	for (int i = 0; i < M; ++i) {
		int x, y;
		input_file >> x >> y;
		g.addEdge(x-1, y-1);
	}
    ap = g.AP();
    int intial = g.MaximumVisit(N, -1);
    int ok = 0;
    /* Now ap[] contains articulation points, print them */
    for (int i = 0; i < N; i++) {
        if (ap[i] == true) {
            output_file << intial - g.MaximumVisit(N, i) -1 << endl;
        } else {
        	if (ok == 0) {
        		ok = intial - g.MaximumVisit(N, i) - 1;
        	}
        	output_file << ok << endl;
        }
    }
	return 0;
}
