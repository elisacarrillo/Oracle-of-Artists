#include "makegraph.h"
using namespace std;


void MakeGraph::BFS_Search(Vertex v1) {
    // Mark all the vertices as not visited
    std::map<Vertex, bool> visited;
    std::vector<Vertex> v = g_.getVertices();
    for (unsigned int i = 0; i < v.size; i++) {
        visited.insert(std::pair<Vertex,bool>(v[i], false))
    }

    // Create a queue for BFS
    std::list<Vertex> queue;
 
    // Mark the current node as visited and enqueue it
    visited[v] = true;
    queue.push_back(v);
 
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        v = queue.front();
        //cout << v << " ";
        queue.pop_front();
 
        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        vector<Vertex> adj = v.getAdjacent();
        for (Vertex adjacent : adj) {
            if (!visited[adjacent]) {
                visited[adjacent] = true;
                queue.push_back(adjacent);
            }
        }
    }
}


std::vector<Vertex> MakeGraph::BFS_Path(Vertex v1, Vertex v2) {
    // Mark all the vertices as not visited
    std::map<Vertex, bool> visited;
    std::vector<Vertex> v = g_.getVertices();
    for (unsigned int i = 0; i < v.size; i++) {
        visited.insert(std::pair<Vertex,bool>(v[i], false))
    }

    // Create a queue for BFS
    std::list<Vertex> queue;
    std::vector<Vertex> path;
    // Mark the current node as visited and enqueue it
    visited[v] = true;
    queue.push_back(v);
 
    while(!queue.empty()) {
        // Dequeue a vertex from queue and print it
        v = queue.front();
        path.push_back(v);
        //cout << v << " ";
        queue.pop_front();
 
        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        vector<Vertex> adj = v.getAdjacent();
        for (Vertex adjacent : adj) {
            if (!visited[adjacent]) {
                visited[adjacent] = true;
                queue.push_back(adjacent);
            }
            if (adjacent == v2) {
                return path;
            }
        }
    }
    return path;
}