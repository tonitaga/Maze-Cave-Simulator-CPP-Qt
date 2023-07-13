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

#ifndef A1_MAZE_1_VIEW_H
#define A1_MAZE_1_VIEW_H

#include <QMainWindow>

#include "controller.h"

class QTimer;

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View final : public QMainWindow {
  Q_OBJECT

  using size_type = ng::size_type;

 public:
  View(ng::Controller *controller, QWidget *parent = nullptr);
  View(const View &) = delete;
  View &operator=(const View &) = delete;

  ~View();

 private slots:
  void on_GenerateAndSolveStructure_clicked();

 private slots:
  void on_actionImport_triggered();
  void on_ImportCave_clicked();
  void on_GenerateCave_clicked();
  void on_StepGenerationCave_clicked();
  void TimerTimeout();
  void on_TimerStartStopCave_clicked();
  void on_ExportCave_clicked();
  void on_actionWall_color_triggered();
  void on_actionWave_Algorithm_triggered();
  void on_actionCave_Generation_triggered();
  void on_ImportMaze_clicked();
  void on_GenerateMaze_clicked();
  void on_tabWidget_currentChanged(int index);
  void on_SolveStrucute_clicked();
  void on_actionPath_color_triggered();
  void on_ExportMaze_clicked();

 private:
  Ui::View *ui;
  QTimer *timer_;
  ng::Controller *controller_;

  int current_structure_ = 0;

  void setFont();
  void setToolTips();
  void setCaveSettings(const ng::CaveWrapper &);
  void setMazeSettings(const ng::MazeWrapper &);
  ng::CaveGenerationSettings getCaveSettingsFromView();
  ng::MazeGenerationSettings getMazeSettingsFromView();
};
#endif  //! A1_MAZE_1_VIEW_H
