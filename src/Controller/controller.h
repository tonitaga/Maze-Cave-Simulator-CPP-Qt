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

#ifndef A1_MAZE_1_CONTROLLER_CONTROLLER_H_
#define A1_MAZE_1_CONTROLLER_CONTROLLER_H_

#include <memory>

#include "../Model/include/model.h"

namespace ng {
/**
 *
 *  Controller final class
 *
 *  Controls Model class
 *  Controller methods should be called from View
 *  Controller at that time calls Model class methods
 *
 *  Default-constuctable, only moveable class
 *
 *  All methods is marked as const noexcept
 *
 */
class Controller final {
 public:
  Controller() : model_(std::make_unique<Model>()) {}

  template <FileTypes T>
  BasicWrapper<T> ReadFile(std::string_view path) const noexcept {
    return model_->ReadFile<T>(path);
  }

  template <FileTypes T>
  bool SaveFile(const BasicWrapper<T> &data,
                std::string_view path) const noexcept {
    return model_->SaveFile(data, path);
  }

  template <FileTypes T, typename... Parameters>
  BasicWrapper<T> Generate(const BasicGenerationSettings<T> &settings,
                           Parameters &&...function_params) const noexcept {
    return model_->Generate(settings,
                            std::forward<Parameters>(function_params)...);
  }

  template <FileTypes T, typename... Parameters>
  std::vector<Point> Solve(const BasicWrapper<T> &data,
                           Parameters &&...function_params) const noexcept {
    return model_->Solve(data, std::forward<Parameters>(function_params)...);
  }

 private:
  std::unique_ptr<Model> model_;
};
}  // namespace ng

#endif  //! A1_MAZE_1_CONTROLLER_CONTROLLER_H_
