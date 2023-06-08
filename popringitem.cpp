#include "popringitem.h"

PopRingItem::PopRingItem(QWidget *parent)
    : QLabel(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setScaledContents(true);
}

PopRingItem::~PopRingItem()
{

}

void PopRingItem::SetRadius(int radius)
{
    m_iRadius = radius;

    int width = m_iRadius / qSqrt(2);
    resize(width, width);
}
int PopRingItem::GetRadius() const
{
    return m_iRadius;
}

void PopRingItem::BindAction(QAction * action)
{
    if (nullptr == m_actAction)
    {
        m_actAction = new QAction(this);
    }

    setPixmap(QPixmap(":/PopRingMenu/Resources/drink.png").scaled(size()));
    //m_actAction->setIcon(action->icon());
    connect(m_actAction, &QAction::triggered, action, &QAction::trigger);
}

void PopRingItem::enterEvent(QEvent * event)
{
    __super::enterEvent(event);

    emit MouseEvent(true);
}

void PopRingItem::leaveEvent(QEvent * event)
{
    __super::leaveEvent(event);

    emit MouseEvent(false);
}

void PopRingItem::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::gray);

    int radius = m_iRadius / qSqrt(2) / 2;
    painter.drawRoundedRect(rect(), radius, radius);

    __super::paintEvent(event);
}

