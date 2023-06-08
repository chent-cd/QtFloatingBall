#ifndef POPRINGITEM_H
#define POPRINGITEM_H

#include <QWidget>
#include <QLabel>
#include <QtMath>
#include <QAction>
#include <QPainter>
#include <QPropertyAnimation>

//#include "popringmenu.h"

#define ShowMenuDuration 100
#define ShowMenuStartValue 500
#define ShowMenuEndValue 1000

#define SlowlyFadeDuration 3000
#define SlowlyStartValue 1
#define SlowLyEndValue 0.3

class PopRingItem : public QLabel
{
    Q_OBJECT

public:
    PopRingItem(QWidget *parent=nullptr);

    ~PopRingItem();

    void SetRadius(int radius);
    int GetRadius() const;

    void BindAction(QAction * action);

signals:
    void MouseEvent(bool);

protected:
    virtual void enterEvent(QEvent * event) override;
    virtual void leaveEvent(QEvent * event) override;

    virtual void paintEvent(QPaintEvent * event) override;

protected:
    int m_iRadius = 50;
    QAction * m_actAction = nullptr;
};

#endif // POPRINGITEM_H
