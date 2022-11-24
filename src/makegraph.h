#pragma once

#include <vector>
#include <algorithm>

#include "../nim_graph/graph.h"
#include "../nim_graph/edge.h"

class MakeGraph {
    public:

        MakeGraph(std::string filename);
        //  void MakeGraph::BFS_Search(Vertex v1);
        // std::vector<Vertex> MakeGraph::BFS_Path(Vertex v1, Vertex v2);
        void getAdjacentNodes(Vertex source);




    private:
        Graph g_;
};