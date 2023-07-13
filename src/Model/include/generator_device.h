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

#ifndef A1_MAZE_1_GENERATOR_DEVICE_H_
#define A1_MAZE_1_GENERATOR_DEVICE_H_

#include "../internal/generator.h"

namespace ng {
/**
 *
 * GeneratorDevice class
 * Exception safety class
 * Класс поддерживает перемещение и копирование
 * Делегирует методы статического класс Generator
 *
 */
class GeneratorDevice final {
 public:
  TRIVIAL_MOVE_COPY_CLASS(GeneratorDevice)

  template <FileTypes T, typename... Parameters>
  BasicWrapper<T> Generate(const BasicGenerationSettings<T> &settings,
                           Parameters &&...function_params) {
    BasicWrapper<T> generation;
    try {
      generation = internal::Generator<T>::Generate(
          settings, std::forward<Parameters>(function_params)...);
    } catch (std::exception &) {
      return {};
    }
    return generation;
  }
};
}  // namespace ng

#endif  // A1_MAZE_1_GENERATOR_DEVICE_H_
