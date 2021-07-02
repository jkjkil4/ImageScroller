#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    mScrollHor->setEnabled(false);
    mScrollVer->setEnabled(false);

    mSpinScale->setRange(0.1, 10);
    mSpinScale->setEnabled(false);
    mSpinScale->setSingleStep(0.1);

    mSpinSpd->setRange(-20, 20);
    mSpinSpd->setSingleStep(0.05);
    mSpinSpd->setEnabled(false);

    connect(mViewport, &Viewport::vaildChanged, [this](bool vaild) {
        mScrollHor->setEnabled(vaild);
        mScrollVer->setEnabled(vaild);
        mSpinScale->setEnabled(vaild);
        mSpinSpd->setEnabled(vaild);
    });
    connect(mViewport, &Viewport::xOffsetChanged, [this](double val) {
        QSignalBlocker blocker(mScrollHor);
        mScrollHor->setValue((int)val);
    });
    connect(mViewport, &Viewport::yOffsetChanged, [this](double val) {
        QSignalBlocker blocker(mScrollVer);
        mScrollVer->setValue(qCeil(val));
    });
    connect(mViewport, &Viewport::maxXOffsetChanged, [this](double val) {
        int iVal = qCeil(val);
        mScrollHor->setRange(-iVal, iVal);
    });
    connect(mViewport, &Viewport::maxYOffsetChanged, [this](double val) {
        mScrollVer->setMaximum(qCeil(val));
    });
    connect(mViewport, &Viewport::scaleChanged, [this](double scale) {
        mSpinScale->setValue(scale);
    });
    connect(mViewport, &Viewport::spdChanged, [this](double spd) {
        mSpinSpd->setValue(spd);
    });

    connect(mScrollHor, &QScrollBar::valueChanged, [this](int val) {
        mViewport->setXOffset(val);
    });
    connect(mScrollVer, &QScrollBar::valueChanged, [this](int val) {
        mViewport->setYOffset(val);
    });
    connect(mSpinScale, SIGNAL(valueChanged(double)), this, SLOT(onSpinScaleChanged(double)));
    connect(mSpinSpd, SIGNAL(valueChanged(double)), this, SLOT(onSpinSpdChanged(double)));

    connect(mBtnLoadImage, &QPushButton::clicked, this, &Widget::onSelectImage);

    QHBoxLayout *layTop = new QHBoxLayout;
    layTop->addWidget(mBtnLoadImage);
    layTop->addSpacing(16);
    layTop->addWidget(new QLabel("缩放"));
    layTop->addWidget(mSpinScale);
    layTop->addSpacing(16);
    layTop->addWidget(new QLabel("速度"));
    layTop->addWidget(mSpinSpd);
    layTop->addStretch();

    QGridLayout *layViewport = new QGridLayout;
    layViewport->addWidget(mViewport, 0, 0);
    layViewport->addWidget(mScrollHor, 1, 0);
    layViewport->addWidget(mScrollVer, 0, 1);
    layViewport->setSpacing(0);

    QVBoxLayout *layMain = new QVBoxLayout;
    layMain->addLayout(layTop);
    layMain->addLayout(layViewport, 1);
    setLayout(layMain);
    resize(800, 608);
}

Widget::~Widget()
{

}

void Widget::onSelectImage() {
    QString imgPath = QFileDialog::getOpenFileName(this);
    if(!imgPath.isEmpty() && !mViewport->load(imgPath)) {
        QMessageBox::warning(this, "错误", "无法载入图片");
    }
}
void Widget::onSpinScaleChanged(double val) { mViewport->setScale(val); }
void Widget::onSpinSpdChanged(double val) { mViewport->setSpd(val); }
