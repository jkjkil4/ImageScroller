#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>
#include <QDoubleSpinBox>
#include <QLabel>

#include <qmath.h>

#include "viewport.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onSelectImage();
    void onSpinScaleChanged(double val);
    void onSpinSpdChanged(double val);

private:
    QPushButton *mBtnLoadImage = new QPushButton("载入图片");
    Viewport *mViewport = new Viewport;
    QScrollBar *mScrollHor = new QScrollBar(Qt::Horizontal);
    QScrollBar *mScrollVer = new QScrollBar(Qt::Vertical);
    QDoubleSpinBox *mSpinScale = new QDoubleSpinBox;
    QDoubleSpinBox *mSpinSpd = new QDoubleSpinBox;
};

