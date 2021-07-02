#include "viewport.h"

Viewport::Viewport(QWidget *parent) : QWidget(parent)
{
    connect(mTimer, &QTimer::timeout, this, &Viewport::onUpdateOffset);
}

void Viewport::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        mPosLMousePress = ev->pos();
    }
}
void Viewport::mouseMoveEvent(QMouseEvent *ev) {
    if(ev->buttons() & Qt::LeftButton) {
        int xMouseOffset = ev->x() - mPosLMousePress.x();
        int yMouseOffset = ev->y() - mPosLMousePress.y();
        mXOffset += xMouseOffset / mScale;
        mYOffset += yMouseOffset / mScale;
        limitOffset();
        mPosLMousePress = ev->pos();
    }
}
void Viewport::wheelEvent(QWheelEvent *ev) {
    mScale = qBound<double>(0.1, mScale + ev->delta() / 1200.0, 10);
    update();
}
void Viewport::paintEvent(QPaintEvent *) {
    QPainter p(this);
    if(!mImage.isNull()) {
        p.setRenderHint(QPainter::Antialiasing);
        p.drawImage(targetRect(), mImage, mImage.rect());
        p.setRenderHint(QPainter::Antialiasing, false);
    }
    j::DrawRecFrame(&p, 0, 0, width(), height(), 1, Qt::black);
}

bool Viewport::load(const QString &imgPath) {
    QImageReader ir(imgPath);
    bool can = ir.canRead();
    if(can) {
        QImageReader ir(imgPath);
        if(!ir.read(&mImage))
            return false;
        resetConfig();
        mTimer->start(60);
    }
    return can;
}

void Viewport::resetConfig() {
    mXOffset = 0;
    mYOffset = 0;
    mScale = 1;
    mSpd = 0.4;
}
double Viewport::maxXOffset() {
    return qMax<double>(0, (mImage.width() - width() / mScale) / 2);
}
double Viewport::maxYOffset() {
    return mImage.height() - height() / mScale;
}
void Viewport::limitOffset() {
    double maxXOff = maxXOffset();
    mXOffset = qBound<double>(-maxXOff, mXOffset, maxXOff);
    mYOffset = qBound<double>(-maxYOffset(), mYOffset, 0);
}

QRectF Viewport::targetRect() {
    double w = mImage.width() * mScale;
    double h = mImage.height() * mScale;
    double x = (width() - w) / 2 + mXOffset * mScale;
    double y = mYOffset * mScale;
    return QRectF(x, y, w, h);
}

void Viewport::onUpdateOffset() {
    mYOffset -= mSpd;
    limitOffset();
    update();
}






//Viewport::Viewport(QWidget *parent) : QWidget(parent)
//{
//    connect(mTimer, &QTimer::timeout, this, &Viewport::onUpdateOffset);
//    setFocusPolicy(Qt::FocusPolicy::StrongFocus);
//}

//void Viewport::keyPressEvent(QKeyEvent *ev) {
//    bool hasCtrl = ev->modifiers() & Qt::ControlModifier;
//    switch((int)ev->key()) {
//    case Qt::Key_Up:
//        if(hasCtrl) yOffset += 50; else spd -= 0.05;
//        limitYOffset();
//        break;
//    case Qt::Key_Down:
//        if(hasCtrl) yOffset -= 50; else spd += 0.05;
//        limitYOffset();
//        break;
//    }
//}
//void Viewport::wheelEvent(QWheelEvent *ev) {
//    scale += ev->delta() / 1200.0;
//}
//void Viewport::paintEvent(QPaintEvent *) {
//    if(!mImage.isNull()) {
//        QPainter p(this);
//        p.setRenderHint(QPainter::Antialiasing);

//        p.drawImage(drawRect(), mImage, mImage.rect());
//    }
//}

//bool Viewport::load(const QString &imgPath) {
//    QImageReader ir(imgPath);
//    bool can = ir.canRead();
//    if(can) {
//        QImageReader ir(imgPath);
//        if(!ir.read(&mImage))
//            return false;
//        yOffset = 0;
//        scale = (width() - 8.0) / mImage.width();
//        spd = -0.5;
//        mTimer->start(60);
//    }
//    return can;
//}

//QRect Viewport::drawRect() {
//    int w = (int)(mImage.width() * scale);
//    int h = (int)(mImage.height() * scale);
//    return QRect((width() - w) / 2, (int)yOffset, w, h);
//}
//int Viewport::minYOffset() {
//    return -(int)(mImage.height() * scale) + height() / 2;
//}
//void Viewport::limitYOffset() {
//    yOffset = qBound<double>(minYOffset(), yOffset, 0);
//}

//void Viewport::onUpdateOffset() {
//    yOffset += spd;
//    limitYOffset();
//    update();
//}
