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


#ifndef A1_MAZE_1_INTERNAL_FILE_SAVER_H_
#define A1_MAZE_1_INTERNAL_FILE_SAVER_H_

#include <fstream>
#include <iterator>

#include "../include/data_wrapper.h"

namespace ng::internal {
/**
 *
 * FileSaver final class
 *
 * Класс сохраняющий данные лабиринта-пещеры в файл.
 * Базовый класс имеет пустое тело и его никак нельзя создать, он нужен лишь
 * для того чтобы от него сделать специализацию для нужных нам типов считывания
 *
 * FileSaver class лежит в namespace detail так как подразумевается,
 * что не будет создаваться отдельно извне.
 *
 * Возможное использование:
 * ng::internal::FileSaver<ng::kMaze>::Save(data, "some/path/.txt")
 * ng::internal::FileSaver<ng::kCave>::Save(data, "some/path/.txt")
 *
 */
template <FileTypes T>
class FileSaver final {
  NON_CONSTRUCTABLE_CLASS(FileSaver)
};

/**
 * Специализация базового класса FileSaver для типа kMaze
 */
template <>
class FileSaver<kMaze> final {
  NON_CONSTRUCTABLE_CLASS(FileSaver)

 public:
  static bool Save(const MazeWrapper &maze, std::string_view path) {
    if (!maze.IsGood()) return false;
    std::ofstream fout(path.data());
    if (!fout.is_open()) return false;
    fout << maze.rows << ' ' << maze.cols << '\n';
    for (size_type row = 0; row != maze.rows; ++row) {
      for (size_type col = 0; col != maze.cols; ++col) {
        fout << maze(row, col) << ' ';
      }
      fout << '\n';
    }
    fout << '\n';
    for (size_type row = 0; row != maze.rows; ++row) {
      for (size_type col = 0; col != maze.cols; ++col) {
        fout << maze(row, col, false) << ' ';
      }
      fout << '\n';
    }
    fout.close();
    return true;
  }
};

/**
 * Специализация базового класса FileSaver для типа kCave
 */
template <>
class FileSaver<kCave> final {
  NON_CONSTRUCTABLE_CLASS(FileSaver)

 public:
  static bool Save(const CaveWrapper &cave, std::string_view path) {
    if (!cave.IsGood()) return false;
    std::ofstream fout(path.data());
    if (!fout.is_open()) return false;
    fout << cave.rows << ' ' << cave.cols << '\n';
    for (size_type row = 0; row != cave.rows; ++row) {
      for (size_type col = 0; col != cave.cols; ++col) {
        fout << cave(row, col) << ' ';
      }
      fout << '\n';
    }
    fout.close();
    return true;
  }
};
}  // namespace ng::internal

#endif  //! A1_MAZE_1_INTERNAL_FILE_SAVER_H_
