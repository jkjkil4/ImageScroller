#pragma once

#include <QWidget>
//#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

#include "viewport.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onSelectImage();

private:
    QPushButton *mBtnLoadImage = new QPushButton("载入图片");
    Viewport *mViewport = new Viewport;
};

