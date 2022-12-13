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
        // Vertex mindist(std::map<Vertex, int> dist, std::list<Vertex> queue);
        void printPathBFS(std::vector<std::pair<Vertex, std::string>> path);


        std::map<int, int> BaconNumber(Vertex v1);
        void PrintBaconNumber(Vertex artist);
        Vertex LowestBaconNumber();
        Vertex HighestBaconNumber();


        void pagerank();
        std::map<Vertex, double> sortPageRankMap(std::map<Vertex, double> map);
        int ArtistsPopularity(Vertex artist);
        Vertex MostPopularArtist();


        std::vector<std::pair<Vertex, std::string>> makeMST(Vertex startingArtist, Vertex endingArtist);
                
        int countConnectedComponents();
        void connectedComponentsHelper(Vertex u, std::map<Vertex, bool> &visited);
        void makeHistogram();
        void histogramHelper(Vertex u, std::map<Vertex, bool> &visited, int &count);
    private:
        Graph g_;
        std::map<Vertex, double> pageRankMap_;
       
};