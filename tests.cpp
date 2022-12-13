#include "src/makegraph.h"

using namespace std;

MakeGraph g("tracks_twoartists.txt");

TEST_CASE("BFS") { 
   
    Vertex artist1 = "The Weeknd";
    Vertex artist2 = "Ariana Grande";
    std::vector<std::pair<Vertex, std::string>> output=g.BFS(artist1, artist2);

    //create solution vector and push in correct output
    //TODO: push back correct solution to sol
    std::vector<std::pair<Vertex, std::string>> sol;
    sol.push_back(std::pair<Vertex, std::string> ("The Weeknd", "empty"));
    sol.push_back(std::pair<Vertex, std::string> ("Calvin Harris", "Over Now (with The Weeknd)"));
    sol.push_back(std::pair<Vertex, std::string> ("Ariana Grande", "Heatstroke (feat. Young Thug Pharrell Williams & Ariana Grande)"));

    REQUIRE(sol == output);
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

    //TODO: replace "bob" w correct most popular artist
    Vertex mostPopArtist="Traditional";
    Vertex mostPopSol=g.MostPopularArtist();
    

    //TODO: Replace -1 w correct popularity
    REQUIRE(artist1popularity == 75977);
    REQUIRE(artist1popularity == 5347);

    REQUIRE(mostPopArtist == mostPopSol);

}

TEST_CASE("BaconNumber") { 

    Vertex artist1 = "The Weeknd";
    int artist1popularity= g.ArtistsPopularity(artist1);
    
    Vertex artist2 = "Ariana Grande";
    int artist2popularity= g.ArtistsPopularity(artist2);

    //TODO: replace "bob" w correct most popular artist
    Vertex mostPopArtist="Traditional";
    Vertex mostPopSol=g.MostPopularArtist();
    

    //TODO: Replace -1 w correct popularity
    REQUIRE(artist1popularity == 75977);
    REQUIRE(artist1popularity == 5347);

    REQUIRE(mostPopArtist == mostPopSol);

}


TEST_CASE("Connected Components") { 

    //create graph and run pagerank

    Vertex artist1 = "The Weeknd";
    int artist1popularity= g.ArtistsPopularity(artist1);
    
    Vertex artist2 = "Ariana Grande";
    int artist2popularity= g.ArtistsPopularity(artist2);

    //TODO: replace "bob" w correct most popular artist
    Vertex mostPopArtist="Traditional";
    Vertex mostPopSol=g.MostPopularArtist();
    

    //TODO: Replace -1 w correct popularity
    REQUIRE(artist1popularity == 75977);
    REQUIRE(artist1popularity == 5347);

    REQUIRE(mostPopArtist == mostPopSol);

}