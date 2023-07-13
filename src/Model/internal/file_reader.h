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

#ifndef A1_MAZE_1_INTERNAL_FILE_READER_H_
#define A1_MAZE_1_INTERNAL_FILE_READER_H_

#include <fstream>
#include <iterator>

#include "../include/data_wrapper.h"

namespace ng::internal {
/**
 *
 * FileReader static final class
 *
 * Класс считывающий данные с файла с формате записи лабиринт-пещера.
 * Базовый класс имеет пустое тело и его никак нельзя создать, он нужен лишь
 * для того чтобы от него сделать специализацию для нужных нам типов считывания
 *
 * FileReader class лежит в namespace detail так как подразумевается,
 * что не будет создаваться отдельно извне.
 *
 * Возможное использование:
 * ng::detail::FileReader<ng::kMaze>::Read("some/path/.txt")
 * ng::detail::FileReader<ng::kCave>::Read("some/path/.txt")
 *
 */
template <FileTypes T>
class FileReader final {
  NON_CONSTRUCTABLE_CLASS(FileReader)
};

/**
 * Специализация базового класса FileReader для типа kMaze
 */
template <>
class FileReader<kMaze> final {
  NON_CONSTRUCTABLE_CLASS(FileReader)

 public:
  using reading_type = size_type;

  static MazeWrapper Read(std::string_view path) {
    std::ifstream fin(path.data());
    if (!fin.is_open()) return {};
    MazeWrapper read_data;
    fin >> read_data.rows >> read_data.cols;
    read_data.right.resize(read_data.rows * read_data.cols);
    for (auto &item : read_data.right) fin >> item;
    read_data.bottom = {std::istream_iterator<reading_type>(fin),
                        std::istream_iterator<reading_type>()};
    fin.close();
    return read_data;
  }
};

/**
 * Специализация базового класса FileReader для типа kCave
 */
template <>
class FileReader<kCave> final {
  NON_CONSTRUCTABLE_CLASS(FileReader)

 public:
  using reading_type = size_type;

  static CaveWrapper Read(std::string_view path) {
    std::ifstream fin(path.data());
    if (!fin.is_open()) return {};
    CaveWrapper read_data;
    fin >> read_data.rows >> read_data.cols;
    read_data.data = {std::istream_iterator<reading_type>(fin),
                      std::istream_iterator<reading_type>()};
    fin.close();
    return read_data;
  }
};
}  // namespace ng::internal

#endif  //! A1_MAZE_1_INTERNAL_FILE_READER_H_
