/** MazeAndCaveSimulator project main source file
 *
 * Copyright (C) Maze Project Developers. All Rights Reserved
 *
 * If the code of this project has helped you in any way,
 * please thank us with a cup of beer.
 *
 * team-lead gmail:    gubaydullin.nurislam@gmail.com
 * team-lead telegram: @tonitaga
 */

#include "View/view.h"

#include <QApplication>

#include "Controller/controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ng::Controller controller;
    View view(&controller);
    view.show();
    return a.exec();
}
