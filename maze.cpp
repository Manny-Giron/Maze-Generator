#include "maze.h"
#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <fstream>

// Constructor
Maze::Maze(int seedGiven, int rows, int cols){
    // initializing header file values
    this->n_rows = rows;
    this->m_cols = cols;
    this->seed = seedGiven;
    this-> size = n_rows * m_cols;
    // initialized with 1 to count first cell visited.
    this-> cellsVisited = 1;
    current = {0, 0}; // initializing current at starting point
    std::srand(seed);

    // Cool way of initializing a 2D vector with filled values
    this->maze = std::vector<std::vector<int>>(n_rows, std::vector<int>(m_cols, 15));

    visited.resize(n_rows, std::vector<bool>(m_cols, false));
    generateMaze();
}

// Deconstructor
Maze::~Maze() {
    // I used vectors so no need to delete stuff
}
// Add first and last cell direction
void Maze::generateMaze(){
    maze[0][0] = 7;  // Start point
    maze[n_rows - 1][m_cols - 1] = 11;  // End point
}

// Output generated maze into a txt file
void Maze::output_Maze(const std::string& fileName){
    std::ofstream outFile(fileName);
    if(!outFile){
        std::cerr << "Error: Couldn't open file " << fileName << std::endl;
    }

    for(int i = 0; i < n_rows; i++){
        for(int j = 0; j < m_cols; j++){
            std::cout << maze[i][j] << " ";
            outFile << maze[i][j];
            if (j < m_cols-1){
                outFile << " ";
            }
        }
        std::cout << "\n";
        outFile << "\n";
    }
    outFile.close();

}
// Checking if all cells have been visited (aka if were done with the maze)

// get surrounding neighbors of the current cell in
void Maze::get_Neighbors(){
    // resetting list of neighbors
    neighbors.clear();

    // Checking NORTH neighbor
    if ((current.first - 1) >= 0) {
        this->neighbors.push_back({current.first - 1, current.second});
    }
    // Checking SOUTH neighbor
    if ((current.first + 1) < n_rows) {
        this->neighbors.push_back({current.first + 1, current.second});
    }
    // Checking EAST neighbor
    if ((current.second + 1) < m_cols) {
        this->neighbors.push_back({current.first, current.second + 1});
    }
    // Checking WEST neighbor
    if ((current.second - 1) >= 0) {
        this->neighbors.push_back({current.first, current.second - 1});
    }

    for(size_t i = 0; i < neighbors.size(); i++) {
        if(visited[neighbors[i].first][neighbors[i].second] == true){
            neighbors.erase(neighbors.begin() + i);
            i--;
        }
    }
}


// insert current cell into stack
void Maze::addTo_A(std::pair<int, int> current){
    this->A.push_back({current.first, current.second});  // Ensure A is a vector of pairs
}

// add neighbor visited to list of visited
void Maze::add_Visited(){
    this->visited[current.first][current.second] = true;
}


// BIT STRING REPRESENTATION FOR WALLs -> 1111 <=> N-S-E-W <=> 8-4-2-1
void Maze::remove_Wall() {
    // Remove wall between current and neighbor

    // Checking  if between C NORTH wall
    if (current.first < lastCell.first ) {
        maze[current.first][current.second] -= 4;
        maze[lastCell.first][lastCell.second] -= 8;
    }
    // Checking  if between C SOUTH wall
    else if (current.first > lastCell.first ) {
        maze[current.first][current.second] -= 8;
        maze[lastCell.first][lastCell.second] -= 4;
    }
    // Checking  if between C EAST wall
    else if (current.second < lastCell.second ) {
        maze[current.first][current.second] -= 2;
        maze[lastCell.first][lastCell.second] -= 1;
    }
    // Checking  if between C WEST wall
    else if (current.second > lastCell.second ) {
        maze[current.first][current.second] -= 1;
        maze[lastCell.first][lastCell.second] -= 2;
    }
}

void Maze::buildMaze() {
    //mark current as visited
    visited[current.first][current.second] = true;

    // if given 1x1 grid, just return it with north and south walls removed.
    if(n_rows == 1 && m_cols == 1)
    {
        maze[current.first][current.second] = 3;
        return;
    }
    A.push_back(current);

    // Implementation of Iterative DFS
    while (cellsVisited < size){

        if(!visited[current.first][current.second]){
            add_Visited();
            cellsVisited++;
        }


        get_Neighbors();
        if (neighbors.empty()) {
            A.pop_back();
            current = A.back();
        }

        else if(!neighbors.empty())
        {
            //selecting random cell to move to
            unsigned long long idx = std::rand() / ((RAND_MAX + 1u) / neighbors.size());

            lastCell = current; //before moving cells remember this cell as previous
            current = neighbors[idx]; //moving to new square
            A.push_back(current);
            remove_Wall();
        }

    }

}


