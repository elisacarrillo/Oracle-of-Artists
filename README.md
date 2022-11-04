# Oracle-of-Artists

## Leading Question 

Our final project is built upon the idea of the six degrees of seperation, the idea that people are six or fewer social connections from eachother. We believe that every artist is less than six degrees of seperation from eachother through song collaborations. Our project will be based off of the dataset 'Spotify 1.2 million songs' created by Rodolfo Figueroa. We will use this dataset to find connections between artists through features. Given two input artists, our algorithm will find the shortest path of collaborations to connect those two artists. The user will also be able to find the shortest cycle, or the shortest path for an artist to itself. We are also looking to implement an A* algorithm that connects two songs together with increasing slowly increasing their energy levels to generate a random playlist from song a to b.

## Dataset Acquisition
https://www.kaggle.com/datasets/rodolfofigueroa/spotify-12m-songs
## Data Format

The data is from a kaggle datset which used the spotify API to get access to 1.2 millions songs. The data set is 24 columns and approx 1.2 million rows. The data is a csv file. We plan to use all the data because we want to mast accurate representaion of conntivity. 

## Data Correction

Using pandas we will drop all the duplicate and null rows in the artist name and song title field. We will also drop all rows where the artist is only 1 person. The artists name is contained in an array with the size of that array being the total number of artists who worked on that song. 

## Data Storage
We are using a dataframe in Python to store and clean the data. Once we parse the data into C++ we will store the parsed data in a graph and the results will be stored in a vector of pairs or a map depending on the traversal algorithm. In terms of complexity the storage cost will be O(n)?

## Algorithm 
For the Dijkstra's algorithm to find the shortest path between two artists we will enter two artists names and output a vector of pairs containing the song and artists connected the two. The runtime for this algorithm would be O(ElogV) where E is the number of edges and V is the number of nodes. The space complexity for this would be O(V) where V is the number of nodes. For the A* algorithm we will input two songs and output a vector of pairs of specified size to generate a random playlist of songs. The hueristic for the A* algorithm will be the energy levels of the songs. The runtime and the space complexity is O(B^D) where D is the shortest path and B is the branching factor.
## Timeline

We would like to finish processing the cleaning our data set in 2 weeks. After that we would like to finish the Dijkstra algotihm in the next 1.5 weeks after and the A* algorithm by 1.5 weeks after that. Finally we would like to create a front end for our program by December 8th. 
