/** MazeAndCaveSimulator project path_finder_device.h using code-sample file 
 *
 * Copyright (C) Maze Project Developers. All Rights Reserved
 *
 * If the code of this project has helped you in any way,
 * please thank us with a cup of beer.
 *
 * team-lead gmail:    gubaydullin.nurislam@gmail.com
 * team-lead telegram: @tonitaga
 *
 */

#include "../include/path_finder_device.h"

int main() {
    // Operating class
    ng::PathFinderDevice device;

    // ng::Point structure for set start and finish position of solving
    ng::Point start, finish;

    // Also need structure of cave or maze
    ng::CaveWrapper cave;
    ng::MazeWrapper maze;

    // Solving
    // Return std::vector<ng::Point>
    auto cave_path = device.Solve(cave, start, finish);
    auto maze_path = device.Solve(maze, start, finish);

    return 0;
}