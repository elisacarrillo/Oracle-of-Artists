#include "makegraph.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

MakeGraph::MakeGraph(string filename) {
    //for each line create array of artists and make node the name of the song
    std::ifstream infile(filename);
    // file.open(filename);
    std::string line;
    std::cout<<"here"<<std::endl;
    // if (infile.is_open()) {
        // std::getline(infile, line);
        // std::cout<<line<<std::endl;
    while (std::getline(infile, line)) {
            // std::cout<<"here 2"<<std::endl;
        std::string content;
        std::vector<std::string> vect;
        std::stringstream ss(line);
            // 683,"12 Études, Op. 25: No. 7 in C-Sharp Minor","['Frédéric Chopin', 'Vladimir Horowitz']",0.0311
        while(std::getline(ss,content,'"')) {
            vect.push_back(content);
            // std::cout<<content<<std::endl;

        }
        // std::cout<<vect.size()<<std::endl;
        for (unsigned int i = 0; i < vect.size(); i++) {
            // std::cout<<"look"<<vect[i]<<std::endl;
            if (vect[i].at(0) == ',') {
                vect[i].erase(vect[i].begin());
                i++;

            }
            // std::cout<<"deleting"<<std::endl;
            if (i != vect.size() && vect[i].at(vect[i].size()-1) == ',') {
                // std::cout<<"deleting 2"<<std::endl;
                vect[i].erase(vect[i].begin() + vect[i].size() -1);
                i++;

            }
        }

        std::string songName = vect[1];
        std::string artists = vect[3];

    
        artists.erase(artists.begin());
        artists.erase(artists.begin() + artists.size() - 1);

        std::cout<<"song name: "<<songName<<std::endl;
        std::cout<<"artists: "<<artists<<std::endl;

        std::vector<std::string> artistVect;
        std::stringstream ssTwo(artists);
        std::string person;

        while(std::getline(ssTwo,person,',')) {
            
            person.erase(person.begin() + person.size() - 1);
            if (person[0] == ' ') {
                person.erase(person.begin());
            }
            person.erase(person.begin());
            artistVect.push_back(person);
            std::cout<<person<<std::endl;
        }

    }

       



}