#include "widget.h"
#include "ui_widget.h"
#include "floatingmenu.h"

#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    FloatingMenu *s=new FloatingMenu();

}

Widget::~Widget()
{
    delete ui;
}

