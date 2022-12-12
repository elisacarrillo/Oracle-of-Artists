#include "src/makegraph.h"

using namespace std;

TEST_CASE("BFS") { 

    //create graph and run BFS, saves result to output
    MakeGraph g("tracks_twoartists.txt");
    Vertex artist1 = "The Weeknd";
    Vertex artist2 = "Ariana Grande";
    std::vector<std::pair<Vertex, std::string>> output=g.BFS(artist1, artist2);

    //create solution vector and push in correct output
    //TODO: push back correct solution to sol
    std::vector<std::pair<Vertex, std::string>> sol;
    sol.push_back();
    sol.push_back();
    sol.push_back();

    REQUIRE(sol == output);
}

TEST_CASE("Prim") { 

    //run prim and save path to var path
    MakeGraph g("tracks_twoartists.txt");
    Vertex artist1 = "The Weeknd";
    Vertex artist2 = "Ariana Grande";
    std::vector<std::pair<Vertex, std::string>> path=g.makeMST(artist1, artist2);

    //set firstInPath and lastInPath
    std::pair<Vertex, std::string> firstInPath= path[0];
    std::pair<Vertex, std::string> lastInPath= path[path.size()-1];

    //create and fill solution variables sol1 and sol2;
    //TODO: set sol1 and sol2 to correct answers
    std::pair<Vertex, std::string> sol1=pair();
    std::pair<Vertex, std::string> sol2=pair();

    REQUIRE(firstInPath == sol1);
    REQUIRE(lastInPath == sol2);


}

TEST_CASE("PageRank") { 

    //create graph and run pagerank
    MakeGraph g("tracks_twoartists.txt");
    g.pageRank();

    Vertex artist1 = "The Weeknd";
    int artist1popularity= g.ArtistsPopularity(artist1);
    
    Vertex artist2 = "Ariana Grande";
    int artist2popularity= g.ArtistsPopularity(artist2);

    //TODO: replace "bob" w correct most popular artist
    Vertex mostPopArtist="bob";
    Vertex mostPopSol=g.MostPopularArtist();
    

    //TODO: Replace -1 w correct popularity
    REQUIRE(artist1popularity == -1);
    REQUIRE(artist1popularity == -1);

    REQUIRE(mostPopArtist == mostPopSol);


}

TEST_CASE("CycleDetection") { 

    //create graph and run cycle detection, saves result to output
    MakeGraph g("tracks_twoartists.txt");
    Vertex artist = "The Weeknd";
    
    std::vector<Vertex> output=g.cycleDetection(artist1, artist2);

    //create solution vector and push in correct output
    //TODO: push back correct solution to sol
    std::vector<Vertex> sol;
    sol.push_back();
    sol.push_back();
    sol.push_back();

    REQUIRE(sol == output);

}