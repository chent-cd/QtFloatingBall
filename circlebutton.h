#ifndef CIRCLEBUTTON_H
#define CIRCLEBUTTON_H

#include <QWidget>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
#include <QObject>
#include <QPointF>

#pragma execution_character_set("utf-8")


class CircleButton : public QPushButton
{

    Q_OBJECT
public:
    Q_PROPERTY(QPoint pos READ pos WRITE move)

    CircleButton(QWidget *parent = nullptr);

    void setText(const QString &text);

signals:
    void moving(QPoint);//�ƶ����ź�
    void moved();//�Ѿ��ƶ��ź�


protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

public:
    bool m_isExpand = false;


private:
    bool m_pressed = false;
    bool m_isMoved = false;

    QPoint m_pressPos;//�������ڰ�ť��λ��
    QPoint m_pressGlobalPos;//��������ȫ�ֵ�λ��

    QString m_text="";


};


#endif // CIRCLEBUTTON_H
