#pragma once

#include <string>
#include <limits.h>

using std::string;

typedef string Vertex;
class Edge
{
  public:
    Vertex source; 
    Vertex dest; 

    Edge(Vertex u, Vertex v)
        : source(u), dest(v), label(""), weight(-1)
    {
    }

    Edge(Vertex u, Vertex v, string lbl)
        : source(u), dest(v), label(lbl), weight(-1)
    { 
    }

    Edge(Vertex u, Vertex v, int w, string lbl)
        : source(u), dest(v), label(lbl), weight(w)
    {
    }

    Edge() : source(""), dest(""), label(""), weight(-1)
    { 
    }


    bool operator<(const Edge& other) const
    {
        return weight < other.weight;
    }

  
    string getLabel() const
    {
        return this->label;
    }

    
    int getWeight() const
    {
        return this->weight;
    }

  
    bool operator==(Edge& other) const
    {
        if (this->source != other.source)
            return false;
        if (this->dest != other.dest)
            return false;
        return true;
    }
private:
    string label;
    int weight; 

};
