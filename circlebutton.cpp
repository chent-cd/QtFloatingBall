#include "circlebutton.h"


CircleButton::CircleButton(CircleButton* parentBut, QWidget *parent)
    : QPushButton(parent),
      m_pParentBut(parentBut)
{
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground);


    if(m_pParentBut!=nullptr)
    {
        connect(m_pParentBut,&CircleButton::closed,this,&QPushButton::close);
        connect(m_pParentBut,&CircleButton::hided,this,&QPushButton::hide);
    }

//        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
//        shadow->setBlurRadius(10);
//        shadow->setColor(Qt::black);
//        shadow->setOffset(0, 0);
//        setGraphicsEffect(shadow);

}

void CircleButton::setText(const QString &text)
{
    this->m_text=text;
}

void CircleButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit pressed();
        m_pressed = true;
        m_pressPos = event->pos();
        m_pressGlobalPos = event->globalPos();
        QPainterPath path;
        path.addEllipse(rect());
        QRegion region(path.toFillPolygon().toPolygon());
        setMask(region);
        update();
        m_isMoved=false;
        event->accept();
    }
}

void CircleButton::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pressed) {
        move(event->globalPos() - m_pressPos);
//        emit moving(event->globalPos() - m_pressPos);
        emit moved();
        event->accept();
    }
}

void CircleButton::mouseReleaseEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton) {
        m_pressed = false;
        setMask(QRegion());
        update();
        if(m_pressGlobalPos == event->globalPos())
        {
            m_isExpand=!m_isExpand;
            emit clicked();
        }
        else
        {
            emit moved();
        }
        event->accept();
    }

}

void CircleButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QRect rect_size=QRect(0, 0, this->geometry().width(), this->geometry().height());


    if (m_pressed) {
        //绘制阴影
        for (int i = 0; i < 5; i++) {
            painter.setBrush(QColor(0, 0, 0, i*20));
            painter.drawEllipse(rect_size.adjusted(i+4, i+4, -i-2, -i-2));
        }

        painter.setBrush(Qt::white);
        painter.drawEllipse(rect_size.adjusted(7,7,-8,-8));

        //绘制文字
        QFont font;
        float pointSize = ((float)rect_size.width()/80)*13;
        font.setPointSizeF(pointSize);
        font.setBold(true);
        painter.setFont(font);
        painter.setPen(Qt::black);
        QRect textRect = rect_size.adjusted(13, 13, -14, -14);
        painter.drawText(textRect, Qt::AlignCenter, m_text);

    }
    else
    {
        //绘制阴影
        for (int i = 0; i < 5; i++) {
            painter.setBrush(QColor(0, 0, 0, i*20));
            painter.drawEllipse(rect_size.adjusted(i, i, -i-3, -i-3));
        }

        painter.setBrush(Qt::white);
        painter.drawEllipse(rect_size.adjusted(7,7,-7,-7));


        //绘制文字
        QFont font;
        float pointSize = ((float)rect_size.width()/80)*13;
        font.setPointSizeF(pointSize);
        font.setBold(true);
        painter.setFont(font);
        painter.setPen(Qt::black);
        QRect textRect = rect_size.adjusted(15, 15, -15, -15);
        painter.drawText(textRect, Qt::AlignCenter, m_text);
    }


//        for (int i = 5; i < 7; i++) {
//            painter.setBrush(QColor(100, 100, 200, i*20));
//            painter.drawEllipse(rect().adjusted(i, i, -i-3, -i-3));
//        }
//        painter.setBrush(Qt::white);
//        painter.drawEllipse(rect().adjusted(7,7,-7,-7));

//        for (int i = 11; i < 13; i++) {
//            painter.setBrush(QColor(100, 100, 200, i*20));
//            painter.drawEllipse(rect().adjusted(i, i, -i-3, -i-3));
//        }

//        painter.setBrush(Qt::blue);
//        painter.drawEllipse(rect().adjusted(7,7,-7,-7));

//        painter.setBrush(Qt::white);
//        painter.drawEllipse(rect().adjusted(11,11,-11,-11));

//        painter.setBrush(Qt::blue);
//        painter.drawEllipse(rect().adjusted(13,13,-13,-13));

//        painter.setBrush(Qt::white);
//        painter.drawEllipse(rect().adjusted(17,17,-17,-17));

//        for (int i = 17; i < 80; i++) {
//            painter.setBrush(QColor(0, 0, 0, (80-i)/80*255));
//            painter.drawEllipse(rect().adjusted(i, i, -i, -i));
    //        }
}

void CircleButton::contextMenuEvent(QContextMenuEvent *event)
{
    if(m_pParentBut==nullptr)
    {
        QMenu menu(this);
        QAction *closeAction = menu.addAction("关闭");
        connect(closeAction, &QAction::triggered, this, &QPushButton::close);
        connect(closeAction, &QAction::triggered, [this](){emit closed();});
        menu.exec(event->globalPos());
    }
}

void CircleButton::closeEvent(QCloseEvent *event)
{
    emit closed();
}

void CircleButton::hideEvent(QHideEvent *event)
{
    emit hided();
    if(m_isExpand)
    {
        emit clicked();
        m_isExpand=!m_isExpand;

    }
}

void CircleButton::showEvent(QShowEvent *event)
{
    emit showed();
}
