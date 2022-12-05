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
        // std::vector<Vertex> MakeGraph::BFS_Path(Vertex v1, Vertex v2);
        




    private:
        Graph g_;
       
};