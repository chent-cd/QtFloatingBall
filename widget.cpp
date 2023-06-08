#include "widget.h"
#include "ui_widget.h"
#include "circlebutton.h"

#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    CircleButton *but1 = new CircleButton();
    but1->setText("≤‚ ‘\n∞¥≈•");
    but1->show();

    but1->setFixedSize(80,80);

    QList<CircleButton *> items;
    for (int i = 0; i < 3; ++i) {
        CircleButton *item = new CircleButton();
        item->setText("≤‚ ‘\n≤Àµ•");
        items << item;
        item->show();

    }
    // States
    QState *rootState = new QState;
    QState *ellipseState = new QState(rootState);
    QState *centeredState = new QState(rootState);
    QState *moveState = new QState(rootState);

    // Values
    for (int i = 0; i < items.count(); ++i) {
        CircleButton *item = items.at(i);

        //
        ellipseState->assignProperty(item, "geometry",
                                         QRect(x+but1->pos().x()+but1->width()/2-60/2 + qCos(((float)(i+1) / items.count()) * 6.28) * 60,
                                                 but1->pos().y()+but1->height()/2-60/2-qSin(((float)(i+1) / items.count()) * 6.28) * 60,60,60));


        centeredState->assignProperty(item, "geometry", QRect(but1->pos().x()+but1->width()/2-10/2,but1->pos().y()+but1->height()/2-10/2,0,0));
    }




    QStateMachine *states=new  QStateMachine(this) ;
    states->addState(rootState);
    states->setInitialState(rootState);
    rootState->setInitialState(centeredState);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    for (int i = 0; i < items.count(); ++i) {
        QPropertyAnimation *anim = new QPropertyAnimation(items[i], "geometry");
        anim->setDuration(750 + i * 25);
        anim->setEasingCurve(QEasingCurve::InOutBack);
        group->addAnimation(anim);
    }



    QSignalTransition *trans = centeredState->addTransition(but1, &QPushButton::clicked, ellipseState);
    QSignalTransition *trans2 = ellipseState->addTransition(but1, &QPushButton::clicked, centeredState);
    trans->addAnimation(group);
    trans2->addAnimation(group);

    connect(but1,&CircleButton::moved,[=]()
    {
        for (int i = 0; i < items.count(); ++i) {
            CircleButton *item = items.at(i);

            if(but1->m_isExpand)
            {
                QPropertyAnimation *anim = new QPropertyAnimation(items[i], "geometry");
                anim->setDuration(750 + i * 25);
                anim->setEasingCurve(QEasingCurve::InOutBack);

                anim->setEndValue(QRect(but1->pos().x()+but1->width()/2-60/2 + qCos(((float)(i+1) / items.count()) * 6.28) * 60,
                                             but1->pos().y()+but1->height()/2-60/2-qSin(((float)(i+1) / items.count()) * 6.28) * 60,60,60));
                anim->start();
//                moveState->assignProperty(item, "geometry",
//                                                 QRect(but1->pos().x()+but1->width()/2-60/2 + qCos(((float)(i+1) / items.count()) * 6.28) * 60,
//                                                         but1->pos().y()+but1->height()/2-60/2-qSin(((float)(i+1) / items.count()) * 6.28) * 60,60,60));

            }
            else
            {
                moveState->assignProperty(item, "geometry", QRect(but1->pos().x()+but1->width()/2-10/2,but1->pos().y()+but1->height()/2-10/2,0,0));

            }



            //
            ellipseState->assignProperty(item, "geometry",
                                             QRect(but1->pos().x()+but1->width()/2-60/2 + qCos(((float)(i+1) / items.count()) * 6.28) * 60,
                                                     but1->pos().y()+but1->height()/2-60/2-qSin(((float)(i+1) / items.count()) * 6.28) * 60,60,60));


            centeredState->assignProperty(item, "geometry", QRect(but1->pos().x()+but1->width()/2-10/2,but1->pos().y()+but1->height()/2-10/2,0,0));
        }

    });

    states->start();

}

Widget::~Widget()
{
    delete ui;
}

