#pragma once

#include <QDebug>

#include <QPainter>

namespace j {
    inline void DrawRecFrame(QPainter* p, int x, int y, int w, int h, int size, QColor c){
        p->fillRect(x, y, w, size, c);  //顶部
        p->fillRect(x, y + size, size, h - 2 * size, c);  //左侧
        p->fillRect(x + w - size, y + size, size, h - 2 * size, c);  //右侧
        p->fillRect(x, y + h - size, w, size, c);  //底部
    }
}
