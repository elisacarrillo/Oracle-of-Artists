#include "makegraph.h"
#include "../nim_graph/graph.h"
#include "../nim_graph/edge.h"


int main() {
    MakeGraph g = MakeGraph("tracks_twoartists.txt");

    Vertex artist1 = g.getRandomArtist();
    Vertex artist2 = g.getRandomArtist();

    //ENTER YOUR OWN ARTISTS HERE
    // Vertex artist1 = "Idina Menzel";
    // Vertex artist2 = "Shawn Mendes";

    std::cout << "Artists 1 is: " << artist1 << std::endl;
    std::cout << "Artists 2 is: " << artist2 << std::endl;
    
    
    std::cout<<"-------------RUNNING BFS---------------"<<std::endl;
    g.BFS(artist1, artist2);
    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"-------------RUNNING MST---------------"<<std::endl;
    g.makeMST(artist1, artist2);
    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"-------------RUNNING BETWEENNESS CENTRALITY---------------"<<std::endl;
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
    int numComponents = g.countConnectedComponents();
    std::cout<<"Number of connected components: "<<numComponents<<std::endl;
    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"----------------------------"<<std::endl;
    //get number of vertices
    int numVertices = g.getGraph().getVertices().size();
    std::cout<<"Number of vertices: "<<numVertices<<std::endl;
    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"-------------BUILDING HISTOGRAM OF CONNECTED COMPONENTS---------------"<<std::endl;
    g.makeHistogram();
    std::cout<<"----------------------------"<<std::endl;
    std::cout<<"----------------------------"<<std::endl;

    return 0;
}