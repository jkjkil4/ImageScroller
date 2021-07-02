#pragma once

#include <QWidget>

#include <QImageReader>
#include <QTimer>
#include <QWheelEvent>
#include <QPainter>

#include "header.h"

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

    VAR_FUNC(scale, setScale, mScale, double, , )
    VAR_FUNC(spd, setSpd, mSpd, double, , )

//    bool load(const QString &imgPath);

//    QRect drawRect();
//    int minYOffset();
//    void limitYOffset();

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


//    QImage mImage;

//    double yOffset = 0;
//    double spd = -0.5;
//    double scale = 1;

//    QTimer *mTimer = new QTimer(this);
};

