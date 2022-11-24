#include "makegraph.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

MakeGraph::MakeGraph(string filename) : g_(false, false) {
    //for each line create array of artists and make node the name of the song
    std::ifstream infile(filename);
    // file.open(filename);
    std::string line;
    std::cout<<"here"<<std::endl;
    // if (infile.is_open()) {
        // std::getline(infile, line);
        // std::cout<<line<<std::endl;
    while (std::getline(infile, line)) {
        std::cout<<"here 2"<<std::endl;
        std::string content;
        std::vector<std::string> vect;
        std::stringstream ss(line);
            // 683,"12 Études, Op. 25: No. 7 in C-Sharp Minor","['Frédéric Chopin', 'Vladimir Horowitz']",0.0311
        while(std::getline(ss,content,'"')) {
            vect.push_back(content);
            std::cout<<content<<std::endl;

        }
        std::cout<<vect.size()<<std::endl;
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
        std::cout<<vect[1]<<std::endl;
        std::string artists = vect[3];
        std::cout<<"3: "<<vect[3]<<std::endl;

        

    
        artists.erase(artists.begin());
        artists.erase(artists.begin() + artists.size() - 1);

        std::cout<<"song name: "<<songName<<std::endl;
        std::cout<<"artists: "<<artists<<std::endl;

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
            std::cout<<person<<std::endl;
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
        // g_.print();
        std::cout<<"------------------------------------"<<std::endl;
       
        g_.savePNG("yoyo");
        // g_.insertEdge()

        // Graph newGraph = new Graph(false);
        // g_.insertVertex( /v);

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
