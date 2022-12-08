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
        std::string content;
        std::vector<std::string> vect;
        std::stringstream ss(line);
        while(std::getline(ss,content,'"')) {
            vect.push_back(content);
        }

        std::string songName = vect[1];
        std::cout<<"Song name: " << vect[1]<<std::endl;
        std::string artists = vect[3];
        std::cout<<"Artists: "<<vect[3]<<std::endl;

        artists.erase(artists.begin());
        artists.erase(artists.begin() + artists.size() - 1);

        std::vector<std::string> artistVect;
        std::stringstream ssTwo(artists);
        std::string person;
        g_.initSnapshot("Artist Graph");
        while(std::getline(ssTwo,person,',')) {
            
            person.erase(person.begin() + person.size() - 1);
            if (person[0] == ' ') {
                person.erase(person.begin());
            }
            person.erase(person.begin());
            artistVect.push_back(person);
        }
        for (unsigned int i = 0; i < artistVect.size(); i++) {
            Vertex v = artistVect[i];
            g_.insertVertex(v);
            if (i == 0) {
                continue;
            }
            for (unsigned int j = 1; j < artistVect.size();j++) {
                if (j <= i) {
                    g_.insertEdge(artistVect[i], artistVect[i-j]);
                    g_.setEdgeLabel(artistVect[i], artistVect[i-j], songName);
                }
                
            }
        }
        
        std::cout<<"------------------------------------"<<std::endl;
    }
    g_.snapshot();

    Vertex artist1 = "The Weeknd";
    Vertex artist2 = "Ariana Grande";
    PrintShortestPath(artist1, artist2);

    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"------------------------------------"<<std::endl;

    Vertex artist3 = "The Weeknd";
    PrintBaconNumber(artist3);
    
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"------------------------------------"<<std::endl;
    //get most popular artist
    Vertex artist4 = BestPageRank();
    std::cout<<"Most popular artist: "<<artist4<<std::endl;

    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"------------------------------------"<<std::endl;
    // std::vector<Vertex> artists = g_.getVertices();
    // std::cout << "BEST CENTER AWARD GOES TO..." << BestBacon(artists) << std::endl;
    std::cout<<"MST"<<std::endl;
    makeMST(artist1, artist2);
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"------------------------------------"<<std::endl;




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
               return path;
            }
        }
    }
    return path;
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
        // std::cout<<"one"<<std::endl;
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
        // std::cout<<"two"<<std::endl;
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
        // std::cout<<"three"<<std::endl;
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

std::map<int, int> MakeGraph::BaconNumber(Vertex v1) {
    std::cout << v1<<" NUMBER" << std::endl;
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
    while(!queue.empty()) {
        //u = mindist(dist, queue);
        u = queue.front();  
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
    std::map <int, int> to_return;
    for (auto it = dist.begin(); it != dist.end(); it++) {
        if (it->second != INT_MAX) {
            if (to_return.find(it->second) == to_return.end()) {
                to_return.insert( std::pair<int,int>(it->second,1));
            } else {
                to_return[it->second] =  to_return[it->second] + 1;
            }
        }
    }
    return to_return;
}

void MakeGraph::PrintShortestPath(Vertex artist1, Vertex artist2) {
    std::vector<std::pair<Vertex, std::string>> path = Dijkstra(artist1, artist2);
    if (path.empty()) {
        std::cout << "There is no path." << std::endl;
    } else {
        for (auto v : path) {
            std::cout << "Artist: " << v.first << " Song: " << v.second << std::endl;
        }
    }
}

const Graph & MakeGraph::getGraph() const {
  return g_;
}

void MakeGraph::PrintBaconNumber(Vertex artist) {
    std::map <int, int> bacon_number = BaconNumber(artist);
    if (bacon_number.empty()) {
        std::cout << "This artist has no connections" << std::endl;
    } else {
        for (auto it = bacon_number.begin(); it != bacon_number.end(); it++) {
            std::cout << artist <<  " Number: " << it->first << " # of People: " << it->second << std::endl;
        }
    }

    //get total amount of linkable artists
    double total = 0;
    for (auto it = bacon_number.begin(); it != bacon_number.end(); it++) {
        total += it->second;
    }
    std::cout << "Total Linkable Artists: " << total << std::endl;
    //get Weighted total of linkable actors
    double weighted_total = 0;
    for (auto it = bacon_number.begin(); it != bacon_number.end(); it++) {
        weighted_total += it->first * it->second;
    }
    std::cout << "Weighted Total: " << weighted_total << std::endl;
    //get average artists number
    std::cout << "Average" << artist << "Number: " << weighted_total / total << std::endl;
    


}

Vertex MakeGraph::BestBacon(std::vector<Vertex> artists) {
    std::map<Vertex, double> average;
    for (Vertex artist : artists) {
        std::map <int, int> bacon_number = BaconNumber(artist);
        //get total amount of linkable artists
        double total = 0;
        for (auto it = bacon_number.begin(); it != bacon_number.end(); it++) {
            total += it->second;
        }
        //get Weighted total of linkable actors
        double weighted_total = 0;
        for (auto it = bacon_number.begin(); it != bacon_number.end(); it++) {
            weighted_total += it->first * it->second;
        }
        //get average artists number
        average.insert(std::pair<Vertex, double>(artist, weighted_total / total));
    }
    double min = INT_MAX;
    Vertex best;
    for (auto it = average.begin(); it != average.end(); it++) {
        if (it->second < min) {
            min = it->second;
            best = it->first;
        }
    }
    return best;
}
//implement pagerank to get most popular artist
std::map<Vertex, double> MakeGraph::pagerank() {
    std::vector<Vertex> v = g_.getVertices();
    std::map<Vertex, double> pagerank;
    for (Vertex artist : v) {
        pagerank.insert(std::pair<Vertex, double>(artist, 1.0));
    }
    for (int i = 0; i < 10; i++) {
        std::cout << "Round: " << i << std::endl;
        for (Vertex artist : v) {
            std::vector<Vertex> adj = g_.getAdjacent(artist);
            double sum = 0;
            for (Vertex adjacent : adj) {
                sum += pagerank[adjacent] / g_.getAdjacent(adjacent).size();
            }
            pagerank[artist] = 0.15 + 0.85 * sum;
        }
    }
    return pagerank;
}

Vertex MakeGraph::BestPageRank() {
    //get top 10g artists
    std::map<Vertex, double> pagerank = this->pagerank();
    std::vector<std::pair<Vertex, double>> top10;
    for (auto it = pagerank.begin(); it != pagerank.end(); it++) {
        if (top10.size() < 10) {
            top10.push_back(std::pair<Vertex, double>(it->first, it->second));
        } else {
            std::pair<Vertex, double> min = top10[0];
            int index = 0;
            for (unsigned int i = 0; i < top10.size(); i++) {
                if (top10[i].second < min.second) {
                    min = top10[i];
                    index = i;
                }
            }
            if (it->second > min.second) {
                top10[index] = std::pair<Vertex, double>(it->first, it->second);
            }
        }
    }
    //sort top 10 artists
    std::sort(top10.begin(), top10.end(), [](const std::pair<Vertex, double> &left, const std::pair<Vertex, double> &right) {
        return left.second > right.second;
    });
    //print top 10
    for (auto it = top10.begin(); it != top10.end(); it++) {
        std::cout << it->first << " " << it->second << std::endl;
    }

    double max = 0;
    Vertex best;
    for (auto it = pagerank.begin(); it != pagerank.end(); it++) {
        if (it->second > max) {
            max = it->second;
            best = it->first;
        }
    }
    return best;
}
 
//implement Prims using a priority queue to get shortest path from starting artist to ending artist
void MakeGraph::makeMST(Vertex startingArtist, Vertex endingArtist) {
    std::vector<Vertex> v = g_.getVertices();
    std::map<Vertex, double> distance;
    std::map<Vertex, Vertex> parent;
    std::map<Vertex, bool> visited;
    for (Vertex artist : v) {
        distance.insert(std::pair<Vertex, double>(artist, INT_MAX));
        parent.insert(std::pair<Vertex, Vertex>(artist, ""));
        visited.insert(std::pair<Vertex, bool>(artist, false));
    }
    distance[startingArtist] = 0;
    std::priority_queue<std::pair<Vertex, double>, std::vector<std::pair<Vertex, double>>, std::greater<std::pair<Vertex, double>>> pq;
    pq.push(std::pair<Vertex, double>(startingArtist, 0));
    while (!pq.empty()) {
        Vertex u = pq.top().first;
        pq.pop();
        visited[u] = true;
        std::vector<Vertex> adj = g_.getAdjacent(u);
        for (Vertex artist : adj) {
            if (!visited[artist]) {
                double weight = g_.getEdgeWeight(u, artist);
                if (distance[artist] > weight) {
                    distance[artist] = weight;
                    parent[artist] = u;
                    pq.push(std::pair<Vertex, double>(artist, distance[artist]));
                }
            }
        }
    }
    std::vector<std::pair<Vertex, std::string>> path;
    Vertex current = endingArtist;
    while (current != startingArtist) {
        std::string songs = g_.getEdgeLabel(parent[current], current);
        path.push_back(std::pair<Vertex, std::string>(current, songs));
        // for (std::string song : songs) {
        //     ;
        // }
        current = parent[current];
    }
    std::reverse(path.begin(), path.end());
    for (auto v : path) {
        std::cout << "Artist: " << v.first << " Song: " << v.second << std::endl;
    }
}
