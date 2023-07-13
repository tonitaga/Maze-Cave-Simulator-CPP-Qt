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

#ifndef A1_MAZE_1_MODEL_H_
#define A1_MAZE_1_MODEL_H_

#include "file_manager.h"
#include "generator_device.h"
#include "path_finder_device.h"

namespace ng {
/**
 *
 *  Model final class
 *  Класс поддерживает перемещение и копирование
 *  Объединяет функционал exception-safety классов:
 *      FileManager, GeneratorDevice, PathFinderDevice
 *
 */
class Model final {
 public:
  TRIVIAL_MOVE_COPY_CLASS(Model)

  template <FileTypes T>
  BasicWrapper<T> ReadFile(std::string_view path) {
    return file_manager_.Read<T>(path);
  }

  template <FileTypes T>
  bool SaveFile(const BasicWrapper<T> &data, std::string_view path) const {
    return file_manager_.Save(data, path);
  }

  template <FileTypes T, typename... Parameters>
  BasicWrapper<T> Generate(const BasicGenerationSettings<T> &settings,
                           Parameters &&...function_params) {
    return generator_device_.Generate(
        settings, std::forward<Parameters>(function_params)...);
  }

  template <FileTypes T, typename... Parameters>
  std::vector<Point> Solve(const BasicWrapper<T> &data,
                           Parameters &&...function_params) {
    return path_finder_device_.Solve(
        data, std::forward<Parameters>(function_params)...);
  }

 private:
  FileManager file_manager_;
  GeneratorDevice generator_device_;
  PathFinderDevice path_finder_device_;
};
}  // namespace ng

#endif  // A1_MAZE_1_MODEL_H_
