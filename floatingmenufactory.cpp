#include "floatingmenufactory.h"

FloatingMenuFactory::FloatingMenuFactory(QObject *parent) : QObject(parent)
{


}

void FloatingMenuFactory::setMenuText(const QString &text)
{
    m_MenuText=text;
}

void FloatingMenuFactory::setActionTexts(const QStringList &titleAction)
{
    m_ActionTexts=titleAction;
}

CircleButton *FloatingMenuFactory::createFloatingMenu()
{
    m_pButMenu=new CircleButton();
    m_pButMenu->setText(m_MenuText);
    m_pButMenu->setFixedSize(80,80);
    m_pButMenu->show();

    //子菜单个数及显示文字
    addAction(m_ActionTexts);

    initSates();

    initSateMachine();

    initAnimation();

    states->start();

    m_pButMenu->m_butActs=m_butActs;

    connect(m_pButMenu, &CircleButton::showed, this, &FloatingMenuFactory::parentButShow);

    return m_pButMenu;
}

void FloatingMenuFactory::parentButShow()
{
//    if(m_pButMenu->m_isExpand)
//    {
//        m_pButMenu->click();
//    }
    qDebug()<<"按钮展开状态"<<m_pButMenu->m_isExpand;
    for (int i = 0; i < m_butActs.count(); ++i) {
        CircleButton *item = m_butActs.at(i);
        item->show();
    }

}

void FloatingMenuFactory::initSates()
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

void FloatingMenuFactory::initSateMachine()
{
    states=new  QStateMachine(this) ;
    states->addState(m_pRootState);
    states->setInitialState(m_pRootState);
    m_pRootState->setInitialState(m_pCenteredState);
}

void FloatingMenuFactory::initAnimation()
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

void FloatingMenuFactory::addAction(const QStringList &titleAction)
{
    for (QString title : titleAction) {
        CircleButton *item = new CircleButton(m_pButMenu);
        item->setText(title);
        m_butActs << item;
        item->show();
    }
}
