#pragma once

#include <vector>
#include <algorithm>
#include <map>

#include "../nim_graph/graph.h"
#include "../nim_graph/edge.h"

class MakeGraph {
    public:

        MakeGraph(std::string filename);
        void getAdjacentNodes(Vertex source);
        Graph getGraph();
        std::vector<std::pair<Vertex, std::string>> BFS_Search(Vertex v1, Vertex v2);
        std::vector<std::pair<Vertex, std::string>> Dijkstra(Vertex v1, Vertex v2);
        Vertex mindist(std::map<Vertex, int> dist, std::list<Vertex> queue);
        std::map<int, int> BaconNumber(Vertex v1);
        void PrintShortestPath(Vertex artist1, Vertex artist2);
        const Graph & getGraph() const;
        void PrintBaconNumber(Vertex artist);
        Vertex BestBacon(std::vector<Vertex> artists);
        std::map<Vertex, double> pagerank();
        Vertex BestPageRank();
        void makeMST(Vertex startingArtist, Vertex endingArtist);
        std::vector<Vertex> cycleDetection(Vertex startingArtist);
        




    private:
        Graph g_;
       
};