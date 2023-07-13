#include <cmath>
#include <filesystem>

#include "../Controller/controller.h"
#include "gtest/gtest.h"

static ng::Controller controller;

TEST(Test, Test_Read_File_Maze) {
  ng::MazeWrapper maze = controller.ReadFile<ng::kMaze>(
      std::filesystem::absolute("Test/resources/maze50x50.txt").string());

  ASSERT_TRUE(maze.IsGood());
  ASSERT_TRUE(maze.cols == 50);
  ASSERT_TRUE(maze.rows == 50);

  auto path = controller.Solve(maze, ng::Point{0, 0},
                               ng::Point{maze.rows - 1, maze.cols - 1});
}

TEST(Test, Test_Find_Path_Maze_5_x_5) {
  ng::MazeWrapper maze = controller.ReadFile<ng::kMaze>(
      std::filesystem::absolute("Test/resources/maze5x5.txt").string());
  ASSERT_TRUE(maze.IsGood());
  ASSERT_TRUE(maze.cols == 5);
  ASSERT_TRUE(maze.rows == 5);

  auto path = controller.Solve(maze, ng::Point{0, 0}, ng::Point{2, 0});
  std::vector<ng::Point> answer_path(3);
  answer_path[0] = {0, 0};
  answer_path[1] = {1, 0};
  answer_path[2] = {2, 0};

  ASSERT_TRUE(path.size() == answer_path.size());

  for (ng::size_type i = 0; i != path.size(); i++) {
    ASSERT_TRUE(path[i].x == answer_path[i].x);
    ASSERT_TRUE(path[i].y == answer_path[i].y);
  }
}

TEST(Test, Test_Find_Path_Maze_10_x_10) {
  ng::MazeWrapper maze = controller.ReadFile<ng::kMaze>(
      std::filesystem::absolute("Test/resources/maze10x15.txt").string());

  ASSERT_TRUE(maze.IsGood());
  ASSERT_TRUE(maze.cols == 5);
  ASSERT_TRUE(maze.rows == 5);

  auto path = controller.Solve(maze, ng::Point{0, 0}, ng::Point{4, 4});
  std::vector<ng::Point> answer_path(9);
  answer_path[0] = {0, 0};
  answer_path[1] = {1, 0};
  answer_path[2] = {2, 0};
  answer_path[3] = {3, 0};
  answer_path[4] = {4, 0};
  answer_path[5] = {4, 1};
  answer_path[6] = {4, 2};
  answer_path[7] = {4, 3};
  answer_path[8] = {4, 4};

  ASSERT_TRUE(path.size() == answer_path.size());

  for (ng::size_type i = 0; i != path.size(); i++) {
    ASSERT_TRUE(path[i].x == answer_path[i].x);
    ASSERT_TRUE(path[i].y == answer_path[i].y);
  }
}

TEST(Test, Test_Find_Path_Maze_20_x_20) {
  ng::MazeWrapper maze = controller.ReadFile<ng::kMaze>(
      std::filesystem::absolute("Test/resources/maze20x20.txt").string());

  ASSERT_TRUE(maze.IsGood());
  ASSERT_TRUE(maze.cols == 20);
  ASSERT_TRUE(maze.rows == 20);

  auto path = controller.Solve(maze, ng::Point{0, 0}, ng::Point{4, 1});
  std::vector<ng::Point> answer_path(8);
  answer_path[0] = {0, 0};
  answer_path[1] = {1, 0};
  answer_path[2] = {2, 0};
  answer_path[3] = {3, 0};
  answer_path[4] = {4, 0};
  answer_path[5] = {5, 0};
  answer_path[6] = {5, 1};
  answer_path[7] = {4, 1};

  ASSERT_TRUE(path.size() == answer_path.size());

  for (ng::size_type i = 0; i != path.size(); i++) {
    ASSERT_TRUE(path[i].x == answer_path[i].x);
    ASSERT_TRUE(path[i].y == answer_path[i].y);
  }
}

TEST(Test, Test_Find_Path_Maze_50_x_50) {
  ng::MazeWrapper maze = controller.ReadFile<ng::kMaze>(
      std::filesystem::absolute("Test/resources/maze50x50.txt").string());

  ASSERT_TRUE(maze.IsGood());
  ASSERT_TRUE(maze.cols == 50);
  ASSERT_TRUE(maze.rows == 50);

  auto path = controller.Solve(maze, ng::Point{7, 14}, ng::Point{7, 21});
  std::vector<ng::Point> answer_path(24);

  answer_path[0] = {7, 14};
  answer_path[1] = {6, 14};
  answer_path[2] = {5, 14};
  answer_path[3] = {5, 15};
  answer_path[4] = {4, 15};
  answer_path[5] = {4, 16};
  answer_path[6] = {3, 16};
  answer_path[7] = {3, 17};
  answer_path[8] = {2, 17};
  answer_path[9] = {1, 17};
  answer_path[10] = {1, 18};
  answer_path[11] = {1, 19};
  answer_path[12] = {0, 19};
  answer_path[13] = {0, 20};
  answer_path[14] = {0, 21};
  answer_path[15] = {1, 21};
  answer_path[16] = {2, 21};
  answer_path[17] = {2, 22};
  answer_path[18] = {3, 22};
  answer_path[19] = {4, 22};
  answer_path[20] = {4, 21};
  answer_path[21] = {5, 21};
  answer_path[22] = {6, 21};
  answer_path[23] = {7, 21};

  ASSERT_TRUE(path.size() == answer_path.size());

  for (ng::size_type i = 0; i != path.size(); i++) {
    ASSERT_TRUE(path[i].x == answer_path[i].x);
    ASSERT_TRUE(path[i].y == answer_path[i].y);
  }
}

TEST(Test, Test_Find_Path_Cave_10_x_10) {
  ng::CaveWrapper cave = controller.ReadFile<ng::kCave>(
      std::filesystem::absolute("Test/resources/cave#1.txt").string());

  ASSERT_TRUE(cave.IsGood());
  ASSERT_TRUE(cave.cols == 10);
  ASSERT_TRUE(cave.rows == 10);

  auto path = controller.Solve(cave, ng::Point{1, 4}, ng::Point{3, 8});
  std::vector<ng::Point> answer_path(7);
  answer_path[0] = {1, 4};
  answer_path[1] = {1, 5};
  answer_path[2] = {1, 6};
  answer_path[3] = {1, 7};
  answer_path[4] = {1, 8};
  answer_path[5] = {2, 8};
  answer_path[6] = {3, 8};

  ASSERT_TRUE(path.size() == answer_path.size());

  for (ng::size_type i = 0; i != path.size(); i++) {
    ASSERT_TRUE(path[i].x == answer_path[i].x);
    ASSERT_TRUE(path[i].y == answer_path[i].y);
  }
}

TEST(Test, Test_Find_Path_Cave_20_x_20) {
  ng::CaveWrapper cave = controller.ReadFile<ng::kCave>(
      std::filesystem::absolute("Test/resources/cave20x20.txt").string());
  ASSERT_TRUE(cave.IsGood());
  ASSERT_TRUE(cave.cols == 20);
  ASSERT_TRUE(cave.rows == 20);

  auto path = controller.Solve(cave, ng::Point{4, 6}, ng::Point{12, 7});
  std::vector<ng::Point> answer_path(38);
  answer_path[0] = {4, 6};
  answer_path[1] = {5, 6};
  answer_path[2] = {5, 7};
  answer_path[3] = {6, 7};
  answer_path[4] = {6, 8};
  answer_path[5] = {7, 8};
  answer_path[6] = {8, 8};
  answer_path[7] = {8, 9};
  answer_path[8] = {9, 9};
  answer_path[9] = {10, 9};
  answer_path[10] = {11, 9};
  answer_path[11] = {11, 10};
  answer_path[12] = {12, 10};
  answer_path[13] = {13, 10};
  answer_path[14] = {13, 11};
  answer_path[15] = {13, 12};
  answer_path[16] = {13, 13};
  answer_path[17] = {14, 13};
  answer_path[18] = {15, 13};
  answer_path[19] = {16, 13};
  answer_path[20] = {17, 13};
  answer_path[21] = {18, 13};
  answer_path[22] = {19, 13};
  answer_path[23] = {19, 12};
  answer_path[24] = {19, 11};
  answer_path[25] = {19, 10};
  answer_path[26] = {19, 9};
  answer_path[27] = {19, 8};
  answer_path[28] = {19, 7};
  answer_path[29] = {19, 6};
  answer_path[30] = {18, 6};
  answer_path[31] = {17, 6};
  answer_path[32] = {16, 6};
  answer_path[33] = {15, 6};
  answer_path[34] = {14, 6};
  answer_path[35] = {13, 6};
  answer_path[36] = {12, 6};
  answer_path[37] = {12, 7};

  ASSERT_TRUE(path.size() == answer_path.size());

  for (ng::size_type i = 0; i != path.size(); i++) {
    ASSERT_TRUE(path[i].x == answer_path[i].x);
    ASSERT_TRUE(path[i].y == answer_path[i].y);
  }
}

TEST(Test, Test_Find_Path_Cave_50_x_50) {
  ng::CaveWrapper cave = controller.ReadFile<ng::kCave>(
      std::filesystem::absolute("Test/resources/cave50x50.txt").string());
  ASSERT_TRUE(cave.IsGood());
  ASSERT_TRUE(cave.cols == 50);
  ASSERT_TRUE(cave.rows == 50);

  auto path = controller.Solve(cave, ng::Point{13, 4}, ng::Point{46, 12});
  std::vector<ng::Point> answer_path(42);
  answer_path[0] = {13, 4};
  answer_path[1] = {13, 5};
  answer_path[2] = {13, 6};
  answer_path[3] = {14, 6};
  answer_path[4] = {15, 6};
  answer_path[5] = {16, 6};
  answer_path[6] = {17, 6};
  answer_path[7] = {17, 7};
  answer_path[8] = {18, 7};
  answer_path[9] = {18, 8};
  answer_path[10] = {19, 8};
  answer_path[11] = {20, 8};
  answer_path[12] = {21, 8};
  answer_path[13] = {21, 9};
  answer_path[14] = {22, 9};
  answer_path[15] = {22, 10};
  answer_path[16] = {23, 10};
  answer_path[17] = {24, 10};
  answer_path[18] = {25, 10};
  answer_path[19] = {26, 10};
  answer_path[20] = {27, 10};
  answer_path[21] = {28, 10};
  answer_path[22] = {29, 10};
  answer_path[23] = {30, 10};
  answer_path[24] = {31, 10};
  answer_path[25] = {32, 10};
  answer_path[26] = {32, 11};
  answer_path[27] = {33, 11};
  answer_path[28] = {33, 12};
  answer_path[29] = {34, 12};
  answer_path[30] = {35, 12};
  answer_path[31] = {36, 12};
  answer_path[32] = {37, 12};
  answer_path[33] = {38, 12};
  answer_path[34] = {39, 12};
  answer_path[35] = {40, 12};
  answer_path[36] = {41, 12};
  answer_path[37] = {42, 12};
  answer_path[38] = {43, 12};
  answer_path[39] = {44, 12};
  answer_path[40] = {45, 12};
  answer_path[41] = {46, 12};

  ASSERT_TRUE(path.size() == answer_path.size());

  for (ng::size_type i = 0; i != path.size(); i++) {
    ASSERT_TRUE(path[i].x == answer_path[i].x);
    ASSERT_TRUE(path[i].y == answer_path[i].y);
  }
}

TEST(Test, Test_Random_Generate_Cave_Count_100_N1) {
  srand(time(nullptr));
  for (ng::size_type i = 0; i < 100; i++) {
    ng::size_type rows = rand() % 51;
    ng::size_type cols = rand() % 51;
    ng::size_type live_chance = rand() % 50;
    ng::size_type generation_count = rand() % 7;
    std::pair<ng::size_type, ng::size_type> live_limit(1, 1);
    std::pair<ng::size_type, ng::size_type> born_limit(1, 1);
    live_limit = {rand() % 9, rand() % 9};
    born_limit = {rand() % 9, rand() % 9};

    ng::CaveGenerationSettings settings{.rows = rows,
                                         .cols = cols,
                                         .live_chance = live_chance,
                                         .generation_count = generation_count,
                                         .live_limit = live_limit,
                                         .born_limit = born_limit};
    auto saved_successfully = controller.SaveFile(
        controller.Generate(settings),
        std::filesystem::absolute("Test/resources/cave#random.txt").string());
    if (!saved_successfully) continue;

    auto cave = controller.ReadFile<ng::kCave>(
        std::filesystem::absolute("Test/resources/cave#random.txt").string());
    ASSERT_TRUE(cave.IsGood());
    ASSERT_TRUE(cave.cols == cols);
    ASSERT_TRUE(cave.rows == rows);
    std::remove("Test/resources/cave#random.txt");
  }
}

TEST(Test, Test_Random_Generate_Cave_Count_100) {
  ng::CaveGenerationSettings settings_copy{.rows = 10,
                                            .cols = 10,
                                            .live_chance = 50,
                                            .generation_count = 5,
                                            .live_limit = {2, 3},
                                            .born_limit = {3, 3}};

  controller.SaveFile(
      controller.Generate(settings_copy),
      std::filesystem::absolute("Test/resources/cave#copy.txt").string());

  auto cave_copy = controller.ReadFile<ng::kCave>(
      std::filesystem::absolute("Test/resources/cave#copy.txt").string());

  for (ng::size_type i = 0; i < 100; i++) {
    ng::size_type rows = rand() % 51;
    ng::size_type cols = rand() % 51;
    ng::size_type live_chance = rand() % 50;
    ng::size_type generation_count = rand() % 7;
    std::pair<ng::size_type, ng::size_type> live_limit(1, 1);
    std::pair<ng::size_type, ng::size_type> born_limit(1, 1);
    live_limit = {rand() % 9, rand() % 9};
    born_limit = {rand() % 9, rand() % 9};

    ng::CaveGenerationSettings settings{.rows = rows,
                                         .cols = cols,
                                         .live_chance = live_chance,
                                         .generation_count = generation_count,
                                         .live_limit = live_limit,
                                         .born_limit = born_limit};
    auto saved_successfully = controller.SaveFile(
        controller.Generate(settings, cave_copy),
        std::filesystem::absolute("Test/resources/cave#random2.txt").string());
    if (!saved_successfully) continue;

    auto cave = controller.ReadFile<ng::kCave>(
        std::filesystem::absolute("Test/resources/cave#random2.txt").string());
    ASSERT_TRUE(cave.IsGood());
    std::remove("Test/resources/cave#random2.txt");
    cave_copy = std::move(cave);
  }
}

TEST(Test, Test_Generate_Cave_50x50) {
  ng::CaveGenerationSettings settings{.rows = 50,
                                       .cols = 50,
                                       .live_chance = 50,
                                       .generation_count = 5,
                                       .live_limit = {2, 3},
                                       .born_limit = {3, 3}};
  controller.SaveFile(
      controller.Generate(settings),
      std::filesystem::absolute("Test/resources/cave#50_50.txt").string());
  auto cave = controller.ReadFile<ng::kCave>(
      std::filesystem::absolute("Test/resources/cave#50_50.txt").string());

  ASSERT_TRUE(cave.IsGood());
  ASSERT_TRUE(cave.cols == 50);
  ASSERT_TRUE(cave.rows == 50);
  cave.Clear();
}

TEST(Test, Test_Generate_Maze_50x50) {
  ng::MazeGenerationSettings settings{.rows = 50, .cols = 50};
  controller.SaveFile(
      controller.Generate(settings),
      std::filesystem::absolute("Test/resources/maze#50_50.txt").string());
  auto maze = controller.ReadFile<ng::kMaze>(
      std::filesystem::absolute("Test/resources/maze#50_50.txt").string());

  ASSERT_TRUE(maze.IsGood());
  ASSERT_TRUE(maze.cols == 50);
  ASSERT_TRUE(maze.rows == 50);
  maze.Clear();
}

TEST(Test, Test_Generate_Cave_0x0) {
  ng::CaveGenerationSettings settings{.rows = 0,
                                       .cols = 0,
                                       .live_chance = 50,
                                       .generation_count = 5,
                                       .live_limit = {2, 3},
                                       .born_limit = {3, 3}};
  controller.SaveFile(
      controller.Generate(settings),
      std::filesystem::absolute("Test/resources/cave#0_0.txt").string());
  auto cave = controller.ReadFile<ng::kCave>(
      std::filesystem::absolute("Test/resources/cave#0_0.txt").string());

  ASSERT_TRUE(!cave.IsGood());
  ASSERT_TRUE(cave.cols == 0);
  ASSERT_TRUE(cave.rows == 0);
  cave.Clear();
}

TEST(Test, Test_Generate_Maze_0x0) {
  ng::MazeGenerationSettings settings{.rows = 0, .cols = 0};
  controller.SaveFile(
      controller.Generate(settings),
      std::filesystem::absolute("Test/resources/maze#0_0.txt").string());
  auto maze = controller.ReadFile<ng::kMaze>(
      std::filesystem::absolute("Test/resources/maze#0_0.txt").string());

  ASSERT_TRUE(!maze.IsGood());
  ASSERT_TRUE(maze.cols == 0);
  ASSERT_TRUE(maze.rows == 0);
  maze.Clear();
}

TEST(Test, Test_Read_Trash_File_Maze) {
  ng::MazeWrapper maze = controller.ReadFile<ng::kMaze>(
      std::filesystem::absolute("Test/resources/trash_file.txt").string());

  ASSERT_TRUE(!maze.IsGood());
  ASSERT_TRUE(maze.cols == 0);
  ASSERT_TRUE(maze.rows == 0);

  auto path = controller.Solve(maze, ng::Point{0, 0},
                               ng::Point{maze.rows - 1, maze.cols - 1});
  ASSERT_TRUE(path.empty());
  ASSERT_TRUE(path.size() == 0);
  maze.Clear();
}

TEST(Test, Test_Read_Trash_File_Cave) {
  ng::CaveWrapper maze = controller.ReadFile<ng::kCave>(
      std::filesystem::absolute("Test/resources/trash_file.txt").string());

  ASSERT_TRUE(!maze.IsGood());
  ASSERT_TRUE(maze.cols == 0);
  ASSERT_TRUE(maze.rows == 0);

  auto path = controller.Solve(maze, ng::Point{0, 0},
                               ng::Point{maze.rows - 1, maze.cols - 1});
  ASSERT_TRUE(path.empty());
  ASSERT_TRUE(path.size() == 0);
  maze.Clear();
}

TEST(Test, Test_Find_Path_By_Click_On_Wall_Maze_10x10) {
  ng::MazeWrapper maze = controller.ReadFile<ng::kMaze>(
      std::filesystem::absolute("Test/resources/maze10x15.txt").string());

  ASSERT_TRUE(maze.IsGood());
  ASSERT_TRUE(maze.cols == 5);
  ASSERT_TRUE(maze.rows == 5);

  auto path =
      controller.Solve(maze,
                       ng::Point{std::numeric_limits<ng::size_type>::max(),
                                  std::numeric_limits<ng::size_type>::max()},
                       ng::Point{4, 4});

  ASSERT_TRUE(path.empty());
  ASSERT_TRUE(path.size() == 0);
  maze.Clear();
}

TEST(Test, Test_Find_Path_By_Click_On_Wall_Maze_20x20) {
  ng::MazeWrapper maze = controller.ReadFile<ng::kMaze>(
      std::filesystem::absolute("Test/resources/maze20x20.txt").string());

  ASSERT_TRUE(maze.IsGood());
  ASSERT_TRUE(maze.cols == 20);
  ASSERT_TRUE(maze.rows == 20);

  auto path =
      controller.Solve(maze,
                       ng::Point{std::numeric_limits<ng::size_type>::max(),
                                  std::numeric_limits<ng::size_type>::max()},
                       ng::Point{10, 12});

  ASSERT_TRUE(path.empty());
  ASSERT_TRUE(path.size() == 0);
  maze.Clear();
}

TEST(Test, Test_Find_Path_By_Click_On_Wall_Maze_50x50) {
  ng::MazeWrapper maze = controller.ReadFile<ng::kMaze>(
      std::filesystem::absolute("Test/resources/maze50x50.txt").string());

  ASSERT_TRUE(maze.IsGood());
  ASSERT_TRUE(maze.cols == 50);
  ASSERT_TRUE(maze.rows == 50);

  auto path =
      controller.Solve(maze,
                       ng::Point{std::numeric_limits<ng::size_type>::max(),
                                  std::numeric_limits<ng::size_type>::max()},
                       ng::Point{32, 4});

  ASSERT_TRUE(path.empty());
  ASSERT_TRUE(path.size() == 0);
  maze.Clear();
}

TEST(Test, Test_Find_Path_By_Click_On_Wall_Cave_20x20) {
  ng::CaveWrapper cave = controller.ReadFile<ng::kCave>(
      std::filesystem::absolute("Test/resources/cave20x20.txt").string());

  ASSERT_TRUE(cave.IsGood());
  ASSERT_TRUE(cave.cols == 20);
  ASSERT_TRUE(cave.rows == 20);

  auto path = controller.Solve(cave, ng::Point{1, 0}, ng::Point{0, 4});

  ASSERT_TRUE(path.empty());
  ASSERT_TRUE(path.size() == 0);
  cave.Clear();
}

TEST(Test, Test_Find_Path_By_Click_On_Wall_Cave_50x50_N1) {
  ng::CaveWrapper cave = controller.ReadFile<ng::kCave>(
      std::filesystem::absolute("Test/resources/cave20x20.txt").string());

  ASSERT_TRUE(cave.IsGood());
  ASSERT_TRUE(cave.cols == 20);
  ASSERT_TRUE(cave.rows == 20);

  auto path = controller.Solve(cave, ng::Point{1, 1}, ng::Point{6, 13});

  ASSERT_TRUE(path.empty());
  ASSERT_TRUE(path.size() == 0);
  cave.Clear();
}

TEST(Test, Test_Find_Path_By_Click_On_Wall_Cave_50x50_N2) {
  ng::CaveWrapper cave = controller.ReadFile<ng::kCave>(
      std::filesystem::absolute("Test/resources/cave20x20.txt").string());

  ASSERT_TRUE(cave.IsGood());
  ASSERT_TRUE(cave.cols == 20);
  ASSERT_TRUE(cave.rows == 20);

  auto path = controller.Solve(cave, ng::Point{49, 49}, ng::Point{10, 13});

  ASSERT_TRUE(path.empty());
  ASSERT_TRUE(path.size() == 0);
  cave.Clear();
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}