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

        const Graph & getGraph() const;
        void PrintBaconNumber(Vertex artist);
        Vertex BestBacon(std::vector<Vertex> artists);
        // std::map<Vertex, double> pagerank();
        // Vertex BestPageRank();
        void makeMST(Vertex startingArtist, Vertex endingArtist);
        std::vector<Vertex> cycleDetection(Vertex startingArtist);
        std::map<int, int> BaconNumber(Vertex v1);
        // void PrintBaconNumber(Vertex artist);
        Vertex LowestBaconNumber();
        Vertex HighestBaconNumber();

        void pagerank();
        std::map<Vertex, double> sortPageRankMap(std::map<Vertex, double> map);
        int ArtistsPopularity(Vertex artist);
        Vertex MostPopularArtist();
        


        


    private:
        Graph g_;
        std::map<Vertex, double> pageRankMap_;
       
};