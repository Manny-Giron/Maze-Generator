#include <vector>
#include <string>
#ifndef MAZE_H
#define MAZE_H




class Maze {
public:

    // fill constructor, creates an array of capacity = length, and set all values to `default_value`
    Maze(int seed, int m_len, int n_len);
    // default destructor, free memory of the array here
    ~Maze();
    std::vector<std::vector<int>> maze;
    // (RAND) seed for maze generation
    int seed;
    // Number of rows
    int n_rows;
    // Number of columns
    int m_cols;

    int cellsVisited;
    int size;
    // Previous current
    std::pair<int, int> lastCell;
    // Current cell in
    std::pair<int, int> current;
    // Stack of previous cells route. (path)
    std::vector<std::pair<int, int>> A;
    // 2d Boolean Array showing cells visited
    std::vector<std::vector<bool>> visited;
    // Vector array holding valid neighboring cells of current position
    std::vector<std::pair<int, int>> neighbors;
    // generate maze
    void generateMaze();
    // output Maze
    void output_Maze(const std::string& fileName);
    // get neighbors
    void get_Neighbors();
    // get singular neighbor
    std::pair<int, int> get_Neighbor();
    // insert current into stack
    void addTo_A(std::pair<int, int> current);
    // add neighbor visited to list of visited
    void add_Visited();
    // Check if all cells have been visited
    bool check_Visited();
    // Remove wall between current and neighbor
    void remove_Wall();
    // Actually go through and create the maze implementing DFS with created functions
    void buildMaze();


};
#endif
