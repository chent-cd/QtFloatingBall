#ifndef FLOATINGMENU_H
#define FLOATINGMENU_H

#include <QObject>
#include <QState>
#include <QtMath>
#include <QStateMachine>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include "circlebutton.h"

class FloatingMenuFactory : public QObject
{
    Q_OBJECT
public:
    explicit FloatingMenuFactory(QObject *parent = nullptr);

    void setMenuText(const QString &text);

    void setActionTexts(const QStringList &titleAction);

    CircleButton* createFloatingMenu();
signals:

public slots:
    //父按钮显示槽
    void parentButShow();

private:
    //初始化状态
    void initSates();

    //初始化状态机
    void initSateMachine();

    //初始化动画
    void initAnimation();

    //初始化

    //菜单动作按钮
    void addAction(const QStringList &titleAction);


private:
    CircleButton *m_pButMenu;//主菜单按钮
    QList<CircleButton *> m_butActs;

    QStateMachine *states=nullptr;

    // States
    //根状态
    QState *m_pRootState=nullptr;
    //环绕状态
    QState *m_pSurroundState=nullptr;
    //中心状态
    QState *m_pCenteredState=nullptr;
    //移动状态
    QState *m_pMoveState=nullptr;

    QString m_MenuText;

    QStringList m_ActionTexts;

};

#endif // FLOATINGMENU_H
