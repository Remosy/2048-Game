#include <QApplication>
#include "boardgui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand((int)time(0));
    BoardGUI boardGUI;
    boardGUI.show();
    return a.exec();
}


