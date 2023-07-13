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

#ifndef A1_MAZE_1_DATA_WRAPPER_H_
#define A1_MAZE_1_DATA_WRAPPER_H_

#include <algorithm>
#include <vector>

#include "../internal/macros.h"
#include "file_types.h"

namespace ng {
using size_type = std::size_t;  // main type of size in ng namespace

/**
 *
 *  BasicWrapper final struct
 *
 *  Оболочка над вектором-матрицей, которая знает размерность вектора-матрицы
 *  Знает в валидном ли состоянии вектор-матрица
 *
 *  Не защищает никаких инвариантов - full-public struct
 *
 *  Базовая структура имеет пустое тело и его никак нельзя создать, он нужен
 * лишь для того чтобы от него сделать специализацию для нужных нам типов
 * считывания
 *
 */
template <FileTypes T>
struct BasicWrapper final {
  NON_CONSTRUCTABLE_CLASS(BasicWrapper)
};

/**
 * Специализация базовой структуры BasicWrapper для типа kMaze
 */
template <>
struct BasicWrapper<kMaze> final {
  using data_type = std::vector<size_type>;

  data_type right, bottom;
  size_type rows = 0, cols = 0;

  bool IsGood() const {
    if (rows == 0 or rows > 75 or cols == 0 or cols > 75) return false;
    if (rows * cols != right.size() or rows * cols != bottom.size())
      return false;

    if (!std::all_of(right.begin(), right.end(),
                     [](size_type i) { return i == 1 or i == 0; }) or
        !std::all_of(bottom.begin(), bottom.end(),
                     [](size_type i) { return i == 1 or i == 0; }))
      return false;

    for (size_type row = 0; row != rows; ++row)
      if (operator()(row, cols - 1) != 1) return false;

    for (size_type col = 0; col != cols; ++col)
      if (operator()(rows - 1, col, false) != 1) return false;

    return true;
  }

  void Clear() noexcept {
    right.clear();
    bottom.clear();
    rows = cols = 0;
  }

  size_type &operator()(std::size_t row, std::size_t col,
                        bool is_right = true) {
    return is_right ? right[row * cols + col] : bottom[row * cols + col];
  }

  size_type operator()(std::size_t row, std::size_t col,
                       bool is_right = true) const {
    return is_right ? right[row * cols + col] : bottom[row * cols + col];
  }
};

/**
 * Специализация базовой структуры BasicWrapper для типа kMaze
 */
template <>
struct BasicWrapper<kCave> final {
  using data_type = std::vector<size_type>;

  data_type data;
  size_type rows = 0, cols = 0;

  bool IsGood() const {
    if (rows == 0 or rows > 150 or cols == 0 or cols > 150) return false;
    if (rows * cols != data.size()) return false;

    if (!std::all_of(data.begin(), data.end(),
                     [](size_type i) { return i == 1 or i == 0; }))
      return false;

    return true;
  }

  void Clear() noexcept {
    data.clear();
    rows = cols = 0;
  }

  size_type &operator()(std::size_t row, std::size_t col) {
    return data[row * cols + col];
  }

  size_type operator()(std::size_t row, std::size_t col) const {
    if (row >= rows or col >= cols) return 1;
    return data[row * cols + col];
  }
};

/**
 * Point final structure
 * Структура хранит координаты точки
 */
struct Point final {
  size_type x, y;

  Point(size_type x = 0, size_type y = 0) : x(x), y(y){};
};

using CaveWrapper = BasicWrapper<kCave>;
using MazeWrapper = BasicWrapper<kMaze>;

}  // namespace ng

#endif  // A1_MAZE_1_DATA_WRAPPER_H_
