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

class FloatingMenu : public QObject
{
    Q_OBJECT
public:
    explicit FloatingMenu(QObject *parent = nullptr);

    //�˵�������ť
    void addAction(const QStringList &titleAction);
signals:

public slots:

private:
    //��ʼ��״̬
    void initSates();

    //��ʼ��״̬��
    void initSateMachine();

    //��ʼ������
    void initAnimation();

    //��ʼ��

private:
    CircleButton *m_pButMenu;//���˵���ť
    QList<CircleButton *> m_butActs;

    QStateMachine *states=nullptr;

    // States
    //��״̬
    QState *m_pRootState=nullptr;
    //����״̬
    QState *m_pSurroundState=nullptr;
    //����״̬
    QState *m_pCenteredState=nullptr;
    //�ƶ�״̬
    QState *m_pMoveState=nullptr;

};

#endif // FLOATINGMENU_H
