#include "Edge.h"
#include <iostream>
#include <climits>
using namespace std;

int main(){

    // start of the initial pipeline that loads the test case file stream from std::cin

    int numOfVertices;
    int numOfEdges;

    if(!std::cin.eof()){
        std::cin >> numOfVertices;
        std::cin >> numOfEdges;
    }
    else{
        std::cout<<"Input not found!"<<std::endl;
        return 0;
    }

    // Creates an adjancey matrix 
    int** matrix = new int*[numOfVertices]; // initializes the adjacency matrix
    for(int i = 0; i < numOfVertices; i++) {
        matrix[i] = new int[numOfVertices]; // initalizes the rows of the adjacency matrix
        for(int k = 0; k < numOfVertices; k++) {
            matrix[i][k] = 0; // intializes the columns of the adjacency matrix to 0
        }
    }

    while(!std::cin.eof()){
        int startVertice;
        int endVertice;
        std::cin >> startVertice;
        std::cin >> endVertice;
        // Here is where you load up the Graph object

        // Makes the vertices compatiable with a 0-indexed array
        int u = startVertice - 1; 
        int v = endVertice   - 1;
        
        // Undirected so we add both ways having an edge
        matrix[u][v] = 1;
        matrix[v][u] = 1;
    }

    // And here is where you start working on the three tasks

    // Print the adjacency matrix
    cout << "The adjacency matrix of G:" << endl;
    for (int i = 0; i < numOfVertices; ++i) {

        for (int k = 0; k < numOfVertices; k++) {
            cout << matrix[i][k];

            if (k + 1 < numOfVertices) {
                cout << " "; // Adds a space between the numbers if its not the last number
            }

            else {
                cout << ""; // No space after the last number
            }

        }

        cout << endl;

    }
    cout << endl;

    // Print the rows of odd number of edges
    cout << "The odd degree vertices in G:" << endl;

    int* odds = new int[numOfVertices]; // initializes the array of odd degree vertices
    int oddRow = 0; // initializes the number of odd degree vertices rows found

    for (int i = 0; i < numOfVertices; i++) {
        int count = 0;

        for (int j = 0; j < numOfVertices; j++) {
            if (matrix[i][j] == 1) {
                count = count + 1; // Increment number of edges for each vertex
            }
        }

        if (count % 2 == 1) {
            odds[oddRow] = i + 1; // Adds the row number to array of odd degree vertices
            oddRow = oddRow + 1; // Increment number of odd degree vertices rows found
        }

    }

    cout << "O = { ";
    for (int i = 0; i < oddRow; ++i) {
        cout << odds[i] << " ";
    }
    cout << "}" << endl << endl;

    // Dijkstra's algorithm for each odd degree vertex
    for (int i = 0; i < oddRow; i++) {

        int row = odds[i] - 1;
        int* distance = new int[numOfVertices];
        bool* visited  = new bool[numOfVertices];

        for (int i = 0; i < numOfVertices; ++i) {
            distance[i] = INT_MAX; // Initialize distances to infinity
            visited[i]  = false; // Initialize visited array
        }
        distance[row] = 0; // Distance from the source to itself is 0

        for (int k = 0; k < numOfVertices; k++) {
            int current = -1;

            for (int i = 0; i < numOfVertices; ++i) {
                if (visited[i] == false && (current == -1 || distance[i] < distance[current])) {
                    current = i; // Find the unvisited vertex with the smallest distance
                }
            }

            if (current == -1) {
                break; // All vertices are visited or unreachable so break
            }

            visited[current] = true; // Mark the vertex as visited
            for (int i = 0; i < numOfVertices; i++) {
                if (matrix[current][i] == 1 && visited[i] == false && distance[current] + 1 < distance[i]) {
                    distance[i] = distance[current] + 1; // Update distance to v if going through current is shorter than from source
                }
            }

        }

        cout << "Single source shortest path lengths from node " << (row + 1) << endl;

        for (int i = 0; i < numOfVertices; i++) {
            cout << "  " << (i + 1) << ": " << distance[i] << endl;
        }

    }

    return 0;
}
