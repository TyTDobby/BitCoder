#include "MessageBox.h"

#include <QPushButton>
#include <QLabel>
#include <QPixmap>

#include "Icons.h"

MessageBox::MessageBox(QWidget *parent) : FrameBase(parent)
{


}

MessageBox::MessageBox(TypeBox type, QWidget *parent) : FrameBase(parent)
{
    this->type = type;
}

void MessageBox::showMessage(QString text)
{
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | windowFlags());
    setWindowButtons(Closed);
    QHBoxLayout *vBoxMain = new QHBoxLayout();
    QVBoxLayout *vBox = new QVBoxLayout();
    QHBoxLayout *hBoxMessage = new QHBoxLayout();
    QHBoxLayout *hBoxButtons = new QHBoxLayout();

    QPushButton *btnOk = new QPushButton("Ok", this);
//    QPushButton *btnCancel = new QPushButton("Cancel", this);

    QLabel *label = new QLabel(this);
    QLabel *icon = new QLabel(this);

    hBoxButtons->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed));
    hBoxButtons->addWidget(btnOk);

    hBoxMessage->addWidget(label);

    vBoxMain->addWidget(icon);
    vBoxMain->addLayout(vBox);

    vBox->addLayout(hBoxMessage);
    vBox->addLayout(hBoxButtons);

    hBoxButtons->setContentsMargins(10, 2, 5, 5);

    label->setAlignment(Qt::AlignBottom);
    label->setText(text);
    label->setWordWrap(true);
    QPixmap pixmap;
    if (type == Warning) {
        pixmap.loadFromData(&iconWarn[0], sizeIconWarn);
        setTitleText("Warning");
    }
    else if (type == Information) {
        pixmap.loadFromData(&iconInfo[0], sizeIconInfo);
        setTitleText("Info");
    }
    else if (type == FatalError) {
        pixmap.loadFromData(&iconFatalError[0], sizeIconFatalError);
        setTitleText("Fatal error");
    }
    else if (type == Question) {
        pixmap.loadFromData(&iconQuestion[0], sizeIconQuestion);
        setTitleText("Help");
    }
    icon->setPixmap(pixmap);
    icon->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    icon->setContentsMargins(15, 2, 2, 5);

    connect(btnOk, SIGNAL(clicked(bool)),
            SLOT(close()));
    selectLayout(vBoxMain);
    setMinimumHeight(150);
    setFixedWidth(350);
    show();
}

void MessageBox::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
    if (type == FatalError) {
        emit fatalError();
    }
}
