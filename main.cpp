#include <QApplication>
#include "tictac.h"

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);
    TicTac game;
    game.show();
    return app.exec();
}


