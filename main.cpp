#include "widget.h"

#include <QApplication>

#include "floatingmenufactory.h"

#pragma execution_character_set("utf-8")


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FloatingMenuFactory w;
    w.setMenuText("²âÊÔ\n°´Å¥");
    w.setActionTexts(QStringList{"1","2","3","4","5"});
    CircleButton *but=w.createFloatingMenu();

    QObject::connect(but,&CircleButton::closed,[&]()
    {
        a.quit();
    });

    for(CircleButton *butSub:but->m_butActs)
    {
        QObject::connect(butSub,&CircleButton::clicked,[&]()
        {
             qDebug()<<"but1";
        });
    }
    QObject::connect(but,&CircleButton::closed,[&]()
    {
        a.quit();
    });
//    w.show();

    return a.exec();
}
