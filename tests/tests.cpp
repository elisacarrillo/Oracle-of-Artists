#include "../src/makegraph.h"

using namespace std;
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#include <stdexcept>
#include <vector>
#include <string>
#include <utility>
#include <map>



MakeGraph g("tracks_twoartists.txt");

TEST_CASE("BFS") { 
   
    Vertex artist1 = "The Weeknd";
    Vertex artist2 = "Ariana Grande";
    Vertex artist3 = "Bach";
    std::vector<std::pair<Vertex, std::string>> output=g.BFS(artist1, artist2);
    std::vector<std::pair<Vertex, std::string>> invalidOutput=g.BFS(artist1, artist3);

    //create solution vector and push in correct output
    //TODO: push back correct solution to sol
    std::vector<std::pair<Vertex, std::string>> sol;
    sol.push_back(std::pair<Vertex, std::string> ("The Weeknd", "empty"));
    sol.push_back(std::pair<Vertex, std::string> ("Calvin Harris", "Over Now (with The Weeknd)"));
    sol.push_back(std::pair<Vertex, std::string> ("Ariana Grande", "Heatstroke (feat. Young Thug Pharrell Williams & Ariana Grande)"));

    REQUIRE(sol == output);
    REQUIRE(invalidOutput == std::vector<std::pair<Vertex, std::string>>());
}

TEST_CASE("Prim") {

    //run prim and save path to var path
    Vertex artist1 = "The Weeknd";
    Vertex artist2 = "Ariana Grande";
    std::vector<std::pair<Vertex, std::string>> path=g.makeMST(artist1, artist2);

    //set firstInPath and lastInPath
    std::pair<Vertex, std::string> firstInPath= path[0];
    std::pair<Vertex, std::string> lastInPath= path[path.size()-1];

    //create and fill solution variables sol1 and sol2;
    //TODO: set sol1 and sol2 to correct answers
    std::pair<Vertex, std::string> sol1=std::pair<Vertex,std::string>("Calvin Harris", "Over Now (with The Weeknd)") ;
    std::pair<Vertex, std::string> sol2=std::pair<Vertex,std::string>("Ariana Grande", "Heatstroke (feat. Young Thug Pharrell Williams & Ariana Grande)");

    REQUIRE(firstInPath == sol1);
    REQUIRE(lastInPath == sol2);


}

TEST_CASE("PageRank") { 

    Vertex artist1 = "The Weeknd";
    int artist1popularity= g.ArtistsPopularity(artist1);
    
    Vertex artist2 = "Ariana Grande";
    int artist2popularity= g.ArtistsPopularity(artist2);

    Vertex mostPopArtist="Traditional";
    Vertex mostPopSol=g.MostPopularArtist();
    

    REQUIRE(artist1popularity == 75977);
    REQUIRE(artist2popularity == 5347);

    REQUIRE(mostPopArtist == mostPopSol);

}

TEST_CASE("BetweenessCentrality") { 

    Vertex artist1 = "The Weeknd";
    std::map<int, int> artist1popularity= g.BaconNumber(artist1);
    
    Vertex artist2 = "Ariana Grande";
    std::map<int, int> artist2popularity= g.BaconNumber(artist2);



    //TODO: Replace -1 w correct popularity
    REQUIRE(artist1popularity.begin()->first == 0);
    REQUIRE(artist1popularity.begin()->second == 1);
    REQUIRE(artist2popularity.begin()->first == 0);
    REQUIRE(artist2popularity.begin()->second == 1);

    auto iterator1 = artist1popularity.begin();
    iterator1++;
    REQUIRE(iterator1->first == 1);
    REQUIRE(iterator1->second == 12);

    auto iterator2 = artist2popularity.begin();
    iterator2++;
    REQUIRE(iterator2->first == 1);
    REQUIRE(iterator2->second == 38);

    iterator1++;
    REQUIRE(iterator1->first == 2);
    REQUIRE(iterator1->second == 383);
    iterator2++;
    REQUIRE(iterator2->first == 2);
    REQUIRE(iterator2->second == 487);

}


TEST_CASE("Connected Components") { 


    
    int numComponents= g.countConnectedComponents();
    
    int numVertices = g.getGraph().getVertices().size();

    

    REQUIRE(numComponents == 7898);
    REQUIRE(numVertices == 86051);
    

}