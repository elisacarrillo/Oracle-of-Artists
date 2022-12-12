#pragma once

#include <vector>
#include <algorithm>
#include <map>

#include "../nim_graph/graph.h"
#include "../nim_graph/edge.h"

class MakeGraph {
    public:

        MakeGraph(std::string filename);
        Graph getGraph();

        std::vector<std::pair<Vertex, std::string>> BFS(Vertex v1, Vertex v2);
        Vertex mindist(std::map<Vertex, int> dist, std::list<Vertex> queue);
        void PrintShortestPath(Vertex artist1, Vertex artist2);


        std::map<int, int> BaconNumber(Vertex v1);
        void PrintBaconNumber(Vertex artist);
        Vertex LowestBaconNumber();
        Vertex HighestBaconNumber();


        void pagerank();
        std::map<Vertex, double> sortPageRankMap(std::map<Vertex, double> map);
        int ArtistsPopularity(Vertex artist);
        Vertex MostPopularArtist();


        void makeMST(Vertex startingArtist, Vertex endingArtist);
        std::vector<Vertex> cycleDetection(Vertex startingArtist);
        
        std::vector<std::pair<Vertex, Vertex>> getBridges();
        void bridgesHelper(Vertex u, std::map<Vertex, bool> &visited, std::map<Vertex, int> &discovery, std::map<Vertex, int> &low, std::map<Vertex, Vertex> &parent, std::vector<std::pair<Vertex, Vertex>> &bridges, int &time);
        void printBridges();
        
        int countConnectedComponents();
        void connectedComponentsHelper(Vertex u, std::map<Vertex, bool> &visited);
        void makeHistogram();
        void connectedComponentsHelper(Vertex u, std::map<Vertex, bool> &visited, int &count);
        void forceDirectedGraph();

        std::vector<Vertex> getConnectedComponent(Vertex u);
        void connectedComponentsHelper(Vertex u, std::map<Vertex, bool> &visited, std::vector<Vertex> &component);
    private:
        Graph g_;
        std::map<Vertex, double> pageRankMap_;
       
};