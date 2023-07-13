/** MazeAndCaveSimulator project generator_device.h using code-sample file 
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

#include "../include/generator_device.h"

#include <iostream>

int main() {
    // Operating class
    ng::GeneratorDevice device;

    // Generation settings
    ng::CaveGenerationSettings cave_settings;
    ng::MazeGenerationSettings maze_settings;

    // Generating with settings
    auto cave_generated = device.Generate(cave_settings);
    auto maze_generated = device.Generate(maze_settings);

    // Also generation of cave has second function
    // Is generationg from current cave

    cave_generated = device.Generate(cave_settings, cave_generated);
    return 0;
}