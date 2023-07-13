#include "scene.h"

#include <QMouseEvent>

Scene::Scene(QWidget *parent)
    : QGraphicsView(parent), scene_(new QGraphicsScene(QRect(0, 0, 500, 500))) {
  InitializeScene();
}

Scene::~Scene() { delete scene_; }

void Scene::setWallColor(QColor color) { wall_color_ = color; }

void Scene::setPathColor(QColor color) { path_color_ = color; }

void Scene::DrawMaze() {
  if (!maze_.IsGood()) return;
  scene_->clear();

  double width = 500.0 / maze_.cols, height = 500.0 / maze_.rows;

  setBackgroundBrush(empty_color_);
  QPen pen(wall_color_, 2);
  scene_->addLine(0, 0, 500, 0, pen);
  scene_->addLine(0, 0, 0, 500, pen);
  for (ng::size_type row = 0; row != maze_.rows; ++row) {
    for (ng::size_type col = 0; col != maze_.cols; ++col) {
      int x0 = width * col, y0 = height * row;
      int x1 = width * (col + 1), y1 = height * (row + 1);
      if (maze_(row, col)) scene_->addLine(x1, y0, x1, y1, pen);
      if (maze_(row, col, false)) scene_->addLine(x0, y1, x1, y1, pen);
    }
  }
}

void Scene::DrawCave() {
  if (!cave_.IsGood()) return;
  scene_->clear();

  double rect_width = scene_->width() / cave_.cols,
         rect_height = scene_->height() / cave_.rows, step_row = 0,
         step_col = 0;

  setBackgroundBrush(empty_color_);
  for (ng::size_type row = 0; row != cave_.rows; ++row) {
    step_row = 0;
    for (ng::size_type col = 0; col != cave_.cols; ++col) {
      if (cave_(row, col)) {
        scene_->addRect(step_row, step_col, rect_width, rect_height,
                        QPen(wall_color_), QBrush(wall_color_));
      }
      step_row += rect_width;
    }
    step_col += rect_height;
  }
}

void Scene::DrawMazePath(const std::vector<ng::Point> &path) {
  if (!maze_.IsGood()) return;
  DrawMaze();
  double width_aspect = 500.0 / maze_.cols, height_aspect = 500.0 / maze_.rows;

  QPen pen(path_color_, 1);

  for (auto [row, col] : path)
    scene_->addRect(col * width_aspect + width_aspect / 5,
                    row * height_aspect + height_aspect / 5, width_aspect * 0.6,
                    height_aspect * 0.6, pen);
}

void Scene::DrawCavePath(const std::vector<ng::Point> &path) {
  if (!cave_.IsGood()) return;
  DrawCave();
  double width_aspect = 500.0 / cave_.cols, height_aspect = 500.0 / cave_.rows;

  QPen pen(path_color_, 1);

  for (auto [row, col] : path)
    scene_->addRect(col * width_aspect + width_aspect / 5,
                    row * height_aspect + height_aspect / 5, width_aspect * 0.6,
                    height_aspect * 0.6, pen);
}

void Scene::ClearScene() noexcept { scene_->clear(); }

void Scene::setCurrentStructure(int structure) {
  current_structure_ = structure;
}

bool Scene::IsCave() const noexcept { return current_structure_ == 0; }

int Scene::getCurrentStructure() const noexcept { return current_structure_; }

ng::Point Scene::getStartPosition() const noexcept { return from_; }

ng::Point Scene::getFinishPosition() const noexcept { return to_; }

const ng::CaveWrapper &Scene::getCave() const { return cave_; }

const ng::MazeWrapper &Scene::getMaze() const { return maze_; }

void Scene::setCave(ng::CaveWrapper &&cave) { cave_ = std::move(cave); }

void Scene::setMaze(ng::MazeWrapper &&maze) { maze_ = std::move(maze); }

bool Scene::StructureIsGood(int current_structure) const {
  if (current_structure)
    return maze_.IsGood();
  else
    return cave_.IsGood();
}

void Scene::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton)
    from_ = getCurrentPointOfStructure(event);
  else if (event->button() == Qt::RightButton)
    to_ = getCurrentPointOfStructure(event);
}

void Scene::InitializeScene() {
  setScene(scene_);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setBackgroundBrush(empty_color_);
}

ng::Point Scene::getCurrentPointOfStructure(QMouseEvent *event) {
  double height_aspect, width_aspect;
  if (current_structure_ == 1) {
    width_aspect = 500.0 / maze_.cols;
    height_aspect = 500.0 / maze_.rows;
  } else {
    width_aspect = 500.0 / cave_.cols;
    height_aspect = 500.0 / cave_.rows;
  }

  return ng::Point(
      static_cast<ng::size_type>(event->pos().y() / height_aspect),
      static_cast<ng::size_type>(event->pos().x() / width_aspect));
}
