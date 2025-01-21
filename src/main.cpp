#include "common.h"
#include "gui.h"

int main(int argc, char* argv[])
{
    Board board;

    const QApplication app(argc, argv);
    Gui gui(&board);
    gui.show();

    return QApplication::exec();
}
