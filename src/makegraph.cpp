#include "makegraph.h"


#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

MakeGraph::MakeGraph(string filename) : g_(false, false) {
    //for each line create array of artists and make node the name of the song
    std::ifstream infile(filename);
    std::string line;
    std::cout<<"-------------BUILDING GRAPH---------------"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
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
    std::cout<<"-------------BUILDING PAGERANK---------------"<<std::endl;
    pagerank();

}

//get graph
Graph MakeGraph::getGraph() {
    return g_;
}

// Get Shortest Path Playist from v1 to v2 using BFS
std::vector<std::pair<Vertex, std::string>> MakeGraph::BFS(Vertex v1, Vertex v2) {
    std::cout << "Shortest Path From " << v1 << " To " << v2 << " IS!!!" << std::endl;
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
        if (u == v2) {
            done = 1;
            break;
        }
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
    printPathBFS(path);
    return path;

}
//print path
void MakeGraph::printPathBFS(std::vector<std::pair<Vertex, std::string>> path) {
    for (unsigned int i = 0; i < path.size(); i++) {
        std::cout << path[i].first << " " << std::endl;
        if (path[i].second != "empty") {
            std::cout << " - " << path[i].second << " - " << std::endl;
        }
    }
    std::cout << std::endl;
}

// Get Bacon Table using BFS AKA betweenness centrality
std::map<int, int> MakeGraph::BaconNumber(Vertex v1) {
    // std::cout << v1<<" NUMBER IS!!" << std::endl;
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

// Print Bacon Table, Total Linkable Artists, Weighted Total, and Print Weighted Bacon Number
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
    std::cout << "Average " << artist << " Number: " << weighted_total / total << std::endl;
    
}

//get artist with lowest Bacon number
Vertex MakeGraph::LowestBaconNumber() {
    std::vector<Vertex> v = g_.getVertices();
    std::map<Vertex, int> lowest;
    for (Vertex artist : v) {
        std::map <int, int> bacon_number = BaconNumber(artist);
        double total = 0;
        for (auto it = bacon_number.begin(); it != bacon_number.end(); it++) {
            total += it->second;
        }
        double weighted_total = 0;
        for (auto it = bacon_number.begin(); it != bacon_number.end(); it++) {
            weighted_total += it->first * it->second;
        }
        lowest.insert(std::pair<Vertex, int>(artist, weighted_total / total));
    }
    int min = INT_MAX;
    Vertex min_artist;
    for (auto it = lowest.begin(); it != lowest.end(); it++) {
        if (it->second < min) {
            min = it->second;
            min_artist = it->first;
        }
    }
    std::cout<<"Artist with lowest Bacon Number: "<<min_artist<<std::endl;
    return min_artist;
}

//get artist with highest Bacon number
Vertex MakeGraph::HighestBaconNumber() {
    std::vector<Vertex> v = g_.getVertices();
    std::map<Vertex, int> highest;
    for (Vertex artist : v) {
        std::map <int, int> bacon_number = BaconNumber(artist);
        double total = 0;
        for (auto it = bacon_number.begin(); it != bacon_number.end(); it++) {
            total += it->second;
        }
        double weighted_total = 0;
        for (auto it = bacon_number.begin(); it != bacon_number.end(); it++) {
            weighted_total += it->first * it->second;
        }
        highest.insert(std::pair<Vertex, int>(artist, weighted_total / total));
    }
    int max = 0;
    Vertex max_artist;
    for (auto it = highest.begin(); it != highest.end(); it++) {
        if (it->second > max) {
            max = it->second;
            max_artist = it->first;
        }
    }
    std::cout<<"Artist with highest Bacon Number: "<<max_artist<<std::endl;

    return max_artist;
}

//implement pagerank to get most popular artist
void MakeGraph::pagerank() {
    std::vector<Vertex> v = g_.getVertices();
    std::map<Vertex, double> pagerank;
    for (Vertex artist : v) {
        pagerank.insert(std::pair<Vertex, double>(artist, 1.0));
    }
    for (int i = 0; i < 10; i++) {
        std::cout << "PageRank Iteration: " << i << std::endl;
        for (Vertex artist : v) {
            std::vector<Vertex> adj = g_.getAdjacent(artist);
            double sum = 0;
            for (Vertex adjacent : adj) {
                sum += pagerank[adjacent] / g_.getAdjacent(adjacent).size();
            }
            pagerank[artist] = 0.15 + 0.85 * sum;
        }
    }
    pageRankMap_ = sortPageRankMap(pagerank);
}


//sort pagerank map by value
std::map<Vertex, double> MakeGraph::sortPageRankMap(std::map<Vertex, double> map) {
    std::vector<std::pair<Vertex, double>> vec;
    for (auto it = map.begin(); it != map.end(); it++) {
        vec.push_back(std::pair<Vertex, double>(it->first, it->second));
    }
    std::sort(vec.begin(), vec.end(), [](const std::pair<Vertex, double> &left, const std::pair<Vertex, double> &right) {
        return left.second > right.second;
    });
    std::map<Vertex, double> sorted;
    for (auto it = vec.begin(); it != vec.end(); it++) {
        sorted.insert(std::pair<Vertex, double>(it->first, it->second));
    }
    return sorted;
}

//get the index of an artist in a map
int MakeGraph::ArtistsPopularity(Vertex artist) {
    std::map<Vertex, double> map = pageRankMap_;
    int i = 0;
    for (auto it = map.begin(); it != map.end(); it++) {
        if (it->first == artist) {
            std::cout<< artist << " is the "<< i << " most popular artist out of " << g_.getVertices().size() << " using PageRank"<<std::endl;
            return i;

        }
        i++;
    }
    
    return -1;
}


//get highest ranked artist pagerank
Vertex MakeGraph::MostPopularArtist() {
    std::map<Vertex, double> pagerank = pageRankMap_;
    double max = 0;
    Vertex best;
    for (auto it = pagerank.begin(); it != pagerank.end(); it++) {
        if (it->second > max) {
            max = it->second;
            best = it->first;
        }
    }
    std::cout<<"Most popular artist through PageRank: "<< best<<std::endl;
    return best;
}


//Prims algorithm to get shortest path from starting artist to ending artist for unweighted graph
std::vector<std::pair<Vertex, std::string>> MakeGraph::makeMST(Vertex startingArtist, Vertex endingArtist) {
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
        if (visited[u] == false) {
            visited[u] = true;
            std::vector<Vertex> adj = g_.getAdjacent(u);
            for (Vertex artist : adj) {
                if (visited[artist] == false && distance[artist] > 1) {
                    distance[artist] = 1;
                    pq.push(std::pair<Vertex, double>(artist, distance[artist]));
                    parent[artist] = u;
                }
            }
        }
    }
    
    std::cout << "Playlist from " << startingArtist << " to " << endingArtist << " is: " << std::endl;
    std::vector<std::pair<Vertex, std::string>> path;
    Vertex current = endingArtist;
    while (current != startingArtist) {
        std::string songs = g_.getEdgeLabel(parent[current], current);
        path.push_back(std::pair<Vertex, std::string>(current, songs));
        current = parent[current];
    }
    std::reverse(path.begin(), path.end());
    printPathBFS(path);
    return path;
}



//count connected components using DFS
int MakeGraph::countConnectedComponents() {
    std::vector<Vertex> v = g_.getVertices();
    std::map<Vertex, bool> visited;
    for (Vertex artist : v) {
        visited.insert(std::pair<Vertex, bool>(artist, false));
    }
    int count = 0;
    for (Vertex artist : v) {
        if (!visited[artist]) {
            count++;
            connectedComponentsHelper(artist, visited);
        }
    }
    return count;
}
//connected components DFS
void MakeGraph::connectedComponentsHelper(Vertex u, std::map<Vertex, bool> &visited) {
    visited[u] = true;
    std::vector<Vertex> adj = g_.getAdjacent(u);
    for (Vertex artist : adj) {
        if (!visited[artist]) {
            connectedComponentsHelper(artist, visited);
        }
    }
}

// make historgram with sizes of connetcted components
void MakeGraph::makeHistogram() {
    std::vector<Vertex> v = g_.getVertices();
    std::map<Vertex, bool> visited;
    for (Vertex artist : v) {
        visited.insert(std::pair<Vertex, bool>(artist, false));
    }
    std::map<int, int> histogram;
    for (Vertex artist : v) {
        if (!visited[artist]) {
            int count = 0;
            histogramHelper(artist, visited, count);
            if (histogram.find(count) == histogram.end()) {
                histogram.insert(std::pair<int, int>(count, 1));
            } else {
                histogram[count]++;
            }
        }
    }
    for (auto v : histogram) {
        std::cout << "Size: " << v.first << " Number of components: " << v.second << std::endl;
    }
}

//connectedComponentsHelper for histogram
void MakeGraph::histogramHelper(Vertex u, std::map<Vertex, bool> &visited, int &count) {
    visited[u] = true;
    count++;
    std::vector<Vertex> adj = g_.getAdjacent(u);
    for (Vertex artist : adj) {
        if (!visited[artist]) {
            histogramHelper(artist, visited, count);
        }
    }
}


