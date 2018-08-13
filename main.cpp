#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    meinWidget widget;
    widget.setGeometry(0, 0, 650, 500);
    widget.setWindowTitle("stII-game");
    widget.show();
    return app.exec();
}
