/** MazeAndCaveSimulator project file_manager.h using code-sample file
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

#include "../include/file_manager.h"

#include <iostream>

int main() {
    // Operating class
    ng::FileManager manager;

    // File Reading
    // Return ng::BasicWrapper<Type>
    {
        auto read_data = manager.Read<ng::kCave>("cave_path.txt");
        
        // Check for correct data
        if (read_data.IsGood())
            std::cout << "read_data.IsGood()";
    }
    {
        auto read_data = manager.Read<ng::kMaze>("maze_path.txt");

        if (read_data.IsGood())
            std::cout << "read_data.IsGood()";
    }

    // File saving
    ng::CaveWrapper cave_data;
    ng::MazeWrapper maze_data;

    manager.Save(cave_data, "cave_save_path.txt");
    manager.Save(maze_data, "maze_save_path.txt");

    return 0;
}