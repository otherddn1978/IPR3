#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Widget w(0, &app);
    w.show();

    return app.exec();
}
