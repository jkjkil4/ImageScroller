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
        mXOffset -= xMouseOffset / mScale;
        mYOffset -= yMouseOffset / mScale;
        limitOffset();
        mPosLMousePress = ev->pos();
        update();
    }
}
void Viewport::wheelEvent(QWheelEvent *ev) {
    double scale = qBound<double>(0.1, mScale + ev->delta() / 1200.0, 10);
    if(scale != mScale) {
        mScale = scale;
        emit scaleChanged(scale);
    }
    update();
}
void Viewport::paintEvent(QPaintEvent *) {
    QPainter p(this);
    if(isVaild()) {
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
        emit vaildChanged(true);
        CHECK_CHANGED(mPrevXOffset, mXOffset, xOffsetChanged);
        CHECK_CHANGED(mPrevYOffset, mYOffset, yOffsetChanged);
        CHECK_CHANGED(mPrevMaxXOffset, maxXOffset(), maxXOffsetChanged);
        CHECK_CHANGED(mPrevMaxYOffset, maxYOffset(), maxYOffsetChanged);
        emit scaleChanged(mScale);
        emit spdChanged(mSpd);
        mTimer->start(100);
    }
    return can;
}

void Viewport::resetConfig() {
    mXOffset = 0;
    mYOffset = 0;
    mScale = (width() - 16.0) / mImage.width();
    mSpd = 0.4;
}
double Viewport::maxXOffset() {
    return qMax<double>(0, (mImage.width() - width() / mScale) / 2 + 8);
}
double Viewport::maxYOffset() {
    return mImage.height() - height() / mScale + 8;
}
void Viewport::limitOffset() {
    double maxXOff = maxXOffset();
    mXOffset = qBound<double>(-maxXOff, mXOffset, maxXOff);
    mYOffset = qBound<double>(0, mYOffset, maxYOffset());
}

QRectF Viewport::targetRect() {
    double xOffset = -mXOffset;
    double yOffset = -mYOffset;
    double w = mImage.width() * mScale;
    double h = mImage.height() * mScale;
    double x = (width() - w) / 2 + xOffset * mScale;
    double y = yOffset * mScale;
    return QRectF(x, y, w, h);
}

void Viewport::onUpdateOffset() {
    mYOffset += mSpd;
    limitOffset();
    CHECK_CHANGED(mPrevXOffset, mXOffset, xOffsetChanged);
    CHECK_CHANGED(mPrevYOffset, mYOffset, yOffsetChanged);
    CHECK_CHANGED(mPrevMaxXOffset, maxXOffset(), maxXOffsetChanged);
    CHECK_CHANGED(mPrevMaxYOffset, maxYOffset(), maxYOffsetChanged);
    update();
}

