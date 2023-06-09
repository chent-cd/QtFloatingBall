#include "widget.h"

#include <QApplication>

#include "floatingmenu.h"

#pragma execution_character_set("utf-8")


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FloatingMenu w;
//    w.show();

    return a.exec();
}
