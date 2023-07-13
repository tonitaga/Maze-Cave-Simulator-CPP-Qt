/** MazeAndCaveSimulator project internal header file
 *
 * Copyright (C) Maze Project Developers. All Rights Reserved
 *
 * If the code of this project has helped you in any way,
 * please thank us with a cup of beer.
 *
 * team-lead gmail:    gubaydullin.nurislam@gmail.com
 * team-lead telegram: @tonitaga
 */


#ifndef A1_MAZE_1_PATH_FINDER_H
#define A1_MAZE_1_PATH_FINDER_H

#include <algorithm>
#include <iostream>

#include "../include/data_wrapper.h"

namespace ng {
namespace internal {
/**
 * SidePoint final structure
 * Нужна для хранения соседней клетки и ее значения
 */
struct SidePoint final {
  size_type x, y, value;
};

/**
 *
 * PathFinder static final class\n
 *
 * Класс решает(находит путь) для FileTypes
 * Базовый класс имеет пустое тело и его никак нельзя создать,\n
 * класс подразумевает работу без объекта
 *
 * При T = ng::kCave | ng::kMaze решение осуществляется,\n
 * используя волновой алгоритм (Wave algorithm) поиска пути
 *
 * Возможное использование:\n
 *
 * @tparam T FileTypes enum
 */
template <FileTypes T>
class PathFinder final {
  NON_CONSTRUCTABLE_CLASS(PathFinder)
};

template <>
class PathFinder<kCave> final {
 public:
  TRIVIAL_MOVE_COPY_CLASS(PathFinder)

  std::vector<Point> Solve(const CaveWrapper &cave, Point from, Point to) & {
    if (!IsValid(cave, from, to)) return {};
    InitializeStartState(cave, from);
    while (!old_wave_.empty())
      if (StepWave(cave, to)) break;
    return MakePath(cave, to);
  }

 private:
  CaveWrapper length_map_;
  std::vector<Point> wave_, old_wave_;
  size_type wave_step_;
  size_type empty_value_ = std::numeric_limits<size_type>::max();

  void InitializeStartState(const CaveWrapper &cave, Point from) {
    wave_.clear();
    wave_step_ = 0u;
    old_wave_ = {from};
    length_map_ = {CaveWrapper::data_type(cave.rows * cave.cols, empty_value_),
                   cave.rows, cave.cols};
    length_map_(from.x, from.y) = wave_step_;
  }

  bool IsValid(const CaveWrapper &cave, Point from, Point to) const {
    if (!cave.IsGood() or cave(from.x, from.y) == 1 or cave(to.x, to.y) == 1 or
        from.x >= cave.rows or from.y >= cave.cols or to.x >= cave.rows or
        to.y >= cave.cols)
      return false;
    return true;
  }

  bool StepWave(const CaveWrapper &cave, Point to) {
    ++wave_step_;
    for (auto [row, col] : old_wave_) {
      for (auto [x, y, value] : {SidePoint{row + 1, col, cave(row + 1, col)},
                                 SidePoint{row - 1, col, cave(row - 1, col)},
                                 SidePoint{row, col + 1, cave(row, col + 1)},
                                 SidePoint{row, col - 1, cave(row, col - 1)}}) {
        if (value == 0) {
          if (length_map_(x, y) == empty_value_) {
            wave_.emplace_back(x, y);
            length_map_(x, y) = wave_step_;
          }

          if (x == to.x and y == to.y) return true;
        }
      }
    }
    old_wave_ = std::move(wave_);
    return false;
  }

  std::vector<Point> MakePath(const CaveWrapper &cave, Point to) {
    std::vector<Point> path{to};
    auto &[row, col] = to;
    while (length_map_(row, col) != 0) {
      if (length_map_(row + 1, col) + 1 == length_map_(row, col) and
          cave(row + 1, col) == 0)
        ++row;
      else if (length_map_(row - 1, col) + 1 == length_map_(row, col) and
               cave(row - 1, col) == 0)
        --row;
      else if (length_map_(row, col + 1) + 1 == length_map_(row, col) and
               cave(row, col + 1) == 0)
        ++col;
      else if (length_map_(row, col - 1) + 1 == length_map_(row, col) and
               cave(row, col - 1) == 0)
        --col;
      else
        return {};
      path.emplace_back(to);
    }
    std::reverse(path.begin(), path.end());
    return path;
  }
};

template <>
class PathFinder<kMaze> final {
 public:
  TRIVIAL_MOVE_COPY_CLASS(PathFinder)

  std::vector<Point> Solve(const MazeWrapper &maze, Point from, Point to) & {
    if (!IsValid(maze, from, to)) return {};
    InitializeStartState(maze, from);
    while (!old_wave_.empty())
      if (StepWave(maze, to)) break;
    return MakePath(maze, to);
  }

 private:
  CaveWrapper length_map_;
  std::vector<Point> wave_, old_wave_;
  size_type wave_step_;
  size_type empty_value_ = std::numeric_limits<size_type>::max();

  void InitializeStartState(const MazeWrapper &maze, Point from) {
    wave_.clear();
    wave_step_ = 0u;
    old_wave_ = {from};
    length_map_ = {CaveWrapper::data_type(maze.rows * maze.cols, empty_value_),
                   maze.rows, maze.cols};
    length_map_(from.x, from.y) = wave_step_;
  }

  bool IsValid(const MazeWrapper &maze, Point from, Point to) const {
    if (!maze.IsGood() or from.x >= maze.rows or from.y >= maze.cols or
        to.x >= maze.rows or to.y >= maze.cols)
      return false;
    return true;
  }

  bool StepWave(const MazeWrapper &maze, Point to) {
    ++wave_step_;
    for (auto [row, col] : old_wave_) {
      for (auto [x, y, value] :
           {SidePoint{row + 1, col, maze(row, col, false)},
            SidePoint{row - 1, col, maze(row - 1, col, false)},
            SidePoint{row, col + 1, maze(row, col)},
            SidePoint{row, col - 1, maze(row, col - 1)}}) {
        if (value == 0) {
          if (length_map_(x, y) == empty_value_) {
            wave_.emplace_back(x, y);
            length_map_(x, y) = wave_step_;
          }

          if (x == to.x and y == to.y) return true;
        }
      }
    }
    old_wave_ = std::move(wave_);
    return false;
  }

  std::vector<Point> MakePath(const MazeWrapper &maze, Point to) {
    std::vector<Point> path{to};
    auto &[row, col] = to;
    while (length_map_(row, col) != 0) {
      if (length_map_(row, col - 1) + 1 == length_map_(row, col) and
          maze(row, col - 1) == 0)  // going left
        --col;
      else if (length_map_(row, col + 1) + 1 == length_map_(row, col) and
               maze(row, col) == 0)  // going right
        ++col;
      else if (length_map_(row - 1, col) + 1 == length_map_(row, col) and
               maze(row - 1, col, false) == 0)  // going top
        --row;
      else if (length_map_(row + 1, col) + 1 == length_map_(row, col) and
               maze(row, col, false) == 0)  // going down
        ++row;
      else
        return {};
      path.emplace_back(to);
    }
    std::reverse(path.begin(), path.end());
    return path;
  }
};
}  // namespace internal
}  // namespace ng

#endif  // A1_MAZE_1_PATH_FINDER_H
