#include <iostream>
#include <vector>
#include <fstream>
#include <list>
using namespace std; // based on the alghorithm by CoffeeBeforeArch.github.io

class Graph{
private:
    int V;
    list<int> *adj;
    ofstream grout;
    vector<int> parent;
    void DFS_helper(int s, bool *visited);
    bool is_Anc(int src, int dest);

public:
    Graph(int v);
    ~Graph();
    void addEdge(int v, int w);
    void DFS(int s);
};

Graph::Graph(int v){
    grout.open("outgraph.dot");
    grout << "digraph outgr { ";
    V = v;
    adj = new list<int>[v];
    parent.resize(v);
}
Graph::~Graph(){
    delete[] adj;
    grout.close();
}

void Graph::addEdge(int v, int w){
    adj[v].push_back(w);
}

bool Graph::is_Anc(int src, int dest){
    while(parent[src] != -2){
        if(parent[src] == dest){
            return true;
        }
        src = parent[src];
    }
    return false;
}

void Graph::DFS_helper(int s, bool *visited){ 
    cout << endl;
    visited[s] = true;
    for(auto i = adj[s].begin(); i != adj[s].end(); i++){
        if(!visited[*i]){
            grout << s << "->" << *i << " [color=blue] "; // dfs tree edges
            parent[*i] = s;
            DFS_helper(*i, visited);
        }
        else{
            if(is_Anc(s, *i)){
                grout << s << "->" << *i << " [color=red] "; // back edges
                continue;
            }
            if(!is_Anc(s, *i) && !is_Anc(*i, s)){
                grout << s << "->" << *i << " [color=green] "; // cross edges
            }
        }
    }
}

void Graph::DFS(int s){
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++){
        visited[i] = false;
    }
    for(int i : parent){
        parent[i] = -1;
    }
    parent[s] = -2;
    DFS_helper(s, visited);
    grout << "}";
}

int main(){

    Graph g(8);
    g.addEdge(0, 3);
    g.addEdge(1, 0);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 0);
    g.addEdge(4, 3);
    g.addEdge(4, 6);
    g.addEdge(5, 1);
    g.addEdge(5, 7);
    g.addEdge(5, 6);
    g.addEdge(6, 2);
    g.addEdge(6, 5);
    g.addEdge(7, 6);
    ifstream in("graph_in");
    int x;
    in >> x;
    g.DFS(x);
    return 0;

}
