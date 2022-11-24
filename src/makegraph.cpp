#include "makegraph.h"

#include <iostream>
#include <string>
#include <vector>
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


    int counter = 0;
    std::vector<Vertex> all_nodes = g_.getVertices();
    for(Vertex it: all_nodes) {
        std::cout << counter << ": " << it << ", ";
        counter++;
    }
    auto it = std::find(all_nodes.begin(), all_nodes.end(), "Raquel Rodriguez");
    if (it == all_nodes.end())
        {
         std::cout << "Name not here" << std::endl;
        } else {
        auto index = std::distance(all_nodes.begin(), it);
        std::cout << "position is:: " << index << std::endl;
    }
    // Vertex here = all_nodes.find("Raquel Rodriguez");
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"------------------------------------"<<std::endl;
    // getAdjacentNodes(here);
}


void MakeGraph::getAdjacentNodes(Vertex source) {
    std::vector<Vertex> adjacent_nodes_vector;
    adjacent_nodes_vector = g_.getAdjacent(source);
    for(Vertex it: adjacent_nodes_vector) {
        std::cout << it << std::endl;
    }
}
// void MakeGraph::BFS_Search(Vertex v1) {
//     // Mark all the vertices as not visited
//     std::map<Vertex, bool> visited;
//     std::vector<Vertex> v = g_.getVertices();
//     for (unsigned int i = 0; i < v.size; i++) {
//         visited.insert(std::pair<Vertex,bool>(v[i], false))
//     }

//     // Create a queue for BFS
//     std::list<Vertex> queue;
 
//     // Mark the current node as visited and enqueue it
//     visited[v] = true;
//     queue.push_back(v);
 
//     while(!queue.empty())
//     {
//         // Dequeue a vertex from queue and print it
//         v = queue.front();
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
//         }
//     }
// }


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
