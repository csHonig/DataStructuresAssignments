#include <iostream>
#include <queue>
#include "Graph.hpp"

using namespace std;

void Graph::addVertex(string name){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == name){
            found = true;
        }
    }
    if(!found){
        vertex* newVertex = new vertex;
        newVertex->name = name;
        vertices.push_back(newVertex);
    }
}

void Graph::addEdge(string v1, string v2){
    for(int i = 0; i < vertices.size(); i++) {
        if(vertices[i]->name == v1) {
            for(int j = 0; j < vertices.size(); j++) {
                if(vertices[j]->name == v2 && i != j) {
                    adjVertex av;
                    av.v = vertices[j];
                    vertices[i]->adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = vertices[i];
                    vertices[j]->adj.push_back(av2);
                }
            }
        }
    }
}

void Graph::displayEdges() {
    //traverse all vertex 
    int s = vertices.size();
    for(int i = 0; i < s; i++) {
        vertex* temp = vertices[i];
        int sofAdj = temp->adj.size();
        cout << temp->name << " --> ";
        for(int j = 0; j < sofAdj;j++) {
            cout << temp->adj[j].v->name << " ";
        }
        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex) {
    vertex* vStart = NULL;
    int numVertices = vertices.size();
    // find sourceVertex
    for(int i = 0; i < numVertices; i++) {
        if(vertices[i]->name == sourceVertex) {
            vStart = vertices[i];
            vertices[i]->distance = 0;
        }
    }
    queue<vertex*> q;
    vStart->visited = true;
    q.push(vStart);
    vertex* n = q.front();
    cout << "Starting vertex (root): " << vStart->name << "-> ";
    bool ignore = true;
    while(!q.empty()) {
        if(!ignore)
            cout << q.front()->name << "(" << q.front()->distance << ")" << " ";
        q.pop();
        int adjSize = n->adj.size();
        for(int i = 0; i < adjSize; i++) {
            if(!n->adj[i].v->visited) {
                n->adj[i].v->visited = true;
                n->adj[i].v->distance = n->distance + 1;
                q.push(n->adj[i].v);
            }
        }
        ignore = false;
        n = q.front();
    }
}

void DFSUntil(vertex* v) {
    v->visited = true;
    int numAdj = v->adj.size();
    vertex* u;
    for(int i = 0; i < numAdj;i++) {
        u = v->adj[i].v;
        if(!u->visited) {
            DFSUntil(u);
        }
    }
}

int Graph::getConnectedComponents() {
    // Mark all the vertices as not visited 
    int numVertices = vertices.size();
    for(int i = 0; i < numVertices; i++) {
        vertices[i]->visited = false;
    }
    int count = 0;
    for(int i = 0; i < numVertices; i++) {
        //If 'v' is not visited before, call DFSUtil(v)
        if(!vertices[i]->visited) {
            DFSUntil(vertices[i]);
            count++;
        }
    }
    return count;
}

bool bipartiteHelp(vertex* v) {
    queue<vertex*> q;
    q.push(v);
    vertex* n;
    vertex* current;
    while(!q.empty()) {
        n = q.front(); // n is the front of the stack every loop
        n->visited = true;
        q.pop();
        int nAdj = n->adj.size();
        for(int i = 0; i < nAdj; i++) { //loop over n's adjacency list
            current = n->adj[i].v; //current will be the current adjacent
            if(n->color=="red" && current->color=="red")
                return false;
            else if(n->color=="blue" && current->color=="blue")
                return false;
            else if(!current->visited) {
                if(n->color == "red")
                    current->color = "blue";
                else if(n->color == "blue")
                    current->color = "red";
                current->visited = true;
                q.push(current);
            }
        }
    }
    return true;
}

bool Graph::checkBipartite() {
    int numVertices = vertices.size();
    for(int i = 0; i < numVertices; i++) {
        vertices[i]->visited = false;
        vertices[i]->color = "";
    }
    for(int i = 0; i < numVertices; i++) {
        if(!vertices[i]->visited) {
            vertices[i]->color = "red";
            if(!bipartiteHelp(vertices[i]))
                return false;
        }
    }
    return true;
}