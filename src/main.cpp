#include <iostream>
#include <string>

#include "board.h"
#include "gui.h"
#include "lib.h"

int main(int argc, char* argv[])
{
    auto const lib = library {};
    auto const message = "Hello from " + lib.name + "!";
    std::cout << message << '\n';

    Board board(true);

    QApplication app(argc, argv);
    Gui gui(&board);
    gui.show();

    return app.exec();
}
