#pragma once

#include <QDebug>

#include <QPainter>

#define VAR_GET_FUNC(Getter, var, Type) \
    Type Getter() const { return var; }
#define VAR_SET_FUNC(Setter, var, Type, Const, Quote) \
    void Setter(Const Type Quote __##var##__) { var = __##var##__; }
#define VAR_FUNC(Getter, Setter, var, Type, Const, Quote) \
    VAR_GET_FUNC(Getter, var, Type) VAR_SET_FUNC(Setter, var, Type, Const, Quote)

namespace j {
    inline void DrawRecFrame(QPainter* p, int x, int y, int w, int h, int size, QColor c){
        p->fillRect(x, y, w, size, c);  //顶部
        p->fillRect(x, y + size, size, h - 2 * size, c);  //左侧
        p->fillRect(x + w - size, y + size, size, h - 2 * size, c);  //右侧
        p->fillRect(x, y + h - size, w, size, c);  //底部
    }
}
