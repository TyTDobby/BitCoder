#pragma once

#include "FrameBase.h"

typedef enum TypeBox{
    Information,
    Warning,
    FatalError,
    Question
} TypeBox;

class MessageBox : public FrameBase
{
    Q_OBJECT
public:
    MessageBox(QWidget *parent = 0);
    MessageBox(TypeBox type, QWidget *parent = 0);

    void showMessage(QString text);

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    TypeBox type;

signals:
    void fatalError(void);

};

