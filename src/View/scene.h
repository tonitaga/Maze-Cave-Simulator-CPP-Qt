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

#ifndef A1_MAZE_1_SCENE_H_
#define A1_MAZE_1_SCENE_H_

#include <QGraphicsScene>
#include <QGraphicsView>

#include "data_wrapper.h"
#include "path_finder_device.h"

class Scene final : public QGraphicsView {
  Q_OBJECT

 public:
  Scene(QWidget *parent = nullptr);
  Scene(const Scene &) = delete;
  Scene &operator=(const Scene &) = delete;

  ~Scene();

  void DrawMaze();
  void DrawCave();
  void setWallColor(QColor color);
  void setPathColor(QColor color);
  void DrawMazePath(const std::vector<ng::Point> &path);
  void DrawCavePath(const std::vector<ng::Point> &path);
  void ClearScene() noexcept;
  void setCurrentStructure(int structure);

  int getCurrentStructure() const noexcept;
  ng::Point getStartPosition() const noexcept;
  ng::Point getFinishPosition() const noexcept;
  const ng::CaveWrapper &getCave() const;
  const ng::MazeWrapper &getMaze() const;
  void setCave(ng::CaveWrapper &&cave);
  void setMaze(ng::MazeWrapper &&maze);

  bool IsCave() const noexcept;
  bool StructureIsGood(int current_structure) const;

 private:
  QGraphicsScene *scene_;
  QColor wall_color_ = QColor("#00aa00"), empty_color_ = QColor("#303030"),
         path_color_ = Qt::red;

  int current_structure_ = 0;

  ng::CaveWrapper cave_;
  ng::MazeWrapper maze_;

  ng::Point from_, to_;

  void mousePressEvent(QMouseEvent *event) override;
  void InitializeScene();
  ng::Point getCurrentPointOfStructure(QMouseEvent *event);
};
#endif  //! A1_MAZE_1_SCENE_H_
