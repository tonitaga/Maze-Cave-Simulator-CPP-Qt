CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17
TESTFLAGS=-lgtest

CC_TEST_FILE =\
./Test/tests.cc\


OS=$(shell uname)
ifeq ($(OS), Linux)
  OPEN=xdg-open
else
  OPEN=open
endif

.PHONY: all

all: install tests open


install:
	@cmake -S View/ -B ./build
	@cmake --build ./build
	@cp -rf ./build/MazeAndCave.app $(HOME)/Applications/

uninstall:
	@rm -rf ./build
	@rm -rf $(HOME)/Applications/MazeAndCave.app

tests:
	@$(CC) $(CFLAGS) $(TESTFLAGS) --coverage $(CC_TEST_FILE) $(CC_FILES) -o maze_cave_test
	@./maze_cave_test

leaks: tests
	@CK_FORK=no leaks --atExit -- ./maze_cave_test

dvi:
	@open info.md

dist:
	@rm -rf A1_Maze-1
	@mkdir A1_Maze-1
	@cp -R ./build/MazeAndCave.app A1_Maze-1
	@tar -czvf A1_Maze-1.tar A1_Maze-1
	@rm -rf A1_Maze-1

bist:
	@rm -rf A1_Maze-1.tar

clean:
	@rm -rf ./build
	@rm -rf ./*.gcda
	@rm -rf ./*.gcno
	@rm -rf ./maze_cave_test
	@rm -rf .clang-format

style:
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -i Controller/*.h Model/include/*.h Model/internal/*.h
	@clang-format -i Test/*.cc
	@clang-format -i View/*.cc View/*.h

	@clang-format -n Controller/*.h Model/include/*.h Model/internal/*.h
	@clang-format -n Test/*.cc
	@clang-format -n View/*.cc View/*.h

open:
	@open ./build/MazeAndCave.app
