## Leading Question 

Our final project is built upon the idea of the six degrees of separation, the idea that people are six or fewer social connections from each other. We believe that every artist is less than six degrees of separation from each other through song collaborations. Our project will be based off of the dataset 'Spotify 1.2 million songs' created by Rodolfo Figueroa. We will use this dataset to find connections between artists through features. Given two input artists, our algorithm will find the shortest path of collaborations to connect those two artists using A*. The user will also be able to input at least three artists in order to create a playlist to see how the artists connect with each other, as well as display the minimum spanning tree.

## Dataset Acquisition
https://www.kaggle.com/datasets/rodolfofigueroa/spotify-12m-songs

## Data Format

The data is from a kaggle dataset which used the spotify API to get access to 1.2 millions songs. The data set is 24 columns and approx 1.2 million rows. The data is a csv file. We plan to use all the data because we want to mast accurate representation of connectivity. 

## Data Correction

Using pandas we will drop all the duplicate and null rows in the artist name and song title field. We will also drop all rows where the artist is only 1 person. The artist's name is contained in an array with the size of that array being the total number of artists who worked on that song. 

## Data Storage
We are using a dataframe in Python to store and clean the data. Once we parse the data into C++ we will store the parsed data in a graph and the results will be stored in a vector of pairs or a map depending on the traversal algorithm. In terms of complexity the storage cost will be O(n)?

## Algorithm 

First, we will use Breadth First Search (BFS) to traverse the graph to find the shortest path between two artists. The input will be a pair of two artists, and the output will be a vector of pairs containing the songs and artists that connect the two artists. This connection will be based on the songs that the two artists have in common. The runtime for this algorithm would be O(m + n), where m is the number of edges and n is the number of nodes. The space complexity for this algorithm would be O(n). The next feature will have the user input at least three artists, and using Prim’s algorithm; we will create a playlist with songs connecting those artists and an image of the MST displaying how each song connects. The input will be a vector of at least three artists. The output will be a subset of our graph or a minimum spanning tree representing a playlist of all the songs connecting the inputted artists. The runtime of this algorithm is O(m log n), where m is the number of edges and n is the number of nodes. The space complexity of this algorithm would be O(n). The last feature will be a playlist created based on “danceability” using an A* algorithm with danceability, as provided by the dataset, as the heuristic and weight. We will create a graph of songs connected by artists they have in common. The nodes of the graph will be songs, and the weights of the edges will be the difference in danceability between the two songs. We will create a playlist connecting two artists, and the songs will all have similar danceability. The input is a pair of songs, and the output vector of pairs containing the songs and the artists that connect the two songs with all the songs in the vector having the smallest difference in danceability. The algorithm's runtime is O(m), where m is the number of edges. The space complexity of the A* algorithm is O(n).  



## Timeline

We would like to finish processing the cleaning of our data set in 2 weeks. After that we would like to finish the minimum spanning tree algorithm in the next weeks after and the A* algorithm by one week after that. After that we would like to create our BFS algorithm within the week after that. Finally we would like to create a front end for our program by December 8th. 
