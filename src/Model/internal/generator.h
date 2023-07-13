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


#ifndef A1_MAZE_1_INTERNAL_GENERATOR_H_
#define A1_MAZE_1_INTERNAL_GENERATOR_H_

#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <random>

#include "../include/data_wrapper.h"

namespace ng {
/**
 *
 * BasicGenerationSettings final structure
 * Базовый класс является пустым, от которого нельзя создать объект
 * Содержит в себе поля настроек для дальнейшей генерации
 *
 */
template <FileTypes T>
struct BasicGenerationSettings final {};

/**
 * Специализация базового класса для шаблонного параметра kCave
 */
template <>
struct BasicGenerationSettings<kCave> final {
  size_type rows = 0, cols = 0, live_chance = 0, generation_count = 0;
  std::pair<size_type, size_type> live_limit, born_limit;
};

/**
 * Специализация базового класса для шаблонного параметра kMaze
 */
template <>
struct BasicGenerationSettings<kMaze> final {
  size_type rows = 0, cols = 0;
};

using CaveGenerationSettings = BasicGenerationSettings<kCave>;
using MazeGenerationSettings = BasicGenerationSettings<kMaze>;

namespace internal {
/**
 *
 * Generator static final class\n
 *
 * Класс генерирующий данные для FileTypes\n
 * Базовый класс имеет пустое тело и его никак нельзя создать,\n
 * класс подразумевает работу без объекта.\n
 *
 * Возможное использование:\n
 *
 * ng::Generator<ng::kCave>::Generate(settings)\n
 * ng::Generator<ng::kCave>::Generate(settings, cave)\n
 * ng::Generator<ng::kMaze>::Generate(settings)\n
 *
 * @tparam T FileTypes enum
 */
template <FileTypes T>
class Generator final {
  NON_CONSTRUCTABLE_CLASS(Generator)
};

template <>
class Generator<kMaze> final {
 public:
  NON_CONSTRUCTABLE_CLASS(Generator);

  /**
   *
   * Метод генерирует лабиринт используя Алгоритм Эллера
   * Возвращает сгенерированный лабиринт в классическом виде
   *
   * @param s настройки генерации лабиринта
   *
   */
  static MazeWrapper Generate(const MazeGenerationSettings &s) {
    CaveWrapper vertical{std::vector<size_type>(s.rows * s.cols, size_type{}),
                         s.rows, s.cols},
        horizontal{std::vector<size_type>(s.rows * s.cols, size_type{}), s.rows,
                   s.cols};

    if (!vertical.IsGood() or !horizontal.IsGood()) return {};

    std::vector<size_type> random(s.rows * s.cols * 3, {});
    {
      // Generating random choices for maze-generation
      // algorithm needs rows * cols * 3 count of random choices
      std::uniform_int_distribution<> distribution(0, 1);
      std::default_random_engine re(
          std::chrono::system_clock::now().time_since_epoch().count());
      std::generate(random.begin(), random.end(),
                    [&distribution, &re] { return distribution(re); });
    }
    size_type rand_index = 0, counter = 1;

    std::vector<size_type> line(s.cols, size_type{});

    auto Merge = [&](size_type i) {
      size_type merged_item = line[i + 1];
      for (size_type col = 0; col != line.size(); ++col) {
        if (line[col] == merged_item) line[col] = line[i];
      }
    };

    for (size_type row = 0; row != s.rows - 1; ++row) {
      std::transform(
          line.begin(), line.end(), line.begin(),
          [&counter](size_type item) { return item == 0 ? counter++ : item; });

      for (size_type col = 0; col != line.size() - 1; ++col)
        if (line[col] == line[col + 1]) vertical(row, col) = 1;
      for (size_type col = 0; col != line.size() - 1; ++col) {
        auto choice = random[rand_index++];
        if (choice == 1 or line[col] == line[col + 1])
          vertical(row, col) = 1;
        else {
          Merge(col);
        }
      }
      vertical(row, line.size() - 1) = 1;

      for (size_type col = 0; col != line.size(); ++col) {
        auto choice = random[rand_index++];
        if (choice == 1) {
          size_type count = 0;
          for (size_type c = 0; c != line.size(); ++c)
            if (line[c] == line[col] and horizontal(row, c) == 0) count++;
          if (count != 1) horizontal(row, col) = 1;
        }
      }

      for (size_type col = 0; col != line.size(); ++col)
        if (horizontal(row, col) == 1) line[col] = 0;
    }
    std::transform(
        line.begin(), line.end(), line.begin(),
        [&counter](size_type item) { return item == 0 ? counter++ : item; });
    for (size_type col = 0; col != line.size() - 1; ++col) {
      auto choice = random[rand_index++];
      if (choice == 1 or line[col] == line[col + 1])
        vertical(s.rows - 1, col) = 1;
      else {
        Merge(col);
      }
    }
    vertical(s.rows - 1, line.size() - 1) = 1;

    for (size_type col = 0; col != line.size(); ++col) {
      if (line[col] != line[col + 1]) {
        vertical(s.rows - 1, col) = 0;
        Merge(col);
      }
      horizontal(s.rows - 1, col) = 1;
    }
    vertical(s.rows - 1, s.cols - 1) = 1;

    return {std::move(vertical.data), std::move(horizontal.data), s.rows,
            s.cols};
  }
};

template <>
class Generator<kCave> final {
 public:
  NON_CONSTRUCTABLE_CLASS(Generator);

  /**
   *
   * Метод генерирует пещеру с начальной инициализацией
   * GenerationSettings::live_chance.\n Также отрабатывает
   * GenerationSettings::generation_count поколений,\n возвращает последнее
   * поколение.\n Пределы жизни и рождения задаются соответственно в
   * GenerationSettings,\n born_limit, GenerationSettings::live_limit)
   * соответственно
   * @param s generation settings
   * @return generated cave
   *
   */
  static CaveWrapper Generate(const CaveGenerationSettings &s) {
    CaveWrapper cave{InitializeRandom(s.rows, s.cols, s.live_chance)};
    size_type generation = 0;
    while (++generation < s.generation_count) Generate(s, cave);
    return cave;
  }

  /**
   *
   * Метод не инициализирует клетки пещеры начальными значениями, а проживает
   * GenerationSettings::generation_count поколений от входного поколения, чтобы
   * перевести 'cave' ровно одно поколение generation_count должно быть равно 1.
   * @param s generation settings
   * @param cave start sample
   *
   */
  static CaveWrapper &Generate(const CaveGenerationSettings &s,
                               CaveWrapper &cave) {
    CaveWrapper tmp = cave;
    for (size_type row = 0; row != cave.rows; ++row) {
      for (size_type col = 0; col != cave.cols; ++col) {
        size_type count = CountLiveNeighbours(row, col, cave);
        if (cave(row, col) == 1 and
            (count < s.live_limit.first or count > s.live_limit.second))
          tmp(row, col) = 0;
        else if (cave(row, col) == 0 and
                 (count >= s.born_limit.first and count <= s.born_limit.second))
          tmp(row, col) = 1;
      }
    }
    cave = std::move(tmp);
    return cave;
  }

 private:
  static CaveWrapper InitializeRandom(size_type rows, size_type cols,
                                      size_type live_chance) {
    std::default_random_engine re(
        std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<size_type> dist(0, 100);

    CaveWrapper::data_type generation(rows * cols);
    std::generate(generation.begin(), generation.end(),
                  [&dist, &re, live_chance] {
                    size_type chance = dist(re);
                    return chance <= live_chance ? 1 : 0;
                  });
    return {generation, rows, cols};
  }

  static size_type CountLiveNeighbours(size_type row, size_type col,
                                       const CaveWrapper &cave) {
    size_type count = 0;
    for (auto item :
         {cave(row, col - 1), cave(row, col + 1), cave(row - 1, col),
          cave(row + 1, col), cave(row - 1, col - 1), cave(row - 1, col + 1),
          cave(row + 1, col - 1), cave(row + 1, col + 1)})
      if (item != 0) count++;
    return count;
  }
};
}  // namespace internal
}  // namespace ng

#endif  // A1_MAZE_1_INTERNAL_GENERATOR_H_
