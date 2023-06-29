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
    //����ť��ʾ��
    void parentButShow();

private:
    //��ʼ��״̬
    void initSates();

    //��ʼ��״̬��
    void initSateMachine();

    //��ʼ������
    void initAnimation();

    //��ʼ��

    //�˵�������ť
    void addAction(const QStringList &titleAction);


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

    QString m_MenuText;

    QStringList m_ActionTexts;

};

#endif // FLOATINGMENU_H
