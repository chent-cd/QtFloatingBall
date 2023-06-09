#include "widget.h"
#include "ui_widget.h"
#include "floatingmenufactory.h"

#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    FloatingMenuFactory *s=new FloatingMenuFactory();

}

Widget::~Widget()
{
    delete ui;
}

