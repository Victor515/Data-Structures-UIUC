/**
 * @file testsquaremaze.cpp
 * Performs basic tests of SquareMaze.
 * @date April 2007
 * @author Jonathan Ray
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    std::srand(std::time(NULL));
    SquareMaze m;
    m.makeMaze(500, 500);
    std::cout << "MakeMaze complete" << std::endl;
    // std::cout << m.canTravel(0, 0, 1);//1
    // std::cout << m.canTravel(0, 0, 0);//2
    // std::cout << m.canTravel(1, 0, 1);//3
    // std::cout << m.canTravel(0, 1, 0);//4
    // std::cout << std::endl;

    PNG* unsolved = m.drawMaze();
    unsolved->writeToFile("unsolved.png");
    delete unsolved;
    std::cout << "drawMaze complete" << std::endl;

    std::vector<int> sol = m.solveMaze();
    std::cout << "solveMaze complete" << std::endl;

    PNG* solved = m.drawMazeWithSolution();
    solved->writeToFile("solved.png");
    delete solved;
    std::cout << "drawMazeWithSolution complete" << std::endl;

    return 0;
}
