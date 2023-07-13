/** MazeAndCaveSimulator project header file
 *
 * Copyright (C) Maze Project Developers. All Rights Reserved
 *
 * If the code of this project has helped you in any way,
 * please thank us with a cup of beer.
 *
 * team-lead gmail:    gubaydullin.nurislam@gmail.com
 * team-lead telegram: @tonitaga
 */

#ifndef A1_MAZE_1_PATH_FINDER_DEVICE_H
#define A1_MAZE_1_PATH_FINDER_DEVICE_H

#include "../internal/path_finder.h"

namespace ng {
/**
 *
 * PathFinderDevice class
 * Exception safety class
 * Класс поддерживает перемещение и копирование
 * Использует методы класса PathFinder
 *
 */
class PathFinderDevice {
 public:
  TRIVIAL_MOVE_COPY_CLASS(PathFinderDevice)

  using path_type = std::vector<Point>;

  template <FileTypes T>
  path_type Solve(const BasicWrapper<T> &data, Point from, Point to) {
    path_type path;
    try {
      internal::PathFinder<T> finder;
      path = finder.Solve(data, from, to);
    } catch (std::exception &) {
      return {};
    }
    return path;
  }
};
}  // namespace ng

#endif  // A1_MAZE_1_PATH_FINDER_DEVICE_H
