#include "makegraph.h"
#include "../nim_graph/graph.h"
#include "../nim_graph/edge.h"


int main() {
    MakeGraph g = MakeGraph("tracks_twoartists.txt");
    Vertex artist1 = "Idina Menzel";
    Vertex artist2 = "Shawn Mendes";
    g.PrintShortestPath(artist1, artist2);
    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"----------------------------"<<std::endl;
    g.PrintBaconNumber(artist1);
    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"----------------------------"<<std::endl;
    g.PrintBaconNumber(artist2);
    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"----------------------------"<<std::endl;
    g.ArtistsPopularity(artist1);
    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"----------------------------"<<std::endl;
    g.ArtistsPopularity(artist2);
    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"----------------------------"<<std::endl;
    g.MostPopularArtist();
    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"----------------------------"<<std::endl;
    

    return 0;
}