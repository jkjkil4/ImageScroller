#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    connect(mBtnLoadImage, &QPushButton::clicked, this, &Widget::onSelectImage);

    QVBoxLayout *layMain = new QVBoxLayout;
    layMain->addWidget(mBtnLoadImage, Qt::AlignLeft);
    layMain->addWidget(mViewport, 1);
    setLayout(layMain);
    resize(800, 608);
}

Widget::~Widget()
{

}

void Widget::onSelectImage() {
    QString imgPath = QFileDialog::getOpenFileName(this);
    if(!mViewport->load(imgPath)) {
        QMessageBox::warning(this, "错误", "无法载入图片");
    }
}
