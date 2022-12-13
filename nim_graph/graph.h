#pragma once

#include <list>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>
#include <vector>

#include "edge.h"
#include "../nim_graph/random.h"

using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::string;
using std::to_string;
using std::vector;
using std::pair;
using std::make_pair;
using std::unordered_map;


class Graph
{
public:
    Graph(bool weighted);
    Graph(bool weighted, bool directed);
    Graph(bool weighted, int numVertices, unsigned long seed);
    vector<Vertex> getAdjacent(Vertex source) const;
    vector<Vertex> getVertices() const;
    Edge getEdge(Vertex source, Vertex destination) const;
    vector<Edge> getEdges() const;
    bool vertexExists (Vertex v) const;
    bool edgeExists(Vertex source, Vertex destination) const;
    Edge setEdgeLabel(Vertex source, Vertex destination, string label);
    string getEdgeLabel(Vertex source, Vertex destination) const;
    void insertVertex(Vertex v);
    bool insertEdge(Vertex source, Vertex destination);
    const static Vertex InvalidVertex;
    const static Edge InvalidEdge;
    const static int InvalidWeight;
    const static string InvalidLabel;
    void setEdgeWeight();

private:
    mutable unordered_map<Vertex, unordered_map<Vertex, Edge>> adjacency_list;
    bool directed;
    bool weighted;
    Random random;
    int weight;
    string picName;
    bool assertVertexExists(Vertex v, string functionName) const;
    bool assertEdgeExists(Vertex source, Vertex destination, string functionName) const;
    void error(string message) const;
};
