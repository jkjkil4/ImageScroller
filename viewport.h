#pragma once

#include <QWidget>

#include <QImageReader>
#include <QTimer>
#include <QWheelEvent>
#include <QPainter>

#include "header.h"

#define CHECK_CHANGED(prevVal, val, emitFn) if(val != prevVal) { prevVal = val; emit emitFn(val);  }

class Viewport : public QWidget
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void wheelEvent(QWheelEvent *ev) override;
    void paintEvent(QPaintEvent *) override;

public:
    explicit Viewport(QWidget *parent = nullptr);

    bool load(const QString &imgPath);

    void resetConfig();
    double maxXOffset();
    double maxYOffset();
    void limitOffset();

    QRectF targetRect();

    bool isVaild() { return !mImage.isNull(); }
    void setXOffset(double val) { mXOffset = val; update(); }
    void setYOffset(double val) { mYOffset = val; update(); }
    double scale() { return mScale; }
    void setScale(double val) { CHECK_CHANGED(mScale, val, scaleChanged); update(); }
    double spd() { return mSpd; }
    void setSpd(double val) { CHECK_CHANGED(mSpd, val, spdChanged); update(); }

signals:
    void vaildChanged(bool vaild);
    void xOffsetChanged(double val);
    void yOffsetChanged(double val);
    void maxXOffsetChanged(double val);
    void maxYOffsetChanged(double val);
    void scaleChanged(double val);
    void spdChanged(double val);

private slots:
    void onUpdateOffset();

private:
    QTimer *mTimer = new QTimer(this);  //定时器，用于更新

    QPoint mPosLMousePress;  //记录鼠标左键按下位置
    QImage mImage;  //图像

    double mXOffset = 0; //x偏移
    double mYOffset = 0; //y偏移
    double mScale = 1;   //缩放
    double mSpd = 0.4;   //移动速度

    double mPrevXOffset = -1;
    double mPrevYOffset = -1;
    double mPrevMaxXOffset = -1;
    double mPrevMaxYOffset = -1;
};

