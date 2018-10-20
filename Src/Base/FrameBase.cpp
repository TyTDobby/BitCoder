#include "FrameBase.h"

#include <QStyle>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QTextOption>
#include <QLabel>

FrameBase::FrameBase(QWidget *parent)
    : QWidget(parent)
{
    isShowMaximized = false;
    isShowMinimized = false;
    isMovingWindow = false;

    isBtnClsUpdate = false;
    isBtnMaxUpdate = false;
    isBtnMinUpdate = false;

    eventShowCount = 0;

    widthBorder = 2;
    heightTitle = 20;

    clButtons = QColor(0, 0, 0);

    widget = new QWidget(this);

    widget->setGeometry(widthBorder,
                        widthBorder + heightTitle,
                        size().width() - widthBorder * 2,
                        size().height() - heightTitle - widthBorder * 2);
    widget->adjustSize();
    this->setWindowFlags(Qt::CustomizeWindowHint);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                          Qt::AlignCenter,
                                          this->size(), QApplication::desktop()->availableGeometry()));
    this->setMouseTracking(true);
//    this->setLayout(boxLayout);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    paramMain.pen = QPen(QBrush(QColor(200, 200, 200)), 1);
    paramMain.h = this->height() - heightTitle - widthBorder * 2;
    paramMain.w = this->width() - widthBorder * 2;

    paramBtnClose.pen = QPen(QBrush(QColor(150, 0, 0)), 1);
    paramBtnClose.h = heightTitle;
    paramBtnClose.w = heightTitle;


    paramBtnMax.pen = QPen(QBrush(QColor(0, 150, 0)), 1);
    paramBtnMax.h = heightTitle;
    paramBtnMax.w = heightTitle;

    paramBtnMin.pen = QPen(QBrush(QColor(0, 0, 150)), 1);
    paramBtnMin.h = heightTitle;
    paramBtnMin.w = heightTitle;
    btns = AllButton;
}

void FrameBase::setTitleText(QString title)
{
    setWindowTitle(title);
    titleText = title;
    update();
}

void FrameBase::setTitleIcon(QString path)
{
    titleIcon = QImage(path).scaled(heightTitle - widthBorder * 2, heightTitle - widthBorder * 3, Qt::KeepAspectRatio);
}

void FrameBase::setTitleFont(QFont font)
{
    titleFont = font;
}

void FrameBase::selectLayout(QLayout *l)
{
    widget->setContentsMargins(0, 0, 0, 0);
    l->setContentsMargins(0, 0, 0, 0);
    widget->setLayout(l);
}

void FrameBase::setWindowButtons(WindowButton btns)
{
    this->btns = btns;
}

void FrameBase::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPen pen = QPen(QBrush(QColor(64, 66, 68)), 4);
    QPainter paint(this);

    paint.setRenderHint(QPainter::Antialiasing);
    paint.setRenderHint(QPainter::HighQualityAntialiasing);

    /* Drawing border and title */
    paint.setPen(pen);
    paint.fillRect(0, 0,
                   this->width(),
                   heightTitle + widthBorder, QBrush(QColor(64, 66, 68)));
    paint.drawRect(0, 0,
                   this->width(),
                   this->height());

    pen.setWidth(2);
    paint.setPen(pen);
    /* Drawing close button */
    if (btns & Closed) {
        pen.setBrush(QBrush(isBtnClsUpdate ? QColor(152, 169, 238) : QColor(189, 191, 193)));
        paint.setPen(pen);
        paintBtnClose(paint);
    }
    /* Drawing maximized button */
    if (btns & Maximized) {
        pen.setBrush(QBrush(isBtnMaxUpdate ? QColor(152, 169, 238) : QColor(189, 191, 193)));
        paint.setPen(pen);
        paintBtnMaximized(paint);
    }
    /* Drawing minimized button */
    if (btns & Minimized) {
        pen.setBrush(QBrush(isBtnMinUpdate ? QColor(152, 169, 238) : QColor(189, 191, 193)));
        paint.setPen(pen);
        paintBtnMinimized(paint);
    }
    /* Drawing title text */
    pen.setBrush(QBrush(QColor(189, 191, 193)));
    paint.setPen(pen);
    paint.setFont(titleFont);
    paint.drawText((this->width() - paramBtnClose.w - paramBtnMin.w - paramBtnMax.w) / 2,
                   heightTitle - widthBorder * 2,
                   titleText);

    /* Drawing title icon */
    paint.drawImage(widthBorder * 2, widthBorder * 2, titleIcon);

}

void FrameBase::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    QPoint pos = event->pos();
    /* Moving window */
    if (isMovingWindow) {
        QPoint point = event->globalPos();
        QPoint pointWindow = QPoint(this->geometry().x(), this->geometry().y());
        int xDelta = lastPoint.x() - point.x();
        int yDelta = lastPoint.y() - point.y();
        move(pointWindow.x() - xDelta,
             pointWindow.y() - yDelta);
        lastPoint = point;
    }

    /* Button close */
    isBtnClsUpdate = isBtnClose(pos);
    isBtnMaxUpdate = isBtnMaximized(pos);
    isBtnMinUpdate = isBtnMinimized(pos);
    update();
}

void FrameBase::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    QPoint pos = event->pos();
    if (isTitle(pos)) {
        lastPoint = event->globalPos();
        isMovingWindow = true;
    }
}

void FrameBase::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    QPoint pos = event->pos();
    isMovingWindow = false;
    /* Button close */
    if (isBtnClose(pos)) {
        close();
    }
    /* Button maximized */
    if (isBtnMaximized(pos)) {
        if (!this->isMaximized()) {
            showMaximized();
            isShowMaximized = true;
        }
        else {
            showNormal();
            isShowMaximized = false;
        }
    }
    /* Button minimized */
    if (isBtnMinimized(pos)) {
        showMinimized();
        isShowMinimized = true;
    }
}

void FrameBase::mouseDoubleClickEvent(QMouseEvent *event)
{
    QWidget::mouseDoubleClickEvent(event);
    QPoint pos = event->pos();
    if (isTitle(pos)) {
        if (!this->isMaximized()) {
            showMaximized();
            isShowMaximized = true;
        }
        else {
            showNormal();
            isShowMaximized = false;
        }
    }
}

void FrameBase::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    if(isShowMinimized && isShowMaximized) {
        if (eventShowCount >= 1) {
            isShowMinimized = false;
            eventShowCount = 0;
            showMaximized();
            return;
        }
        eventShowCount++;
    }
}

void FrameBase::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    widget->setGeometry(widthBorder,
                        widthBorder + heightTitle,
                        size().width() - widthBorder * 2,
                        size().height() - heightTitle - widthBorder * 2);
}

void FrameBase::paintBtnClose(QPainter &paint)
{
    paint.drawLine(this->width() - paramBtnClose.w,
                   (heightTitle / 3) + widthBorder,
                   this->width() - paramBtnClose.w + (heightTitle / 2.5),
                   (heightTitle / 3) + widthBorder + (heightTitle / 2.5));
    paint.drawLine(this->width() - paramBtnClose.w,
                   (heightTitle / 3) + widthBorder + (heightTitle / 2.5),
                   this->width() - paramBtnClose.w + (heightTitle / 2.5),
                   (heightTitle / 3) + widthBorder);
}

void FrameBase::paintBtnMaximized(QPainter &paint)
{
    paint.drawRect(this->width() - paramBtnClose.w - paramBtnMax.w + 2,
                   (heightTitle / 3) + widthBorder,
                   (heightTitle / 2.5),
                   (heightTitle / 2.5));
}

void FrameBase::paintBtnMinimized(QPainter &paint)
{
    paint.drawLine(this->width() - paramBtnClose.w - paramBtnMax.w - paramBtnMin.w + 4,
                   (heightTitle / 2) + widthBorder,
                   this->width() - paramBtnClose.w - paramBtnMax.w - widthBorder * 2 - 4,
                   (heightTitle / 2) + widthBorder);
}

bool FrameBase::isBtnClose(QPoint &pos)
{
    return  pos.rx() > this->width() - paramBtnClose.w - widthBorder &&
           (pos.rx() < this->width() - widthBorder) &&
            pos.ry() > widthBorder &&
           (pos.ry() < widthBorder + paramBtnClose.h);
}

bool FrameBase::isBtnMaximized(QPoint &pos)
{
    return  pos.rx() > this->width() - paramBtnClose.w - paramBtnMax.w - widthBorder &&
           (pos.rx() < this->width() - paramBtnClose.w - widthBorder) &&
            pos.ry() > widthBorder &&
           (pos.ry() < widthBorder + paramBtnMax.h);
}

bool FrameBase::isBtnMinimized(QPoint &pos)
{
    return  pos.rx() > this->width() - paramBtnClose.w - paramBtnMin.w - paramBtnMax.w - widthBorder &&
           (pos.rx() < this->width() - paramBtnClose.w - paramBtnMax.w - widthBorder) &&
            pos.ry() > widthBorder &&
           (pos.ry() < widthBorder + paramBtnMin.h);
}

bool FrameBase::isTitle(QPoint &pos)
{
    return  pos.rx() > widthBorder &&
           (pos.rx() < this->width() - paramBtnClose.w - paramBtnMin.w - paramBtnMax.w - widthBorder) &&
            pos.ry() > widthBorder &&
           (pos.ry() < widthBorder + heightTitle);
}
