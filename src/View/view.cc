#include "view.h"

#include <QColorDialog>
#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>
#include <QFontDatabase>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTimer>

#include "./ui_view.h"

View::View(ng::Controller *controller, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::View),
      timer_(new QTimer),
      controller_(controller) {
  ui->setupUi(this);
  setWindowTitle("Maze & Cave Simulator");
  setFont();
  setToolTips();
  connect(timer_, &QTimer::timeout, this, &View::TimerTimeout);
}

View::~View() {
  delete ui;
  delete timer_;
}

ng::CaveGenerationSettings View::getCaveSettingsFromView() {
  return {
      .rows = static_cast<size_type>(ui->cave_rows->value()),
      .cols = static_cast<size_type>(ui->cave_cols->value()),
      .live_chance = static_cast<size_type>(ui->live_chance->value()),
      .generation_count = static_cast<size_type>(ui->population_count->value()),
      .live_limit = {static_cast<size_type>(ui->survive_left_border->value()),
                     static_cast<size_type>(ui->survive_rigth_border->value())},
      .born_limit = {static_cast<size_type>(ui->born_left_border->value()),
                     static_cast<size_type>(ui->born_rigth_border->value())}};
}

ng::MazeGenerationSettings View::getMazeSettingsFromView() {
  return {
      .rows = static_cast<size_type>(ui->maze_rows->value()),
      .cols = static_cast<size_type>(ui->maze_cols->value()),
  };
}

void View::setCaveSettings(const ng::CaveWrapper &cave) {
  ui->cave_rows->setValue(cave.rows);
  ui->cave_cols->setValue(cave.cols);
}

void View::setMazeSettings(const ng::MazeWrapper &maze) {
  ui->maze_rows->setValue(maze.rows);
  ui->maze_cols->setValue(maze.cols);
}

void View::on_actionImport_triggered() {
  std::string path =
      QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "*.txt")
          .toStdString();
  if (path.empty()) return;
  ng::MazeWrapper maze = controller_->ReadFile<ng::kMaze>(path);
  if (maze.IsGood()) {
    setMazeSettings(maze);
    ui->graphicsView->setMaze(std::move(maze));
    ui->graphicsView->DrawMaze();
    ui->tabWidget->setCurrentIndex(1);
    return;
  }

  ng::CaveWrapper cave = controller_->ReadFile<ng::kCave>(path);
  if (cave.IsGood()) {
    setCaveSettings(cave);
    ui->graphicsView->setCave(std::move(cave));
    ui->graphicsView->DrawCave();
    ui->tabWidget->setCurrentIndex(0);
    return;
  }
  QMessageBox::information(this, "Wrong file",
                           "Dude, this is a wrong file...\n\n"
                           "      ╭(ರ⌓ರ)╮");
}

void View::on_ImportCave_clicked() {
  std::string path = QFileDialog::getOpenFileName(this, "Import cave",
                                                  QDir::homePath(), "*.txt")
                         .toStdString();
  if (path.empty()) return;
  ng::CaveWrapper cave = controller_->ReadFile<ng::kCave>(path);
  if (cave.IsGood()) {
    setCaveSettings(cave);
    ui->graphicsView->setCave(std::move(cave));
    ui->graphicsView->DrawCave();
    ui->graphicsView->setCurrentStructure(0);
  } else
    QMessageBox::information(this, "Wrong file",
                             "Dude, this is not a cave...\n\n"
                             "      ╭(ರ⌓ರ)╮");
}

void View::on_GenerateCave_clicked() {
  ui->current_population->setText(QString::number(0));
  auto settings = getCaveSettingsFromView();
  auto current_population = settings.generation_count;
  ui->graphicsView->setCave(controller_->Generate(settings));
  ui->graphicsView->DrawCave();
  ui->current_population->setText(QString::number(current_population));
}

void View::on_StepGenerationCave_clicked() {
  ng::CaveWrapper cave = ui->graphicsView->getCave();
  controller_->Generate(getCaveSettingsFromView(), cave);
  ui->graphicsView->setCave(std::move(cave));
  ui->graphicsView->DrawCave();
  auto current_population = ui->current_population->text().toUInt();
  ui->current_population->setText(QString::number(++current_population));
}

void View::TimerTimeout() { on_StepGenerationCave_clicked(); }

void View::on_TimerStartStopCave_clicked() {
  if (!ui->graphicsView->StructureIsGood(0)) return;
  if (!timer_->isActive()) {
    timer_->start(ui->timer_value_ms->value());
    ui->TimerStartStopCave->setText("Stop");
  } else {
    timer_->stop();
    ui->TimerStartStopCave->setText("Start");
  }
}

void View::on_ExportCave_clicked() {
  ng::CaveWrapper cave = ui->graphicsView->getCave();
  if (!cave.IsGood()) return;
  std::string path =
      QFileDialog::getSaveFileName(this, "Save cave", QDir::homePath(), "*.txt")
          .toStdString();
  controller_->SaveFile(cave, path);
}

void View::on_ExportMaze_clicked() {
  ng::MazeWrapper maze = ui->graphicsView->getMaze();
  if (!maze.IsGood()) return;
  std::string path =
      QFileDialog::getSaveFileName(this, "Save maze", QDir::homePath(), "*.txt")
          .toStdString();
  controller_->SaveFile(maze, path);
}

void View::setFont() {
  int id = QFontDatabase::addApplicationFont(":/fonts/PixelBoldFont.ttf");
  QString family = QFontDatabase::applicationFontFamilies(id).at(0);
  QFont pixel(family, 16);

  ui->ExportCave->setFont(pixel);
  ui->ExportMaze->setFont(pixel);
  ui->ImportCave->setFont(pixel);
  ui->ImportMaze->setFont(pixel);
  ui->GenerateCave->setFont(pixel);
  ui->GenerateMaze->setFont(pixel);
  ui->TimerStartStopCave->setFont(pixel);
  ui->StepGenerationCave->setFont(pixel);
  ui->SolveStrucute->setFont(pixel);
  ui->GenerateAndSolveStructure->setFont(pixel);
  pixel.setPixelSize(10);
  QVector<QLabel *> labels{ui->label,
                           ui->label_11,
                           ui->label_2,
                           ui->label_3,
                           ui->label_4,
                           ui->label_5,
                           ui->label_6,
                           ui->label_7,
                           ui->label_8,
                           ui->label_9,
                           ui->label_cols,
                           ui->label_rows_cave,
                           ui->label_cols_cave,
                           ui->label_rows,
                           ui->current_structure,
                           ui->current_population,
                           ui->path_length,
                           ui->label_path_info,
                           ui->label_10,
                           ui->label_13,
                           ui->label_start_position,
                           ui->label_finish_position,
                           ui->label_eyler};
  QVector<QSpinBox *> spixboxes{
      ui->cave_rows,           ui->cave_cols,           ui->maze_cols,
      ui->maze_rows,           ui->live_chance,         ui->population_count,
      ui->timer_value_ms,      ui->born_left_border,    ui->born_rigth_border,
      ui->survive_left_border, ui->survive_rigth_border};
  for (auto spinbox : spixboxes) spinbox->setFont(pixel);
  for (auto label : labels) label->setFont(pixel);
}

void View::setToolTips() {
  ui->StepGenerationCave->setToolTip(
      "Generates next population of current cave");
  ui->TimerStartStopCave->setToolTip(
      "Starts/Stops auto generation of next population");
  ui->timer_value_ms->setToolTip("Time between next generation in ms");
  ui->SolveStrucute->setToolTip("Found path of structure in scene");
}

void View::on_actionWall_color_triggered() {
  ui->graphicsView->setWallColor(
      QColorDialog::getColor(Qt::green, this, "Select Wall color"));
}

void View::on_actionWave_Algorithm_triggered() {
  QDesktopServices::openUrl(QUrl("https://habr.com/ru/articles/745294/"));
}

void View::on_actionCave_Generation_triggered() {
  QDesktopServices::openUrl(QUrl("https://habr.com/ru/articles/741564/"));
}

void View::on_ImportMaze_clicked() {
  std::string path = QFileDialog::getOpenFileName(this, "Import maze",
                                                  QDir::homePath(), "*.txt")
                         .toStdString();
  if (path.empty()) return;
  ng::MazeWrapper maze = controller_->ReadFile<ng::kMaze>(path);
  if (maze.IsGood()) {
    setMazeSettings(maze);
    ui->graphicsView->setMaze(std::move(maze));
    ui->graphicsView->DrawMaze();
    ui->graphicsView->setCurrentStructure(1);
  } else
    QMessageBox::information(this, "Wrong file",
                             "Dude, this is not a maze...\n\n"
                             "      ╭(ರ⌓ರ)╮");
}

void View::on_GenerateMaze_clicked() {
  ui->graphicsView->setMaze(controller_->Generate(getMazeSettingsFromView()));
  ui->graphicsView->DrawMaze();
}

void View::on_tabWidget_currentChanged(int index) {
  if (timer_->isActive()) {
    timer_->stop();
    ui->TimerStartStopCave->setText("Start");
  }
  if (index == 2) return;
  current_structure_ = index;
  if (index) {
    if (ui->graphicsView->StructureIsGood(current_structure_))
      ui->graphicsView->DrawMaze();
    else
      ui->graphicsView->ClearScene();
  } else {
    if (ui->graphicsView->StructureIsGood(current_structure_))
      ui->graphicsView->DrawCave();
    else
      ui->graphicsView->ClearScene();
  }
  ui->graphicsView->setCurrentStructure(index);
  ui->current_structure->setText(current_structure_ ? "Maze" : "Cave");
}

void View::on_SolveStrucute_clicked() {
  ng::Point start = ui->graphicsView->getStartPosition();
  ng::Point finish = ui->graphicsView->getFinishPosition();
  ng::size_type length = 0;
  if (current_structure_) {
    auto path = controller_->Solve(ui->graphicsView->getMaze(), start, finish);
    length = path.size();
    ui->graphicsView->DrawMazePath(path);
  } else {
    auto path = controller_->Solve(ui->graphicsView->getCave(), start, finish);
    length = path.size();
    ui->graphicsView->DrawCavePath(path);
  }
  ui->path_length->setText(QString::number(length));
  ui->label_start_position->setText("{" + QString::number(start.x) + ", " +
                                    QString::number(start.y) + "}");
  ui->label_finish_position->setText("{" + QString::number(finish.x) + ", " +
                                     QString::number(finish.y) + "}");
}

void View::on_actionPath_color_triggered() {
  ui->graphicsView->setPathColor(
      QColorDialog::getColor(Qt::green, this, "Select Wall color"));
}

void View::on_GenerateAndSolveStructure_clicked() {
  auto current_structure = ui->graphicsView->getCurrentStructure();
  ng::Point start = ui->graphicsView->getStartPosition(),
             finish = ui->graphicsView->getFinishPosition();
  ng::size_type path_length = 0;
  if (current_structure) {
    ui->graphicsView->setMaze(controller_->Generate(getMazeSettingsFromView()));
    ui->graphicsView->DrawMaze();
    auto path = controller_->Solve(ui->graphicsView->getMaze(), start, finish);
    path_length = path.size();
    ui->graphicsView->DrawMazePath(path);
  } else {
    ui->graphicsView->setCave(controller_->Generate(getCaveSettingsFromView()));
    ui->graphicsView->DrawCave();
    auto path = controller_->Solve(ui->graphicsView->getCave(), start, finish);
    path_length = path.size();
    ui->graphicsView->DrawCavePath(path);
  }
  ui->path_length->setText(QString::number(path_length));
  ui->label_start_position->setText("{" + QString::number(start.x) + ", " +
                                    QString::number(start.y) + "}");
  ui->label_finish_position->setText("{" + QString::number(finish.x) + ", " +
                                     QString::number(finish.y) + "}");
}
