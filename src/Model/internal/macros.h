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


#ifndef A1_MAZE_1_INTERNAL_MACROS_H_
#define A1_MAZE_1_INTERNAL_MACROS_H_

#define NON_CONSTRUCTABLE_CLASS(ClassName) \
  ClassName() = delete;                    \
  ClassName(const ClassName &) = delete;   \
  ClassName &operator=(const ClassName &) = delete;

#define TRIVIAL_MOVE_COPY_CLASS(ClassName)           \
  ClassName() = default;                             \
  ClassName(const ClassName &) = default;            \
  ClassName(ClassName &&) = default;                 \
  ClassName &operator=(const ClassName &) = default; \
  ClassName &operator=(ClassName &&) = default;

#endif  //! A1_MAZE_1_INTERNAL_MACROS_H_
