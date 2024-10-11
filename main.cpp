#include "maze.h"
#include <iostream>
#include <random>

/*
 maze.h: class declaration

maze.cpp: implementation of all methods defined in maze.h

main.cpp: driver program that takes CLAs and uses the class Maze
 to generate output
*/


int main(int argc, char *argv[]) {

    Maze maze(std::stoi(argv[1]),std::stoi(argv[2]), std::stoi(argv[3]));
    maze.buildMaze();
    maze.output_Maze(argv[4]);
    return 0;
}