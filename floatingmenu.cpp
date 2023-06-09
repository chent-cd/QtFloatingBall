#include "floatingmenu.h"

FloatingMenu::FloatingMenu(QObject *parent) : QObject(parent)
{
    m_pButMenu=new CircleButton();
    m_pButMenu->setText("测试\n按钮");
    m_pButMenu->setFixedSize(80,80);
    m_pButMenu->show();

    //子菜单个数及显示文字
    addAction(QStringList{"1","2","3","4","5"});

    initSates();

    initSateMachine();

    initAnimation();

    states->start();

}

void FloatingMenu::addAction(const QStringList &titleAction)
{
    for (QString title : titleAction) {
        CircleButton *item = new CircleButton();
        item->setText(title);
        m_butActs << item;
        item->show();
    }
}

void FloatingMenu::initSates()
{

    m_pRootState = new QState();
    m_pSurroundState = new QState(m_pRootState);
    m_pCenteredState = new QState(m_pRootState);
    m_pMoveState = new QState(m_pRootState);

    // Values
    for (int i = 0; i < m_butActs.count(); ++i) {
        CircleButton *item = m_butActs.at(i);

        //
        m_pSurroundState->assignProperty(item, "geometry",
                                         QRect(m_pButMenu->pos().x()+m_pButMenu->width()/2-60/2 + qCos(((float)(i+1) / m_butActs.count()) * 6.28) * 60,
                                                 m_pButMenu->pos().y()+m_pButMenu->height()/2-60/2-qSin(((float)(i+1) / m_butActs.count()) * 6.28) * 60,60,60));


        m_pCenteredState->assignProperty(item, "geometry", QRect(m_pButMenu->pos().x()+m_pButMenu->width()/2-10/2,m_pButMenu->pos().y()+m_pButMenu->height()/2-10/2,1,1));
    }
}

void FloatingMenu::initSateMachine()
{
    states=new  QStateMachine(this) ;
    states->addState(m_pRootState);
    states->setInitialState(m_pRootState);
    m_pRootState->setInitialState(m_pCenteredState);
}

void FloatingMenu::initAnimation()
{
    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    for (int i = 0; i < m_butActs.count(); ++i) {
        QPropertyAnimation *anim = new QPropertyAnimation(m_butActs[i], "geometry");
        anim->setDuration(750 + i * 25);
        anim->setEasingCurve(QEasingCurve::InOutBack);
        group->addAnimation(anim);
    }


    //添加状态交互
    QSignalTransition *trans = m_pCenteredState->addTransition(m_pButMenu, &QPushButton::clicked, m_pSurroundState);
    QSignalTransition *trans2 = m_pSurroundState->addTransition(m_pButMenu, &QPushButton::clicked, m_pCenteredState);
    //添加动画
    trans->addAnimation(group);
    trans2->addAnimation(group);

    connect(m_pButMenu,&CircleButton::moved,[=]()
    {
        for (int i = 0; i < m_butActs.count(); ++i) {
            CircleButton *item = m_butActs.at(i);

            if(m_pButMenu->m_isExpand)
            {
                QPropertyAnimation *anim = new QPropertyAnimation(m_butActs[i], "geometry");
                anim->setDuration(750 + i * 25);
                anim->setEasingCurve(QEasingCurve::InOutBack);

                anim->setEndValue(QRect(m_pButMenu->pos().x()+m_pButMenu->width()/2-60/2 + qCos(((float)(i+1) / m_butActs.count()) * 6.28) * 60,
                                             m_pButMenu->pos().y()+m_pButMenu->height()/2-60/2-qSin(((float)(i+1) / m_butActs.count()) * 6.28) * 60,60,60));
                anim->start();
//                m_pMoveState->assignProperty(item, "geometry",
//                                                 QRect(m_pButMenu->pos().x()+m_pButMenu->width()/2-60/2 + qCos(((float)(i+1) / m_butActs.count()) * 6.28) * 60,
//                                                         m_pButMenu->pos().y()+m_pButMenu->height()/2-60/2-qSin(((float)(i+1) / m_butActs.count()) * 6.28) * 60,60,60));

            }
            else
            {
                m_pMoveState->assignProperty(item, "geometry", QRect(m_pButMenu->pos().x()+m_pButMenu->width()/2-10/2,m_pButMenu->pos().y()+m_pButMenu->height()/2-10/2,0,0));

            }



            //
            m_pSurroundState->assignProperty(item, "geometry",
                                             QRect(m_pButMenu->pos().x()+m_pButMenu->width()/2-60/2 + qCos(((float)(i+1) / m_butActs.count()) * 6.28) * 60,
                                                     m_pButMenu->pos().y()+m_pButMenu->height()/2-60/2-qSin(((float)(i+1) / m_butActs.count()) * 6.28) * 60,60,60));


            m_pCenteredState->assignProperty(item, "geometry", QRect(m_pButMenu->pos().x()+m_pButMenu->width()/2-10/2,m_pButMenu->pos().y()+m_pButMenu->height()/2-10/2,0,0));
        }

    });

}
