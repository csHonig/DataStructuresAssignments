#include <iostream>
#include <climits>
#include <vector>
#include <stack>
#include "Graph.hpp"

using namespace std;

void Graph::addEdge(string v1, string v2, int num) {
    int size = vertices.size();
    for(int i = 0; i < size; i++) {
        if(vertices[i]->name == v1) {
            for(int j = 0; j < size; j++) {
                if(vertices[j]->name == v2 && i != j) {
                    adjVertex av;
                    av.v = vertices[j];
                    av.weight = num;
                    vertices[i]->adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = vertices[i];
                    av2.weight = num;
                    vertices[j]->adj.push_back(av2);
                }
            }
        }
    }
}

void Graph::addVertex(string name) {
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

void DFSUntil(vertex* v) {
    v->visited = true;
    cout<< v->name << " --> ";
    int numAdj = v->adj.size();
    vertex* u;
    for(int i = 0; i < numAdj;i++) {
        u = v->adj[i].v;
        if(!u->visited) {
            DFSUntil(u);
        }
    }
}

void Graph::depthFirstTraversal(string sourceVertex) {
    int size = vertices.size();
    vertex* source = NULL;
    // set all vertices as unvisited and find source vertex
    for(int i = 0; i < size; i++) {
        vertices[i]->visited = false;
        if(vertices[i]->name == sourceVertex)
            source = vertices[i];
    }
    //call recursive function
    DFSUntil(source);
    cout << "Done" << endl;
}

vertex* Graph::DijkstraAlgorithm(string start, string end) {
    vertex* vStart = NULL;
    vertex* vEnd = NULL;
    int size = vertices.size();
    for(int i = 0; i < size; i++) { 
        vertices[i]->visited = false; //set all vertices as unvisited
        vertices[i]->distance = INT_MAX; // set all distance as infinity
        vertices[i]->pred = NULL; // set predecessor as NULL
        if(vertices[i]->name == start) // find vStart
            vStart = vertices[i];
        if(vertices[i]->name == end) // find vEnd
            vEnd = vertices[i];
    }
    vector<vertex*> solved; // vector to hold all solved vertices
    solved.push_back(vStart);
    vStart->visited = true;
    vStart->distance = 0;
    int minDistance,dist;
    vertex* s = NULL; // current adj vectors
    vertex* solvedV = NULL; // vertex to be added to solved vector
    vertex* parent = NULL; // parent to solvedV
    while(!vEnd->visited) {
        minDistance = INT_MAX;
        int solvedSize = solved.size();
        for(int x = 0; x < solvedSize; x++) {
            s = solved[x];
            int adjSize = s->adj.size();
            for(int y = 0; y < adjSize; y++) {
                if(!s->adj[y].v->visited) {
                    dist = s->distance + s->adj[y].weight;
                    if(dist < minDistance) {
                        solvedV = s->adj[y].v;
                        minDistance = dist;
                        parent = s;
                    }
                }
            }
        }
        solvedV->distance = minDistance;
        solvedV->pred = parent;
        solvedV->visited = true;
        solved.push_back(solvedV);
    }
    return vEnd;
}

void Graph::shortestpath(string start, string end) {
    int size = vertices.size();
    vertex* vEnd;
    for(int i = 0; i < size; i++) {
        if(vertices[i]->name == end)
            vEnd = vertices[i];
    }
    stack<vertex*> path;
    vertex* current = vEnd;
    while(current != NULL) {
        path.push(current);
        current = current->pred;
    }
    while(!path.empty()) {
        cout << path.top()->name << " ";
        path.pop();
    }
}

void Graph::setAllVerticesUnvisited() {
    int size = vertices.size();
    for(int i = 0; i < size; i++) {
        vertices[i]->visited = false;
    }
}