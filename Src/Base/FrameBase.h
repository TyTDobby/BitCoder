#pragma once

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QShowEvent>
#include <QMenuBar>
#include <QMenu>
#include <QLayout>
#include <QResizeEvent>
#include <QAbstractNativeEventFilter>

typedef struct {
    QPen pen;
    int h;
    int w;
} ParamPainter;

typedef enum WindowButton{
    Minimized   = 0x01,
    Maximized   = 0x02,
    Closed      = 0x04,
    AllButton   = Closed | Minimized | Maximized
} WindowButton;

class FrameBase : public QWidget
{
    Q_OBJECT
public:
    FrameBase(QWidget *parent = NULL);

    void setTitleText(QString title);
    void setTitleIcon(QString path);
    void setTitleFont(QFont font);

    void hideBorder();

    void selectLayout(QLayout *l);
    void setWindowButtons(WindowButton btns);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

private:
    int heightTitle, widthBorder;
    ParamPainter paramMain, paramBtnClose, paramBtnMin, paramBtnMax;
    bool isShowMaximized, isShowMinimized, isMovingWindow;
    bool isBtnMaxUpdate, isBtnClsUpdate, isBtnMinUpdate;
    bool isUpdated;
    int eventShowCount;
    QPoint lastPoint;
    QColor clButtons;
    QString titleText;
    QImage titleIcon;
    QFont titleFont;
    WindowButton btns;
    QWidget *widget;
    QColor colorBorder;
    bool isShowenBorder;

    void paintBtnClose(QPainter &paint);
    void paintBtnMaximized(QPainter &paint);
    void paintBtnMinimized(QPainter &paint);

    bool isBtnClose(QPoint &pos);
    bool isBtnMaximized(QPoint &pos);
    bool isBtnMinimized(QPoint &pos);
    bool isTitle(QPoint &pos);


};
