#include "makegraph.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
using namespace std;

MakeGraph::MakeGraph(string filename) : g_(false, false) {
    //for each line create array of artists and make node the name of the song
    std::ifstream infile(filename);
    std::string line;
    std::cout<<"here"<<std::endl;
    

    while (std::getline(infile, line) && infile.eof() == false) {
        // std::cout<<"here 2"<<std::endl;
        std::string content;
        std::vector<std::string> vect;
        std::stringstream ss(line);
        while(std::getline(ss,content,'"')) {
            vect.push_back(content);
            // std::cout<<content<<std::endl;
        }
        // std::cout<<vect.size()<<std::endl;
        // for (unsigned int i = 0; i < vect.size(); i++) {
        //     std::cout<<"look"<<i<<std::endl;
        //     if (vect[i].at(0) == ',') {
        //         vect[i].erase(vect[i].begin());
        //         // i++;

        //     }
        //     std::cout<<"deleting"<<std::endl;
        //     if (i != vect.size() && vect[i].at(vect[i].size()-1) == ',') {
        //         std::cout<<"deleting 2"<<std::endl;
        //         vect[i].erase(vect[i].begin() + vect[i].size() -1);
        //         // i++;

        //     }
        // }

        std::string songName = vect[1];
        std::cout<<"Song name: " << vect[1]<<std::endl;
        std::string artists = vect[3];
        std::cout<<"Artists: "<<vect[3]<<std::endl;

        artists.erase(artists.begin());
        artists.erase(artists.begin() + artists.size() - 1);

        std::vector<std::string> artistVect;
        std::stringstream ssTwo(artists);
        std::string person;
        g_.initSnapshot("YOYO");
        while(std::getline(ssTwo,person,',')) {
            
            person.erase(person.begin() + person.size() - 1);
            if (person[0] == ' ') {
                person.erase(person.begin());
            }
            person.erase(person.begin());
            artistVect.push_back(person);
            // std::cout<<person<<std::endl;
        }
        for (unsigned int i = 0; i < artistVect.size(); i++) {
            Vertex v = artistVect[i];
            // if (g_.assertVertexExists(v, ))
            g_.insertVertex(v);
            if (i == 0) {
                continue;
            }
            if (i == 1) {
                g_.insertEdge(artistVect[i], artistVect[i-1]);
                g_.setEdgeLabel(artistVect[i], artistVect[i-1], songName);
            }
            // FIXME: if needed add more artists 
        }
        
        
        std::cout<<"------------------------------------"<<std::endl;
    }
    // std::cout<<"total Lines is ::" << number_of_lines<<std::endl;
    g_.snapshot();
    // g_.print();
     std::vector<Vertex> all_nodes = g_.getVertices();
    // for(Vertex it: all_nodes) {
    //     std::cout << counter << ": " << it << ", ";
    //     counter++;
    // }
    // std::cout << "FINDING ADJACENT" << std::endl;
    // auto it = std::find(all_nodes.begin(), all_nodes.end(), "Pat Mastelotto");
    // if (it == all_nodes.end())
    //     {
    //      std::cout << "Name not here" << std::endl;
    //     } else {
    //     auto index = std::distance(all_nodes.begin(), it);
    //     std::cout << "position is:: " << index << std::endl;
    //     Vertex v = "Pat Mastelotto";
    //     getAdjacentNodes(v);
    // }
    // Vertex bfs1 = "Martin Garrix";
    // Vertex bfs2 = "Kanye West";
    // std::vector<std::pair<Vertex, std::string>> bfs = BFS_Search(bfs1, bfs2);
    // for (auto v : bfs) {
    //     std::cout << "Artist: " << v.first << " Song: " << v.second << std::endl;
    // }

    Vertex dj1 = "Bad Bunny";
    Vertex dj2 = "Shakiera";
    std::vector<std::pair<Vertex, std::string>> dj = Dijkstra(dj1, dj2);
    if (dj.empty()) {
        std::cout << "There is no path." << std::endl;
    } else {
        for (auto v : dj) {
            std::cout << "Artist: " << v.first << " Song: " << v.second << std::endl;
        }
    }
    
   
    // Vertex here = all_nodes.find("Raquel Rodriguez");
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"------------------------------------"<<std::endl;
    // getAdjacentNodes(here);
}


void MakeGraph::getAdjacentNodes(Vertex source) {
    std::vector<Vertex> adjacent_nodes_vector;
    adjacent_nodes_vector = g_.getAdjacent(source);
    std::cout << "Size: " << adjacent_nodes_vector.size() << std::endl;
    for(Vertex it: adjacent_nodes_vector) {
        std::cout << it << std::endl;
    }
}

Graph MakeGraph::getGraph() {
    return g_;
}
std::vector<std::pair<Vertex, std::string>>  MakeGraph::BFS_Search(Vertex v1, Vertex v2) {
    std::cout << "BFS" << std::endl;
    // Mark all the vertice as as not visited
    std::map<Vertex, bool> visited;
    std::vector<Vertex> v = g_.getVertices();
    for (unsigned int i = 0; i < v.size(); i++) {
        visited.insert(std::pair<Vertex,bool>(v[i], false));
    }

    // Create a queue for BFS
    std::list<Vertex> queue;
    std::vector<std::pair<Vertex, std::string>> path;
    // Mark the current node as visited and enqueue it
    visited[v1] = true;
    queue.push_back(v1);
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        v1 = queue.front();
        std::pair<Vertex, std::string> p(v1, "empty");
        path.push_back(p);
        //std::cout << v1 << std::endl;
        queue.pop_front();
        // if (!queue.empty()) {
        //     Vertex v_new = queue.front();
        //     std::vector<Vertex> vec = g_.getAdjacent(v1);
        //     if ( std::find(vec.begin(), vec.end(), v_new) != vec.end() ) {
        //         std::pair<Vertex, std::string> p(v1, g_.getEdgeLabel(v1,v_new));
        //         path.push_back(p);
        //     }
        // } else {
        //     std::pair<Vertex, std::string> p(v1, "empty");
        //     path.push_back(p);
        // }
    
 
        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        std::vector<Vertex> adj = g_.getAdjacent(v1);
        for (Vertex adjacent : adj) {
            if (!visited[adjacent]) {
                visited[adjacent] = true;
                queue.push_back(adjacent);
                std::pair<Vertex, std::string> p(adjacent, g_.getEdgeLabel(v1, adjacent));
                path.push_back(p);
            }
            if (adjacent == v2) {
                // std::pair<Vertex, std::string> p(adjacent, g_.getEdgeLabel(v1, adjacent));
                // path.push_back(p);
               return path;
            }
        }
    }
    return path;
    // std::cout << adj.size() << std::endl;
}

Vertex MakeGraph::mindist(std::map<Vertex, int> dist, std::list<Vertex> queue) {
    int min = INT_MAX;
    Vertex to_return;
    for(std::map<Vertex,int>::iterator iter = dist.begin(); iter != dist.end(); ++iter) {
        if (iter->second < min && (std::find(queue.begin(), queue.end(), iter->first) != queue.end())) {
            to_return = iter->first;
        }
    }
    return to_return;
}

std::vector<std::pair<Vertex, std::string>> MakeGraph::Dijkstra(Vertex v1, Vertex v2) {
    std::cout << "DIJKSTRA" << std::endl;
    std::map<Vertex, int> dist;
    std::map<Vertex, Vertex> prev;
    std::map<Vertex, bool> visited;
    std::list<Vertex> queue;
    std::vector<Vertex> v = g_.getVertices();
    for (unsigned int i = 0; i < v.size(); i++) {
        dist.insert(std::pair<Vertex,int>(v[i], INT_MAX));
        prev.insert(std::pair<Vertex,Vertex>(v[i], ""));
        visited.insert(std::pair<Vertex,bool>(v[i], false));
        
    }
    queue.push_back(v1);
    dist[v1] = 0;
    Vertex u = v1;
    int done = 0;
    while(!queue.empty()) {
        //u = mindist(dist, queue);
        u = queue.front();
        //std::cout << u << std::endl;
        if (u == v2) {
            done = 1;
            break;
        }
        //queue.remove(u);  
        queue.pop_front();
        std::vector<Vertex> adj = g_.getAdjacent(u);
        for (Vertex adjacent : adj) {
            // CHECK IF VERTEX IS STILL IN QUEUE --> not visited
            if (!visited[adjacent]) {
                int alt = dist[u] + 1;
                if (alt < dist[adjacent]) {
                    dist[adjacent] = alt;
                    prev[adjacent] = u;
                }
                visited[adjacent] = true;
                queue.push_back(adjacent);
            }
        }
    }
    std::vector<std::pair<Vertex, std::string>> path;
    if (done == 0) {
        return path;
    }
    if (prev[u] != "" || u == v1) {
        while(u != "") {
            std::string label;
            if (g_.edgeExists(u, prev[u]))
                label = g_.getEdgeLabel(u, prev[u]);
            else 
                label = "empty";
            std::pair<Vertex, std::string> p(u, label);
            path.insert(path.begin(), p);
            u = prev[u];
        }
    }
    return path;
}


// std::vector<Vertex> MakeGraph::BFS_Path(Vertex v1, Vertex v2) {
//     // Mark all the vertices as not visited
//     std::map<Vertex, bool> visited;
//     std::vector<Vertex> v = g_.getVertices();
//     for (unsigned int i = 0; i < v.size; i++) {
//         visited.insert(std::pair<Vertex,bool>(v[i], false))
//     }

//     // Create a queue for BFS
//     std::list<Vertex> queue;
//     std::vector<Vertex> path;
//     // Mark the current node as visited and enqueue it
//     visited[v] = true;
//     queue.push_back(v);
 
//     while(!queue.empty()) {
//         // Dequeue a vertex from queue and print it
//         v = queue.front();
//         path.push_back(v);
//         //cout << v << " ";
//         queue.pop_front();
 
//         // Get all adjacent vertices of the dequeued
//         // vertex s. If a adjacent has not been visited,
//         // then mark it visited and enqueue it
//         vector<Vertex> adj = v.getAdjacent();
//         for (Vertex adjacent : adj) {
//             if (!visited[adjacent]) {
//                 visited[adjacent] = true;
//                 queue.push_back(adjacent);
//             }
//             if (adjacent == v2) {
//                 return path;
//             }
//         }
//     }
//     return path;
       




// }
