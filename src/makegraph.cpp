#include "makegraph.h"

#include <chrono>
#include <thread>
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
    std::cout<<"BUILDING GRAPH"<<std::endl;
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
    // Vertex artist4 = BestPageRank();
    // std::cout<<"Most popular artist: "<<artist4<<std::endl;

    // std::cout<<"------------------------------------"<<std::endl;
    // std::cout<<"------------------------------------"<<std::endl;
    // // std::vector<Vertex> artists = g_.getVertices();
    // // std::cout << "BEST CENTER AWARD GOES TO..." << BestBacon(artists) << std::endl;
    // std::cout<<"MST"<<std::endl;
    // makeMST(artist1, artist2);

    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"Building Page Rank"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    pagerank();
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"Cycle Detection"<<std::endl;
    std::vector<Vertex> cycle = cycleDetection(artist1);
    //print cycle
    for (unsigned int i = 0; i < cycle.size(); i++) {
        std::cout<<cycle[i]<<std::endl;
    }
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"------------------------------------"<<std::endl;

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
    return path;
}

//Get Minimum Distance Vertex from Queue of Vertices 
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

void MakeGraph::PrintShortestPath(Vertex artist1, Vertex artist2) {
    std::vector<std::pair<Vertex, std::string>> path = BFS(artist1, artist2);
    if (path.empty()) {
        std::cout << "There is no path." << std::endl;
    } else {
        for (auto v : path) {
            std::cout << "Artist: " << v.first << " Song: " << v.second << std::endl;
        }
    }
}

// Get Bacon Table using BFS
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


// cycle detection using BFS from starting artist to ending artist return the cycle if there is one
std::vector<Vertex> MakeGraph::cycleDetection(Vertex startingArtist) {
    std::vector<Vertex> v = g_.getVertices();
    std::map<Vertex, Vertex> parent;
    std::map<Vertex, bool> visited;
    for (Vertex artist : v) {
        parent.insert(std::pair<Vertex, Vertex>(artist, ""));
        visited.insert(std::pair<Vertex, bool>(artist, false));
    }
    std::queue<Vertex> q;
    q.push(startingArtist);
    visited[startingArtist] = true;
    // int count = 0;
    while (!q.empty()) {
        // std::cout<<"Count: "<<count++<<std::endl;
        Vertex u = q.front();
        q.pop();
        std::vector<Vertex> adj = g_.getAdjacent(u);
        for (Vertex artist : adj) {
            // std::cout<<"artist searched : " <<artist<<std::endl;
            if (!visited[artist]) {
                visited[artist] = true;
                parent[artist] = u;
                q.push(artist);
            } else if (parent[u] != artist) {
                std::vector<Vertex> cycle;
                Vertex current = artist;
                while (current != u && current != "") {
                    // std::cout<<"Current: "<<current<<std::endl;
                    cycle.push_back(current);
                    current = parent[current];
                }
                cycle.push_back(u);
                std::reverse(cycle.begin(), cycle.end());
                return cycle;
            }
        }
    }
    std::vector<Vertex> empty;
    return empty;
}

